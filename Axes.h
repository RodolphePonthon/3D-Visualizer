#ifndef AXES_H
#define AXES_H

#include <vector>
#include <glm/glm/glm.hpp>
#include "PointsRenderer.h"
#include "VectorsRenderer.h"
#include "Shader.h"

class Axes {
private:
	PointsRenderer* directionPoints = nullptr;
	VectorsRenderer* axes = nullptr;
public:
	Axes(Shader* shader);
	~Axes(void);
	void draw(void);
};

#endif