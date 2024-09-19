#include "Shader.h"


Shader_Program::Shader_Program(const char* vertex_path, const char* fragment_path) {

    std::string vertex_shader_code;
    std::string fragment_shader_code;

    std::ifstream vertex_shader_file;
    std::ifstream fragment_shader_file;

    vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {

        vertex_shader_file.open(vertex_path);
        fragment_shader_file.open(fragment_path);

        std::stringstream vertex_shader_stream, fragment_shader_stream;

        vertex_shader_stream << vertex_shader_file.rdbuf();
        fragment_shader_stream << fragment_shader_file.rdbuf();

        vertex_shader_file.close();
        fragment_shader_file.close();

        vertex_shader_code = vertex_shader_stream.str();
        fragment_shader_code = fragment_shader_stream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vertex_shader = vertex_shader_code.c_str();
    const char* fragment_shader = fragment_shader_code.c_str();

    GLuint vertex_sh = 0;
    vertex_sh = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_sh, 1, &vertex_shader, NULL);
    glCompileShader(vertex_sh);
    Check_Correct_Compile(vertex_sh, "Vertex\n");

    GLuint fragment_sh = 0;
    fragment_sh = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_sh, 1, &fragment_shader, NULL);
    glCompileShader(fragment_sh);
    Check_Correct_Compile(fragment_sh, "Fragment\n");

    _shader_program = glCreateProgram();

    glAttachShader(_shader_program, vertex_sh);
    glAttachShader(_shader_program, fragment_sh);
    glLinkProgram(_shader_program);
    Check_Correct_Link();

    glDeleteShader(vertex_sh);
    glDeleteShader(fragment_sh);


}

void Shader_Program::USE() {

    glUseProgram(_shader_program);

}

void Shader_Program::Check_Correct_Compile(GLuint id, const char* type) {

    int success = 0;
    char log[512];

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, log);
        std::cout << type << log << std::endl;

    }

}

void Shader_Program::Check_Correct_Link() {

    int success = 0;
    char log[512];

    glGetProgramiv(_shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(_shader_program, 512, NULL, log);
        std::cout << "Linker\n" << log << std::endl;

    }

}
