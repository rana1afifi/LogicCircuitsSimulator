#pragma once

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "UI_Info.h"

class Output;
class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window

public:
	Input(window*);
	void GetPointClicked(int &, int &);	//Get coordinate where user clicks
	string GetSrting(Output*);		//Returns a string entered by the user

	ActionType GetUserAction(int &x, int &y) const; //Reads the user click and maps it to an action
	
	clicktype GetMouseclickandType(int &x,int&y); 

	void getlastpointclicked(int &x,int&y);

	void getMouseCoordinates(int&x,int&y); 

	~Input();
};
