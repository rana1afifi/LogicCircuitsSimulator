#ifndef _EDIT_H
#define _EDIT_H

#include "action.h"
#include "..\Components\Component.h"


class Edit : public Action
{
private:
	bool CancelOperation;	//bool to check if the operation is cancelled
	bool EditComponent;
	bool EditConnectionSD;      //bool to check if edit the source and destination of a source
	bool EditConnectionLabel;   //bool to check if edit label of a connection
	OutputPin *pSrcPin;
	InputPin *pDstPin;
	int X1, X2, Y1, Y2;  //Coordinates of new connection
	vector<Component*> SelectedComp;
public:
	Edit(ApplicationManager *pApp);
	virtual ~Edit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif