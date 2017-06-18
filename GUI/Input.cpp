//#include "Input.h"
#include "Output.h"
#define Enter 13
#define Backspace 8

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

clicktype Input::GetMouseclickandType(int &x,int &y) //T name of the function 
{
	return (pWind->GetMouseClick(x,y));

}

void Input:: getMouseCoordinates(int&x,int&y)
{
	pWind->GetMouseCoord(x,y);
}

string Input::GetSrting(Output *pOut)
{
	keytype key;
	string str;
	char c;
	const char * cursor = "|";
	int index = 0;
	int count = 0;

	pWind->FlushKeyQueue();
	key = pWind->WaitKeyPress(c);
	
	while (c != Enter)
	{       
		if (key == ESCAPE)
		{
			str.erase();
			break;
		}
		else if (key == ARROW)
		{
			switch (c)
			{
			case 1: //end key//
				index = count;
				break;

			case 4: //left key//
				if (index != 0)
					--index;
				break;
			case 6: //right key//
				if (index != count)
					++index;
				break;

			case 7: //home key//
				index = 0;
				break;
			}
		}
		else if (c == Backspace && index != 0 && !str.empty())
		{
			str.erase(--index, 1);
			count--;
		}
		else
		{
			if (c != Backspace)
			{
				str.insert(str.begin() + index, c);
				count++; index++;
			}
		}
		str.insert(index, cursor);
		pOut->PrintMsg("enter label:" + str);
		Sleep(200);
		str.erase(index, 1);
		key = pWind->WaitKeyPress(c);
	}
	///TODO: Implement this Function
	//Read a complete string from the user until the user presses "ENTER".
	//If the user presses "ESCAPE". This function should return an empty string.
	//"BACKSPACE" should be also supported
	//User should see what he is typing at the status bar

	return str;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(int &x, int &y) const
{
	if(x==0 && y==0)
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_NAND2: return ADD_NAND_GATE_2;
			case ITM_NOR2: return ADD_NOR_GATE_2;
			case ITM_XOR2: return ADD_XOR_GATE_2;
			case ITM_XNOR2: return ADD_XNOR_GATE_2;
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_NOR3:  return ADD_NOR_GATE_3;
			case ITM_XOR3: return ADD_XOR_GATE_3;
			case ITM_BUFFER: return ADD_Buff;
			case ITM_INVERTER: return  ADD_INV;
			case ITM_SWITCH:  return ADD_Switch;
			case ITM_LED: return ADD_LED;
			case ITM_CONNECT: return ADD_CONNECTION;
			case ITM_LABEL:  return ADD_Label;
			case ITM_EDIT:   return EDIT_Label;
			case ITM_DELETE: return DEL;
			case ITM_LOAD:   return LOAD;
			case ITM_SAVE:   return SAVE;
			case ITM_COPY:   return COPY;
			case ITM_CUT:    return CUT;
			case ITM_PASTE:  return PASTE;
			case ITM_MULTISELECT: return MULTISELECT;
			case ITM_MOVE: return MOVE;
			case ITM_SIMMODE: return SIM_MODE;
			case ITM_EXIT: return EXIT;

			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a statement in the flowchart
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			switch (ClickedItemOrder)
			{
			//case ITM_SIM:     return Change_Switch;
			case ITM_TRUTH:   return  Create_TruthTable;
			case ITM_PROBING: return PROBE;
			case ITM_DESIGN:  return  DSN_MODE;
			default:    	  return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
			}

		}
		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (UI.AppMode == DESIGN)
			return SELECT;	//user want to select/unselect a statement in the flowchart
			else
			return Change_Switch;
		}

		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
}

Input::~Input()
{
}
