#include "BUFFER.h"
#include <fstream>
BUFFER::BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
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



InputPin* BUFFER::GetInputpinCoorinates(int &x,int &y ,int &i)
{
	if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.Buffer_Height/2)+6) && y>=(m_GfxInfo.y1+(UI.Buffer_Height/2)-6))
   {
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.Buffer_Height/2);
	   i = 1; 
	   return &(this->m_InputPins[0]);
   }
   return NULL;
}

InputPin* BUFFER::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	if (index==1)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.Buffer_Height/2);
	   return &(this->m_InputPins[0]);
	}
	return NULL;
}

void BUFFER::Operate()
{
	STATUS input1 =m_InputPins[0].getStatus();
	if(input1==HIGH) m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);

	m_OutputPin.OperateTheConnections();

}
void BUFFER::ResetStatus()
{
	m_InputPins[0].setStatus(LOW);
	m_OutputPin.setStatus(LOW);

}


// Function Draw
// Draws BUFFER gate
void BUFFER::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawBuffer(m_GfxInfo,selected);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);
}

void BUFFER::DrawWithDisplacement(int x, int y ,Output* pOut) //T
{
	pOut->DrawBuffer(m_GfxInfo,selected,x,y);

}

//returns status of outputpin
int BUFFER::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int BUFFER::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void BUFFER::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

bool BUFFER::Validate ()
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



void BUFFER::Save(ofstream &out)
{
	out << "\nBUFFER";
	Gate::Save(out);

}
Component* BUFFER::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	BUFFER* ptr = new BUFFER (temp, BUFFER_FANOUT);
	ptr->setLabel(c->GetLabel());
	return ptr;
}

