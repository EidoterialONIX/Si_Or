#include "Eidor.h"

/// PRIMITIVE ///////////////////////////////////////////////////////////////////////////

Primitive::Primitive(a_t::Vector3D_f v0, a_t::Vector3D_f v1, a_t::Vector3D_f v2) {
	this->_point[0] = v0; this->_point[1] = v1; this->_point[2] = v2;

}

a_t::Vector3D_f& Primitive::get_Point(int index) {
	return this->_point[index];

}

void Primitive::set_Point(int index, a_t::Vector3D_f v) {
	this->_point[index] = v;

}

void Primitive::operator=(Primitive p) {
	this->_point[0] = p.get_Point(0); this->_point[1] = p.get_Point(1); this->_point[2] = p.get_Point(2);

}

bool Primitive::operator==(Primitive p) {
	if (this->_point[0] == p.get_Point(0) && this->_point[1] == p.get_Point(1) && this->_point[2] == p.get_Point(2)) return true; else return false;

}

void Primitive::operator+=(Primitive p) {
	this->_point[0] = this->_point[0] + p.get_Point(0); this->_point[1] = this->_point[1] + p.get_Point(1); this->_point[2] = this->_point[2] + p.get_Point(2);

}
void Primitive::operator-=(Primitive p) {
	this->_point[0] = this->_point[0] - p.get_Point(0); this->_point[1] = this->_point[1] - p.get_Point(1); this->_point[2] = this->_point[2] - p.get_Point(2);

}
void Primitive::operator*=(Primitive p) {
	this->_point[0] = this->_point[0] * p.get_Point(0); this->_point[1] = this->_point[1] * p.get_Point(1); this->_point[2] = this->_point[2] * p.get_Point(2);

}
void Primitive::operator/=(Primitive p) {
	this->_point[0] = this->_point[0] / p.get_Point(0); this->_point[1] = this->_point[1] / p.get_Point(1); this->_point[2] = this->_point[2] / p.get_Point(2);

}

Primitive Primitive::operator+(Primitive p) {
	return Primitive(this->_point[0] + p.get_Point(0), this->_point[1] + p.get_Point(1), this->_point[2] + p.get_Point(2));

}
Primitive Primitive::operator-(Primitive p) {
	return Primitive(this->_point[0] - p.get_Point(0), this->_point[1] - p.get_Point(1), this->_point[2] - p.get_Point(2));

}
Primitive Primitive::operator*(Primitive p) {
	return Primitive(this->_point[0] * p.get_Point(0), this->_point[1] * p.get_Point(1), this->_point[2] * p.get_Point(2));

}
Primitive Primitive::operator/(Primitive p) {
	return Primitive(this->_point[0] / p.get_Point(0), this->_point[1] / p.get_Point(1), this->_point[2] / p.get_Point(2));

}

/// PRIMITIVE ///////////////////////////////////////////////////////////////////////////


/// TRANSFORM ///////////////////////////////////////////////////////////////////////////

void Transform::set_Scale(a_t::Vector3D_f scale) {
	this->_scale = scale;

}

void Transform::change_Rotate(int rotate) {
	if (rotate > 360) this->_rotate = 360;
	else this->_rotate = rotate;

}

void Transform::TRANSFORM_SCALE(Primitive& primitive) {
	primitive *= Primitive(this->_scale, this->_scale, this->_scale);

}

void Transform::CONVERT_CORDINAT(Primitive primitive, GLfloat* cordinat, a_t::Vector3D_f screen_size){
	for (int i{ 0 }; i < 3; i++) {
		cordinat[i * 3] = (primitive.get_Point(i).x / (screen_size.x / 2.0f / 100.0f) - 100) / 100.0f;
		cordinat[1 + i * 3] = -(primitive.get_Point(i).y / (screen_size.y / 2.0f / 100.0f) - 100) / 100.0f;

	}

}

/// TRANSFORM ///////////////////////////////////////////////////////////////////////////


/// RECT ////////////////////////////////////////////////////////////////////////////////

void Rect::_Update() {
	this->_points[0] = this->_position;
	this->_points[1] = this->_position + a_t::Vector3D_f(this->_size.x, 0.0f, 0.0f);
	this->_points[2] = this->_position + this->_size;
	this->_points[3] = this->_position + a_t::Vector3D_f(0.0f, this->_size.y, 0.0f);

}

a_t::Vector3D_f Rect::get_Position() const {
	return this->_position;

}

void Rect::set_Position(a_t::Vector3D_f position) {
	this->_position = position;
	this->_Update();

}

a_t::Vector3D_f Rect::get_Size() const {
	return this->_size;

}

void Rect::set_Size(a_t::Vector3D_f size) {
	this->_size = size;
	this->_Update();

}

int Rect::get_Count_Point() const {
	return this->_count_point;

}

a_t::Vector3D_f Rect::get_Point(int index) const {
	return this->_points[index];

}

a_t::Vector3D_f* Rect::get_Points() {
	return this->_points;

}

void Rect::set_Color(a_t::Vector3D_f color, float alpha) {
	this->_color[0] = color.x; this->_color[1] = color.y; this->_color[2] = color.z;
	this->_color[3] = alpha;

}

float* Rect::get_Color() {
	return this->_color;

}


/// RECT ////////////////////////////////////////////////////////////////////////////////


/// DRAW_ON_SCREEN //////////////////////////////////////////////////////////////////////

Draw_on_screen::Draw_on_screen(a_t::Vector3D_f screen_size) {
	this->_screen_size = screen_size;
	this->_cordinat[0] = 0.0f; this->_cordinat[1] = 0.0f; this->_cordinat[2] = 0.0f;
	this->_cordinat[3] = 0.0f; this->_cordinat[4] = 0.0f; this->_cordinat[5] = 0.0f;
	this->_cordinat[6] = 0.0f; this->_cordinat[7] = 0.0f; this->_cordinat[8] = 0.0f;

}

void Draw_on_screen::Draw(Rect RECT, Shader_Program shader_program) {
	for (int i{ 0 }; i < RECT.get_Count_Point() - 2; i++) {

		_primitive = Primitive(RECT.get_Point(0), RECT.get_Point(1 + i), RECT.get_Point(2 + i));

		RECT.TRANSFORM_SCALE(_primitive);
		RECT.CONVERT_CORDINAT(_primitive, this->_cordinat, this->_screen_size);

		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);


		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->_cordinat), this->_cordinat, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
		glBindVertexArray(0);

		shader_program.USE();
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

}

/// DRAW_ON_SCREEN //////////////////////////////////////////////////////////////////////




