#pragma once

#include "Eidor.h"
#include "Location/Map_Location.h"
#include "Vectors.h"
#include <iostream>



struct  Camera_Configuration {

	float _speed_camera = 1.0f;

	a_t::Vector3D_f _color_filter = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

	float _zoom = 1.0f;

};



class Camera {
private:

	a_t::Vector2D_f _size_screen = a_t::Vector2D_f(0.0f, 0.0f);

	a_t::Vector2D_f _position_camera = a_t::Vector2D_f(0.0f, 0.0f);

	Camera_Configuration _camera_configuration;

	Draw_on_screen Drawing = Draw_on_screen(a_t::Vector3D_f(0.0f, 0.0f, 0.0f));

public:

	Camera(a_t::Vector2D_f size_screen);
	
	void move_Camera(char vector);

	void change_Zoom(char vector);

	void draw_Camera(Map_Location map_location);

	Camera_Configuration get_Camera_Configuration() const;

	void set_Camera_Configuration(float s_c, a_t::Vector3D_f c_f, float z);

	void show_Camera_Info();

};