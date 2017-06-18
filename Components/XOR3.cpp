#include "XOR3.h"
#include<fstream>
XOR3::XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	selected =false ; 
	level =-1;
	visited = false;
	Count++;
	ID = Count; 
}



InputPin* XOR3::GetInputpinCoorinates(int &x,int &y ,int&i)
{
	if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.XOR3_Height/4)+6) && y>=(m_GfxInfo.y1+(UI.XOR3_Height/4)-6))
   {
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR3_Height/4);
	   i = 1; 
	   return &(this->m_InputPins[0]);
   }
	else if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.XOR3_Height/2)+6) && y>=(m_GfxInfo.y1+(UI.XOR3_Height/2)-6))
   {
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR3_Height/2);
	   i = 2; 
	   return &(this->m_InputPins[1]);
   }
	else if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.XOR3_Height*3/4)+6) && y>=(m_GfxInfo.y1+(UI.XOR3_Height*3/4)-6))
   {
	    x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+(UI.XOR3_Height*3/4);
		i = 3; 
	   return &(this->m_InputPins[2]);
   }
   return NULL;
}

InputPin* XOR3::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	if (index==1)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR3_Height/4);
	   return &(this->m_InputPins[0]);
	}
	else if (index==2)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR3_Height/2);
	   return &(this->m_InputPins[1]);
	}
	else if (index==3)
	{   
	    x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+(UI.XOR3_Height*3/4);
	   return &(this->m_InputPins[2]);
	}
	return NULL;
}

void XOR3::Operate()
{
	int countHigh = 0;
	for (int i = 0; i < 3; i++)
	{
		if (m_InputPins[i].getStatus() == HIGH)
			countHigh++;
	}
	if ((countHigh % 2) != 0)
		m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);

	m_OutputPin.OperateTheConnections();

}

void XOR3::ResetStatus()
{
	m_InputPins[0].setStatus(LOW);
	m_InputPins[1].setStatus(LOW);
	m_InputPins[2].setStatus(LOW);
	m_OutputPin.setStatus(LOW);

}


// Function Draw
// Draws XOR3 gate
void XOR3::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR3(m_GfxInfo,selected);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);
}

void XOR3::DrawWithDisplacement(int x, int y ,Output* pOut)
{
	pOut->DrawXOR3(m_GfxInfo,selected,x,y);
}


//returns status of outputpin
int XOR3::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR3::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR3::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

bool XOR3::Validate ()
{
	if (m_OutputPin.isconnected()==false)
		return false;

	for (int i=0 ; i<m_Inputs;i++)
	{
		if(m_InputPins[i].isconnected()==false)
		return false;
	}
	return true;
}


void XOR3::Save(ofstream &out)
{
	out << "\nXOR3 ";
	Gate::Save(out);

}
Component* XOR3::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	XOR3* ptr = new XOR3(temp, XOR3_FANOUT);
	ptr->setLabel(c->GetLabel());
	return ptr;
}