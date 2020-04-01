#include "Camera.h"

Camera::Camera(const glm::vec3 p, const unsigned int scrWidth, const unsigned int scrHeight, const float fov, const float miniRendDist, const float maxiRendDist) : fieldOfView(fov), screenWidth(scrWidth), screenHeight(scrHeight), minimalRenderDistance(miniRendDist), maximalRenderDistance(maxiRendDist) {
	setPosition(p);
}

Camera::Camera(const Camera& c) : transformations(c.transformations), fieldOfView(c.fieldOfView), screenWidth(c.screenWidth), screenHeight(c.screenHeight), minimalRenderDistance(c.minimalRenderDistance), maximalRenderDistance(c.maximalRenderDistance) {

}

Camera::~Camera(void) {

}

glm::vec3 Camera::getPosition(void) const {
	return glm::vec3(this->transformations[3]);
}

void Camera::setPosition(const glm::vec3 p) {
	this->transformations[3] = glm::vec4(p, 1.0f);
}

glm::vec3 Camera::getDirection(void) const {
	return glm::vec3(this->transformations[1]);
}

void Camera::setDirection(const glm::vec3 d, ObjectVector referenceVectorType, glm::vec3 referenceVector) {
	if (d == glm::vec3(0.0f, 0.0f, 0.0f)) {
		std::cout << "The direction vector you entered is null !" << std::endl;
		return;
	}
	else if (referenceVectorType == ObjectVector::DIRECTION) {
		std::cout << "You cannot specify a reference vector that is the same as the one you want to set, in this case : the direction vector.\n\
			Please choose UP or RIGHT." << std::endl;
		return;
	}
	else if (referenceVectorType != ObjectVector::RIGHT && referenceVectorType != ObjectVector::UP) {
		std::cout << "You did not select a valid ObjectVector :\n\
			Please choose UP or RIGHT." << std::endl;
		return;
	}
	if (referenceVector == glm::vec3(0.0f, 0.0f, 0.0f ) || glm::areCollinear(d, referenceVector, collinearityThreshold)) {
		switch (referenceVectorType) {
			case ObjectVector::UP:
				if (glm::areCollinear(d, getUpVector(), collinearityThreshold)) {
					referenceVector = getRightVector();
					referenceVectorType = ObjectVector::RIGHT;
				}
				else {
					referenceVector = getUpVector();
				}
				break;
			case ObjectVector::RIGHT:
				if (glm::areCollinear(d, getRightVector(), collinearityThreshold)) {
					referenceVector = getUpVector();
					referenceVectorType = ObjectVector::UP;
				}
				else {
					referenceVector = getRightVector();
				}
				break;
		}
	}
	this->transformations[1] = glm::vec4(glm::normalize(d), 0.0f);
	if (referenceVectorType == ObjectVector::RIGHT) {
		this->transformations[2] = glm::vec4(glm::normalize(glm::cross(referenceVector, getDirection())), 0.0f); // up vector
		this->transformations[0] = glm::vec4(glm::normalize(glm::cross(getDirection(), getUpVector())), 0.0f); // right vector
	}
	else {
		this->transformations[0] = glm::vec4(glm::normalize(glm::cross(getDirection(), referenceVector)), 0.0f); // right vector
		this->transformations[2] = glm::vec4(glm::normalize(glm::cross(getRightVector(), getDirection())), 0.0f); // up vector
	}
}

glm::vec3 Camera::getUpVector(void) const {
	return glm::vec3(this->transformations[2]);
}

void Camera::setUpVector(const glm::vec3 u, ObjectVector referenceVectorType, glm::vec3 referenceVector) {
	if (u == glm::vec3(0.0f, 0.0f, 0.0f)) {
		std::cout << "The up vector you entered is null !" << std::endl;
		return;
	}
	else if (referenceVectorType == ObjectVector::UP) {
		std::cout << "You cannot specify a reference vector that is the same as the one you want to set, in this case : the up vector.\n\
			Please choose RIGHT or DIRECTION." << std::endl;
		return;
	}
	else if (referenceVectorType != ObjectVector::RIGHT && referenceVectorType != ObjectVector::DIRECTION) {
		std::cout << "You did not select a valid ObjectVector :\n\
			Please choose DIRECTION or RIGHT." << std::endl;
		return;
	}
	if (referenceVector == glm::vec3(0.0f, 0.0f, 0.0f) || glm::areCollinear(u, referenceVector, collinearityThreshold)) {
		switch (referenceVectorType) {
		case ObjectVector::RIGHT:
			if (glm::areCollinear(u, getRightVector(), collinearityThreshold)) {
				referenceVector = getDirection();
				referenceVectorType = ObjectVector::DIRECTION;
			}
			else {
				referenceVector = getRightVector();
			}
			break;
		case ObjectVector::DIRECTION:
			if (glm::areCollinear(u, getDirection(), collinearityThreshold)) {
				referenceVector = getRightVector();
				referenceVectorType = ObjectVector::RIGHT;
			}
			else {
				referenceVector = getDirection();
			}
			break;
		}
	}
	this->transformations[2] = glm::vec4(glm::normalize(u), 0.0f);
	if (referenceVectorType == ObjectVector::RIGHT) {
		this->transformations[1] = glm::vec4(glm::normalize(glm::cross(getUpVector(), referenceVector)), 0.0f); // direction vector
		this->transformations[0] = glm::vec4(glm::normalize(glm::cross(getDirection(), getUpVector())), 0.0f); // right vector
	}
	else {
		this->transformations[0] = glm::vec4(glm::normalize(glm::cross(referenceVector, getUpVector())), 0.0f); // right vector
		this->transformations[1] = glm::vec4(glm::normalize(glm::cross(getUpVector(), getRightVector())), 0.0f); // direction vector
	}
}

glm::vec3 Camera::getRightVector(void) const {
	return glm::vec3(this->transformations[0]);
}

void Camera::setRightVector(const glm::vec3 r, ObjectVector referenceVectorType, glm::vec3 referenceVector) {
	if (r == glm::vec3(0.0f, 0.0f, 0.0f)) {
		std::cout << "The right vector you entered is null !" << std::endl;
		return;
	}
	else if (referenceVectorType == ObjectVector::RIGHT) {
		std::cout << "You cannot specify a reference vector that is the same as the one you want to set, in this case : the right vector.\n\
			Please choose UP or DIRECTION." << std::endl;
		return;
	}
	else if (referenceVectorType != ObjectVector::DIRECTION && referenceVectorType != ObjectVector::UP) {
		std::cout << "You did not select a valid ObjectVector :\n\
			Please choose UP or DIRECTION." << std::endl;
		return;
	}
	if (referenceVector == glm::vec3(0.0f, 0.0f, 0.0f) || glm::areCollinear(r, referenceVector, collinearityThreshold)) {
		switch (referenceVectorType) {
		case ObjectVector::UP:
			if (glm::areCollinear(r, getUpVector(), collinearityThreshold)) {
				referenceVector = getDirection();
				referenceVectorType = ObjectVector::DIRECTION;
			}
			else {
				referenceVector = getUpVector();
			}
			break;
		case ObjectVector::DIRECTION:
			if (glm::areCollinear(r, getDirection(), collinearityThreshold)) {
				referenceVector = getUpVector();
				referenceVectorType = ObjectVector::UP;
			}
			else {
				referenceVector = getDirection();
			}
			break;
		}
	}
	this->transformations[0] = glm::vec4(glm::normalize(r), 0.0f);
	if (referenceVectorType == ObjectVector::UP) {
		this->transformations[1] = glm::vec4(glm::normalize(glm::cross(referenceVector, getRightVector())), 0.0f); // direction vector
		this->transformations[2] = glm::vec4(glm::normalize(glm::cross(getRightVector(), getDirection())), 0.0f); // up vector
	}
	else {
		this->transformations[2] = glm::vec4(glm::normalize(glm::cross(getRightVector(), referenceVector)), 0.0f); // up vector
		this->transformations[1] = glm::vec4(glm::normalize(glm::cross(getUpVector(), getRightVector())), 0.0f); // direction vector
	}
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

std::string Camera::to_string(void) const {
	std::string data = \
		"Position  : " + glm::to_string(getPosition()) + "\n"\
		"Up        : " + glm::to_string(getUpVector()) + "\n"\
		"Direction : " + glm::to_string(getDirection()) + "\n"\
		"Right     : " + glm::to_string(getRightVector()) + "\n";
	return data;
}

void Camera::move(const glm::vec3 m) {
	this->transformations[3] = glm::vec4(this->transformations[3].x + m.x, this->transformations[3].y + m.y, this->transformations[3].z + m.z, 1.0f);
}

void Camera::selfRotate(const float angle, const glm::vec3 around) {
	glm::mat4 rotationMatrix = glm::rotate(angle, around);
	this->transformations[0] = glm::normalize(rotationMatrix * this->transformations[0]);
	this->transformations[1] = glm::normalize(rotationMatrix * this->transformations[1]);
	this->transformations[2] = glm::normalize(rotationMatrix * this->transformations[2]);
	// Locking Camera at 90° up and 90° down
	if (getUpVector().z < 0.0f) {
		if (getDirection().z > 0) {
			setDirection(glm::vec3(0.0f, 0.0f, 1.0f), ObjectVector::RIGHT);
		}
		else {
			setDirection(glm::vec3(0.0f, 0.0f, -1.0f), ObjectVector::RIGHT);
		}
	}
}

void Camera::rotate(const float angle, const glm::vec3 around) {
	glm::mat4 rotationMatrix = glm::rotate(angle, around);
	this->transformations = rotationMatrix * this->transformations;
}

glm::mat4 Camera::getViewMatrix(void) const {
	return glm::lookAt(getPosition(), getPosition() + getDirection(), getUpVector());
}

glm::mat4 Camera::getProjectionMatrix(void) const {
	return glm::perspective(glm::radians(fieldOfView), (float)screenWidth / (float)screenHeight, minimalRenderDistance, maximalRenderDistance);
}
