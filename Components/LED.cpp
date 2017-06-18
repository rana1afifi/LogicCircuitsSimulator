#include "LED.h"
#include "Connection.h"
#include<fstream>
LED::LED(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	
	m_InputPin = new InputPin;
	//Associate  input pin to the led
	m_InputPin->setComponent(this);

	StatusLED = LOW;
	selected =false ; 
	level =-1;
	visited = false;
	Count++;
	ID = Count; 
}

 vector<Component*> LED::GetListofNextGates()
{
	 vector<Component*> dummy;
	 return dummy;
}


InputPin* LED::GetInputPin(int & NoOfInputs)
{
	NoOfInputs=1;
	return m_InputPin;
}

OutputPin* LED::GetOutputpinCoorinates(int &x,int &y)
{
	return NULL;
}

OutputPin* LED::GetComponentOutputpinCoordinates(int &x , int &y)
{
		return NULL;
}

InputPin* LED::GetInputpinCoorinates(int &x,int &y ,int &i)
{
   if (x<=(m_GfxInfo.x1+(UI.LEDOFF_Width/2)+6) && x>=(m_GfxInfo.x1+(UI.LEDOFF_Width/2)-6) && y<=(m_GfxInfo.y2+6) && y>=(m_GfxInfo.y2-6))
   {
	   x=m_GfxInfo.x1+(UI.LEDOFF_Width/2);
	   y=m_GfxInfo.y2;
	   i = 1; 
	   return &(this->m_InputPin[0]);
   }
 
   return NULL;
}

InputPin* LED::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	if (index==1)
	{
	    x=m_GfxInfo.x1+(UI.LEDOFF_Width/2);
	   y=m_GfxInfo.y2;
	   return &(this->m_InputPin[0]);
	}
	return NULL;
}

void LED::Operate()
{

	if (GetInputPinStatus(1) == HIGH)
		StatusLED = HIGH;
	else StatusLED = LOW;
	
}

void LED::ResetStatus()
{
	StatusLED = LOW;
	m_InputPin->setStatus(LOW);

}


// Function Draw
// Draws 2-input AND gate
void LED::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	if (StatusLED == HIGH)
		pOut->DrawLEDON(m_GfxInfo,selected);
	else if (StatusLED == LOW)
		pOut->DrawLEDOFF(m_GfxInfo,selected);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);

}

void LED::DrawWithDisplacement(int x, int y ,Output* pOut)
{
	if (StatusLED == HIGH)
		pOut->DrawLEDON(m_GfxInfo,selected,x,y);
	else if (StatusLED == LOW)
		pOut->DrawLEDOFF(m_GfxInfo,selected,x,y);

}

//returns status of outputpin
int LED::GetOutPinStatus()
{
	return -1;
}


//returns status of Inputpin #n
int LED::GetInputPinStatus(int n)
{
	return m_InputPin->getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void LED::setInputPinStatus(int n, STATUS s)
{
	m_InputPin->setStatus(s);
}

void LED::Move(int x ,int y)
{
	m_GfxInfo.x1+=x;
	m_GfxInfo.x2+=x;
	m_GfxInfo.y1+=y;
	m_GfxInfo.y2+=y;

	Connection * inputconnection;
	
	if(m_InputPin->isconnected())
	{
		GetComponentInputpinCoordinates(x,y,1);
		inputconnection=m_InputPin->getconnection();
		if(inputconnection!=NULL)
		inputconnection->ChangeConnectionEndPoints(x,y);
	}
}

bool LED::Validate()//T
{
	if (m_InputPin->isconnected()==false)
		return false;

	return true;

}

void LED::Load(ifstream &inp)
{
	string label;
	int X1, Y1, X2, Y2, ID;
	GraphicsInfo GInfo;
	inp >> ID >> label >> X1 >> Y1;
	X2 = X1 + UI.LEDON_Width;
	Y2 = Y1 + UI.LEDON_Height;
	GInfo.x1 = X1; GInfo.x2 = X2; GInfo.y1 = Y1; GInfo.y2 = Y2;
	if (label == "$") label = " "; 
	this->SetID(ID);
	this->setLabel(label);
	this->setGraphicsInfo(GInfo);
}
void LED::Save(ofstream & out)
{
	out << "\nLED   ";
	out << "      " << GetID() << "      ";
	if (GetLabel().empty())
		out << "$";
	else out << GetLabel();
	out << "      " << m_GfxInfo.x1 << "      " << m_GfxInfo.y1;


}
Component* LED::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	LED* ptr = new LED(temp);
	ptr->setLabel(c->GetLabel());
	return ptr;
}


LED:: ~LED()
{
	delete m_InputPin;
}
