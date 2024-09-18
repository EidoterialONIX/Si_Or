cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project (Si_Or)

add_executable(Si_Or src/main.cpp src/Eidor.cpp 
							src/Render/Shader.h src/Render/Shader.cpp)

add_subdirectory(external/glad)
target_link_libraries(Si_Or glad)

add_subdirectory(external/glfw)
target_link_libraries(Si_Or glfw)