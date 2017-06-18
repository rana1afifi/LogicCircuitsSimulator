#ifndef _LED_H
#define _LED_H

/*
Class LED
-----------
represent the LED
*/

#include "Component.h"
#include "InputPin.h"
#include "..\Defs.h"
#include "..\ApplicationManager.h"

class LED :public Component
{
	InputPin * m_InputPin;
	STATUS StatusLED;
	
public:
	LED(const GraphicsInfo &r_GfxInfo);
	virtual void Operate();	//Calculates the output of the  LED
	virtual void Draw(Output* pOut);	//Draws LED ON and OFF

	void DrawWithDisplacement(int x, int y ,Output* pOut);

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	InputPin* GetInputPin(int & NoOfInputs);
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	InputPin* GetInputpinCoorinates(int &x,int &y , int &i);

	OutputPin* GetOutputpinCoorinates(int &x,int &y);

	OutputPin* GetComponentOutputpinCoordinates(int &x , int &y);  

	InputPin* GetComponentInputpinCoordinates(int &x, int &y, int index); 
	 vector<Component*> GetListofNextGates(); 
	void Move(int x ,int y);

	void ResetStatus();
	bool Validate();//T
	virtual void Load(ifstream & inp); 
	virtual void Save(ofstream & out); 
	virtual Component* MakeCopy(Component*);  
	bool AreaOccupied ( const GraphicsInfo & );

	 ~LED();
};

#endif