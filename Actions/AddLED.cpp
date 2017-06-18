#include "AddLED.h"
#include "..\ApplicationManager.h"

AddLED::AddLED(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation=false;
}

AddLED::~AddLED(void)
{
}

void AddLED::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("LED: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);
	
	int Len = UI.LEDOFF_Width;
	int Wdth = UI.LEDOFF_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddLED::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	if (CancelOperation)
		return;

	//Calculate the rectangle Corners
	int Len = UI.LEDOFF_Width;
	int Wdth = UI.LEDOFF_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the led

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	LED *pA = new LED(GInfo);
	pManager->AddComponent(pA);
}

void AddLED::Undo()
{}

void AddLED::Redo()
{}

