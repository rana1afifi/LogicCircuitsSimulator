#include "Gate.h"
#include "Connection.h"
#include<fstream>
//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
		m_InputPins[i].setComponent(this);

	    m_OutputPin.setComponent(this);
}


OutputPin* Gate::GetOutputpinCoorinates(int &x,int &y)
{
	
	if (x<=m_GfxInfo.x2+6 && x>=m_GfxInfo.x2-6 && y<=(m_GfxInfo.y2-(UI.AND2_Height/2)+6) && y>=(m_GfxInfo.y2-(UI.AND2_Height/2)-6) )
	{
		x = m_GfxInfo.x2;
		y = m_GfxInfo.y2-(UI.AND2_Height/2);
		return &(this->m_OutputPin);
	}

	return NULL;

}

OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

 vector<Component*> Gate::GetListofNextGates()
{
	return(m_OutputPin.GetListofNextGates());
}


InputPin* Gate::GetInputPin(int & NoOfInputs)
{
	NoOfInputs=m_Inputs;
	return m_InputPins;
}

OutputPin* Gate::GetComponentOutputpinCoordinates(int &x , int &y)
{
		x = m_GfxInfo.x2;
		y = m_GfxInfo.y2-(UI.AND2_Height/2);
		return &(this->m_OutputPin);
}

void Gate::Move(int x ,int y)
{
	vector <Connection *> outputconnections=m_OutputPin.GetListOfOutputConnecctions();
	
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
	Connection * inputconnection;
	
	for (int i=0;i<m_Inputs;i++)
	{

		if(m_InputPins[i].isconnected())
		{
			GetComponentInputpinCoordinates(A,B,i+1);
			inputconnection=m_InputPins[i].getconnection();
			if(inputconnection!=NULL)
			inputconnection->ChangeConnectionEndPoints(A,B);
		}
	}
}





Gate::~Gate()
{
	m_OutputPin.setComponent(NULL);
	for(int i=0; i<m_Inputs; i++)
	{
		m_InputPins->setComponent(NULL);
	///	m_InputPins->getconnection()->setDestPin(NULL);
	}
	m_InputPins->setComponent(NULL);

}

void Gate::Load(ifstream & inp)
{
	string label;
	int X1, Y1, X2, Y2, ID;
	GraphicsInfo GInfo;
	inp >> ID >> label >> X1 >> Y1;
	X2 = X1 + UI.AND2_Width;
	Y2 = Y1 + UI.AND2_Height;
	GInfo.x1 = X1; GInfo.x2 = X2; GInfo.y1 = Y1; GInfo.y2 = Y2;
	this->SetID(ID);
	this->setLabel(label);
	this->setGraphicsInfo(GInfo); 

}
void Gate::Save(ofstream &out)
{
	out << "      " << GetID() << "      ";
	if (GetLabel().empty())
		out<< "$";
	else out << GetLabel();
	out<< "      " << m_GfxInfo.x1 << "      " << m_GfxInfo.y1;


}
Component* Gate::MakeCopy(Component* c)
{
	return NULL; 
}


