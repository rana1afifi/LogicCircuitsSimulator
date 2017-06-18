#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"
#include "..\ApplicationManager.h"
class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate.
public:
	Gate(int r_Inputs, int r_FanOut);

    OutputPin*  GetOutputpinCoorinates(int &x,int &y);
	OutputPin* GetOutputPin();
	InputPin* GetInputPin(int & NoOfInputs);
	virtual InputPin* GetInputpinCoorinates(int &x,int &y , int&i)=0;
	OutputPin* GetComponentOutputpinCoordinates(int &x , int &y) ; //T
	virtual vector<Component*> GetListofNextGates();
	void Move(int x ,int y);  
	virtual bool Validate()=0;
	virtual void Load(ifstream & inp); 
	virtual void Save(ofstream & out); 
	virtual Component* MakeCopy(Component*);  
	

	~Gate();
	

};

#endif
