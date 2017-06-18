#include "ChangeToSimulation.h"
#include "..\ApplicationManager.h"

ChangeToSimulation::ChangeToSimulation(ApplicationManager *pApp) :Action(pApp)
{
	CancelOperation=false;
}

ChangeToSimulation::~ChangeToSimulation()
{
}

void ChangeToSimulation::ReadActionParameters()
{  
	int numofleds=pManager->getNumberOfOuputs();
	int numofswitches=pManager->getNumberOfInputs();
	Output* pOut = pManager->GetOutput();

	if (pManager->GetnComponents()==0) // check if there are no components
	{
		pOut->PrintMsg("ERROR!! : You can't simulate without gates ");
		CancelOperation=true;
		pManager->SetSimulationstatus(false); // set the abiltiy to simulate false 
		return ;
	}
	else if (numofleds==0 && numofswitches ==0 ) // check if there are no switches and  no leds
	{
		pOut->PrintMsg("ERROR!! : circuit does not contain switches and leds");
		CancelOperation=true;
		pManager->SetSimulationstatus(false);
	}
	else if (numofleds==0 && numofswitches !=0 )  // check if there are  switches and no  leds
	{
		pOut->PrintMsg("ERROR!! : circuit does not contain leds");
		pManager->SetSimulationstatus(false);
		CancelOperation=true;
	}
	else if (numofleds!=0 && numofswitches ==0 )  // check if there are no switches and there are leds
	{
		pOut->PrintMsg("ERROR!! : circuit does not contain switches ");
		pManager->SetSimulationstatus(false);
		CancelOperation=true;
	}
	else if (pManager->GetFloatingPinsStatus() && pManager->GetFeedbackStatus()) // check both feedback and floating pins
	{
		pOut->PrintMsg("ERROR!! : there are floating pins and feedback");
		CancelOperation=true;
		pManager->SetFloatingPinstatus(false);
		pManager->SetFeedbackStatus(false);
		pManager->SetSimulationstatus(false);
		return ;
	}
	else if (pManager->GetFloatingPinsStatus() && pManager->GetFeedbackStatus()==false) // check floatingpin
	{
		pOut->PrintMsg("ERROR!! : there are floating pins");
		CancelOperation=true;
		pManager->SetFloatingPinstatus(false);
		pManager->SetSimulationstatus(false);
		return ;
	}
	else if(pManager->GetFloatingPinsStatus()==false && pManager->GetFeedbackStatus()) // check feedback 
	{
		pOut->PrintMsg("ERROR!! : there is feedback");
		CancelOperation=true;
		pManager->SetFeedbackStatus(false);
		pManager->SetSimulationstatus(false);
		return;
	}
}

void ChangeToSimulation::Execute()
{
	ReadActionParameters();
	if (CancelOperation)
		return;
	Output* pOut = pManager->GetOutput();
	pOut->CreateSimulationToolBar();
	pManager->SortComponentList();
	
}

void ChangeToSimulation::Undo()
{}

void ChangeToSimulation::Redo()
{}

