#ifndef _XOR2_H
#define _XOR2_H

/*
  Class XOR2
  -----------
  represent the XOR2 gate
*/

#include "Gate.h"

class XOR2:public Gate
{
public:
	XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the XOR gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	void XOR2::DrawWithDisplacement(int x, int y ,Output* pOut);

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	InputPin* GetInputpinCoorinates(int &x,int &y , int&i);
	InputPin * GetComponentInputpinCoordinates(int &x , int &y ,int index); 
	void ResetStatus();
	bool Validate ();
	
	virtual void Save(ofstream & out); 
	virtual Component* MakeCopy(Component*);  
};

#endif