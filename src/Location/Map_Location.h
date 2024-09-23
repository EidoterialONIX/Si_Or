#pragma once
#include "Vectors.h"
#include <vector>
#include <iostream>

struct Map_Configuration {

	a_t::Vector2D_f _size_element = a_t::Vector2D_f(100.0f, 100.0f);

	a_t::Vector3D_f _color_water = a_t::Vector3D_f(0.0f, 0.0f, 1.0f);
	a_t::Vector3D_f _color_plain = a_t::Vector3D_f(0.0f, 1.0f, 0.0f);
	a_t::Vector3D_f _color_hill = a_t::Vector3D_f(1.0f, 1.0f, 0.0f);

};

struct Zone {
	a_t::Vector2D_i _start_id = a_t::Vector2D_i(0, 0);
	int _count_elements = 0;
	int _type_element;

};

class Map_Location {
private:

	std::vector<std::vector<Zone>> _map_location;

	Map_Configuration _map_configuration;


public:

	Map_Location(std::vector<std::vector<int>> main_location);

	std::vector<std::vector<Zone>> get_Map_Location() const;

	Map_Configuration get_Map_Configuration() const;

	void set_Map_Configuration(a_t::Vector2D_f s_e, a_t::Vector3D_f c_w, a_t::Vector3D_f c_p, a_t::Vector3D_f c_h);

	void show_Map_Location(bool show_full_info);



		
};

