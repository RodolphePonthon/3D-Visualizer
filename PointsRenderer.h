#ifndef POINTSRENDERER_H
#define POINTSRENDERER_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "GLError.h"

class PointsRenderer {
private:
	float* points;
	size_t nbPoints;
	unsigned int VBO;
	unsigned int VAO;
	Shader* shader;

public:
	PointsRenderer(std::vector<glm::vec3> points, Shader* shdr);
	~PointsRenderer(void);
	void updateData(void);
	void draw(void);
};

#endif