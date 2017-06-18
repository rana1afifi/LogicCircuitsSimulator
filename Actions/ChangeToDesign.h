#pragma once
#include "action.h"


class ChangeToDesign : public Action
{
public:
	ChangeToDesign(ApplicationManager *pApp);
	virtual ~ChangeToDesign();

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};