#pragma once
#include "Action.h"

class Cut: public Action
{
	Component * Object;
	bool CancelOperation;

public: 
	Cut(ApplicationManager *pManager); 
	~Cut(); 
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual void Undo();
	virtual void Redo();
};
