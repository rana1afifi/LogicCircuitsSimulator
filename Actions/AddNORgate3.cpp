#include "AddNORgate3.h"
#include"..\ApplicationManager.h"

AddNORgate3::AddNORgate3(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation=false;
}

AddNORgate3::~AddNORgate3(void)
{
}

void AddNORgate3::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("3-Input NOR Gate: Click to add the gate");

	pIn->GetPointClicked(Cx, Cy);

	int Len = UI.NOR3_Width;
	int Wdth = UI.NOR3_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddNORgate3::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	if (CancelOperation)
		return;
	//Calculate the rectangle Corners
	int Len = UI.NOR3_Width;
	int Wdth = UI.NOR3_Height;

	GraphicsInfo GInfo; //Gfx info to be used to construct the NOR3 gate

	GInfo.x1 = Cx - Len / 2; // Cx : Center pt of gate 
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	NOR3 *pA = new NOR3(GInfo, NOR3_FANOUT);
	pManager->AddComponent(pA);
}

void AddNORgate3::Undo()
{}

void AddNORgate3::Redo()
{}


