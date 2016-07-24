#pragma once
class Get
{
private:
	Peer* peer;
	int key;
public:
	Get(void);
	Get(Peer* peer,int key);
	void start_get();
	virtual ~Get(void);
};

