#include <glad/glad.h>
#include <iostream>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/string_cast.hpp>

#include "GlfwWindow.h"
#include "Camera.h"
#include "PointsRenderer.h"
#include "VectorsRenderer.h"
#include "Shader.h"
#include "GLError.h"
#include "GeometryFileReader.h"

// Settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 600;

int main(int argc, char** argv) {

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), SCR_WIDTH, SCR_HEIGHT, 45.0f, 0.1f, 100000.0f);

	GlfwWindow* window = nullptr;
	try {
		window = new GlfwWindow(SCR_WIDTH, SCR_HEIGHT, "3D Visualizer", false, camera);
	}
	catch (std::string & e) {
		std::cout << "Exception : " << e << std::endl;
		delete camera;
		camera = NULL;
		return -1;
	}

	std::string fileName = "input.csv";
	if (argc >= 2) {
		fileName = argv[1];
	}
	GeometryFileReader* fileData;
	try {
		fileData = new GeometryFileReader(fileName);
	}
	catch (std::string & e) {
		std::cout << "Exception : " << e << std::endl;
		delete camera;
		camera = NULL;
		delete window;
		window = NULL;
		return -1;
	}

	Shader* shader = new Shader("Shaders/pointsRendererShaders.vs", "Shaders/pointsRendererShaders.fs");
	glm::mat4 model = glm::mat4(1.0f);

	PointsRenderer* pointsRenderer = new PointsRenderer(fileData->getPoints(), fileData->getColors(), shader);

	std::vector<glm::vec3> axisPoints;
	std::vector<glm::vec3> axisColors;
	axisPoints.push_back(glm::vec3(-1000000.0f, 0.0f, 0.0f));
	axisPoints.push_back(glm::vec3(1000000.0f, 0.0f, 0.0f));
	axisColors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	axisPoints.push_back(glm::vec3(0.0f, -1000000.0f, 0.0f));
	axisPoints.push_back(glm::vec3(0.0f, 1000000.0f, 0.0f));
	axisColors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	axisPoints.push_back(glm::vec3(0.0f, 0.0f, -1000000.0f));
	axisPoints.push_back(glm::vec3(0.0f, 0.0f, 1000000.0f));
	axisColors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	VectorsRenderer* axisXYZ = new VectorsRenderer(axisPoints, axisColors, shader);

	std::vector<glm::vec3> axisPositivePoints;
	std::vector<glm::vec3> axisPositiveColors;
	axisPositivePoints.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	axisPositiveColors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	axisPositivePoints.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	axisPositiveColors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	axisPositivePoints.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	axisPositiveColors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	PointsRenderer* axisXYZArrows = new PointsRenderer(axisPositivePoints, axisPositiveColors, shader);

	GLCall(glClearColor(0.15f, 0.15f, 0.15f, 1.0f));
	GLCall(glEnable(GL_PROGRAM_POINT_SIZE));
	GLCall(glEnable(GL_DEPTH_TEST));
	while (!window->shouldStop()) {
		window->processEvents();
		shader->setMat4("view", camera->getViewMatrix());
		shader->setMat4("projection", camera->getProjectionMatrix());
		shader->setMat4("model", model);
		shader->setVec3("cameraPos", camera->getPosition());
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		pointsRenderer->draw();
		if (window->areAxisXYZDisplayed()) {
			axisXYZ->draw();
			axisXYZArrows->draw();
		}

		window->swapBuffers();
		window->lookForEvents();
	}

	delete window;
	window = NULL;
	delete shader;
	shader = NULL;
	delete camera;
	camera = NULL;
	delete pointsRenderer;
	pointsRenderer = NULL;
	delete axisXYZ;
	axisXYZ = NULL;
	delete axisXYZArrows;
	axisXYZArrows = NULL;
	delete fileData;
	fileData = NULL;
	return 0;
}