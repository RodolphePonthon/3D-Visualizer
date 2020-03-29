#include "Camera.h"

Camera::Camera(const glm::vec3 p, const unsigned int scrWidth, const unsigned int scrHeight, const float fov, const float miniRendDist, const float maxiRendDist) : fieldOfView(fov), screenWidth(scrWidth), screenHeight(scrHeight), minimalRenderDistance(miniRendDist), maximalRenderDistance(maxiRendDist) {
	setPosition(p);
}

Camera::Camera(const Camera& c) : transformations(c.transformations), direction(c.direction), up(c.up), right(c.right), fieldOfView(c.fieldOfView), screenWidth(c.screenWidth), screenHeight(c.screenHeight), minimalRenderDistance(c.minimalRenderDistance), maximalRenderDistance(c.maximalRenderDistance) {

}

Camera::~Camera(void) {

}

void Camera::setPosition(const glm::vec3 p) {
	this->transformations = glm::translate(this->transformations, p - glm::vec3(this->transformations * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
}

glm::vec3 Camera::getPosition(void) const {
	return glm::vec3(this->transformations * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

glm::vec3 Camera::getDirection(void) const {
	return glm::normalize(glm::vec3(this->transformations * glm::vec4(this->direction, 1.0f)) - getPosition());
}

glm::vec3 Camera::getUpVector(void) const {
	return glm::normalize(glm::vec3(this->transformations * glm::vec4(this->up, 1.0f)) - getPosition());
}

glm::vec3 Camera::getRightVector(void) const {
	return glm::normalize(glm::vec3(this->transformations * glm::vec4(this->right, 1.0f)) - getPosition());
}

void Camera::setFieldOfView(const float fov) {
	this->fieldOfView = fov;
}

float Camera::getVelocity(void) const {
	return this->velocity;
}

void Camera::setVelocity(const float vel) {
	this->velocity = vel;
}

float Camera::getRotationSensitivity(void) const {
	return this->rotationSensitivity;
}

void Camera::move(const glm::vec3 m) {
	this->transformations = glm::translate(this->transformations, m);
}

void Camera::selfRotate(const float angle, const glm::vec3 around) {
	this->transformations = glm::rotate(this->transformations, glm::radians(angle), around);
	// Locking Camera at 90° up and 90° down
	if (getUpVector().z < 0.0f) {
		float correctingAngle = asin(glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), getUpVector()));
		if (getDirection().z > 0) {
			this->transformations = glm::rotate(this->transformations, glm::radians(correctingAngle), getRightVector());
		}
		else {
			this->transformations = glm::rotate(this->transformations, glm::radians(correctingAngle), -getRightVector());
		}
	}
}

void Camera::rotate(const float angle, const glm::vec3 around) {
	glm::mat4 rotationMatrix = glm::rotate(angle, around);
	this->transformations = rotationMatrix * this->transformations;
}

glm::mat4 Camera::getViewMatrix(void) const {
	return glm::lookAt(getPosition(), getPosition() - getDirection(), getUpVector());
}

glm::mat4 Camera::getProjectionMatrix(void) const {
	return glm::perspective(glm::radians(fieldOfView), (float)screenWidth / (float)screenHeight, minimalRenderDistance, maximalRenderDistance);
}
