#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "Defs.h"
#include "GUI\Output.h"
#include "GUI\Input.h"
#include "Actions\Action.h"
#include "Components\Component.h"
#include <vector>
//Main class that manages everything in the application.
class ApplicationManager
{

	enum { MaxCompCount = 200 };	//Max no of Components	

private:
	int CompCount;		//Actual number of Components
	Component* CompList[MaxCompCount];	//List of all Components (Array of pointers)
	int nComponents; // no of  components without connections 
	Output* OutputInterface; //pointer to the Output Clase Interface
	Input* InputInterface; //pointer to the Input Clase Interface
    vector <Component*> SelectedList;
	ActionType OldActType;
	bool floatingpins;
	bool feedback;
	bool canbesimulated;
	
	Component* CopiedComponent; 
	Component* CutComponent;


public:	
	ApplicationManager(); //constructor

	//Reads the required action from the user and returns the corresponding action type
	ActionType GetUserAction(int &x, int &y);
	
	//Creates an action and executes it
	void ExecuteAction(ActionType,int &x, int &y);
	
	void UpdateInterface();	//Redraws all the drawing window
	void UpdateInterfacewithToolbar();
	Component * FindComponent(int x, int y , int &index,bool searchselected = false); //T 
	OutputPin* getoutputpin(int &x ,int &y);
	InputPin* getinputpin(int &x ,int &y);
	//Gets a pointer to Input / Output Object
	Output* GetOutput();
	Input* GetInput();
	// return the selected list
	vector<Component*> GetSelectedList(); //T
   
	
    void DrawDisplacedComponent(int x,int y,const GraphicsInfo &info); ///  T
	
	bool GetFloatingPinsStatus();
	bool GetFeedbackStatus();
	void SetFeedbackStatus(bool);
	void SetFloatingPinstatus(bool);
	bool GetSimulationStatus();
	void SetSimulationstatus(bool);
	
	void ValidateandSetCiruitLevel();
	void ResetCircuitLevels();

	unsigned int GetSelectedSize();	//Adds a new component to the list of components

	void AddComponent(Component* pComp);
	
	//Removes a component to the list of components
	void RemoveComponent(Component* pComp);

	//Removes all component from the list of components
	void DeleteComponents(); /////D

	void SelectRelatedComp(); ///////D 

	//Sets the Selected list
	void SetSelected(vector<Component*>);

	void UnSelectAll();

	void SortComponentList(); //T

	void FeedBackCheck(Component * Comp , int lvl);
	void OperateCircuit();
	void ResetCircuitStatus();
	void UnProbeAll();
	vector<Component*> GetListOfSwitches();
	vector<Component*> GetListofLeds();
	
	bool isEmpty();
	void LoadFn(ifstream& inp);
	void SaveFn(ofstream  &out);
	Component *FindComponentID(int ID);
	bool Reset();
	int GetnComponents(); 
	Component* GetCopied();
	void SetCopied(Component* c); 
	Component* GetCut(); 
	void SetCut(Component* c);
	int getNumberOfInputs(); //get Number of inputs in the circuit
	int getNumberOfOuputs(); //get Number of Outputs in the circuit
	~ApplicationManager();
};

#endif