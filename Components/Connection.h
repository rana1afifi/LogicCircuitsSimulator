#pragma once
#include "component.h"
#include "InputPin.h"
#include "OutputPin.h"
#include <vector>
#include "..\ApplicationManager.h"
class Connection :	public Component
{
	//Component*	SrcCmpnt;	//Connection source component
	//Component*	DstCmpnt;	//Connection Destination component
	//int		DstPin;		//The Input pin to which this connection is linked
	OutputPin* SrcPin;	//The Source pin of this connection (an output pin of certain Component)
	InputPin* DstPin;	//The Destination pin of this connection (an input pin of certain Component)
	STATUS status;
	vector<GraphicsInfo> connection;
	
public:
	//Connection(const GraphicsInfo &r_GfxInfo, Component *pS=NULL,Component *pD=NULL, int Pin=0);
	Connection(const GraphicsInfo &r_GfxInfo, OutputPin *pSrcPin,InputPin *pDstPin);

	virtual void Operate() ;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut);	//for each component to Draw itself

	void DrawWithDisplacement(int x, int y ,Output* pOut); 

	void setSourcePin(OutputPin *pSrcPin);
	void setDestPin(InputPin *pDstPin);
	OutputPin* getSourcePin();
	InputPin* getDestPin();

	OutputPin* GetOutputpinCoorinates(int &x,int &y);

	InputPin* GetInputpinCoorinates(int &x,int &y ,int&i);

	InputPin * GetComponentInputpinCoordinates(int &x , int &y ,int index); 

	OutputPin* GetComponentOutputpinCoordinates(int &x , int &y); 

	virtual int GetOutPinStatus();	//returns status of outputpin if LED, return -1
	virtual int GetInputPinStatus(int n);	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s);	//set status of Inputpin # n, to be used by connection class.
	bool FindConnection(int x, int y);

	void Move(int x ,int y); 

	void ChangeConnectionEndPoints(int x , int y); 
	void ChangeConnectionStartPoints(int x, int y); 

	void SetStatus(STATUS status);
	STATUS GetStatus();
	void ResetStatus();


	bool Validate();//T
	vector<Component*> GetListofNextGates();

	virtual void Load(ifstream & inp); 
	virtual void Save(ofstream &out); 
	virtual Component* MakeCopy(Component*);  
	bool AreaOccupied ( const GraphicsInfo & );


	
	~Connection();
};
