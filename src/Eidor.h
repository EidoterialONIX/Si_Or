#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render/Shader.h"

#include "Vectors.h"



class Primitive {
private:

    a_t::Vector3D_f _point[3];

public:

    Primitive() = default;

    Primitive(a_t::Vector3D_f v0, a_t::Vector3D_f v1, a_t::Vector3D_f v2);

    a_t::Vector3D_f& get_Point(int index);
    void set_Point(int index, a_t::Vector3D_f v);

    void operator=(Primitive p);

    bool operator==(Primitive p);

    void operator+=(Primitive p);
    void operator-=(Primitive p);
    void operator*=(Primitive p);
    void operator/=(Primitive p);

    Primitive operator+(Primitive p);
    Primitive operator-(Primitive p);
    Primitive operator*(Primitive p);
    Primitive operator/(Primitive p);

};

struct Options {

    int WINDOW_SIZE[2] = { 640, 480 };


};

class Transform {
private:

    a_t::Vector3D_f _scale = a_t::Vector3D_f(1.0f, 1.0f, 1.0f);

    int _rotate = 0;

public:

    Transform() = default;

    void set_Scale(a_t::Vector3D_f scale);

    void change_Rotate(int rotate);
    void TRANSFORM_SCALE(Primitive& primitive);

    void CONVERT_CORDINAT(Primitive primitive, GLfloat* cordinat, a_t::Vector3D_f screen_size);

};

class Rect : public Transform {
private:

    a_t::Vector3D_f _position = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

    a_t::Vector3D_f _size = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

    int _count_point = 4;

    a_t::Vector3D_f _points[4];

    a_t::Vector3D_f _origin = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

    float _color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    void _Update();

public:

    Rect() = default;

    a_t::Vector3D_f get_Position() const;
    void set_Position(a_t::Vector3D_f position);

    a_t::Vector3D_f get_Size() const;
    void set_Size(a_t::Vector3D_f size);

    int get_Count_Point() const;

    a_t::Vector3D_f get_Point(int index) const;
    a_t::Vector3D_f* get_Points();

    void set_Color(a_t::Vector3D_f color, float alpha);
    float* get_Color();
};


class Draw_on_screen {

    a_t::Vector3D_f _screen_size = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

    GLuint VBO = 0;
    GLuint VAO = 0;

    Primitive _primitive;

    GLfloat _cordinat[9];


public:

    Draw_on_screen(a_t::Vector3D_f screen_size);

    void Draw(Rect RECT, Shader_Program shader_program);

};