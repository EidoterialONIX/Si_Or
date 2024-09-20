#include "Map_Location.h"


Map_Location::Map_Location(std::vector<std::vector<int>> main_location) {

	a_t::Vector2D_i pos_correct = a_t::Vector2D_i(0, 0);

	int count_correct = 0;

	int type_correct = 0;
	int type_selecter = 0;

	for (int i{ 0 }; i < main_location.size(); i++) {
		type_correct = main_location[i][0];
		count_correct = 0;

		for (int j{ 0 }; j < main_location[0].size(); j++) {
			type_selecter = main_location[i][j];
			

			if (type_selecter != type_correct) {
				this->_map_location.resize(this->_map_location.size() + 1);

				this->_map_location[this->_map_location.size() - 1]._start_id = pos_correct;
				this->_map_location[this->_map_location.size() - 1]._count_elements = count_correct;
				this->_map_location[this->_map_location.size() - 1]._type_element = type_correct;

				pos_correct.x = j; pos_correct.y = i;

				type_correct = type_selecter;
				count_correct = 1;


				continue;
				
			}

			count_correct++;
			
		}

		this->_map_location.resize(this->_map_location.size() + 1);

		this->_map_location[this->_map_location.size() - 1]._start_id = pos_correct;
		this->_map_location[this->_map_location.size() - 1]._count_elements = count_correct;
		this->_map_location[this->_map_location.size() - 1]._type_element = type_correct;

		
	}

}


std::vector<Zone> Map_Location::get_Map_Location() const {
	return this->_map_location;

}

void Map_Location::show_Map_Location() {

	for (int i{ 0 }; i < this->_map_location.size(); i++) {

		std::cout << "X- " << this->_map_location[i]._start_id.x << " : " << "Y- " << this->_map_location[i]._start_id.y << "  ";
		std::cout << "Count: " << this->_map_location[i]._count_elements << "  ";
		std::cout << "Type: " << this->_map_location[i]._type_element << std::endl;

	}

}

