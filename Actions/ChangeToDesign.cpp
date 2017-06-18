#include "ChangeToDesign.h"
#include "..\ApplicationManager.h"

ChangeToDesign::ChangeToDesign(ApplicationManager *pApp) :Action(pApp)
{
}

ChangeToDesign::~ChangeToDesign()
{
}

void ChangeToDesign::ReadActionParameters()
{
}

void ChangeToDesign::Execute()
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	pOut->CreateDesignToolBar();
	pManager->SetFloatingPinstatus(false); // reset the value so we can check again after returning to design mode
	pManager->SetFeedbackStatus(false);	// reset the value so we can check again after returning to design mode
	pManager->ResetCircuitStatus();	// reset the all circuit status to low 
	pManager->ResetCircuitLevels();  // reset circuit level so wi can set them again after returning to design mode
}

void ChangeToDesign::Undo()
{}

void ChangeToDesign::Redo()
{}

