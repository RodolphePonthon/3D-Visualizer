#ifndef VECTORRENDERER_H
#define VECTORRENDERER_H

#include "RenderableMesh.h"

class VectorsRenderer : RenderableMesh {
public:
	VectorsRenderer(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr);
	bool updateColors(std::vector<glm::vec3> clrs) override;
	void draw(void) override;
};

#endif