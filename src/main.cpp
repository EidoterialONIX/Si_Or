#include "Eidor.h"
#include "Render/Shader.h"
#include "Location/Location.h"
#include "Location/Map_Location.h"
#include "Camera.h"

#include <vector>
#include <math.h>


Options _option;

Draw_on_screen drawing = Draw_on_screen(a_t::Vector3D_f(_option.WINDOW_SIZE[0], _option.WINDOW_SIZE[1], 0.0f));

Camera camera(a_t::Vector2D_f(_option.WINDOW_SIZE[0], _option.WINDOW_SIZE[1]));



void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    _option.WINDOW_SIZE[0] = width;
    _option.WINDOW_SIZE[1] = height;
    glViewport(0, 0, _option.WINDOW_SIZE[0], _option.WINDOW_SIZE[1]);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        camera.move_Camera('A');
        camera.show_Camera_Info();
    }
    else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        camera.move_Camera('D');
        camera.show_Camera_Info();
    }
    else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        camera.move_Camera('W');
        camera.show_Camera_Info();
    }
    else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        camera.move_Camera('S');
        camera.show_Camera_Info();
    }
}


int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(_option.WINDOW_SIZE[0], _option.WINDOW_SIZE[1], "OGL_P", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);



    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);



    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1); 

    Rect rect;

    rect.set_Position(a_t::Vector3D_f(100.0f, 100.0f, 0.0f));
    rect.set_Size(a_t::Vector3D_f(100.0f, 100.0f, 0.0f));

	Shader_Program shader = Shader_Program("E:/project/Si_Or/src/Render/Shaders/Basic_vertex.txt", "E:/project/Si_Or/src/Render/Shaders/Basic_fragment.txt");


    Location loc(a_t::Vector2D_f(100.0f, 100.0f));

    loc.set_Elements_Location(110, 170, 255);
    loc.generate_Location(true);
    loc.show_Main_Location();

    Map_Location map_location(loc.get_Main_Location());
    map_location.show_Map_Location(false);

    camera.show_Camera_Info();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        drawing.Draw(rect, shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}