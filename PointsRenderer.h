#ifndef POINTSRENDERER_H
#define POINTSRENDERER_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "GLError.h"

class PointsRenderer {
private:
	float* points = nullptr;
	float* colors = nullptr;
	size_t nbPoints;
	unsigned int VBO[2];
	unsigned int VAO;
	Shader* shader;

public:
	PointsRenderer(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr) throw(std::string);
	~PointsRenderer(void);
	void updatePoints(std::vector<glm::vec3> pts) throw(std::string);
	void updateColors(std::vector<glm::vec3> clrs) throw(std::string);
	void updateVAO(void);
	void draw(void);
};

#endif