#pragma once
#include "Action.h"
class Exit: public Action
{
	bool OperationCancelled; 

public: 
	Exit(ApplicationManager *pApp);
	virtual ~Exit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

}; 