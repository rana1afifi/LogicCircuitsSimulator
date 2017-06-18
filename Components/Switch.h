#pragma once
#include "Component.h"
#include "OutputPin.h"
#include "..\ApplicationManager.h"
class Switch :public Component
{
	OutputPin * m_OutputPin;	// output pin
	STATUS SwitchStatus;

public:
	Switch(const GraphicsInfo &r_GfxInfo , int r_FanOut );
	

	virtual void Operate() ;  	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself

	void DrawWithDisplacement(int x, int y ,Output* pOut);

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n = 0); //	 return -1
	OutputPin* GetOutputPin();
	virtual void setInputPinStatus(int n, STATUS s);//set status of Inputpin # n, to be used by connection class.
	InputPin* GetInputpinCoorinates(int &x,int &y ,int&i);
	OutputPin* GetOutputpinCoorinates(int &x,int &y);
	InputPin* GetComponentInputpinCoordinates(int &x, int &y, int index);
	OutputPin* GetComponentOutputpinCoordinates(int &x , int &y);
	void Move(int x ,int y);
	vector<Component*> GetListofNextGates();
	void ResetStatus();
	bool Validate();//T
	void SetSwitchstatus(STATUS ) ;
	STATUS GetSwitchStatus();
	virtual void Load(ifstream & inp); 
	virtual void Save(ofstream & out); 
	virtual Component* MakeCopy(Component*);  

	~Switch ();
};

