#pragma once
#include "action.h"


class ChangeToSimulation : public Action
{
	bool CancelOperation;
public:
	ChangeToSimulation(ApplicationManager *pApp);
	virtual ~ChangeToSimulation();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

