#include "AddConnection.h"
#include "..\ApplicationManager.h"

AddConnection::AddConnection(ApplicationManager *pApp) :Action(pApp)
{
	  pSrcPin =NULL;
      pDstPin =NULL;
	  CancelOperation=false;
}


AddConnection::~AddConnection()
{
}

void AddConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	/*bool Dstconnected ;
	bool Srcconected  ;*/

	//Print Action Message
	pOut->PrintMsg("AddConnection: Click on output pin to start ");
	
	//Wait for User Input
	pIn->GetPointClicked(x1,y1);

	pSrcPin = pManager->getoutputpin(x1,y1);
    if (pSrcPin==NULL)
	{
		pOut->PrintMsg("operation is cancelled: wrong selection ");
		CancelOperation=true;
		return;
	}
	else if (pSrcPin->AvailableConnection()==false)
	{
		pOut->PrintMsg("operation is cancelled: cant add more connection to this gate.max fanout reached");
		CancelOperation=true;
		return;
	}
	
	pOut->PrintMsg("Click on input pin to connect the wire ");
	
	pIn->GetPointClicked(x2,y2);
	
	pDstPin=pManager->getinputpin(x2,y2);
	
	if (pDstPin==NULL)
	{
		pOut->PrintMsg("operation is cancelled: wrong selection ");
		CancelOperation=true;
		return;
	}

	else if (pDstPin->getComponent()==pSrcPin->getComponent())
	{
		pOut->PrintMsg("operation is cancelled: You cant connect the output and input of the same gate ");
		CancelOperation=true;
		return;
	}
	else if (pDstPin->isconnected())
	{
		pOut->PrintMsg("cant add more connection to this gate : inputpin already connected ");
		CancelOperation=true;
		return;
	}

	//Clear Status Bar
	pOut->ClearStatusBar();
}

void AddConnection::Execute()
{  
	vector<GraphicsInfo*>ConnectionPoints;
	ReadActionParameters();
	if (CancelOperation)
		return;
	
	GraphicsInfo GInfo; //Gfx info to be used to draw the connection
	GInfo.x1=x1;
	GInfo.x2=x2;
	GInfo.y1=y1;
	GInfo.y2=y2;
	//ConnPoints.push_back(&GInfo);

	//while(MustShift)
	//{
	//	Component*Found = NULL;
	//	GraphicsInfo *CurrentLine = MustShift(Found);
	//   ShiftConnection(*CurrentLine, Found);
	//}
	Connection *pA=new Connection(GInfo,pSrcPin,pDstPin ); 
	pManager->AddComponent(pA);
	
	
}
//GraphicsInfo* AddConnection::MustShift(Component &*Found)
//{
//	for (int i = 0; i < ConnPoints.size(); i++)
//	{
//		GraphicsInfo Gfx = *ConnPoints[i];
//		int x1 = Gfx.x1;
//		int y1 = Gfx.y1;
//		int x2 = Gfx.x2;
//		int y2 = Gfx.y2;
//		if (y1 == y2)
//		{
//			Found = pManager->IsFoundY(y1);
//			if (Found != NULL && !(dynamic_cast<Connection*>(Found)))
//			{
//				int X1 = Found->GetGraphicsInfo()->x1;
//				int X2 = Found->GetGraphicsInfo()->x2;
//				int Y1 = Found->GetGraphicsInfo()->y1;
//				int Y2 = Found->GetGraphicsInfo()->y2;
//				if ((X1 > x1 && x2 > X2) || (X1 < x1 && x2 < X2))
//				{
//					return &Gfx;
//				}
//			}
//			
//		}
//		else if (x1 == x2)
//		{
//			Found = pManager->IsFoundX(x1);
//			Found = pManager->IsFoundY(y1);
//			if (Found != NULL && !(dynamic_cast<Connection*>(Found)))
//			{
//				int X1 = Found->GetGraphicsInfo()->x1;
//				int X2 = Found->GetGraphicsInfo()->x2;
//				int Y1 = Found->GetGraphicsInfo()->y1;
//				int Y2 = Found->GetGraphicsInfo()->y2;
//				if ((Y1 > y1 && y2 > Y2) || (Y1 < y1 && y2 < Y2))
//				{
//					return &Gfx;
//				}
//			}
//		}
//
//	}
//	return NULL;
//}
//vector<GraphicsInfo*> AddConnection::ShiftConnection(GraphicsInfo CurrentLine, Component* FoundComp)
//{
//	int X1 = FoundComp->GetGraphicsInfo()->x1;
//	int X2 = FoundComp->GetGraphicsInfo()->x2;
//	int Y1 = FoundComp->GetGraphicsInfo()->y1;
//	int Y2 = FoundComp->GetGraphicsInfo()->y2;
//	vector<GraphicsInfo*> newGfx;
//	if(CurrentLine.y1==CurrentLine.y2)
//	{
//		int i = 0;
//		
//		if (X1 > x1 && x2 > X2)
//		{
//			newGfx[i]->x1 = X1 - 20;
//			newGfx[i]->y1 = Y2;
//			newGfx[i]->x2 = X1 - 20;
//			newGfx[i]->y2 = Y2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->x1 = X1 - 20;
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x2 = X2 + 20;
//			newGfx[i]->y2 = Y2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x2 = X2 + 20;
//			newGfx[i]->y2 = CurrentLine.y2;
//			ConnPoints.push_back(newGfx[i]);
//		}
//		else if (X1 < x1 && x2 < X2)
//		{
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y1 = Y2;
//			newGfx[i]->x2 = X2 + 20;
//			newGfx[i]->y2 = Y2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x2 = X1 - 20;
//			newGfx[i]->y2 = Y2+20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->x1 = X1 - 20;
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x2 = X1 - 20;
//			newGfx[i]->y2 = CurrentLine.y2;
//			ConnPoints.push_back(newGfx[i]);
//		}
//	}
//	else if (CurrentLine.x1 == CurrentLine.x2)
//	{
//		int i = 0;
//		if (Y1 > y1 && y2 > Y2)
//		{
//			newGfx[i]->y1 = Y1 - 20;
//			newGfx[i]->x1 = X2;
//			newGfx[i]->y2 = Y1 - 20;
//			newGfx[i]->x2 = X2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->y1 = Y1 - 20;
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y2 = Y2 + 20;
//			newGfx[i]->x2 = X2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y2 = Y2 + 20;
//			newGfx[i]->x2 = CurrentLine.x2;
//			ConnPoints.push_back(newGfx[i]);
//		}
//		else if (Y1 < y1 && y2 < y2)
//		{
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x1 = X2;
//			newGfx[i]->y2 = Y2 + 20;
//			newGfx[i]->x2 = X2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->y1 = Y2 + 20;
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y2 = Y1 - 20;
//			newGfx[i]->x2 = X2 + 20;
//			ConnPoints.push_back(newGfx[i]);
//			i++;
//			newGfx[i]->y1 = Y1 - 20;
//			newGfx[i]->x1 = X2 + 20;
//			newGfx[i]->y2 = Y1 - 20;
//			newGfx[i]->x2 = CurrentLine.x2;
//			ConnPoints.push_back(newGfx[i]);
//		}
//	}
//	return ConnPoints;
//}
void AddConnection::Undo()
{}

void AddConnection::Redo()
{}
