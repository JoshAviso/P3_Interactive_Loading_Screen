#pragma once

#include <Threading/IThread.h>
#include <Threading/WorkerTasks/IWorkerTask.h>
#include <Threading/IWorkerTaskFinishedCallback.h>

class WorkerThread : public IThread
{
private:
	int _id;
	IWorkerTaskFinishedCallback* _onFinished;
	IWorkerTask* _task;

public:
	WorkerThread(int id, IWorkerTaskFinishedCallback* callback);
	~WorkerThread() = default;

	void AssignTask(IWorkerTask* task) { this->_task = task; }
	int GetID() const { return _id; }

private:
	void Run() override;
};