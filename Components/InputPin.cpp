#include "InputPin.h"

InputPin::InputPin()
{pCon=NULL;}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}

void InputPin::setConnection(Connection *pCn)
{
	pCon = pCn;
}
Connection* InputPin::getconnection()
{
    return pCon; 
}
bool InputPin::isconnected( )
{
	if (pCon==NULL)
	{
		return false;
	}
	return true;
}

