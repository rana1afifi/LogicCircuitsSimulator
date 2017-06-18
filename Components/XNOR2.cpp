#include "XNOR2.h"
#include<fstream>
XNOR2::XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
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

InputPin* XNOR2::GetInputpinCoorinates(int &x,int &y ,int&i)
{
	if (x<=m_GfxInfo.x1+6 && x>=m_GfxInfo.x1-6 && y<=(m_GfxInfo.y1+(UI.XNOR2_Height/4)+6) && y>=(m_GfxInfo.y1+(UI.XNOR2_Height/4)-6))
   {
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XNOR2_Height/4);
	   i = 1; 
	   return &(this->m_InputPins[0]);
   }
	else if (x<=m_GfxInfo.x1+6 && x>=m_GfxInfo.x1-6 && y<=(m_GfxInfo.y1+(UI.XNOR2_Height*3/4+6)) && y>=(m_GfxInfo.y1+(UI.XNOR2_Height*3/4)-6))
   {
	    x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+(UI.XNOR2_Height*3/4);
		i = 2; 
	   return &(this->m_InputPins[1]);
   }
   return NULL;
}

InputPin* XNOR2::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	if (index==1)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XNOR2_Height/4);
	   return &(this->m_InputPins[0]);
	}
	else if (index==2)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.XNOR2_Height*3/4);
	   return &(this->m_InputPins[1]);
	}
	return NULL;
}

void XNOR2::Operate()
{

	STATUS input1 =m_InputPins[0].getStatus();
	STATUS input2 =m_InputPins[1].getStatus();
	
	if((input1==LOW && input2==LOW) || (input1==HIGH && input2==HIGH)  ) m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);

	m_OutputPin.OperateTheConnections();

}

void XNOR2::ResetStatus()
{
	m_InputPins[0].setStatus(LOW);
	m_InputPins[1].setStatus(LOW);
	m_OutputPin.setStatus(LOW);

}


// Function Draw
// Draws 2-input AND gate
void XNOR2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawXNOR2(m_GfxInfo,selected);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);
}

void XNOR2::DrawWithDisplacement(int x, int y ,Output* pOut)
{
	pOut->DrawXNOR2(m_GfxInfo,selected,x,y);

}

//returns status of outputpin
int XNOR2::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int XNOR2::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void XNOR2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

bool XNOR2::Validate ()
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


void XNOR2::Save(ofstream &out)
{
	out << "\nXNOR2 ";
	Gate::Save(out);

}
Component* XNOR2::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	XNOR2* ptr = new XNOR2(temp, XNOR2_FANOUT);
	ptr->setLabel(c->GetLabel());
	return ptr;
}