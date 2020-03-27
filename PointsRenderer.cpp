#include "PointsRenderer.h"

PointsRenderer::PointsRenderer(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr) throw(std::string) : shader(shdr) {
	try {
		updatePoints(pts);
	}
	catch (std::string & e) {
		throw e;
	}
	try {
		updateColors(clrs);
	}
	catch (std::string & e) {
		delete this->points;
		this->points = nullptr;
		throw e;
	}

	GLCall(glGenVertexArrays(1, &this->VAO));
	GLCall(glGenBuffers(2, this->VBO));
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->nbPoints * 3 * sizeof(float), this->points, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->nbPoints * 3 * sizeof(float), this->colors, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

PointsRenderer::~PointsRenderer(void) {
	delete[] this->points;
	this->points = NULL;
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(2, this->VBO);
}

void PointsRenderer::updatePoints(std::vector<glm::vec3> pts) throw(std::string) {
	if (pts.empty())
		throw std::string("The size of points list is empty !");

	if (pts.size() != this->nbPoints) {
		this->nbPoints = pts.size();
		if (this->points != nullptr)
			delete this->points;
		this->points = new float[this->nbPoints * 3];
		if (this->colors != nullptr)
			delete this->colors;
		this->colors = new float[this->nbPoints * 3];
	}

	for (size_t i = 0; i < this->nbPoints; i++) {
		this->points[3 * i] = pts[i].x;
		this->points[(3 * i) + 1] = pts[i].y;
		this->points[(3 * i) + 2] = pts[i].z;
	}
}

void PointsRenderer::updateColors(std::vector<glm::vec3> clrs) throw(std::string) {
	if (clrs.size() != this->nbPoints && !clrs.empty() && clrs.size() != 1)
		throw std::string("The size of colors list does not match with the number of points contained in the points list !");

	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	if (clrs.size() == 1)
		color = clrs[0];

	for (size_t i = 0; i < this->nbPoints; i++) {
		if (!clrs.empty() && clrs.size() != 1)
			color = clrs[i];
		this->colors[3 * i] = color.x;
		this->colors[(3 * i) + 1] = color.y;
		this->colors[(3 * i) + 2] = color.z;
	}
}

void PointsRenderer::updateVAO(void) {
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->VBO[0]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->nbPoints * 3 * sizeof(float), this->points, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->VBO[1]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->nbPoints * 3 * sizeof(float), this->colors, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void PointsRenderer::draw(void) {
	this->shader->use();
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glDrawArrays(GL_POINTS, 0, static_cast<unsigned int>(nbPoints)));
	GLCall(glBindVertexArray(0));
}
