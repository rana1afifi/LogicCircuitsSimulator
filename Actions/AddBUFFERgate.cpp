#include "AddBUFFERgate.h"
#include "..\ApplicationManager.h"

AddBUFFERgate::AddBUFFERgate(ApplicationManager *pApp):Action(pApp)
{
	CancelOperation=false;
}

AddBUFFERgate::~AddBUFFERgate(void)
{
}

void AddBUFFERgate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	//Print Action Message
	pOut->PrintMsg("1-Input BUFFER Gate: Click to add the gate");

	//Wait for User Input
	pIn->GetPointClicked(Cx, Cy);

	int Len = UI.Buffer_Width;
	int Wdth = UI.Buffer_Height;

	if (Cy-Wdth/2 <= UI.ToolBarHeight || Cy+Wdth/2 >= UI.height - UI.StatusBarHeight)
	{
		CancelOperation=true;
		pOut->PrintMsg("you cant draw on the toolbar or status bar");
		return;
	}
	pOut->ClearStatusBar();

}

void AddBUFFERgate::Execute()
{
	//Get Center point of the Gate
	ReadActionParameters();
	
	if (CancelOperation)
		return ;

	//Calculate the rectangle Corners
	int Len = UI.Buffer_Width;
	int Wdth = UI.Buffer_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the BUFFER2 gate
	
	GInfo.x1 = Cx - Len/2;
	GInfo.x2 = Cx + Len/2;
	GInfo.y1 = Cy - Wdth/2;
	GInfo.y2 = Cy + Wdth/2;
	BUFFER *pA=new BUFFER(GInfo, BUFFER_FANOUT); 
	pManager->AddComponent(pA);
}

void AddBUFFERgate::Undo()
{}

void AddBUFFERgate::Redo()
{}

