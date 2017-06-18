#include "AddSwitch.h"
#include"..\ApplicationManager.h"



AddSwitch::AddSwitch(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation=false;
}

AddSwitch::~AddSwitch(void)
{
}

void AddSwitch::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("Switch: Click to add the component");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddSwitch::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	if (CancelOperation)
		return;

	//Calculate the rectangle Corners
	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the switch

	GInfo.x1 = Cx - Len / 2; // Cx : Center pt of gate 
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	Switch *pA = new Switch(GInfo, SWITCH_FANOUT);
	pManager->AddComponent(pA);
}

void AddSwitch::Undo()
{}

void AddSwitch::Redo()
{}

