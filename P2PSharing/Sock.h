#pragma once
/**
* Defines a classes that wraps up the winsock API.These classes
* do not supports only TCP/IP.
* @author  WHU WH
* @version 1.0.0
*/ 
#include <vector>
#include<string>
#include<windows.h>
using namespace std;

namespace SockUtil{
	
	class CSocket;
	class CSocketException;
	class CSocketAddress;
	
	/**
	* class CWinSock
	* Performs winsock initialization and cleanup
	* @since 1.0.0
	*/
	class CWinSock {
	public:
		static void Initialize();/// WSAStartup
		static void Finalize();/// WSACleanup
	};

	/**
	* class CServerSocket.
	* Wraps up win32 calls for creating a server.
	* @since 1.0.0
	*/
	class CServerSocket {
	private:		
		SOCKET m_socket; /// listening socket
		SOCKADDR_IN m_sockAddrIn; /// default socket settings
		int m_nPort; /// server port
		int m_nQueue; /// number of clients that can be in queue waiting for acceptance.
		CSocketAddress *m_sockAddr; /// Address to which this server is attached.
		bool m_bBound; /// true if bound to port.
		bool m_bListening; /// true if listening
	public:
		CServerSocket();  /// default constructor
		CServerSocket(int port); /// overloaded constructor
		CServerSocket(int port,int queue); /// overloaded constructor
		~CServerSocket(); /// default destructor
		void Bind(CSocketAddress *scok_addr);/// Binds the server to the given address.
		CSocket* Accept() throw (CSocketException);/// Accepts a client connection.
		void Close(); /// Closes the Socket.	
		bool IsListening(); /// returns the listening flag
		
		void SetPort(int port); /// Sets the port
		void SetQueue(int q); /// Sets the queue size
		int GetPort(); /// returns the port
		int GetQueue(); /// returns the queue size
		CSocketAddress* GetSocketAddress(); /// Returns the socket address
	private:
		void Init(); /// default initialization
	};

	/**
	* class CSocket
	* Wraps up a raw SOCKET
	* @since 1.0.0
	*/
	class CSocket {
	private:
		SOCKET m_socket; /// SOCKET for communication
		CSocketAddress *m_clientAddr; /// Address details of this socket.
	public:
		CSocket(); /// Default constructor
		void SetSocket(SOCKET sock); /// Sets the SOCKET
		void SetClientAddr(SOCKADDR_IN addr); /// Sets address details
		int Connect(const char* host_name,int port) throw (CSocketException); /// Connects to host
		CSocketAddress* GetAddress() { return m_clientAddr; } /// Returns the client address
		int Send(const char* data) throw (CSocketException); /// Writes data to the socket
		int WriteLine(string data) throw (CSocketException); /// Writes line to the socket
		int Send(const char* data,int len) throw (CSocketException); /// Writes data to the socket using the len
		int Read(char* buffer,int len) throw (CSocketException); /// Reads data from the socket
		int ReadLine(char* buffer) throw (CSocketException);/// Reads a line from a buffer pool, the max length is 1M, which is 1024 bytes
		string ReadLine() throw (CSocketException);
		void Close(); /// Closes the socket
		~CSocket(); /// Destructor
	};
	
	/**
	* class CSocketAddress
	* Wraps up an internet address object.
	* @since 1.0.0
	*/
	class CSocketAddress {
	private:
		SOCKADDR_IN m_sockAddrIn; /// server info
		const char* m_IP;// the ip
		int m_nPort; /// port 
	public:
		CSocketAddress(int port); /// default constructor		
		CSocketAddress(SOCKADDR_IN sockAddr);/// Constructor initialized by a SOCKADDR_IN
		const char* GetIP(); /// Returns the IP address
		int GetPort() { return m_nPort; } /// Returns the port
		SOCKADDR_IN GetSockAddrIn() throw (CSocketException); /// returns the sockaddr_in
		void operator = (CSocketAddress addr); /// Assignment operation
		~CSocketAddress(); /// Destructor
	};
	
	/**
	* class CSocketException
	* Thrown by all sock.h classes.
	* @since 1.0.0
	*/
	class CSocketException {
	private:
		string m_strError; /// error message
		int m_nCode; /// Error code
	public:
	/**
	* Default constructor.
	* @param code Error code.
	* @param msg Error message
	* @since 1.0.0
		*/
		CSocketException(int code,const char* msg) {
			m_nCode = code;
			m_strError = msg;
		}
		/**
		* returns the error code.
		* @return int
		* @since 1.0.0
		*/
		inline int GetCode() { return m_nCode; }
		/**
		* returns the error message.
		* @return const char*
		* @since 1.0.0
		*/
		inline const char* GetMessage() { return m_strError.c_str(); }
	};
}