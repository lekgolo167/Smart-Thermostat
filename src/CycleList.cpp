#include "CycleList.hpp"

CycleList::CycleList() : LinkedList()
{
	m_dayID = -1;
}

CycleList::~CycleList()
{
}

void CycleList::print_cycles()
{
}

cycle_t *CycleList::find_next_cycle(uint8_t hr, uint8_t min)
{
	for (auto current : *this)
	{
		if (current->start_hour > hr)
		{
			continue;
		}
		else if (current->start_hour == hr && current->start_min < min)
		{
			continue;
		}
		else
			return current;
	}
	return nullptr;
}

void CycleList::update_cycles(uint8_t day)
{
	this->clear();
}