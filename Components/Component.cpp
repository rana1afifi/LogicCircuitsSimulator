#include "Component.h"

int Component::Count = 0; 
Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;
	

}

void Component::SetSelected (bool select)
{
	selected = select;
}

bool Component::IsSelected()
{
	return selected;
}

GraphicsInfo* Component::GetGraphicsInfo()
{
	return &m_GfxInfo;
}

void Component:: setGraphicsInfo(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;
}

void Component::SetLevel(int xLevel ) //T
{
	level = max(level,xLevel);
}

int Component::GetLevel()
{
    return level;
}

//Set label of a component
void Component::setLabel(string label)
{
	if (label !="$")
	m_Label = label;
}

//Get the label of a component
string Component::GetLabel()
{
	return m_Label;
}

bool Component::getvisitedstatus()
{
	return  visited;
}

void Component::setvisitedstatus(bool xVisited)
{
	visited =xVisited;
}


void Component::SetID(int id)
{
	ID = id;
}
int Component::GetID()
{
	return ID;
}

Component::Component()
{}

Component::~Component()
{}

