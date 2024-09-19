#include "Location.h"



Location::Location(a_t::Vector2D_f size) {
	srand(time(NULL));

	this->_size = size;

	this->_main_location.resize(this->_size.y);
	for (int i{ 0 }; i < this->_size.y; i++) {
		this->_main_location[i].resize(this->_size.x);

	}

	for (int i{ 0 }; i < this->_size.y; i++) {
		for (int j{ 0 }; j < this->_size.x; j++) {
			this->_main_location[i][j] = rand() % 256;

		}

	}

}


void Location::SMOOTHING(std::vector<std::vector<int>>& mask) {

	int sum = 0;

	for (int i{ 0 }; i < this->_size.y; i++) {
		for (int j{ 0 }; j < this->_size.x; j++) {
			
			for (int index_y{ 0 }; index_y < 3; index_y++) {
				for (int index_x{ 0 }; index_x < 3; index_x++) {

					if ((i == 0 || i == this->_size.y - 1) && (index_y == 0 || index_y == 2)) continue;
					else if ((j == 0 || j == this->_size.x - 1) && (index_x == 0 || index_x == 2)) continue;
					else sum += this->_main_location[i - 1 + index_y][j - 1 + index_x];

				}

			}

			sum = (sum / 9.0f) * this->_settings._level_smoothing;
			if (sum > 255) sum = 255;

			mask[i][j] = sum;
			sum = 0;

		}

	}

}

void Location::CHANGE_LOCATION_MASK(std::vector<std::vector<int>>& mask) {
	for (int i{ 0 }; i < this->_size.y; i++) {
		for (int j{ 0 }; j < this->_size.x; j++) {
			this->_main_location[i][j] = mask[i][j];

		}

	}

}

void Location::CONVERT_ELEMENTS_LEVEL() {

	for (int i{ 0 }; i < this->_size.y; i++) {
		for (int j{ 0 }; j < this->_size.x; j++) {

			if (this->_main_location[i][j] <= this->_elements_location.minimum_water_level) this->_main_location[i][j] = 0;
			else if (this->_main_location[i][j] <= this->_elements_location.minimum_plain_level) this->_main_location[i][j] = 1;
			else this->_main_location[i][j] = 2;


		}

	}

}


void Location::generate_Location(bool active_smoothing) {

	std::vector<std::vector<int>> mask;

	mask.resize(this->_size.y);
	for (int i{ 0 }; i < this->_size.y; i++) {
		mask[i].resize(this->_size.x);

	}

	for (int i{ 0 }; i < this->_size.y; i++) {
		for (int j{ 0 }; j < this->_size.x; j++) {
			mask[i][j] = this->_main_location[i][j];

		}

	}

	Location::SMOOTHING(mask);

	Location::CHANGE_LOCATION_MASK(mask);

	Location::CONVERT_ELEMENTS_LEVEL();

}


Elements_Location Location::get_Elements_Location() const {
	return this->_elements_location;

}

void Location::set_Elements_Location(int water, int plain, int hill) {
	
	this->_elements_location.minimum_water_level = water;
	this->_elements_location.minimum_plain_level = plain;
	this->_elements_location.minimum_hill_level = hill;

}

Settings Location::get_Settings() const {
	return this->_settings;

}

void Location::set_Settings(float level_smoothing) {

	this->_settings._level_smoothing = level_smoothing;

}


void Location::show_Main_Location() {

	for (int i{ 0 }; i < this->_size.y; i++) {
		for (int j{ 0 }; j < this->_size.x; j++) {
			std::cout << this->_main_location[i][j] << " - ";

		}

		std::cout << std::endl;

	}

}
