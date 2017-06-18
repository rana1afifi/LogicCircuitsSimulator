#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters

	UI.AppMode = DESIGN;	//Design Mode is the startup mode

	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = BLUE;
	UI.BkGrndColor = WHITE;
	
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	
	ChangeTitle("Programming Techniques Project");

	CreateDesignToolBar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar


}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.height-UI.StatusBarHeight, UI.width, UI.height-UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg) const
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsgonArea(string msg, int x, int y)
{
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->SetPen(ORANGE, 1);
	pWind->DrawString(x, y, msg);
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
void Output::PrintTruthTable(STATUS *Inputs, int NumberOfInputs, STATUS *Outputs, int NumberOfOutputs, int x, int y, window *pWind)
{

	for (int i = 0; i < NumberOfInputs; i++)
	{
		if (Inputs[i] == HIGH)
			pWind->DrawString(x + 50 * i, y + 20, "1");
		else pWind->DrawString(x + 50 * i, y + 20, "0");
	}
	for (int i = 0; i < NumberOfOutputs; i++)
	{
		if (Outputs[i] == HIGH)
			pWind->DrawString(x + 200 + 50 * i, y + 20, "1");
		else pWind->DrawString(x + 200 + 50 * i, y + 20, "0");
	}
}
///////////////////////////////////////////////////////////////////////////////////
window * Output::CreateTruthTableWindow(int NumberOfInputs, int NumberOfOutputs)
{
	window *pWind;
	pWind = CreateWind(400, 400, 50, 200);
	pWind->ChangeTitle("Truth Table");
	pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial");
	pWind->SetPen(UI.MsgColor);
	pWind->SetPen(BLACK, 1);
	for (int i = 0; i < NumberOfInputs; i++)
	{
		int x = i + 1;
		if (x == 1)
			pWind->DrawString(5, 0, "I1");
		else if (x == 2)
			pWind->DrawString(55, 0, "I2");
		else if (x==3)
			pWind->DrawString(105, 0, "I3");
		else
			pWind->DrawString(155, 0, "I4");
	}

	for (int i = 0; i < NumberOfOutputs; i++)
	{
		int x = i + 1;
		if (x == 1)
			pWind->DrawString(205, 0, "O1");
		else if (x == 2)
			pWind->DrawString(255, 0, "O2");
		else if (x == 3)
			pWind->DrawString(305, 0, "O3");
		else
			pWind->DrawString(355, 0, "O4");
	}
	//pWind->DrawString(200, 0, "Outputs");
	pWind->SetPen(ORANGE, 3);
	pWind->DrawLine(0, 20, 400, 20);
	pWind->DrawLine(199, 0, 200, 400);
	pWind->SetPen(BLACK, 1);
	return pWind;
}
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()const
{
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	//Overwrite using bachground color to erase the message
	pWind->SetPen(UI.BkGrndColor);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(MsgX, UI.height - MsgY, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (degin) area
void Output::ClearDrawingArea() const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolBar()const
{
	pWind->SetPen(RED, 1);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////

//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const
{
	ClearToolBar();
	UI.AppMode = DESIGN;	//Design Mode

	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";
	

	//TODO: Prepare image for each menu item and add it to the list
	MenuItemImages[ITM_NAND2] = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2] = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2] = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2] = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_AND3] = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\Menu_NOR3.jpg";
	MenuItemImages[ITM_XOR3] = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_BUFFER] = "images\\Menu\\Menu_BUFFER.jpg";
	MenuItemImages[ITM_INVERTER] = "images\\Menu\\Menu_INVERTER.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_SWITCH.jpg";
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_OLED.jpg";
	MenuItemImages[ITM_CONNECT] = "images\\Menu\\Menu_CONNECT.jpg";
	MenuItemImages[ITM_LABEL] = "images\\Menu\\Menu_LABEL.jpg";
	MenuItemImages[ITM_EDIT] = "images\\Menu\\Menu_EDIT.jpg";
	MenuItemImages[ITM_DELETE] = "images\\Menu\\Menu_DELETE.jpg";
	MenuItemImages[ITM_LOAD] = "images\\Menu\\Menu_LOAD..jpg";
	MenuItemImages[ITM_SAVE] = "images\\Menu\\Menu_SAVE.jpg";
	MenuItemImages[ITM_COPY] = "images\\Menu\\Menu_COPY.jpg";
	MenuItemImages[ITM_CUT] = "images\\Menu\\Menu_CUT.jpg";
	MenuItemImages[ITM_SIMMODE] = "images\\Menu\\Menu_SIMMODE.jpg";
	MenuItemImages[ITM_EXIT] = "images\\Menu\\Menu_Exit.jpg";
	MenuItemImages[ITM_PASTE] = "images\\Menu\\Menu_PASTE.jpg";
	MenuItemImages[ITM_MULTISELECT] = "images\\Menu\\Menu_MULTISELECT.jpg";
	MenuItemImages[ITM_MOVE] = "images\\Menu\\Menu_MOVE.jpg";
	//Draw menu item one image at a time
	for(int i=0; i<ITM_DSN_CNT; i++)
		pWind->DrawImage(MenuItemImages[i],i*UI.ToolItemWidth,0,UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED,3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);	

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	ClearToolBar();
	UI.AppMode = SIMULATION;	//Simulation Mode

	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_TRUTH] = "images\\Menu\\Menu_TRUTHTABLE.jpg";
	MenuItemImages[ITM_PROBING] = "images\\Menu\\Menu_PROBING.jpg";
	MenuItemImages[ITM_DESIGN] = "images\\Menu\\Menu_DESIGN.jpg";
	for (int i = 0; i<ITM_SIM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.ToolItemWidth, 0, UI.ToolItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);



}

//////////////////////////////////////////////////////////////////////////////////

void Output::SetWindowBuffer(bool status)
{
	pWind->SetBuffering(status);
}

void Output::UpdateBuffer() const
{
	pWind->UpdateBuffer();

}
//////////////////////////////////////////////////////////////////////////////////

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//

void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND2.jpg";

	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.AND2_Width, UI.AND2_Height);
}


//TODO: Add similar functions to draw all components
void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected, int x, int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_OR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_OR2.jpg";

	//Draw OR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by OR2 Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.OR2_Width, UI.OR2_Height);
	
}

void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NAND2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NAND2.jpg";

	//Draw NAND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NAND2 Image Parameter in UI_Info
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.NAND2_Width, UI.NAND2_Height);
	
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR2.jpg";

	//Draw NOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NOR2 Image Parameter in UI_Info
	
	pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.NOR2_Width, UI.NOR2_Height);
	
}
void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR2.jpg";

	//Draw XOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by XOR2 Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.XOR2_Width, UI.XOR2_Height);
	
}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XNOR2_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XNOR2.jpg";

	//Draw XNOR2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by XNOR2 Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.XNOR2_Width, UI.XNOR2_Height);
	
}

void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected, int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_Buffer_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_Buffer.jpg";

	//Draw Buffer Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by Buffer Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.Buffer_Width, UI.Buffer_Height);
	
}

void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOT_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOT.jpg";

	//Draw NOT Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NOT Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.NOT_Width, UI.NOT_Height);
	
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_AND3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_AND3.jpg";

	//Draw AND3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND3 Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.AND3_Width, UI.AND3_Height);
	
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_NOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_NOR3.jpg";

	//Draw NOR3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by NOR3 Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.NOR3_Width, UI.NOR3_Height);
	
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected ,int x,int y) const
{
	string GateImage;
	if (selected)	//use image in the highlighted case
		GateImage = "Images\\Gates\\Gate_XOR3_Hi.jpg";
	else
		GateImage = "Images\\Gates\\Gate_XOR3.jpg";

	//Draw XOR3 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by XOR3 Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.XOR3_Width, UI.XOR3_Height);
	
}

void Output::DrawSwitch(GraphicsInfo r_GfxInfo, bool selected, int x, int y,STATUS status) const
{
	string GateImage;
	if (status == HIGH)
		{
			GateImage = "Images\\Gates\\SwitchOn.jpg";
		}
	else
	{
		if (selected)	//use image in the highlighted case
			GateImage = "Images\\Gates\\Switch_Hi.jpg";
		else
			GateImage = "Images\\Gates\\SwitchOff.jpg";
	}
	//Draw Switch at Gfx_Info (1st corner)
	//Set the Image Width & Height by Switch Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.Switch_Width, UI.Switch_Height);
	
}

void Output::DrawLEDOFF(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)
	   GateImage = "Images\\Gates\\led-off-hi.jpg";
	else
	   GateImage = "Images\\Gates\\led-off.jpg";
		
	//Draw led at Gfx_Info (1st corner)
	//Set the Image Width & Height by Switch Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.LEDOFF_Width, UI.LEDOFF_Height);
	
}
void Output::DrawLEDON(GraphicsInfo r_GfxInfo, bool selected,int x,int y) const
{
	string GateImage;
	if (selected)
	  GateImage = "Images\\Gates\\led-on-hi.jpg";
	else
	  GateImage = "Images\\Gates\\led-on.jpg";

	//Draw led at Gfx_Info (1st corner)
	//Set the Image Width & Height by Switch Image Parameter in UI_Info
	
		pWind->DrawImage(GateImage, r_GfxInfo.x1 + x, r_GfxInfo.y1 + y, UI.LEDON_Width, UI.LEDON_Height);
	
}


void Output::DrawConnection(GraphicsInfo r_GfxInfo, vector<GraphicsInfo>& points, bool selected, STATUS status) const
{
	points.clear();
	//TODO: Add code to draw connection
	    if (status == HIGH)
		   pWind->SetPen(GREEN, 2);
		else if (selected)
			pWind->SetPen(BLUE, 2);
		else if (!selected)
			pWind->SetPen(BLACK, 2);
		
		if (r_GfxInfo.y1 == r_GfxInfo.y2)
		{
			pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2);
			GraphicsInfo GInfo;
			GInfo.x1 = r_GfxInfo.x1;
			GInfo.x2 = r_GfxInfo.x2;
			GInfo.y1 = r_GfxInfo.y1;
			GInfo.y2 = r_GfxInfo.y2;
			points.push_back(GInfo);
		}
		else
		{
			pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, ((r_GfxInfo.x1) + (r_GfxInfo.x2)) / 2, r_GfxInfo.y1);
			pWind->DrawLine((r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y1, (r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y2);
			pWind->DrawLine(((r_GfxInfo.x1) + (r_GfxInfo.x2)) / 2, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
			GraphicsInfo GInfo1, GInfo2, GInfo3;
			GInfo1.x1 = r_GfxInfo.x1;
			GInfo1.x2 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo1.y1 = r_GfxInfo.y1;
			GInfo1.y2 = r_GfxInfo.y1;
			GInfo2.x1 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo2.x2 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo2.y1 = r_GfxInfo.y1;
			GInfo2.y2 = r_GfxInfo.y2;
			GInfo3.x1 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo3.x2 = r_GfxInfo.x2;
			GInfo3.y1 = r_GfxInfo.y2;
			GInfo3.y2 = r_GfxInfo.y2;
			points.push_back(GInfo1);
			points.push_back(GInfo2);
			points.push_back(GInfo3);
		}
	
	/*else
	{
		pWind->SetPen(BLACK, 2);
		if (r_GfxInfo.y1 == r_GfxInfo.y2)
		{
			pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, r_GfxInfo.x2, r_GfxInfo.y2);
			GraphicsInfo GInfo;
			GInfo.x1 = r_GfxInfo.x1;
			GInfo.x2 = r_GfxInfo.x2;
			GInfo.y1 = r_GfxInfo.y1;
			GInfo.y2 = r_GfxInfo.y2;
			points.push_back(GInfo);
		}
		else
		{
			pWind->DrawLine(r_GfxInfo.x1, r_GfxInfo.y1, ((r_GfxInfo.x1) + (r_GfxInfo.x2)) / 2, r_GfxInfo.y1);
			pWind->DrawLine((r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y1, (r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y2);
			pWind->DrawLine((r_GfxInfo.x1 + r_GfxInfo.x2) / 2, r_GfxInfo.y2, r_GfxInfo.x2, r_GfxInfo.y2);
			GraphicsInfo GInfo1, GInfo2, GInfo3;
			GInfo1.x1 = r_GfxInfo.x1;
			GInfo1.x2 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo1.y1 = r_GfxInfo.y1;
			GInfo1.y2 = r_GfxInfo.y1;
			GInfo2.x1 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo2.x2 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo2.y1 = r_GfxInfo.y1;
			GInfo2.y2 = r_GfxInfo.y2;
			GInfo3.x1 = (r_GfxInfo.x1 + r_GfxInfo.x2) / 2;
			GInfo3.x2 = r_GfxInfo.x2;
			GInfo3.y1 = r_GfxInfo.y2;
			GInfo3.y2 = r_GfxInfo.y2;
			points.push_back(GInfo1);
			points.push_back(GInfo2);
			points.push_back(GInfo3);
		}*/

}


void Output::DrawSelectedRectangle(const GraphicsInfo& info,int x, int y)
{
	pWind->SetPen(ORANGE,2);
	pWind->DrawRectangle(info.x1+x,info.y1+y,info.x2+x,info.y2+y,FRAME);

}

Output::~Output()
{
	delete pWind;
}