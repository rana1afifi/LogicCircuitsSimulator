#pragma once
#include "action.h"
class Copy:public Action
{                        
	Component* Copied; 
	bool CancelOperation;
public:
	Copy(ApplicationManager * pManager);
	virtual ~Copy(); 
	virtual void ReadActionParameters(); 
	virtual void Execute(); 

	virtual void Undo();
	virtual void Redo(); 

};