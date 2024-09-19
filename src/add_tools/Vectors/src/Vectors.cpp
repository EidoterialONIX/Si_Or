#include "Vectors.h"

/// VECTOR2D_F
/// //////////

a_t::Vector2D_f::Vector2D_f(float x, float y) {
	this->x = x; this->y = y;
	
}

void a_t::Vector2D_f::operator=(Vector2D_f v) {
	this->x = v.x; this->y = v.y;
	
}

bool a_t::Vector2D_f::operator==(Vector2D_f v) {
	if (this->x == v.x && this->y == v.y) return true;  else false;

}

void a_t::Vector2D_f::operator+=(Vector2D_f v) {
	this->x = this->x + v.x; this->y = this->y + v.y;

}
void a_t::Vector2D_f::operator-=(Vector2D_f v) {
	this->x = this->x - v.x; this->y = this->y - v.y;

}
void a_t::Vector2D_f::operator*=(Vector2D_f v) {
	this->x = this->x * v.x; this->y = this->y * v.y;

}
void a_t::Vector2D_f::operator/=(Vector2D_f v) {
	this->x = this->x / v.x; this->y = this->y / v.y;

}

a_t::Vector2D_f a_t::Vector2D_f::operator+(Vector2D_f v) {
	return Vector2D_f(this->x + v.x, this->y + v.y);

}
a_t::Vector2D_f a_t::Vector2D_f::operator-(Vector2D_f v) {
	return Vector2D_f(this->x - v.x, this->y - v.y);

}
a_t::Vector2D_f a_t::Vector2D_f::operator*(Vector2D_f v) {
	return Vector2D_f(this->x * v.x, this->y * v.y);

}
a_t::Vector2D_f a_t::Vector2D_f::operator/(Vector2D_f v) {
	return Vector2D_f(this->x / v.x, this->y / v.y);

}

/// //////////


/// VECTOR3D_F
/// //////////
/// 
a_t::Vector3D_f::Vector3D_f(float x, float y, float z) {
	this->x = x; this->y = y; this->z = z;

}

void a_t::Vector3D_f::operator=(Vector3D_f v) {
	this->x = v.x; this->y = v.y; this->z = v.z;

}

bool a_t::Vector3D_f::operator==(Vector3D_f v) {
	if (this->x == v.x && this->y == v.y && this->z == v.z) return true;  else false;

}

void a_t::Vector3D_f::operator+=(Vector3D_f v) {
	this->x = this->x + v.x; this->y = this->y + v.y; this->z = this->z + v.z;

}
void a_t::Vector3D_f::operator-=(Vector3D_f v) {
	this->x = this->x - v.x; this->y = this->y - v.y; this->z = this->z - v.z;

}
void a_t::Vector3D_f::operator*=(Vector3D_f v) {
	this->x = this->x * v.x; this->y = this->y * v.y; this->z = this->z * v.z;

}
void a_t::Vector3D_f::operator/=(Vector3D_f v) {
	this->x = this->x / v.x; this->y = this->y / v.y; this->z = this->z / v.z;

}

a_t::Vector3D_f a_t::Vector3D_f::operator+(Vector3D_f v) {
	return Vector3D_f(this->x + v.x, this->y + v.y, this->z + v.z);

}
a_t::Vector3D_f a_t::Vector3D_f::operator-(Vector3D_f v) {
	return Vector3D_f(this->x - v.x, this->y - v.y, this->z - v.z);

}
a_t::Vector3D_f a_t::Vector3D_f::operator*(Vector3D_f v) {
	return Vector3D_f(this->x * v.x, this->y * v.y, this->z * v.z);

}
a_t::Vector3D_f a_t::Vector3D_f::operator/(Vector3D_f v) {
	return Vector3D_f(this->x / v.x, this->y / v.y, this->z / v.z);

}

/// //////////
