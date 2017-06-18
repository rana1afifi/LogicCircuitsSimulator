#pragma once
#include "..\Defs.h"
#include "Input.h"
#include <vector>
using std::vector;
class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateStatusBar() const;	//Create Status bar

	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area
	void ClearToolBar() const; //Clears the tool bar

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	void SetWindowBuffer(bool status); //T

	void UpdateBuffer() const; //T
	
// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false , int x=0 ,int y=0) const;
	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawBuffer(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawNOT(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawSwitch(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0,STATUS status = LOW) const;
	void DrawLEDON(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;
	void DrawLEDOFF(GraphicsInfo r_GfxInfo, bool selected = false, int x=0 ,int y=0) const;

	
	// Draws Connection
	void DrawConnection(GraphicsInfo r_GfxInfo, vector<GraphicsInfo>& points,bool selected = false, STATUS status=LOW) const; //T
	void PrintMsgonArea(string msg, int x, int y);
	void PrintMsg(string msg) const;	//Print a message on Status bar
	//Truth table
	window *CreateTruthTableWindow(int NumberOfInputs, int NumberOfOutputs);
	void PrintTruthTable(STATUS *inputs, int NumberOfInputs, STATUS *Outputs, int NumberOfOutputs, int x, int y, window *pWind);
	////// draw rectangle used in moving
	void Output::DrawSelectedRectangle(const GraphicsInfo& info,int x, int y); //T


	~Output();
};
