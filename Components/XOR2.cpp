#include "XOR2.h"
#include<fstream>
XOR2::XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
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



InputPin* XOR2::GetInputpinCoorinates(int &x,int &y , int&i)
{
	if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.XOR2_Height/4)+6) && y>=(m_GfxInfo.y1+(UI.XOR2_Height/4)-6))
   {
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR2_Height/4);
	   i = 1; 
	   return &(this->m_InputPins[0]);
   }
   else if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.XOR2_Height*3/4)+6) && y>=(m_GfxInfo.y1+(UI.XOR2_Height*3/4)-6))
   {
	    x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR2_Height*3/4);
	   i = 2; 
	   return &(this->m_InputPins[1]);
   }
   return NULL;
}

InputPin* XOR2::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	if (index==1)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR2_Height/4);
	   return &(this->m_InputPins[0]);
	}
	else if (index==2)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XOR2_Height*3/4);
	   return &(this->m_InputPins[1]);
	}
	return NULL;
}

void XOR2::Operate()
{
	STATUS input1 =m_InputPins[0].getStatus();
	STATUS input2 =m_InputPins[1].getStatus();
	if(input1==input2) m_OutputPin.setStatus(LOW);
	else m_OutputPin.setStatus(HIGH);

	m_OutputPin.OperateTheConnections();

}
void XOR2::ResetStatus()
{
	m_InputPins[0].setStatus(LOW);
	m_InputPins[1].setStatus(LOW);
	m_OutputPin.setStatus(LOW);

}



// Function Draw
// Draws 2-input XOR gate
void XOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXOR2(m_GfxInfo,selected);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);
}

void XOR2::DrawWithDisplacement(int x, int y ,Output* pOut)
{
	pOut->DrawXNOR2(m_GfxInfo,selected,x,y);

}

//returns status of outputpin
int XOR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XOR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

bool XOR2::Validate ()
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


void XOR2::Save(ofstream &out)
{
	out << "\nXOR2  ";
	Gate::Save(out);

}
Component* XOR2::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	XOR2* ptr = new XOR2(temp, XOR2_FANOUT);
	ptr->setLabel(c->GetLabel());
	return ptr;
}