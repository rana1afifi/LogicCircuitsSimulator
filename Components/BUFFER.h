#ifndef _BUFFER_H
#define _BUFFER_H

/*
  Class BUFFER
  -----------
  represent the BUFFER gate
*/

#include "Gate.h"

class BUFFER:public Gate
{
public:
	BUFFER(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate();	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut);	//Draws 2-input gate

	void DrawWithDisplacement(int x, int y ,Output* pOut); //T

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	InputPin* GetInputpinCoorinates(int &x,int &y ,int &i);
	InputPin * GetComponentInputpinCoordinates(int &x , int &y ,int index); 
	void ResetStatus();
	bool Validate (); 
	virtual void Save(ofstream &out); 
	virtual Component* MakeCopy(Component*);  

};

#endif