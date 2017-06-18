#include "AddINVERTERgate.h"
#include "..\ApplicationManager.h"

AddINVERTERgate::AddINVERTERgate(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation=false;
}

AddINVERTERgate::~AddINVERTERgate(void)
{
}

void AddINVERTERgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg(" INVERTER Gate: Click to add the gate");

	pIn->GetPointClicked(Cx, Cy);
	int Len = UI.NOT_Width;
	int Wdth = UI.NOT_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();
}

void AddINVERTERgate::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();

	if (CancelOperation)
		return;
	
	//Calculate the rectangle Corners
	int Len = UI.AND2_Width;
	int Wdth = UI.AND2_Height;

	GraphicsInfo GInfo; // graphics info used to construct inverter

	GInfo.x1 = Cx - Len / 2;
	GInfo.x2 = Cx + Len / 2;
	GInfo.y1 = Cy - Wdth / 2;
	GInfo.y2 = Cy + Wdth / 2;
	INVERTER *pA = new INVERTER(GInfo, INVERTER_FANOUT);
	pManager->AddComponent(pA);
}

void AddINVERTERgate::Undo()
{}

void AddINVERTERgate::Redo()
{}

