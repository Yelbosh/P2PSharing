#pragma once
#include "cthread.h"

class PlayThread :
	public CThread
{
private:
	int key;
public:
	PlayThread(void);
	PlayThread(int key);
	virtual ~PlayThread(void);
	void run();
	void play();
};

