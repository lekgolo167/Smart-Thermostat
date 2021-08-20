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
		else if (current->start_hour == hr && current->start_min > min)
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
	char buffer[1024];
	sprintf(buffer, URL_GET_CYCLES, day);
	get_request(buffer, buffer, 1024);

	JSON_Value* raw = json_parse_string(buffer);
	JSON_Object* obj = json_value_get_object(raw);
	JSON_Array* cycles_array = json_object_get_array(obj, "cycles");

	int count = json_array_get_count(cycles_array);
	Serial.print("COUNT: ");
	Serial.println(count);
	for (int i = 0; i < count; i++) {
		cycle c;
		JSON_Object* cycle_obj = json_array_get_object(cycles_array, i);
		
		c.id = (int)json_object_get_number(cycle_obj, "id");
		c.start_hour = (int)json_object_get_number(cycle_obj, "h");
		c.start_min = (int)json_object_get_number(cycle_obj, "m");
		c.temp_F = (float)json_object_get_number(cycle_obj, "t");
		this->push_front(c);
		Serial.print("Pused Back: ");
		Serial.println(c.id);
	}
	Serial.print("Pointer ---");
	Serial.println(this->find_next_cycle(0,0)->id);
	json_value_free(raw);
}