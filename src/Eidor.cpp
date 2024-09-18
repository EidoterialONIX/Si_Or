#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Render/Shader.h"


template <class T>
class Vector_3 {
public:

    T _x = 0;
    T _y = 0;
    T _z = 0;

    Vector_3() = default;

    Vector_3(T x, T y, T z) : _x(x), _y(y), _z(z) {}

    void operator=(Vector_3<T> v) { _x = v._x; _y = v._y; _z = v._z; }

    bool operator==(Vector_3<T> v) { if (_x == v._x && _y == v._y && _z == v._z) return true; else return false; }

    Vector_3<T> operator+(Vector_3<T> v) { return Vector_3<T>(_x + v._x, _y + v._y, _z + v._z); }
    Vector_3<T> operator-(Vector_3<T> v) { return Vector_3<T>(_x - v._x, _y - v._y, _z - v._z); }
    Vector_3<T> operator*(Vector_3<T> v) { return Vector_3<T>(_x * v._x, _y * v._y, _z * v._z); }
    Vector_3<T> operator/(Vector_3<T> v) { return Vector_3<T>(_x / v._x, _y / v._y, _z / v._z); }

    void operator+=(Vector_3<T> v) { _x = _x + v._x; _y = _y + v._y; _z = _z + v._z; }
    void operator-=(Vector_3<T> v) { _x = _x - v._x; _y = _y - v._y; _z = _z - v._z; }
    void operator*=(Vector_3<T> v) { _x = _x * v._x; _y = _y * v._y; _z = _z * v._z; }
    void operator/=(Vector_3<T> v) { _x = _x / v._x; _y = _y / v._y; _z = _z / v._z; }

};

class Primitive {
private:

    Vector_3<float> _point[3];

public:

    Primitive() = default;

    Primitive(Vector_3<float> v0, Vector_3<float> v1, Vector_3<float> v2) {

        _point[0] = v0; _point[1] = v1; _point[2] = v2;

    };

    Vector_3<float>& get_Point(int index) { return _point[index]; }
    void set_Point(int index, Vector_3<float> v) { _point[index] = v; }

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

    Vector_3<float> _scale = Vector_3<float>(1.0f, 1.0f, 1.0f);

    int _rotate = 0;


public:

    Transform() = default;

    void set_Scale(Vector_3<float> scale) { _scale = scale; }

    void change_Rotate(int rotate) { if (_rotate == 360) _rotate = 0; else _rotate += rotate; }

    void TRANSFORM_SCALE(Primitive& primitive) {
        primitive *= Primitive(_scale, _scale, _scale);
    }

    void CONVERT_CORDINAT(Primitive primitive, GLfloat* cordinat, Vector_3<float> screen_size) {

        for (int i{ 0 }; i < 3; i++) {
            cordinat[i * 3] = (primitive.get_Point(i)._x / (screen_size._x / 2.0f / 100.0f) - 100) / 100.0f;
            cordinat[1 + i * 3] = -(primitive.get_Point(i)._y / (screen_size._y / 2.0f / 100.0f) - 100) / 100.0f;

        }

    }

};

class Rect : public Transform {
private:

    Vector_3<float> _position;

    Vector_3<float> _size;

    int _count_point = 4;

    Vector_3<float> _points[4];

    Vector_3<float> _origin;

    float _color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

    void _Update() {

        _points[0] = _position;
        _points[1] = _position + Vector_3<float>(_size._x, 0.0f, 0.0f);
        _points[2] = _position + _size;
        _points[3] = _position + Vector_3<float>(0.0f, _size._y, 0.0f);

    }

public:

    Rect() {

        _position = Vector_3<float>(0.0f, 0.0f, 0.0f);

        _size = Vector_3<float>(0.0f, 0.0f, 0.0f);

        _origin = Vector_3<float>(0.0f, 0.0f, 0.0f);

        _Update();

    };

    Vector_3<float> get_Position() const { return _position; }
    void set_Position(Vector_3<float> position) { _position = position; _Update(); }

    Vector_3<float> get_Size() const { return _size; }
    void set_Size(Vector_3<float> size) { _size = size; _Update(); }

    int get_Count_Point() const { return _count_point; }

    Vector_3<float> get_Point(int index) const { return _points[index]; }
    Vector_3<float>* get_Points() { return _points; }

    void set_Color(float red, float green, float blue, float alpha) { _color[0] = red; _color[1] = green; _color[2] = blue; _color[3] = alpha; };
    float* get_Color() { return _color; }
};


class Draw_on_screen {

    Vector_3<float> _screen_size = Vector_3<float>(0.0f, 0.0f, 0.0f);

    GLuint VBO = 0;
    GLuint VAO = 0;

    Primitive _primitive;

    GLfloat _cordinat[9];


public:

    Draw_on_screen(Vector_3<float> screen_size) {
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