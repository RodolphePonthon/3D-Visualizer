#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <iostream>
#include <glm/glm/gtx/vector_query.hpp>
#include <glm/glm/gtx/string_cast.hpp>

enum class ObjectVector {
	UP,
	RIGHT,
	DIRECTION
};

static const float collinearityThreshold = 0.0001f;

class Camera {
private:
	glm::mat4 transformations = glm::mat4(1.0f);
	float fieldOfView;
	unsigned int screenWidth, screenHeight;
	float minimalRenderDistance, maximalRenderDistance;
	float velocity = 0.1f;
	float rotationSensitivity = 0.005f;

public:
	Camera(const glm::vec3 p = glm::vec3(0.0f), const unsigned int scrWidth = 800, const unsigned int scrHeight = 600, const float fov = 45.0f, const float miniRendDist = 0.1f, const float maxiRendDist = 1000.0f);
	Camera(const Camera &c);
	~Camera(void);

	glm::vec3 getPosition(void) const;
	void setPosition(const glm::vec3 p);
	glm::vec3 getDirection(void) const;
	void setDirection(const glm::vec3 d, ObjectVector referenceVectorType, glm::vec3 referenceVector = glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 getUpVector(void) const;
	void setUpVector(const glm::vec3 u, ObjectVector referenceVectorType, glm::vec3 referenceVector = glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 getRightVector(void) const;
	void setRightVector(const glm::vec3 r, ObjectVector referenceVectorType, glm::vec3 referenceVector = glm::vec3(0.0f, 0.0f, 0.0f));
	void setFieldOfView(const float fov);
	float getVelocity(void) const;
	void setVelocity(const float vel);
	float getRotationSensitivity(void) const;

	std::string to_string(void) const;

	void move(const glm::vec3 m);
	void selfRotate(const float angle, const glm::vec3 around);
	void rotate(const float angle, const glm::vec3 around);
	glm::mat4 getViewMatrix(void) const;
	glm::mat4 getProjectionMatrix(void) const;
};

#endif