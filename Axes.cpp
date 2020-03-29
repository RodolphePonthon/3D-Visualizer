#include "Axes.h"

Axes::Axes(Shader* shader) {
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
	this->axes = new VectorsRenderer(axisPoints, axisColors, shader);

	std::vector<glm::vec3> axisPositivePoints;
	std::vector<glm::vec3> axisPositiveColors;
	axisPositivePoints.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	axisPositiveColors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	axisPositivePoints.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	axisPositiveColors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	axisPositivePoints.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	axisPositiveColors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	this->directionPoints = new PointsRenderer(axisPositivePoints, axisPositiveColors, shader);
}

Axes::~Axes(void) {
	delete this->axes;
	this->axes = NULL;
	delete this->directionPoints;
	this->directionPoints = NULL;
}

void Axes::draw(void) {
	this->axes->draw();
	this->directionPoints->draw();
}
