#include "PointsRenderer.h"

PointsRenderer::PointsRenderer(std::vector<glm::vec3> pts, Shader* shdr) : shader(shdr) {
	this->nbPoints = pts.size();
	this->points = new float[this->nbPoints * 3];
	for (size_t i = 0; i < this->nbPoints; i++) {
		this->points[3 * i] = pts[i].x;
		this->points[(3 * i) + 1] = pts[i].y;
		this->points[(3 * i) + 2] = pts[i].z;
	}

	GLCall(glGenVertexArrays(1, &this->VAO));
	GLCall(glGenBuffers(1, &this->VBO));
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->nbPoints * 3 * sizeof(float), this->points, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

PointsRenderer::~PointsRenderer(void) {
	delete[] this->points;
	this->points = NULL;
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void PointsRenderer::updateData(void) {
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->VBO));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->nbPoints * 3 * sizeof(float), this->points, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
}

void PointsRenderer::draw(void) {
	this->shader->use();
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glDrawArrays(GL_POINTS, 0, static_cast<unsigned int>(nbPoints)));
	GLCall(glBindVertexArray(0));
}
