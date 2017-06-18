#include "ApplicationManager.h"
#include "Actions\AddANDgate2.h"
#include "Actions\AddANDgate3.h"
#include "Actions\AddNORgate2.h"
#include "Actions\AddXNORgate2.h"
#include "Actions\AddConnection.h"
#include "Actions\AddBUFFERgate.h"
#include "Actions\AddINVERTERgate.h"
#include "Actions\AddLED.h"
#include "Actions\AddXORgate2.h"
#include "Actions\AddXORgate3.h"
#include "Actions\AddORgate2.h"
#include "Actions\AddNANDgate2.h"
#include "Actions\AddNORgate3.h"
#include "Actions\AddSwitch.h"
#include "Actions\Delete.h"
#include "Actions\MultiSelect.h"
#include "Actions\Move.h"
#include "Actions\Select.h"
#include"Actions\Label.h"
#include"Actions\Edit.h"
#include"Actions\validate.h"
#include"Actions\ChangeToSimulation.h"
#include"Actions\Load.h"
#include"Actions\Save.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Paste.h"
#include "Actions\Simulate.h"
#include "Actions\Probe.h"
#include "Actions\\TruthTable.h"
#include "Actions\\ChangeToDesign.h"
#include "Actions\\Exit.h"
#include <string>
#include<fstream>
ApplicationManager::ApplicationManager()
{
	CompCount = 0; nComponents = 0; 
	
	for(int i=0; i<MaxCompCount; i++)
		CompList[i] = NULL;

	//Creates the Input / Output Objects & Initialize the GUI
	OutputInterface = new Output();
	InputInterface = OutputInterface->CreateInput();	
	floatingpins=false;
	feedback=false;
	canbesimulated=true;
	CutComponent = NULL; 
	CopiedComponent = NULL; 
}
////////////////////////////////////////////////////////////////////
void ApplicationManager::AddComponent(Component* pComp)
{
	
	Component* connection = dynamic_cast<Connection*>(pComp); 
	if (connection == NULL) nComponents++; 
	CompList[CompCount++] = pComp;		
	
}
	

////////////////////////////////////////////////////////////////////
void ApplicationManager::RemoveComponent(Component* Comp)
{
	Component*x;
	for(int i=0; i<CompCount; i++)
	{
		if(CompList[i]==Comp)
		{
			x=CompList[i];
			CompList[i]=CompList[CompCount-1];
			CompList[CompCount-1]=NULL;
			CompCount--;
		}
	}
}

////////////////////////////////////////////////////////////////////
void ApplicationManager::SetSelected(vector<Component*> SelectedComp)
{
	SelectedList=SelectedComp;
}
////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
void ApplicationManager::UnSelectAll()
{
	for(UINT i=0; i<SelectedList.size(); i++)
	{
		SelectedList[i]->SetSelected(false);
	}
	SelectedList.clear();
	UpdateInterface();
}
////////////////////////////////////////////////////////////////////
ActionType ApplicationManager::GetUserAction(int &x, int &y)
{
	//Call input to get what action is reuired from the user
	return InputInterface->GetUserAction(x, y); 	
}
////////////////////////////////////////////////////////////////////
Component* ApplicationManager::FindComponent(int x, int y , int &index,bool searchselected)
{
	if(searchselected==false)
	{
		for (int i = 0; i<CompCount; i++)
	   {
		Connection* Conn=dynamic_cast<Connection*>(CompList[i]);
		if(Conn)
		{
			bool IsSelectedConn=Conn->FindConnection(x, y);
			if(IsSelectedConn) return CompList[i];
		}
		else
	    { if((CompList[i]->GetGraphicsInfo()->x1) < x && (CompList[i]->GetGraphicsInfo()->x2) > x && (CompList[i]->GetGraphicsInfo()->y1) < y && (CompList[i]->GetGraphicsInfo()->y2) >y)
			{
				index = i;
 				return CompList[i];
		    }
		}
	  }
	index = -1 ;
	return NULL;
	}
	else
		{
      for(UINT i = 0; i<SelectedList.size(); i++)
	 {
		 Connection* Conn=dynamic_cast<Connection*>(SelectedList[i]);
		if(Conn)
		{
			return NULL; // ad i dont need to get the selected wire in any class // in move i must click on gate to move it 
			
		}
		else
		 if ((SelectedList[i]->GetGraphicsInfo()->x1) < x && (SelectedList[i]->GetGraphicsInfo()->x2) > x && (SelectedList[i]->GetGraphicsInfo()->y1) < y && (SelectedList[i]->GetGraphicsInfo()->y2) >y)
			{
				index = i;
 				return SelectedList[i];
		    }
	 } 
	index = -1 ;
	return NULL;
	}
	
}

/////////////////////////////////////////////////////////////////
void ApplicationManager::DeleteComponents()
{
	Component* x;
	for(int i=0; i<CompCount; i++)
	{ 
		if(CompList[i]->IsSelected())
		{
			if (dynamic_cast<Connection*>(CompList[i])==NULL)
				nComponents--;
			x=CompList[i];
			CompList[i]=CompList[CompCount-1];
			CompList[CompCount-1]=NULL;
			delete x;
			x=NULL;
			i--;
			CompCount--;
			
		}
	}
	SelectedList.clear();
	UpdateInterface();
	return;
}

void ApplicationManager::SelectRelatedComp()
{
	for(int i=0; i<CompCount; i++)
	{
		Connection* xConn=dynamic_cast<Connection*>(CompList[i]);
		if(xConn)
		{
			OutputPin* out=xConn->getSourcePin();
			InputPin* In=xConn->getDestPin();
			if(xConn->IsSelected()==false)
			{
			 if(out->getComponent()->IsSelected())
			{
				xConn->SetSelected(true);
				SelectedList.push_back(xConn);
			}

			 else if(In->getComponent()->IsSelected())
			{
				xConn->SetSelected(true);
				SelectedList.push_back(xConn);
			}
			}
			
		}
	}
	
}

////////////////////////////////////////////////////////////////////////

OutputPin* ApplicationManager::getoutputpin(int &x ,int &y)
{
	OutputPin * pin =NULL;

	for(int i=0; i<CompCount; i++)
	{ 
		pin=CompList[i]->GetOutputpinCoorinates(x,y);
		if (pin !=NULL)
		{
			return pin;
		}

	}
	return NULL;
}
////////////////////////////////////////////////////////////////////

InputPin* ApplicationManager::getinputpin(int &x , int &y)
{   int index;
	InputPin * pin =NULL;
	for(int i=0; i<CompCount; i++)
	{ 
		pin=CompList[i]->GetInputpinCoorinates(x,y,index);
		if (pin !=NULL)
		{
			return pin;
		}
	}
	return NULL;
}
////////////////////////////////////////////////////////////////////

void ApplicationManager::ExecuteAction(ActionType ActType, int &x, int &y)
{
	Action* pAct = NULL;
	bool AddComp = false;
	switch (ActType)
	{
	case ADD_AND_GATE_2:
		pAct = new AddANDgate2(this);
		AddComp = true;
		break;

	case ADD_AND_GATE_3:
		pAct = new AddANDgate3(this);
		AddComp = true;
		break;

	case ADD_XNOR_GATE_2:
		pAct = new AddXNORgate2(this);
		AddComp = true;
		break;

	case ADD_NOR_GATE_2:
		pAct = new AddNORgate2(this);
		AddComp = true;
		break;

	case ADD_CONNECTION:
		pAct = new AddConnection(this);
		AddComp = true;
		break;
	case ADD_Buff:
		pAct = new AddBUFFERgate(this);
		AddComp = true;
		break;

	case ADD_INV:
		pAct = new AddINVERTERgate(this);
		AddComp = true;
		break;

	case ADD_LED:
		pAct = new AddLED(this);
		AddComp = true;
		break;
	case ADD_OR_GATE_2:
		pAct = new AddORgate2(this);
		AddComp = true;
		break;
	case ADD_XOR_GATE_2:
		pAct = new AddXORgate2(this);
		AddComp = true;
		break;
	case ADD_XOR_GATE_3:
		pAct = new AddXORgate3(this);
		AddComp = true;
		break;
	case ADD_NOR_GATE_3:
		pAct = new AddNORgate3(this);
		AddComp = true;
		break;
	case ADD_NAND_GATE_2:
		pAct = new AddNANDgate2(this);
		AddComp = true;
		break;
	case ADD_Switch:
		pAct = new AddSwitch(this);
		AddComp = true;
		break;
	case MULTISELECT:
		pAct = new MultiSelect(this);
		UnSelectAll();
		break;
	case SELECT:
	{
				   Select* pSelect = new Select(this);
				   pSelect->SetX(x);
				   pSelect->SetY(y);
				   pAct = pSelect;
				   break;
	}
	case DEL:
		pAct = new Delete(this);
		break;
	case MOVE:
		pAct = new Move(this);
		break;
	case ADD_Label:
		pAct = new Label(this);
		break;
	case EDIT_Label:
		pAct = new Edit(this);
		break;
	case SIM_MODE:
	{ 	UnSelectAll();
		pAct = new validate(this);
     	pAct->Execute();
	    delete pAct;
	    pAct = new ChangeToSimulation(this);
		pAct->Execute();
		delete pAct;
		pAct=new Simulate(this);
	    break;
	}
		case LOAD: 
		pAct = new Load(this);
		break;
	case SAVE:
		pAct = new Save(this);
		break; 
	case COPY: 
		pAct = new Copy(this);
		break; 
	case CUT: 
		pAct = new Cut(this); 
		break; 
	case PASTE: 
		pAct = new Paste(this); 
		break; 
	case Change_Switch:
		 {
			Simulate* pSimulate = new Simulate(this);
			pSimulate->SetX(x);
			pSimulate->SetY(y);
			pAct = pSimulate;
			break;
		 }
	case PROBE:
		pAct = new Probe(this);
		break;
	case Create_TruthTable:
	{
		pAct = new TruthTable(this);
		pAct->Execute();
		delete pAct;
		pAct = new Simulate(this);
		break;
	}
	case DSN_MODE:
	{
		pAct = new ChangeToDesign(this);
		break;
	}
	case EXIT:		
		pAct= new Exit(this);
		break;
	}
	if (pAct)
	{
		if(SelectedList.size()!=0 && AddComp==true)
			UnSelectAll();
		pAct->Execute();
	
		x = 0; y = 0;
		if (SelectedList.size() != 0)
		{
			if (ActType == SELECT)
			{
				Select* pSelect = dynamic_cast<Select*>(pAct);
				x = pSelect->GetX();
				y = pSelect->GetY();
			}
			else if (ActType == MULTISELECT)
			{
				MultiSelect* pMulti = dynamic_cast<MultiSelect*>(pAct);
				x = pMulti->GetX();
				y = pMulti->GetY();
			}
		}

	}
	delete pAct;
	pAct = NULL;
}

////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterfacewithToolbar()
{
	OutputInterface->SetWindowBuffer(true);
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface);
	if (UI.AppMode==DESIGN)
		OutputInterface->CreateDesignToolBar();
	else 
		OutputInterface->CreateSimulationToolBar();
	OutputInterface->UpdateBuffer();

}
void ApplicationManager::UpdateInterface()
{    
	
	OutputInterface->ClearDrawingArea();
	for(int i=0; i<CompCount; i++)
		CompList[i]->Draw(OutputInterface);

}

////////////////////////////////////////////////////////////////////
Input* ApplicationManager::GetInput()
{
	return InputInterface;
}


////////////////////////////////////////////////////////////////////
Output* ApplicationManager::GetOutput()
{
	return OutputInterface;
}

////////////////////////////////////////////////////////////////////


vector<Component*> ApplicationManager::GetSelectedList()
{
	return SelectedList;

}


/////////////////////////////////////////////////////////////////////
void ApplicationManager::DrawDisplacedComponent(int x, int y, const GraphicsInfo & info) //T
{
	OutputInterface->ClearDrawingArea();
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->IsSelected() == false || dynamic_cast<Connection*>(CompList[i]))
		{
			CompList[i]->Draw(OutputInterface);
		}
	}
	for (UINT i = 0; i < SelectedList.size(); i++)
	{
		SelectedList[i]->DrawWithDisplacement(x, y, OutputInterface);
	}
	OutputInterface->DrawSelectedRectangle(info, x, y);


}

/////////////////////////////////////////////////////////////////////


bool ApplicationManager::GetFloatingPinsStatus ()
{
	return floatingpins;
}
bool ApplicationManager::GetFeedbackStatus()
{
	return feedback;
}
void  ApplicationManager::SetFeedbackStatus(bool Status)
{
	feedback=Status;
}
void  ApplicationManager::SetFloatingPinstatus(bool Status)
{
	floatingpins = Status;
}

bool ApplicationManager::GetSimulationStatus()
{
	return canbesimulated;
}
void ApplicationManager::SetSimulationstatus(bool status)
{
	canbesimulated = status;
}


void ApplicationManager::ResetCircuitLevels()
{
	for (int i =0; i<CompCount;i++)
	{
		if(dynamic_cast <Connection*>(CompList[i]))
			CompList[i]->SetLevel(1000); // so it is always at the end of the array when sorting 
		else
			CompList[i]->SetLevel(-1);
	}
}



void ApplicationManager::ValidateandSetCiruitLevel()
{
	int numofleds=getNumberOfOuputs();
	int numofswitches=getNumberOfInputs();

	if (numofleds ==0 || numofswitches==0)
		return;

	for (int i = 0; i<CompCount ; i++)
	{
		if (CompList[i]->Validate()==false)
		{
			floatingpins = true;
			break;
		}
	}
	///////////////////////////// checking feedback while setting their levels 
	int z=0;
	Component *temp;
	for (int i=0;i<CompCount;i++)
	{
		if (dynamic_cast<Switch*>(CompList[i]))
		{   CompList[i]->SetLevel(0);
			temp=CompList[z];
			CompList[z]=CompList[i];
			CompList[i]=temp;
			z++;
		}
	}
 
	for (int i=0 ; i<CompCount;i++)
	{   
		FeedBackCheck(CompList[i],1);
	}
	
}

void ApplicationManager:: FeedBackCheck(Component * Comp , int lvl)
{
	
	if (dynamic_cast<LED *>(Comp))
	{
		return;
	}
	if (Comp->getvisitedstatus()==true)
	{   feedback = true;
		ResetCircuitLevels();
		return;
	}
	Comp->setvisitedstatus(true);
	vector<Component*> cComponnent = Comp->GetListofNextGates();
	
	for (UINT i=0 ; i < cComponnent.size(); i++)
	{
		cComponnent[i]->SetLevel(lvl);
		FeedBackCheck(cComponnent[i],++lvl);
	}
	Comp->setvisitedstatus(false);
}

void ApplicationManager::SortComponentList()
{
	int index;
	Component * temp;
	
	for (int i=1;i<CompCount;i++)
	{
		index = i;
		while (index > 0 && CompList[index-1]->GetLevel() > CompList[index]->GetLevel()) 
         {
		 temp = CompList[index];
		 CompList[index] = CompList[index-1];
         CompList[index-1] = temp;
		 index--;
		}
	}
}

void ApplicationManager::UnProbeAll()
{
	for (int i = 0; i < CompCount; i++)
	{
		Connection* Conn = dynamic_cast<Connection*>(CompList[i]);
		if (Conn)
		{
			Conn->SetStatus(LOW);
		}
	}
}


void ApplicationManager::OperateCircuit()
{
	Connection* temp;
	for (int i =0 ; i<CompCount;i++)
	{
		temp=dynamic_cast<Connection*>(CompList[i]);
		if (temp)
			break;
		CompList[i]->Operate();
	}
}

void ApplicationManager::ResetCircuitStatus()
{
	for (int i=0;i<CompCount;i++)
	{
		CompList[i]->ResetStatus();
	}
}

Component * ApplicationManager::FindComponentID(int ID) // Rana 
{
	for (int i = 0; i < CompCount; i++)
	{
		if (CompList[i]->GetID() == ID)
			return CompList[i];
	}
	return NULL;
}

 
void ApplicationManager::LoadFn(ifstream& inp) //Rana`
{
	int count;     inp >> count;
	string type;
	
	GraphicsInfo GInfo;
	GInfo.x1 = 0; GInfo.y1 = 0; GInfo.x2 = 0; GInfo.y2 = 0;
	for (int i = 0; i <count; i++)
	{
		Component* ptr; 
		inp >> type; 
		if (type == "AND2")
		{  ptr = new AND2(GInfo, AND2_FANOUT);		}

		else if (type == "AND3")
		{ ptr = new AND3(GInfo, AND3_FANOUT);}
		else if (type == "BUFFER")
		{  ptr = new BUFFER(GInfo, BUFFER_FANOUT);	}

		else	 if (type == "NOT")
		{  ptr = new INVERTER(GInfo, INVERTER_FANOUT);}
		else if (type == "LED")
		{	ptr = new LED(GInfo);
			
		}
		else if (type == "NAND2")
		{
		 ptr = new NAND2(GInfo, NAND2_FANOUT);
		
		}
		else if (type == "NOR2")
		{
		   ptr = new NOR2(GInfo, NOR2_FANOUT);
		}
		else	 if (type == "NOR3")
		{	 ptr = new NOR3(GInfo, NOR3_FANOUT);		}
		else	 if (type == "OR2")
		{
			ptr = new OR2(GInfo, OR2_FANOUT);
		}
		else if ("SWITCH" == type)
		{
		    ptr = new Switch(GInfo, SWITCH_FANOUT);
	
		}

		else	 if (type == "XNOR2")
		{   ptr = new XNOR2(GInfo, XNOR2_FANOUT);
		  

		}
		else	if (type == "XOR2")
		{
	   	  ptr = new XOR2(GInfo, XOR2_FANOUT);
		
		}
		else if (type == "XOR3")
		{    ptr = new XOR3(GInfo, XOR3_FANOUT);
	   }
    ptr->Load(inp);
	AddComponent(ptr);

	}
	
	inp >> type;  // To read the word connections; 
	int srcID;     	   inp >> srcID;
	while (srcID != -1)
	{  
		Component* srcComp, *destComp;
		OutputPin *srcPin; InputPin* dstPin;
		int destID, nPin;
		inp >> destID >> nPin;
		srcComp = FindComponentID(srcID);
		destComp = FindComponentID(destID);
		int x1, y1, x2, y2;
		srcPin = srcComp->GetComponentOutputpinCoordinates(x1, y1);
		dstPin = destComp->GetComponentInputpinCoordinates(x2, y2, nPin);
		GraphicsInfo GfxInfo;
		GfxInfo.x1 = x1;
		GfxInfo.y1 = y1;
		GfxInfo.x2 = x2;
		GfxInfo.y2 = y2;
		Connection* c = new Connection(GfxInfo, srcPin, dstPin);
		c->Load(inp); 
		AddComponent(c);
		inp >> srcID;
	}
}
int ApplicationManager::GetnComponents()
{
	nComponents = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection *> (CompList[i]) == NULL)
			nComponents ++;
	}
	return nComponents; 
}
void ApplicationManager::SaveFn(ofstream &out) 
{
	nComponents = 0;
	for (int i = 0; i < CompCount; i++)
	{
		if (dynamic_cast<Connection *> (CompList[i]) == NULL)
			nComponents++;
	}
	out << nComponents;  Component *ptr;  // First Save Gates 
	for (int i = 0; i < CompCount; i++)
	{
		ptr = dynamic_cast<Connection *> (CompList[i]);
		if (ptr == NULL)
		{
			CompList[i]->Save(out);
		}

	}
	out << "\nConnections: \n";
	for (int i = 0; i < CompCount; i++)
	{
		ptr = dynamic_cast<Connection *> (CompList[i]);
		if (ptr)
		{
			CompList[i]->Save(out);
		}
	}
	out << "\n -1";

}
bool ApplicationManager::isEmpty()
{
	if (CompCount == 0)
		return true; 
	return false;
}
bool ApplicationManager::Reset()
{
	for (int i = 0; i < CompCount; i++)
	{
		delete CompList[i];
		CompList[i] = NULL;
	}
	CompCount = 0; 
	return true;
}

vector<Component*> ApplicationManager::GetListOfSwitches()
{
	vector<Component*>Listofswitches;
	for (int i=0;i<CompCount;i++)
	{
		if (dynamic_cast<Switch*>(CompList[i]))
		{
			Listofswitches.push_back(CompList[i]);
		}
	}
	return Listofswitches;
}

vector<Component*> ApplicationManager::GetListofLeds()
{
	vector<Component*>Listofleds;
	for(int i=0;i<CompCount;i++)
	{
		if(dynamic_cast<LED*>(CompList[i]))
		{
			Listofleds.push_back(CompList[i]);
		}
	}
	return Listofleds;
}

Component* ApplicationManager:: GetCopied()
{
	return CopiedComponent; 
}
void ApplicationManager::SetCopied(Component* c)
{ 
	// I only have one component to be copied or cut ...If I set copied Object then any other objects in the clipboard should be automatically deleted 
	if (CutComponent != NULL)
	{
		CutComponent = NULL;
	} 
	if (CopiedComponent!=NULL ) // so as not to delete an object then assign copied component to it 
	{
	CopiedComponent = NULL;
	} 
	 
	CopiedComponent = c->MakeCopy(c);

}
Component* ApplicationManager::GetCut()
{
	return CutComponent; 
}
void ApplicationManager::SetCut(Component* c)
{   if (c==NULL) // If paste calls this fn to indicate that the cut-paste operation has been performed 
{
	CutComponent = NULL; 
	return; 
} // I only have one component to be copied or cut ...If I set Cut Object then any other objects in the clipboard should be automatically deleted 
if (CopiedComponent != NULL)
{
	
	CopiedComponent = NULL;
}
if (CutComponent!=NULL)
{
	 
	CutComponent = NULL; 
}
CutComponent = c->MakeCopy(c); 
}

unsigned int ApplicationManager::GetSelectedSize()
{
	return SelectedList.size();
} 
int ApplicationManager::getNumberOfInputs()
{
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		Switch *S = dynamic_cast<Switch*>(CompList[i]);
		if (S != NULL)
			count++;
	}
	return count;
}

//Function to get the number of inputs
int ApplicationManager::getNumberOfOuputs()
{
	int count = 0;
	for (int i = 0; i < CompCount; i++)
	{
		LED *S = dynamic_cast<LED*>(CompList[i]);
		if (S != NULL)
			count++;
	}
	return count;
}



ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<CompCount; i++)
		delete CompList[i];
	delete OutputInterface;
	delete InputInterface;

}