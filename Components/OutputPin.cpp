#include "OutputPin.h"
#include "Connection.h"

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS: r_FanOut;	//set the fan out of the pin.
}


//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if(m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}

void OutputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* OutputPin::getComponent()
{
	return pComp;
}

void OutputPin::RemoveConnections()
{
	for(int i=0; i<m_Conn; i++)
	{
		Deleteconnection(m_Connections[i]);
	}
}
bool OutputPin::AvailableConnection ( )
{
	if (m_Conn< m_FanOut)
	{
		return true;
	}
	return false;
}

void OutputPin::Deleteconnection(Connection *M_Conn)
{
	for (int i=0;i<m_Conn;i++)
	{
		if (m_Connections[i]==M_Conn)
		{  
			m_Connections[i]=m_Connections[m_Conn-1];
			m_Connections[m_Conn-1]=NULL;
			m_Conn--;
			return;
		}
	}
}

bool OutputPin::isconnected()
{
    if(m_Conn>0)
	{
	   return true;
	}
	return false;
}

void OutputPin::OperateTheConnections()
{
	for (int i=0; i<m_Conn;i++)
	{
		m_Connections[i]->Operate();
	}
}
vector<Connection*> OutputPin:: GetListOfOutputConnecctions()  //T
{
	vector<Connection*> OutputConnections;
	for(int i=0 ;i<m_Conn ;i++)
	{
		OutputConnections.push_back(m_Connections[i]);

	}
	return OutputConnections;
}

vector<Component*>  OutputPin::GetListofNextGates() 
{
	vector <Component*> nextcomponents;
	for(int i=0 ;i<m_Conn;i++)
	{
		nextcomponents.push_back(m_Connections[i]->getDestPin()->getComponent());
	}
	return nextcomponents;

}

OutputPin::~OutputPin()
{
	for (int i=0;i<m_Conn;i++)
	{
		 m_Connections[i]->setSourcePin(NULL);
	}
}
