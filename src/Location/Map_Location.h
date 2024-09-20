#pragma once
#include "Vectors.h"
#include <vector>
#include <iostream>



struct Zone {
	a_t::Vector2D_i _start_id = a_t::Vector2D_i(0, 0);
	int _count_elements = 0;
	int _type_element;

};

class Map_Location {
private:

	std::vector<Zone> _map_location;


public:

	Map_Location(std::vector<std::vector<int>> main_location);

	std::vector<Zone> get_Map_Location() const;

	void show_Map_Location();

		
};

