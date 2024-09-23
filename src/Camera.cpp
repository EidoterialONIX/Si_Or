#include "Camera.h"



Camera::Camera(a_t::Vector2D_f size_screen) {

	this->_size_screen = size_screen;

}

void Camera::move_Camera(char vector) {

	if (vector == 'A') this->_position_camera.x -= this->_camera_configuration._speed_camera;
	else if (vector == 'D') this->_position_camera.x += this->_camera_configuration._speed_camera;
	else if (vector == 'W') this->_position_camera.y -= this->_camera_configuration._speed_camera;
	else if (vector == 'S') this->_position_camera.y += this->_camera_configuration._speed_camera;

}

void Camera::change_Zoom(char vector) {

	if (vector == '+' && this->_camera_configuration._zoom < 2.0f) this->_camera_configuration._zoom += 0.1f;
	else if (vector == '-' && this->_camera_configuration._zoom > 0.5f) this->_camera_configuration._zoom -= 0.1f;

}

Camera_Configuration Camera::get_Camera_Configuration() const {
	return this->_camera_configuration;

}

void Camera::set_Camera_Configuration(float s_c, a_t::Vector3D_f c_f, float z) {

	this->_camera_configuration._speed_camera = s_c;

	this->_camera_configuration._color_filter = c_f;

	this->_camera_configuration._zoom = z;

}

void Camera::show_Camera_Info() {

	std::cout << "Size screen: " << "(X:" << this->_size_screen.x << ", " << "Y:" << this->_size_screen.y << ")" << std::endl;
	std::cout << "Position camera: " << "(X:" << this->_position_camera.x << ", " << "Y:" << this->_position_camera.y << ")" << std::endl;
	std::cout << "Speed camera: " << this->_camera_configuration._speed_camera << std::endl;
	std::cout << "Color filter: " << "R: " << this->_camera_configuration._color_filter.x << " |  G:" << this->_camera_configuration._color_filter.y << " |  B" << this->_camera_configuration._color_filter.z << std::endl;
	std::cout << "Zoom: " << this->_camera_configuration._zoom << std::endl;

}

