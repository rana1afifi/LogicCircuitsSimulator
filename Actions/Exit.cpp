#include"Exit.h"
#include"../ApplicationManager.h"
#include "Save.h"
Exit:: Exit(ApplicationManager *pApp): Action(pApp)
{
	OperationCancelled = false; 
}
Exit::~Exit()
{}

void Exit::ReadActionParameters()
{
	int x=0, y=0; // so that getUserAction would work 

	Output* pOut = pManager->GetOutput(); 
	pOut->PrintMsg("If you want to exit, please click on the exit icon again"); 
	ActionType act = pManager->GetInput()->GetUserAction(x, y);
    if (act==EXIT)
	{
		OperationCancelled = false; 
	}

	else 
	{
		OperationCancelled = true; 
	}

}
void Exit::Execute()
{
	ReadActionParameters(); 
	if (OperationCancelled) return; 

Output* pOut= pManager->GetOutput();
int x = 0, y = 0;
if (pManager->isEmpty() == false)
{
	pOut->PrintMsg("If you want to save the circuit you are working on, click on save icon");
	if (pManager->GetUserAction(x, y) == SAVE)
	{
		Save S(pManager);
    	S.Execute();
     }
}
pManager->Reset();
Component* c = pManager->GetCopied();
Component *c2 = pManager->GetCut(); 
if (c != NULL) { delete c; c = NULL; }
if (c2 !=NULL) { delete c2; c2 = NULL; }
return; 

}

void Exit::Undo()
{}
void Exit::Redo()
{}