#include "Switch.h"
#include "Connection.h"
#include<fstream>


Switch::Switch(const GraphicsInfo &r_GfxInfo, int r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;

	m_OutputPin = new OutputPin(r_FanOut);
	//Associate  output pin to the led
	m_OutputPin->setComponent(this);

	SwitchStatus=LOW;
	selected =false ;
	level =-1;
	visited = false;
	Count++;
	ID = Count; 
}

OutputPin* Switch::GetOutputPin()
{
	return m_OutputPin;
}

 vector<Component*> Switch::GetListofNextGates()
{
	return(m_OutputPin->GetListofNextGates());
}


InputPin* Switch::GetInputpinCoorinates(int &x,int &y , int&i)
{
	return NULL;
}
OutputPin* Switch::GetOutputpinCoorinates(int &x,int &y)
{
	if (x<=m_GfxInfo.x2+6 && x>=m_GfxInfo.x2-6 && y<=(m_GfxInfo.y2-(UI.Switch_Height/2)+6) && y>=(m_GfxInfo.y2-(UI.Switch_Height/2)-6) )
	{
		x = m_GfxInfo.x2;
		y = m_GfxInfo.y2-(UI.Switch_Height/2);
		return (this->m_OutputPin);
	}
	return NULL;
}

OutputPin* Switch::GetComponentOutputpinCoordinates(int &x , int &y)
{
		x = m_GfxInfo.x2;
		y = m_GfxInfo.y2-(UI.Switch_Height/2);
		return (this->m_OutputPin);
}

InputPin* Switch::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	return NULL;
}

void Switch::Operate()
{
	if (SwitchStatus == HIGH)
		m_OutputPin->setStatus(HIGH);
	else m_OutputPin->setStatus(LOW);

	m_OutputPin->OperateTheConnections();
}

void Switch::ResetStatus()
{
	SwitchStatus=LOW;
	m_OutputPin->setStatus(LOW);

}

void Switch::SetSwitchstatus(STATUS xSTATUS ) 
{
	SwitchStatus=xSTATUS;
}

STATUS Switch::GetSwitchStatus()
{
	return SwitchStatus;
}

// Function Draw

void Switch::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawSwitch(m_GfxInfo,selected,0,0,SwitchStatus);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);
}

void Switch::DrawWithDisplacement(int x, int y ,Output* pOut)
{
	pOut->DrawSwitch(m_GfxInfo,selected,x,y);

}

//returns status of outputpin
int Switch::GetOutPinStatus()
{
	return m_OutputPin->getStatus();
}


//returns -1
int Switch::GetInputPinStatus(int n)
{
	return -1; 	
}

//Set status of an input pin ot HIGH or LOW
void Switch::setInputPinStatus(int n, STATUS s)
{
	return;
}

void Switch::Move(int x ,int y)
{
	vector <Connection *> outputconnections=m_OutputPin->GetListOfOutputConnecctions();
	m_GfxInfo.x1+=x;
	m_GfxInfo.x2+=x;
	m_GfxInfo.y1+=y;
	m_GfxInfo.y2+=y;

	int A,B;
	GetComponentOutputpinCoordinates(A,B);
	for (UINT i=0; i<outputconnections.size();i++)
	{
		outputconnections[i]->ChangeConnectionStartPoints(A,B);
	}
}

bool Switch::Validate()//T
{
	if (m_OutputPin->isconnected()==false)
	{
		return false;
	}
	return true;
}

void Switch::Load(ifstream &inp)
{
	string label;
	int X1, Y1, X2, Y2, ID;
	GraphicsInfo GInfo;
	inp >> ID >> label >> X1 >> Y1;
	X2 = X1 + UI.Switch_Width;
	Y2 = Y1 + UI.Switch_Height;
	GInfo.x1 = X1; GInfo.x2 = X2; GInfo.y1 = Y1; GInfo.y2 = Y2;
	this->SetID(ID);
	this->setLabel(label);
	this->setGraphicsInfo(GInfo);
}
void Switch::Save(ofstream &out)
{
	out << "\nSWITCH";
	out << "      " << GetID() << "      ";
	if (GetLabel().empty())
		out << "$";
	else out << GetLabel();
	out << "      " << m_GfxInfo.x1 << "      " << m_GfxInfo.y1;


}
Component* Switch::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	Switch* ptr = new Switch(temp, SWITCH_FANOUT);
	ptr->setLabel(c->GetLabel());
	return ptr;
}



Switch:: ~Switch()
{
	delete  m_OutputPin;
}