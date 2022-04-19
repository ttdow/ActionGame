#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Scene/Entity.h"
#include "Rendering/Camera.h"

Camera camera;

int main()
{
	Window window(800, 600, "TEST");

	float vertices[] = 
	{
		// Vertex			  // Texture
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // 0
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // 1
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 3
		
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 4
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 5
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // 6
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // 7

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 8
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 9
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 10
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 11

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 12
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 13
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 14
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 15

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // 16
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // 17
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // 18
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // 19

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // 20
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // 21
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // 22
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // 23
	};

	unsigned int indices[] = 
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);	

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader shader("res/shaders/vertex.txt", "res/shaders/fragment.txt");
	Shader lightSource("res/shaders/lightVertex.txt", "res/shaders/lightFragment.txt");
	
	Texture texture1, texture2;
	texture1.load("res/textures/container.jpg", GL_LINEAR);
	texture2.load("res/textures/awesomeface.png", GL_LINEAR);

	glViewport(0, 0, 800, 600);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	camera.update(glm::vec3(0.0f, 0.0f, 3.0f));

	while (!window.shouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		texture1.bind();
		glActiveTexture(GL_TEXTURE1);
		texture2.bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0));

		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		shader.use();
		shader.setInt("texture1", 0);
		shader.setInt("texture2", 1);
		shader.setMat4("model", model);
		shader.setMat4("view", camera.view);
		shader.setMat4("proj", proj);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));

		lightSource.use();
		lightSource.setMat4("model", model);
		lightSource.setMat4("view", camera.view);
		lightSource.setMat4("proj", proj);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		window.swapAndPoll();
	}
		
	glfwTerminate();
	return 0;
}