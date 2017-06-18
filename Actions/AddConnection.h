#pragma once
#include "action.h"
#include "..\Components\Connection.h"
class AddConnection : public Action
{   OutputPin *pSrcPin;
    InputPin *pDstPin;
	int x1,y1,x2,y2;  // click coordinates
	bool CancelOperation;
	/*vector<GraphicsInfo*> ConnPoints;*/
public:
	AddConnection(ApplicationManager *pApp);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();
	/*vector<GraphicsInfo*> ShiftConnection(GraphicsInfo CurrentLine, Component* );*/
	virtual void Undo();
	virtual void Redo();
	/*GraphicsInfo* MustShift(Component &*FoundComp );*/
	~AddConnection();
};

