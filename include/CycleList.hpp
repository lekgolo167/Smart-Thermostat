#pragma once

#include <stdint.h>

#include "LinkedList.hpp"

typedef struct cycle {
	int id;
	int start_hour;
	int start_min;
	float temp_F;
} cycle_t;

class CycleList : public LinkedList<cycle_t>{
	private:
		
	public:
		CycleList();
		~CycleList();
		void print_cycles();
		cycle_t* find_next_cycle(uint8_t hr, uint8_t min);
		void update_cycles(uint8_t day);

		int m_dayID;
};
