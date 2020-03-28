#ifndef POINTSRENDERER_H
#define POINTSRENDERER_H

#include "RenderableMesh.h"

class PointsRenderer : public RenderableMesh {
public:
	PointsRenderer(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr);
	void draw(void) override;
};

#endif