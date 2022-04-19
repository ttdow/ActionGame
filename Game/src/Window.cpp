#include <iostream>

#include "Window.h"
#include "Rendering/Camera.h"

extern Camera camera;

Window::Window(int width, int height, std::string name)
	: width(width), height(height), title(title)
{
	glfwInit();
	setup();

	/*
	if (fullScreen)
	{
		window = std::unique_ptr<GLFWwindow, WindowDeleter>(glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL));
	}
	else
	{
		window = std::unique_ptr<GLFWwindow, WindowDeleter>(glfwCreateWindow(width, height, title.c_str(), NULL, NULL));
	}
	*/

	this->window = std::unique_ptr<GLFWwindow, WindowDeleter>(glfwCreateWindow(width, height, title.c_str(), NULL, NULL));
	
	verifyGLFW();

	glfwMakeContextCurrent(window.get());
	glfwSetFramebufferSizeCallback(window.get(), framebufferSizeCallback);
	glfwSetKeyCallback(window.get(), keyCallback);
	
	verifyGLAD();
}

void Window::setup() 
{
	// Define window settings
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int Window::verifyGLFW()
{
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	return 1;
}

int Window::verifyGLAD()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 1;
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		const float cameraSpeed = 0.5f;

		if (key == GLFW_KEY_W)
		{
			glm::vec3 newPos = camera.getPosition() + cameraSpeed * glm::normalize(glm::cross(camera.getUp(), camera.getRight()));
			camera.update(newPos);
		}
		else if (key == GLFW_KEY_S)
		{
			glm::vec3 newPos = camera.getPosition() - cameraSpeed * glm::normalize(glm::cross(camera.getUp(), camera.getRight()));
			camera.update(newPos);
		}
		else if (key == GLFW_KEY_A)
		{
			glm::vec3 newPos = camera.getPosition() - cameraSpeed * camera.getRight();
			camera.update(newPos);
		}
		else if (key == GLFW_KEY_D)
		{
			glm::vec3 newPos = camera.getPosition() + cameraSpeed * camera.getRight();
			camera.update(newPos);
		}
	}
}