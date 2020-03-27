#ifndef GEOMETRYFILEREADER_H
#define GEOMETRYFILEREADER_H

#include <glm/glm/glm.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class GeometryFileReader {
private:
	std::vector<glm::vec3> points;
	std::vector<glm::vec3> colors;
	void readerSelector(std::ifstream* f, std::string l);
	void readPoints(std::ifstream* f, std::string l);

public:
	GeometryFileReader(std::string f) throw(std::string);
	std::vector<glm::vec3> getPoints(void) const;
	std::vector<glm::vec3> getColors(void) const;
};

#endif