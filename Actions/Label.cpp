#include "Label.h"
#include<vector>
#include "..\ApplicationManager.h"



Label::Label(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation = false;
}

Label::~Label(void)
{
}

void Label::ReadActionParameters()
{

	//Check if there is a selected component
	SelectedComp = pManager->GetSelectedList();
	if (SelectedComp.size() == 0 || SelectedComp.size() > 1)
		CancelOperation = true;
	if (SelectedComp.size() == 1)
	{
		if (SelectedComp[0]->GetLabel() != "")
			CancelOperation = true;
	}
}

void Label::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//Get Center point of the Gate
	ReadActionParameters();

	if (CancelOperation == false) //the user clicked on a component
	{
		pOut->PrintMsg("Action Label. enter label: ");
		string str = pIn->GetSrting(pOut);
		
		SelectedComp[0]->setLabel(str);
		pOut->ClearStatusBar();
	}
	else
	{
		pOut->PrintMsg("Action is cancelled . No selected component.");
	}

}

void Label::Undo()
{}

void Label::Redo()
{}
