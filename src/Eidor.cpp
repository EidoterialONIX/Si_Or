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

    Primitive(a_t::Vector3D_f v0, a_t::Vector3D_f v1, a_t::Vector3D_f v2) {

        _point[0] = v0; _point[1] = v1; _point[2] = v2;

    };

    a_t::Vector3D_f& get_Point(int index) { return _point[index]; }
    void set_Point(int index, a_t::Vector3D_f v) { _point[index] = v; }

    void operator=(Primitive p) {

        _point[0] = p.get_Point(0); _point[1] = p.get_Point(1); _point[2] = p.get_Point(2);

    }

    bool operator==(Primitive p) { if (_point[0] == p.get_Point(0) && _point[1] == p.get_Point(1) && _point[2] == p.get_Point(2)) return true; else return false; }

    Primitive operator+(Primitive p) { return Primitive(_point[0] + p.get_Point(0), _point[1] + p.get_Point(1), _point[2] + p.get_Point(2)); }
    Primitive operator-(Primitive p) { return Primitive(_point[0] - p.get_Point(0), _point[1] - p.get_Point(1), _point[2] - p.get_Point(2)); }
    Primitive operator*(Primitive p) { return Primitive(_point[0] * p.get_Point(0), _point[1] * p.get_Point(1), _point[2] * p.get_Point(2)); }
    Primitive operator/(Primitive p) { return Primitive(_point[0] / p.get_Point(0), _point[1] / p.get_Point(1), _point[2] / p.get_Point(2)); }

    void operator+=(Primitive p) {

        _point[0] = _point[0] + p.get_Point(0); _point[1] = _point[1] + p.get_Point(1); _point[2] = _point[2] + p.get_Point(2);

    }
    void operator-=(Primitive p) {

        _point[0] = _point[0] - p.get_Point(0); _point[1] = _point[1] - p.get_Point(1); _point[2] = _point[2] - p.get_Point(2);

    }
    void operator*=(Primitive p) {

        _point[0] = _point[0] * p.get_Point(0); _point[1] = _point[1] * p.get_Point(1); _point[2] = _point[2] * p.get_Point(2);

    }
    void operator/=(Primitive p) {

        _point[0] = _point[0] / p.get_Point(0); _point[1] = _point[1] / p.get_Point(1); _point[2] = _point[2] / p.get_Point(2);

    }

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

    void set_Scale(a_t::Vector3D_f scale) { _scale = scale; }

    void change_Rotate(int rotate) { if (_rotate == 360) _rotate = 0; else _rotate += rotate; }

    void TRANSFORM_SCALE(Primitive& primitive) {
        primitive *= Primitive(_scale, _scale, _scale);
    }

    void CONVERT_CORDINAT(Primitive primitive, GLfloat* cordinat, a_t::Vector3D_f screen_size) {

        for (int i{ 0 }; i < 3; i++) {
            cordinat[i * 3] = (primitive.get_Point(i).x / (screen_size.x / 2.0f / 100.0f) - 100) / 100.0f;
            cordinat[1 + i * 3] = -(primitive.get_Point(i).y / (screen_size.y / 2.0f / 100.0f) - 100) / 100.0f;

        }

    }

};

class Rect : public Transform {
private:

    a_t::Vector3D_f _position;

    a_t::Vector3D_f _size;

    int _count_point = 4;

    a_t::Vector3D_f _points[4];

    a_t::Vector3D_f _origin;

    float _color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    void _Update() {

        _points[0] = _position;
        _points[1] = _position + a_t::Vector3D_f(_size.x, 0.0f, 0.0f);
        _points[2] = _position + _size;
        _points[3] = _position + a_t::Vector3D_f(0.0f, _size.y, 0.0f);

    }

public:

    Rect() {

        _position = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

        _size = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

        _origin = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

        _Update();

    };

    a_t::Vector3D_f get_Position() const { return _position; }
    void set_Position(a_t::Vector3D_f position) { _position = position; _Update(); }

    a_t::Vector3D_f get_Size() const { return _size; }
    void set_Size(a_t::Vector3D_f size) { _size = size; _Update(); }

    int get_Count_Point() const { return _count_point; }

    a_t::Vector3D_f get_Point(int index) const { return _points[index]; }
    a_t::Vector3D_f* get_Points() { return _points; }

    void set_Color(float red, float green, float blue, float alpha) { _color[0] = red; _color[1] = green; _color[2] = blue; _color[3] = alpha; };
    float* get_Color() { return _color; }
};


class Draw_on_screen {

    a_t::Vector3D_f _screen_size = a_t::Vector3D_f(0.0f, 0.0f, 0.0f);

    GLuint VBO = 0;
    GLuint VAO = 0;

    Primitive _primitive;

    GLfloat _cordinat[9];


public:

    Draw_on_screen(a_t::Vector3D_f screen_size) {
        _screen_size = screen_size;
        _cordinat[0] = 0.0f; _cordinat[1] = 0.0f; _cordinat[2] = 0.0f;
        _cordinat[3] = 0.0f; _cordinat[4] = 0.0f; _cordinat[5] = 0.0f;
        _cordinat[6] = 0.0f; _cordinat[7] = 0.0f; _cordinat[8] = 0.0f;

    };

    void Draw(Rect RECT, Shader_Program shader_program) {

        for (int i{ 0 }; i < RECT.get_Count_Point() - 2; i++) {

            _primitive = Primitive(RECT.get_Point(0), RECT.get_Point(1 + i), RECT.get_Point(2 + i));

            RECT.TRANSFORM_SCALE(_primitive);
            RECT.CONVERT_CORDINAT(_primitive, _cordinat, _screen_size);

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);


            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(_cordinat), _cordinat, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindVertexArray(0);

            shader_program.USE();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

        }

    }

};