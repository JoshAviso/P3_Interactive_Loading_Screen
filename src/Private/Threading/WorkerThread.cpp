#include <Threading/WorkerThread.h>

WorkerThread::WorkerThread(int id, IWorkerThreadFinishCallback* callback)
 : _id(id), _onFinished(callback), _task(nullptr) {}

void WorkerThread::Run()
{
	if (_task != nullptr) {
		_task->DoWorkerTask(_id);
		delete _task;
	}
	if (_onFinished != nullptr) 
		_onFinished->OnWorkerFinished(_id);
}
