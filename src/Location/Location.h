#pragma once
#include "Vectors.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>


struct Elements_Location {

	int minimum_water_level = 0;
	int minimum_plain_level = 0;
	int minimum_hill_level = 0;

};


struct Settings {

	float _level_smoothing = 1.0f;


};


class Location {
private:

	a_t::Vector2D_f _size;

	Elements_Location _elements_location;

	Settings _settings;

	std::vector<std::vector<int>> _main_location;

	void SMOOTHING(std::vector<std::vector<int>>& mask);


	void CHANGE_LOCATION_MASK(std::vector<std::vector<int>>& mask);
	void CONVERT_ELEMENTS_LEVEL();


public:

	Location(a_t::Vector2D_f size);

	void generate_Location(bool active_smoothing);

	Elements_Location get_Elements_Location() const;
	void set_Elements_Location(int water, int plain, int hill);

	Settings get_Settings() const;
	void set_Settings(float level_smooting);




	void show_Main_Location();






};