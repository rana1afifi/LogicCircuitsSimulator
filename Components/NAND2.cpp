#include "NAND2.h"
#include<fstream>
NAND2::NAND2(const GraphicsInfo &r_GfxInfo, int r_FanOut) :Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	selected =false;
	level =-1;
	visited = false;
	Count++;
	ID = Count; 
}


void NAND2::Operate()
{
	STATUS input1 =m_InputPins[0].getStatus();
	STATUS input2 =m_InputPins[1].getStatus();
	if(input1==LOW || input2==LOW) m_OutputPin.setStatus(HIGH);
	else m_OutputPin.setStatus(LOW);

	m_OutputPin.OperateTheConnections();

}

void NAND2::ResetStatus()
{
	m_InputPins[0].setStatus(LOW);
	m_InputPins[1].setStatus(LOW);
	m_OutputPin.setStatus(LOW);

}

InputPin* NAND2::GetInputpinCoorinates(int &x,int &y ,int&i)
{
	if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.NAND2_Height/4)+6) && y>=(m_GfxInfo.y1+(UI.NAND2_Height/4)-6))
   {
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.NAND2_Height/4);
	   i = 1; 
	   return &(this->m_InputPins[0]);
   }
   else if (x<=(m_GfxInfo.x1+6) && x>=(m_GfxInfo.x1-6) && y<=(m_GfxInfo.y1+(UI.NAND2_Height*3/4)+6) && y>=(m_GfxInfo.y1+(UI.NAND2_Height*3/4)-6))
   {
	    x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.NAND2_Height*3/4);
	   i = 2;
	   return &(this->m_InputPins[1]);
   }
   return NULL;
}

InputPin* NAND2::GetComponentInputpinCoordinates(int &x, int &y, int index)
{
	if (index==1)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.NAND2_Height/4);
	   return &(this->m_InputPins[0]);
	}
	else if (index==2)
	{
	   x=m_GfxInfo.x1;
	   y=m_GfxInfo.y1+(UI.NAND2_Height*3/4);
	   return &(this->m_InputPins[1]);
	}
	return NULL;
}

// Function Draw
// Draws 2-input NAND gate
void NAND2::Draw(Output* pOut)
{
	//Call output class and pass gate drawing info to it.
	pOut->DrawNAND2(m_GfxInfo,selected);
	int x = GetGraphicsInfo()->x1;
	int y = (GetGraphicsInfo()->y1) - 20;
	pOut->PrintMsgonArea(GetLabel(), x, y);
}

void NAND2::DrawWithDisplacement(int x, int y ,Output* pOut)
{
	pOut->DrawNAND2(m_GfxInfo,selected,x,y);

}

//returns status of outputpin
int NAND2::GetOutPinStatus()
{
	return m_OutputPin.getStatus();
}


//returns status of Inputpin #n
int NAND2::GetInputPinStatus(int n)
{
	return m_InputPins[n - 1].getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin ot HIGH or LOW
void NAND2::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n - 1].setStatus(s);
}

bool NAND2::Validate ()
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


void NAND2::Save(ofstream &out)
{
	out << "\nNAND2 ";
	Gate::Save(out);

}
Component* NAND2::MakeCopy(Component* c)
{
	GraphicsInfo temp;
	temp.x1 = (c->GetGraphicsInfo())->x1;
	temp.x2 = (c->GetGraphicsInfo())->x2;
	temp.y1 = (c->GetGraphicsInfo())->y1;
	temp.y2 = (c->GetGraphicsInfo())->y2;
	NAND2* ptr = new NAND2(temp, NAND2_FANOUT);
	ptr->setLabel(c->GetLabel());
	return ptr;
}




