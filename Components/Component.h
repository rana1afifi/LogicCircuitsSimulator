#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "OutputPin.h"
#include "InputPin.h"
#include <vector>
#include "..\ApplicationManager.h"

//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
 
protected:
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool selected;
	int level;
	bool visited;
	int ID;
	static int Count; 
public:
	Component(const GraphicsInfo &r_GfxInfo);
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself

	virtual vector<Component*> GetListofNextGates()=0;

	virtual OutputPin* GetOutputpinCoorinates(int &x,int &y)=0;

	virtual InputPin* GetInputpinCoorinates(int &x,int &y , int&i)=0;

	virtual OutputPin* GetComponentOutputpinCoordinates(int &x , int &y)=0;  

	virtual InputPin * GetComponentInputpinCoordinates(int &x , int &y,int index)=0;  

	void SetSelected (bool x);

	bool IsSelected();
	virtual void ResetStatus()=0;

	virtual int GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1

	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.

	GraphicsInfo* GetGraphicsInfo();
    void setGraphicsInfo(const GraphicsInfo &r_GfxInfo);

	void setLabel(string label);  //Set the label of a component
	string GetLabel();
	virtual void DrawWithDisplacement(int x, int y ,Output* pOut)=0; 
	virtual void Move(int x ,int y)=0;
	virtual bool Validate()=0; 
	bool getvisitedstatus();
	void setvisitedstatus(bool xVisited);
	void SetLevel(int ); 
	int GetLevel(); 

	void SetID(int id); 
	int GetID(); 
	virtual void Load(ifstream & inp) = 0; 
	virtual void Save(ofstream &out) = 0; 
	virtual Component* MakeCopy(Component*) = 0; 
	

	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
