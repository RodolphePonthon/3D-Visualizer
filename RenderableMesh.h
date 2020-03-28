#ifndef RENDERABLEMESH_H
#define RENDERABLEMESH_H

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <vector>
#include "Shader.h"
#include "GLError.h"

class RenderableMesh {
protected:
	float* points = nullptr;
	float* colors = nullptr;
	size_t nbPoints;
	unsigned int VBO[2];
	unsigned int VAO;
	Shader* shader = nullptr;

public:
	RenderableMesh(std::vector<glm::vec3> pts, std::vector<glm::vec3> clrs, Shader* shdr);
	~RenderableMesh(void);
	virtual bool updatePoints(std::vector<glm::vec3> pts);
	virtual bool updateColors(std::vector<glm::vec3> clrs);
	virtual void initializeVAO(void);
	virtual void updateVAO(void);
	virtual void draw(void) = 0;
};

#endif