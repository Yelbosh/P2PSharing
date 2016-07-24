#include "StdAfx.h"
#include <string>
#include <vector>
using namespace std;
#include <windows.h>
#include "Sock.h"

#pragma comment(lib,"ws2_32.lib")

using namespace SockUtil;

/**
* Defines a classes that wraps up the winsock API.These classes
* do not supports only TCP/IP.
* @version 1.0.0
*/ 

/**
* WSAStartup
* @since 1.0.0
*/
void CWinSock::Initialize() {
	WORD ver = MAKEWORD(1, 1);
	WSADATA wsadata;
	WSAStartup(ver, &wsadata);
}

/**
* WSACleanup
* @since 1.0.0
*/
void CWinSock::Finalize() {
	WSACleanup();
}

/**
* Default constructor
* @since 1.0.0
*/
CServerSocket::CServerSocket() {
	m_nPort = 80;
	m_nQueue = 100;
	Init();
}

/**
* Overloaded constructor.
* @param port Port on which the server listens
* @since 1.0.0
*/
CServerSocket::CServerSocket(int port) {
	m_nPort = port;
	m_nQueue = 100;
	Init();	
}

/**
* Overloaded constructor.
* @param port Port on which the server listens
* @param queue Number of clients that will wait for accept()
* @since 1.0.0
*/
CServerSocket::CServerSocket(int port,int queue) {
	m_nPort = port;
	m_nQueue = queue;
	Init();	
}

/**
* Binds the server to the given address.
* @param *sock_addr Socket address to bind to.
* @since 1.0.0
*/
void CServerSocket::Bind(CSocketAddress *sock_addr) {
	m_bBound = false;	
	Close();
	m_sockAddr = sock_addr;
	Accept();	
}

/**
* Listens and accepts a client.Returns the accepted connection.
* @return CSocket*.
* @throw CSocketException
* @since 1.0.0
*/
CSocket* CServerSocket::Accept() throw (CSocketException) {
	if(m_sockAddr != NULL) 
		m_sockAddrIn = m_sockAddr->GetSockAddrIn();
	if(!m_bBound) {	
		m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		int nret = bind(m_socket, (LPSOCKADDR)&m_sockAddrIn, sizeof(struct sockaddr));
		if (nret == SOCKET_ERROR) {
			nret = WSAGetLastError();
			throw CSocketException(nret, "Failed to bind: Accept()");
		}
		m_bBound = true;
	}	
	int nret = listen(m_socket, m_nQueue);
	if (nret == SOCKET_ERROR) {
		nret = WSAGetLastError();
		throw CSocketException(nret, "Failed to listen: Accept()");
	}
	SOCKET theClient;
	SOCKADDR_IN clientAddr;
	int ssz = sizeof(struct sockaddr);
	theClient = accept(m_socket,(LPSOCKADDR)&clientAddr,&ssz);
	//theClient = accept(m_socket,NULL,NULL);
	if (theClient == INVALID_SOCKET) {
		int nret = WSAGetLastError();
		throw CSocketException(nret, "Invalid client socket: Accept()");		
	}
	CSocket *sockClient = new CSocket();
	sockClient->SetSocket(theClient);
	sockClient->SetClientAddr(clientAddr);		
	return sockClient;
}


/**
* Closes the socket.
* @throw CSocketException
* @since 1.0.0
*/
void CServerSocket::Close() {
	closesocket(m_socket);
	m_sockAddr = NULL;	
	m_bBound = false;
	m_bListening = false;
}


/**
* default initialization
* @throw CSocketException
* @since 1.0.0
*/
void CServerSocket::Init() {		
	m_sockAddrIn.sin_family = AF_INET;
	m_sockAddrIn.sin_addr.s_addr = INADDR_ANY;//any ip will connect this server	
	m_sockAddrIn.sin_port = htons(m_nPort);// transfer the hosts bytes to the network bytes
	
	m_sockAddr = NULL; // bind the same machine
	m_bBound = false;
	m_bListening = true;
}

/**
* Destructor. Releases all resource.
* @since 1.0.0
*/
CServerSocket::~CServerSocket() {
	Close();
}

/**
* Sets the port
* @param port Value of port
* @since 1.0.0
*/
void CServerSocket::SetPort(int port) {
	m_nPort = port;
	Init();
}

/**
* Sets the queue size
* @param port Value of port
* @since 1.0.0
*/
void CServerSocket::SetQueue(int q) {
	m_nQueue = q;	
}

/**
* Returns the port
* @return int
* @since 1.0.0
*/
int CServerSocket::GetPort() {
	return m_nPort;
}

/**
* Returns the queue size
* @return int
* @since 1.0.0
*/
int CServerSocket::GetQueue() {
	return m_nQueue;
}

/**
* Returns the socket address
* @return CSocketAddress*
* @since 1.0.0
*/
CSocketAddress* CServerSocket::GetSocketAddress() {
	return m_sockAddr;
}

/**
* Returns the listening flag
* @return bool
* @since 1.0.0
*/
bool CServerSocket::IsListening() {
	return m_bListening;
}

// class CSocket

/**
* Default constructor
* @since 1.0.0
*/
CSocket::CSocket() {
	m_clientAddr = NULL;
}

/**
* Sets the SOCKET
* @param sock SOCKET
* @since 1.0.0
*/
void CSocket::SetSocket(SOCKET sock) {
	m_socket = sock;
}

/**
* Sets address details
* @param addr SOCKADDR_IN
* @since 1.0.0
*/
void CSocket::SetClientAddr(SOCKADDR_IN addr) {
	if(m_clientAddr != NULL) delete m_clientAddr;
	m_clientAddr = new CSocketAddress(addr);
}

/**
* Connects to a server
* @param host_name Server name
* @param port Port to connect
* @since 1.0.0
*/
int CSocket::Connect(const char* ip,int port) 
throw (CSocketException) {	
	m_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		int nret = WSAGetLastError();
		throw CSocketException(nret,"Failed to create client socket");
	}
	
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.S_un.S_addr = inet_addr(ip);
	serverInfo.sin_port = htons(port);
	int nret = connect(m_socket,(sockaddr*)&serverInfo,sizeof(struct sockaddr));
	if (nret == SOCKET_ERROR) {
		nret = WSAGetLastError();
		throw CSocketException(nret,"Connect failed.");		
	}
	return nret;// return 0 if succeed, ~0 if unsucceed
}

/**
* Writes data to the socket. Returns number of bytes written
* @param data data to write
* @return int
* @throw CSocketException
* @since 1.0.0
*/
int CSocket::Send(const char* data) throw (CSocketException) {
	int nret = send(m_socket,data,1024,0);
	if(nret == SOCKET_ERROR) {
		nret = WSAGetLastError();
		throw CSocketException(nret, "Network failure: Send()");		
	}
	return nret;
}

int CSocket::WriteLine(string data) throw (CSocketException) 
{
	string::size_type position = data.find("\n");
	if(position != data.npos)//如果没有找到
	{
		data += "\n";
	}
	int nret = send(m_socket,data.c_str(),strlen(data.c_str()),0);
	//Sleep(500);
	if(nret == SOCKET_ERROR) {
		nret = WSAGetLastError();
		throw CSocketException(nret, "Network failure: Send()");		
	}
	return nret;
}

/**
* Writes data to the socket. Returns number of bytes written
* @param data data to write
* @return int
* @throw CSocketException
* @since 1.0.0
*/
int CSocket::Send(const char* data,int len) throw (CSocketException) {
	int nret = send(m_socket,data,len,0);
	if(nret == SOCKET_ERROR) {
		nret = WSAGetLastError();
		throw CSocketException(nret, "Network failure: Send()");		
	}
	return nret;
}

/**
* Reads data from the socket.Returns number of bytes actually read.
* @param buffer Data buffer
* @param len Number of bytes to read
* @throw CSocketException
* @since 1.0.0
*/
int CSocket::Read(char* buffer,int len) throw (CSocketException) {
	int nret = 0;	
	nret = recv(m_socket,buffer,len,0);
	if(nret == SOCKET_ERROR) {
		nret = WSAGetLastError();		
		throw CSocketException(nret, "Network failure: Read()");		
	}
	//buffer[nret] = '\0';
	return nret;	
}

/**
* Reads data from the socket.Once a line
* @param buffer Data buffer
* @param len Number of bytes to read
* @throw CSocketException
* @since 1.0.0
*/
int CSocket::ReadLine(char* buffer) throw (CSocketException) {
	int nret = 0;	
	nret = recv(m_socket,buffer,1024,0);
	if(nret == SOCKET_ERROR) {
		int errorCode = WSAGetLastError();
		throw CSocketException(errorCode, "Network failure: Read()");		
	}
	if(nret <= 0) {
		return nret;
	}
	int i;
	for(i=0;i<nret;i++)
	{
		if(buffer[i] == '\n')
		{
			break;
		}
	}
	for(;i<1024;i++)
	{
		buffer[i] == '\0';
	}
	return nret;	
}

/**
* Reads data from the socket.Once a line,just return the result
* @param buffer Data buffer
* @param len Number of bytes to read
* @throw CSocketException
* @since 1.0.0
*/
string CSocket::ReadLine() throw (CSocketException) {

	int BUFFER_LENGTH = 1024;
	char* BUFFER = (char*)LocalAlloc(LMEM_FIXED,BUFFER_LENGTH);
	memset(BUFFER,0,BUFFER_LENGTH);
	int nret = ReadLine(BUFFER);
	string data(BUFFER);
	LocalFree(BUFFER);
	return data;	
}

/**
* Closes the socket
* @since 1.0.0
*/
void CSocket::Close() {	
	closesocket(m_socket);
	if(m_clientAddr != NULL) delete m_clientAddr;
}

/**
* Destructor
* @since 1.0.0
*/
CSocket::~CSocket() {
	Close();
}

// CSocketAddress

/**
* Default constructor
* @param host Host name.
* @param port Host port
* @since 1.0.0
*/
CSocketAddress::CSocketAddress(int port) {
	m_sockAddrIn.sin_family = AF_INET; 
	m_sockAddrIn.sin_addr.s_addr = INADDR_ANY; // initialized only in GetSockAddrIn()
	m_sockAddrIn.sin_port = htons(port);
	m_nPort = port;
}

/**
* Constructor initialized by a SOCKADDR_IN
* @param sockAddr Address information
* @since 1.0.0
*/
CSocketAddress::CSocketAddress(SOCKADDR_IN sockAddr) {
	m_sockAddrIn.sin_family = sockAddr.sin_family;
	m_sockAddrIn.sin_addr.s_addr = sockAddr.sin_addr.s_addr;
	m_sockAddrIn.sin_port = sockAddr.sin_port;
	m_IP = inet_ntoa(m_sockAddrIn.sin_addr);
	m_nPort = sockAddr.sin_port;;
}

/**
* Returns the IP address
* @return const char*
* @since 1.0.0
*/
const char* CSocketAddress::GetIP() {
	return (const char*)inet_ntoa(m_sockAddrIn.sin_addr);
}

/**
* Returns the sockaddr_in. tries to bind with the server.
* throws CSocketException on failure.
* @return SOCKADDR_IN
* @since 1.0.0
*/
SOCKADDR_IN CSocketAddress::GetSockAddrIn() throw (CSocketException) {
	return m_sockAddrIn;
}

/**
* Assignment operation
* @param addr Object is copied into this.
* @since 1.0.0
*/
void CSocketAddress::operator = (CSocketAddress addr) {
	m_sockAddrIn = addr.m_sockAddrIn;
	m_nPort = addr.m_nPort;
	m_IP = addr.m_IP;
}

/**
* Destructor
* @since 1.0.0
*/
CSocketAddress::~CSocketAddress() {
}
