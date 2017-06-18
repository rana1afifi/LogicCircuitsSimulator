#include "Delete.h"
#include "..\ApplicationManager.h"


Delete::Delete(ApplicationManager *pApp):Action(pApp)
{
	 CancelOperation=false;
}

Delete::~Delete(void)
{
}

void Delete:: ReadActionParameters()
{
	if (pManager->GetSelectedSize()==0)
		CancelOperation=true;
}


void Delete::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if(CancelOperation)
	{
		 pOut->PrintMsg("No selected components to delete");
		 return;
	}
	
    pOut->PrintMsg("Deleting selected components");
	pManager->SelectRelatedComp();
	pManager->DeleteComponents();
	pManager->UpdateInterface();
}

void Delete::Undo()
{}

void Delete::Redo()
{}