#pragma once

#include <thread>
#include <Core/Common.h>

class IThread
{
public:
	IThread() = default;
	virtual ~IThread() = default;

	void StartThread() { std::thread(&IThread::Run, this).detach(); } ;
	static void Sleep(uint ms) 
		{ std::this_thread::sleep_for(std::chrono::milliseconds(ms)); };

protected:
	virtual void Run() = 0;
};

