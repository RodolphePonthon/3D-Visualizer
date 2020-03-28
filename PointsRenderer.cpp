#include "PointsRenderer.h"

PointsRenderer::PointsRenderer(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr) : RenderableMesh(pts, clrs, shdr) {
	assert(updatePoints(pts));
	assert(updateColors(clrs));
	initializeVAO();
}

void PointsRenderer::draw(void) {
	this->shader->use();
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glDrawArrays(GL_POINTS, 0, static_cast<unsigned int>(nbPoints)));
	GLCall(glBindVertexArray(0));
}
