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

bool clicked = false;
float x_explos;
float y_explos;

// Explosion flags to trigger only once
bool exploded1 = false;
bool exploded2 = false;
bool exploded3 = false;
bool exploded4 = false;

// For click-spawned fireworks explosions tracking
std::vector<bool> explodedClicks;

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
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
    ParticleSystem::GetRenderer().perspective(radians(60.0f), 1.0f, 0.1f, 100.0f);
}

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

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
        explodedClicks.push_back(false); // no explosion triggered yet for this system
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    theSystem2.count = 0;

    theSystem3.setOffset(vec3(0.5f, 1.5, 0));
    theSystem3.setColor(vec3(0.4f, 0.9f, 0.4f));
    theSystem3.init(100);
    theSystem3.count = 0;

    theSystem4.setOffset(vec3(2, 1, 0));
    theSystem4.setColor(vec3(0.87f, 0.34f, 0.4f));
    theSystem4.init(100);
    theSystem4.count = 0;

    float fov = radians(45.0f);
    ParticleSystem::GetRenderer().perspective(fov, 1.0f, 0.1f, 10.0f);
    ParticleSystem::GetRenderer().lookAt(vec3(0, 0, 8), vec3(0, 0, 0));

    float lastTime = glfwGetTime();

    int counter = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dt = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        // Update and draw click-spawned fireworks
        for (int i = 0; i < fireworkSystems.size(); i++)
        {
            fireworkSystems[i].update(dt);
            fireworkSystems[i].draw();
            fireworkSystems[i].count++;

            // Explode click fireworks after some lifetime (e.g., count == 100)
            if (fireworkSystems[i].count == 100 && !explodedClicks[i])
            {
                fireworkSystems[i].explodeParticles(150);
                explodedClicks[i] = true;
            }
        }

        // 1st firework always updates/draws
        theSystem.update(dt);
        theSystem.draw();
        theSystem.count++;

        // Explode 1st firework once after counter >= 3500
        if (counter >= 3500 && !exploded1)
        {
            theSystem.explodeParticles(100);
            exploded1 = true;
        }

        // Start 2nd firework after counter >= 3500
        if (counter >= 3500)
        {
            theSystem2.update(dt);
            theSystem2.draw();
            theSystem2.count++;
        }
        // Explode 2nd firework once after counter >= 6800
        if (counter >= 6800 && !exploded2)
        {
            theSystem2.explodeParticles(250);
            exploded2 = true;
        }

        // Start 3rd firework after counter >= 6000
        if (counter >= 6000)
        {
            theSystem3.update(dt);
            theSystem3.draw();
            theSystem3.count++;
        }
        // Explode 3rd firework once after counter >= 8000
        if (counter >= 8000 && !exploded3)
        {
            theSystem3.explodeParticles(100);
            exploded3 = true;
        }

        // Start 4th firework after counter >= 8500
        if (counter >= 8500)
        {
            theSystem4.update(dt);
            theSystem4.draw();
            theSystem4.count++;
        }
        // Explode 4th firework once after counter >= 10000
        if (counter >= 10000 && !exploded4)
        {
            theSystem4.explodeParticles(200);
            exploded4 = true;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        counter++;
    }

    glfwTerminate();
    return 0;
}
