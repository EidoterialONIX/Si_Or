cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project (Si_Or)

add_executable(Si_Or src/main.cpp src/Eidor.cpp 
							src/Render/Shader.h src/Render/Shader.cpp 
							src/Location/Location.h src/Location/Location.cpp 
							src/Location/Map_Location.h src/Location/Map_Location.cpp)

add_subdirectory(external/glad)
target_link_libraries(Si_Or glad)

add_subdirectory(external/glfw)
target_link_libraries(Si_Or glfw)

add_subdirectory(src/add_tools/Vectors)
target_link_libraries(Si_Or add_tools)