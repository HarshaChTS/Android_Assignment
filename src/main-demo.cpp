#include "renderer.h"
#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include "myparticlesystem.h"

using namespace std;
using namespace glm;
using namespace agl;

std::vector<MyParticleSystem> fireworkSystems;

MyParticleSystem theSystem;
MyParticleSystem theSystem2;
MyParticleSystem theSystem3;
MyParticleSystem theSystem4;

float x_explos;
float y_explos;
bool clicked;

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // Prevent a divide by zero
    if (height == 0)
        height = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);
    ParticleSystem::GetRenderer().perspective(radians(60.0f), 1.0f, 0.1f, 100.0f);
}

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // TODO: CAmera controls

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS)
    {
        clicked = true;
        x_explos = float(xpos) / (-112.5f) + 4;
        y_explos = float(ypos) / (112.5f) - 4;
        cout << "click " << x_explos << " " << y_explos << endl;

        MyParticleSystem system;
        system.setOffset(vec3(x_explos, y_explos, 0) + vec3(0, 3, 0));
        system.setColor(vec3(abs(random_float(0, 1)), abs(random_float(0, 1)), abs(random_float(0, 1))));
        system.init(100);
        system.count = 0;
        fireworkSystems.push_back(system);
        system.draw();
    }
    else
    {
        clicked = false;
    }
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
}

static void PrintShaderErrors(GLuint id, const std::string label)
{
    std::cerr << label << " failed\n";
    GLint logLen;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0)
    {
        char *log = (char *)malloc(logLen);
        GLsizei written;
        glGetShaderInfoLog(id, logLen, &written, log);
        std::cerr << "Shader log: " << log << std::endl;
        std::printf("%s\n", &(log[0]));
        free(log);
    }
}

static std::string LoadShaderFromFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file)
    {
        std::cout << "Cannot load file: " << fileName << std::endl;
        return "";
    }

    std::stringstream code;
    code << file.rdbuf();
    file.close();

    return code.str();
}

int main(int argc, char **argv)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        return -1;
    }

    // Explicitly ask for a 4.0 context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    float width = 900;
    float height = 900;
    window = glfwCreateWindow(width, height, "Particle Viewer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

#ifndef APPLE
    if (glewInit() != GLEW_OK)
    {
        cout << "Cannot initialize GLEW\n";
        return -1;
    }
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor(0, 0, 0, 1);

    theSystem.setOffset(vec3(1.5, 2, 0));
    theSystem.setColor(vec3(0.6f, 0.2f, 0.8f));
    theSystem.init(100);
    theSystem.count = 0;

    theSystem2.setOffset(vec3(-2, 1, 0));
    theSystem2.setColor(vec3(0.2f, 0.5f, 0.9f));
    theSystem2.init(100);

    theSystem3.setOffset(vec3(0.5f, 1.5, 0));
    theSystem3.setColor(vec3(0.4f, 0.9f, 0.4f));
    theSystem3.init(100);

    theSystem4.setOffset(vec3(2, 1, 0));
    theSystem4.setColor(vec3(0.87f, 0.34f, 0.4f));
    theSystem4.init(100);

    float fov = radians(45.0f);
    ParticleSystem::GetRenderer().perspective(fov, 1.0f, 0.1f, 10.0f);
    ParticleSystem::GetRenderer().lookAt(vec3(0, 0, 8), vec3(0, 0, 0));

    float lastTime = glfwGetTime();
    theSystem.draw();

    int counter = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

        float dt = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        for (int i = 0; i < fireworkSystems.size(); i++)
        {
            // MyParticleSystem cur_syst = fireworkSystems[i];
            fireworkSystems[i].update(dt);
            fireworkSystems[i].draw();
            fireworkSystems[i].count++;
        }

        // 1st firework starts right away
        theSystem.update(dt);
        theSystem.draw();
        theSystem.count++;

        // initiate second firework with a slight delay
        if (counter == 3500)
        {
            theSystem2.draw();
        }
        else if (counter > 3500)
        {
            theSystem2.update(dt);
            theSystem2.draw();
        }

        // initiate third firework with a slight delay
        if (counter == 6000)
        {
            theSystem3.draw();
        }
        else if (counter > 6000)
        {
            theSystem3.update(dt);
            theSystem3.draw();
        }

        // initiate third firework with a slight delay
        if (counter == 8500)
        {
            theSystem4.draw();
        }
        else if (counter > 8500)
        {
            theSystem4.update(dt);
            theSystem4.draw();
        }

        // explode 1st firework
        if (counter == 3500)
        {
            theSystem.explodeParticles(100);
        }
        // explode 2nd firework
        if (counter == 6800)
        {
            theSystem2.explodeParticles(250);
        }
        // explode 3rd firework
        if (counter == 8000)
        {
            theSystem3.explodeParticles(100);
        }
        // explode 4th firework
        if (counter == 10000)
        {
            theSystem4.explodeParticles(200);
        }

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
        counter++;
    }

    glfwTerminate();
    return 0;
}
