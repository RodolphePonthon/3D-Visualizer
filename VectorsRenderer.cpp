#include "VectorsRenderer.h"

VectorsRenderer::VectorsRenderer(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr) : RenderableMesh(pts, clrs, shdr) {
	assert(updatePoints(pts));
	assert(updateColors(clrs));
	initializeVAO();
}

bool VectorsRenderer::updateColors(std::vector<glm::vec3> clrs) {
	if (clrs.size() != this->nbPoints && !clrs.empty() && clrs.size() != 1 && this->nbPoints / clrs.size() != 2) {
		std::cout << "The size of colors list does not match with the number of points contained in the points list !" << std::endl;
		return false;
	}

	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	if (clrs.size() == 1)
		color = clrs[0];

	for (size_t i = 0; i < this->nbPoints; i++) {
		if (!clrs.empty() && clrs.size() != 1 && this->nbPoints / clrs.size() != 2) {
			color = clrs[i];
		}
		else if (!clrs.empty() && clrs.size() != 1 && this->nbPoints / clrs.size() == 2) {
			color = clrs[static_cast<size_t>(i / 2)];
		}
		this->colors[3 * i] = color.x;
		this->colors[(3 * i) + 1] = color.y;
		this->colors[(3 * i) + 2] = color.z;
	}
	return true;
}

void VectorsRenderer::draw(void) {
	this->shader->use();
	GLCall(glBindVertexArray(this->VAO));
	GLCall(glDrawArrays(GL_LINES, 0, static_cast<unsigned int>(nbPoints)));
	GLCall(glBindVertexArray(0));
}