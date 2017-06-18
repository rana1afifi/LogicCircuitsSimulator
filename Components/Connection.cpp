#include "Connection.h"
#include <fstream>
Connection::Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin):Component(r_GfxInfo)	
{
	SrcPin = pSrcPin;
	DstPin = pDstPin;
	if (SrcPin)
	{
		SrcPin->ConnectTo(this);
	}
	if (DstPin)
	{
	DstPin->setConnection(this);
	}
   selected = false;
   status = LOW;
   level=1000;
   visited = false;
}

vector<Component*> Connection::GetListofNextGates()
{
	vector <Component*>dummy;
	return dummy;
}

void Connection::setSourcePin(OutputPin *pSrcPin)
{	SrcPin = pSrcPin;}

OutputPin* Connection::getSourcePin()
{	return SrcPin;	}

OutputPin* Connection::GetOutputpinCoorinates(int &x,int &y)
{
    return NULL;
}

 InputPin* Connection::GetInputpinCoorinates(int &x,int &y, int &i)
{
	return NULL;
}

 
InputPin * Connection::GetComponentInputpinCoordinates(int &x , int &y ,int index) //T
{
    return NULL;
}

OutputPin* Connection::GetComponentOutputpinCoordinates(int &x,int &y)
{
	return NULL;
}
void Connection::setDestPin(InputPin *pDstPin)
{	DstPin = pDstPin;
    if (DstPin)
	{
		DstPin->setConnection(this);
	}
}

InputPin* Connection::getDestPin()
{	return DstPin;	}


void Connection::Operate()
{
	DstPin->setStatus((STATUS)SrcPin->getStatus());
}

void Connection::ResetStatus()
{
	status=LOW;

}

void Connection::Draw(Output* pOut)
{
		pOut->DrawConnection(m_GfxInfo, connection, selected, status);
	
	int x = GetGraphicsInfo()->x1+20;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);

}

void Connection::DrawWithDisplacement(int x, int y ,Output* pOut) //T
{
	//pOut->DrawConnection(m_GfxInfo,connection,x,y,selected);
	
}

int Connection::GetOutPinStatus()	//returns status of outputpin if LED, return -1
{
	return DstPin->getStatus();
}


int Connection::GetInputPinStatus(int n)	//returns status of Inputpin # n if SWITCH, return -1
{
	return SrcPin->getStatus();	//n is ignored as connection has only one input pin (src pin)	
}

void Connection::setInputPinStatus(int n, STATUS s)
{
	SrcPin->setStatus(s);
}

bool Connection::FindConnection(int x, int y)
{
	for (UINT i = 0; i < connection.size(); i++)
	{
		if (connection[i].y1 > connection[i].y2)
		{
				if (connection[i].x1 - 5 < x && connection[i].x2 + 5 > x && connection[i].y1 - 5 > y && connection[i].y2 + 5 < y)
					return true;
		}
		else
		{
				if (connection[i].x1 - 5 < x && connection[i].x2 + 5 > x && connection[i].y1 - 5 < y && connection[i].y2 + 5 > y)
					return true;	
		}
	}
	return false;
}

void Connection::Move(int x ,int y)
{
	return;
}

void Connection::ChangeConnectionEndPoints(int x , int y) //T
{
	connection[connection.size()-1].x2=x;
	connection[connection.size()-1].y2=y;
	GraphicsInfo info;
	info.x1=connection[0].x1;
	info.y1=connection[0].y1;
	info.x2=x;
	info.y2=y;
	this->setGraphicsInfo(info);


}
void Connection::ChangeConnectionStartPoints(int x, int y) //T
{
	connection[0].x1=x;
	connection[0].y1=y;
	GraphicsInfo info;
	info.x1=x;
	info.y1=y;
	info.x2=connection[connection.size()-1].x2;
	info.y2=connection[connection.size()-1].y2;
	this->setGraphicsInfo(info);
}

bool Connection::Validate()
{
	return true ;
}


void Connection::SetStatus(STATUS x)
{
	status = x;
}

STATUS Connection::GetStatus() 
{
	return status;
}

Connection::~Connection()
{
	if(DstPin)
	DstPin->setConnection(NULL);
	if(SrcPin)
	SrcPin->Deleteconnection(this);
}

void Connection::Load(ifstream & inp)
{

}
void Connection::Save(ofstream &out)
{
	int n; 
	Component* src, *dest;
	src = SrcPin->getComponent();
	dest = DstPin->getComponent();
	dest->GetInputpinCoorinates(m_GfxInfo.x2, m_GfxInfo.y2, n); 
	int srcID, destID;
	srcID = src->GetID();
	destID = dest->GetID();
	out << endl << srcID << "   " << destID << "   " << n; 

}
Component* Connection::MakeCopy(Component* c)
{
	return NULL; 
}


