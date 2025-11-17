#pragma once

class IWorkerTaskFinishedCallback {
public:
	virtual void OnWorkerFinished(int id) = 0;
};