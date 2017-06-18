#include "AddNORgate2.h"
#include "..\ApplicationManager.h"

AddNORgate2::AddNORgate2(ApplicationManager *pApp):Action(pApp)
{
	CancelOperation=false;
}

AddNORgate2::~AddNORgate2()
{
}

void AddNORgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NOR Gate: Click to add the gate");
	pIn->GetPointClicked(Cx, Cy);

	int Len = UI.NOR2_Width;
	int Wdth = UI.NOR2_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddNORgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	if (CancelOperation)
		return;
	
	//Calculate the rectangle Corners
	int Len = UI.NOR2_Width;
	int Wdth = UI.NOR2_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	NOR2 *pA=new NOR2(GInfo, NOR2_FANOUT); 
	pManager->AddComponent(pA);
}

void AddNORgate2::Undo()
{}

void AddNORgate2::Redo()
{}

