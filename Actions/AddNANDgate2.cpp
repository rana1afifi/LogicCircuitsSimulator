#include "AddNANDgate2.h"
#include"..\ApplicationManager.h"


AddNANDgate2::AddNANDgate2(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation=false;
}


AddNANDgate2::~AddNANDgate2()
{
}


void AddNANDgate2::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("2-Input NAND Gate: Click to add the gate");

	pIn->GetPointClicked(Cx, Cy);
	int Len = UI.NAND2_Width;
	int Wdth = UI.NAND2_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddNANDgate2::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	if (CancelOperation)
		return;

	//Calculate the rectangle Corners
	int Len = UI.NAND2_Width;
	int Wdth = UI.NAND2_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NAND2 gate

	GInfo.x1 = Cx - Len / 2; // Cx : Center pt of gate 
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NAND2 *pA = new NAND2(GInfo, NAND2_FANOUT);
	pManager->AddComponent(pA);
}

void AddNANDgate2::Undo()
{}

void AddNANDgate2::Redo()
{}

