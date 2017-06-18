#include "AddXNORgate2.h"
#include "..\ApplicationManager.h"
AddXNORgate2::AddXNORgate2(ApplicationManager *pApp):Action(pApp)
{
	CancelOperation=false;
}

AddXNORgate2::~AddXNORgate2()
{
}

void AddXNORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input XNOR Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	int Len = UI.XNOR2_Width;
	int Wdth = UI.XNOR2_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddXNORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	if (CancelOperation)
		return;
	
	//Calculate the rectangle Corners
	int Len = UI.XNOR2_Width;
	int Wdth = UI.XNOR2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the XNOR2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	XNOR2 *pA=new XNOR2(GInfo, XNOR2_FANOUT); 
	pManager->AddComponent(pA);
}

void AddXNORgate2::Undo()
{}

void AddXNORgate2::Redo()
{}

