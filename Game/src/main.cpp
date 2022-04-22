#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Scene/Entity.h"
#include "Rendering/Camera.h"
#include "Rendering/Mesh.h"

Camera camera;

int main()
{
	Window window(800, 600, "TEST");

	std::vector<Vertex> temp;
	temp.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f))); // 0
	temp.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f))); // 1
	temp.emplace_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f))); // 2
	temp.emplace_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f))); // 3

	temp.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));// 4
	temp.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f))); // 5
	temp.emplace_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));// 6
	temp.emplace_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));// 7

	temp.emplace_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f))); // 8
	temp.emplace_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f))); // 9
	temp.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f))); // 10
	temp.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f))); // 11

	temp.emplace_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f))); // 12
	temp.emplace_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f))); // 13
	temp.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f))); // 14
	temp.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f))); // 15

	temp.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f))); // 16
	temp.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f))); // 17
	temp.emplace_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f))); // 18
	temp.emplace_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f))); // 19

	temp.emplace_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))); // 20
	temp.emplace_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f))); // 21
	temp.emplace_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f))); // 22
	temp.emplace_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)));  // 23

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

	std::vector<unsigned int> temp2;
	temp2.insert(temp2.end(), &indices[0], &indices[sizeof(indices) / sizeof(unsigned int)]);

	Shader shader("res/shaders/vertex.txt", "res/shaders/fragment.txt");
	Shader lightSource("res/shaders/lightVertex.txt", "res/shaders/lightFragment.txt");
	
	Texture texture1, texture2, diffuseMap, specularMap;
	texture1.load("res/textures/container.jpg", GL_LINEAR);
	texture2.load("res/textures/awesomeface.png", GL_LINEAR);
	diffuseMap.load("res/textures/container-diffuse.png", GL_LINEAR);
	specularMap.load("res/textures/container-specular.png", GL_LINEAR);

	glViewport(0, 0, 800, 600);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	camera.update(glm::vec3(0.0f, 0.0f, 3.0f));

	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(3.0f, 0.0f, 0.0f);

	Mesh box(temp, temp2);

	while (!window.shouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		texture1.bind();
		glActiveTexture(GL_TEXTURE1);
		texture2.bind();
		glActiveTexture(GL_TEXTURE2);
		diffuseMap.bind();
		glActiveTexture(GL_TEXTURE3);
		specularMap.bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0));

		glm::mat4 proj = glm::mat4(1.0f);
		proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		shader.use();
		shader.setInt("material.diffuse", 2);
		shader.setInt("material.specular", 3);
		shader.setFloat("material.shininess", 64.0f);

		shader.setMat4("model", model);
		shader.setMat4("view", camera.view);
		shader.setMat4("proj", proj);

		shader.setVec3("pointLights[0].position", lightPos);
		shader.setFloat("pointLights[0].constant", 1.0f);
		shader.setFloat("pointLights[0].linear", 0.09f);
		shader.setFloat("pointLights[0].quadratic", 0.032f);
		shader.setVec3("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
		shader.setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
		shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);

		shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader.setVec3("dirLight.ambient", 0.2f, 0.2f, 0.2f);
		shader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
		shader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

		glm::vec3 cameraPos = camera.getPosition();
		glm::vec3 cameraFront = camera.getFront();
		shader.setVec3("cameraPos", cameraPos);
		shader.setVec3("spotLight.position", cameraPos);
		shader.setVec3("spotLight.direction", cameraFront);
		shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		shader.setFloat("spotLight.constant", 1.0f);
		shader.setFloat("spotLight.linear", 0.09f);
		shader.setFloat("spotLight.quadratic", 0.032f);
		shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

		box.draw(shader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);

		lightSource.use();
		lightSource.setMat4("model", model);
		lightSource.setMat4("view", camera.view);
		lightSource.setMat4("proj", proj);
		lightSource.setVec3("lightColor", lightColor);

		box.draw(lightSource);

		window.swapAndPoll();
	}
		
	glfwTerminate();
	return 0;
}