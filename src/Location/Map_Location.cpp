#include "Map_Location.h"


Map_Location::Map_Location(std::vector<std::vector<int>> main_location) {

	this->_map_location.resize(main_location.size());

	a_t::Vector2D_i pos_correct = a_t::Vector2D_i(0, 0);

	int count_correct = 0;

	int type_correct = 0;
	int type_selecter = 0;

	for (int i{ 0 }; i < main_location.size(); i++) {
		type_correct = main_location[i][0];
		count_correct = 0;
		pos_correct = a_t::Vector2D_i(0, i);

		for (int j{ 0 }; j < main_location[0].size(); j++) {
			type_selecter = main_location[i][j];

			if (type_correct == type_selecter) count_correct++;
			else {
				this->_map_location[i].resize(this->_map_location[i].size() + 1);

				this->_map_location[i][this->_map_location[i].size() - 1]._start_id = pos_correct;
				this->_map_location[i][this->_map_location[i].size() - 1]._count_elements = count_correct;
				this->_map_location[i][this->_map_location[i].size() - 1]._type_element = type_correct;

				pos_correct = a_t::Vector2D_i(j, i);
				count_correct = 1;
				type_correct = type_selecter;

			}

			if (j == main_location.size() - 1) {
				this->_map_location[i].resize(this->_map_location[i].size() + 1);

				this->_map_location[i][this->_map_location[i].size() - 1]._start_id = pos_correct;
				this->_map_location[i][this->_map_location[i].size() - 1]._count_elements = count_correct;
				this->_map_location[i][this->_map_location[i].size() - 1]._type_element = type_correct;

				break;

			}

		}
		
	}

}


std::vector<std::vector<Zone>> Map_Location::get_Map_Location() const {
	return this->_map_location;

}

Map_Configuration Map_Location::get_Map_Configuration() const {
	return this->_map_configuration;

}

void Map_Location::set_Map_Configuration(a_t::Vector2D_f s_e, a_t::Vector3D_f c_w, a_t::Vector3D_f c_p, a_t::Vector3D_f c_h) {
	this->_map_configuration._size_element = s_e;

	this->_map_configuration._color_water = c_w;
	this->_map_configuration._color_plain = c_p;
	this->_map_configuration._color_hill = c_h;

}

void Map_Location::show_Map_Location(bool show_full_info) {

	int total_element = 0;

	for (int i{ 0 }; i < this->_map_location.size(); i++) {
		if (show_full_info) std::cout << "Layot: " << i << std::endl;

		for (int j{ 0 }; j < this->_map_location[i].size(); j++) {

			if (show_full_info) {
				std::cout << "X- " << this->_map_location[i][j]._start_id.x << " : " << "Y- " << this->_map_location[i][j]._start_id.y << "  ";
				std::cout << "Count: " << this->_map_location[i][j]._count_elements << "  ";
				std::cout << "Type: " << this->_map_location[i][j]._type_element << std::endl;

			}
			
			total_element++;

		}

	}

	std::cout << "Total elements : "  << total_element << std::endl;

}

