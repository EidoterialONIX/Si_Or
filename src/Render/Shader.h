#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader_Program {
private:

    GLuint _shader_program = 0;

    void Check_Correct_Compile(GLuint id, const char* type);

    void Check_Correct_Link();


public:

    Shader_Program(const char* vertex_path, const char* fragment_path);

    void USE();

};