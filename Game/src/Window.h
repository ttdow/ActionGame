#pragma once

#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowDeleter 
{
	void operator() (GLFWwindow* window) const 
	{
		glfwDestroyWindow(window);
	}
};

class Window
{
public:
	Window(int width, int height, std::string name);

	void swapAndPoll() { swapBuffer(); glfwPollEvents(); }
	void swapBuffer() { glfwSwapBuffers(window.get()); }
	int shouldClose() { return glfwWindowShouldClose(window.get()); }
	GLFWwindow* getWindow() { return window.get(); };

private:
	std::unique_ptr<GLFWwindow, WindowDeleter> window;

	void setup();
	int verifyGLFW();
	int verifyGLAD();

	int width;
	int height;
	std::string title;

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};