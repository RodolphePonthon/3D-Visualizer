#include "GeometryFileReader.h"

GeometryFileReader::GeometryFileReader(std::string f) throw(std::string) {
    std::ifstream* file = new std::ifstream(f);
    std::string line;
    if (file->is_open()) {
        while (getline(*file, line)) {
            if (line[0] == '#') {
                readerSelector(file, line);
            }
            break;
        }
        file->close();
        delete file;
    }
    else {
        throw std::string("Failed to open input file !");
    }
}

std::vector<glm::vec3> GeometryFileReader::getPoints(void) const {
    return this->points;
}

std::vector<glm::vec3> GeometryFileReader::getColors(void) const {
    return this->colors;
}

void GeometryFileReader::readerSelector(std::ifstream* f, std::string l) {
    if (l.find("#POINTS") != std::string::npos) {
        readPoints(f, l);
    }
}

void GeometryFileReader::readPoints(std::ifstream* f, std::string l) {
    while (getline(*f, l) && l[0] != '#') {
        float x, y, z, r, v, b;
        std::string tmpFloat;
        tmpFloat = l.substr(0, l.find(";"));
        if (tmpFloat.find(",") != std::string::npos)
            tmpFloat[tmpFloat.find(",")] = '.';
        x = stof(tmpFloat);
        l = l.substr(l.find(";") + 1, l.length() - l.find(";") + 1);
        tmpFloat = l.substr(0, l.find(";"));
        if (tmpFloat.find(",") != std::string::npos)
            tmpFloat[tmpFloat.find(",")] = '.';
        y = stof(tmpFloat);
        l = l.substr(l.find(";") + 1, l.length() - l.find(";") + 1);
        tmpFloat = l.substr(0, l.find(";"));
        if (tmpFloat.find(",") != std::string::npos)
            tmpFloat[tmpFloat.find(",")] = '.';
        z = stof(tmpFloat);
        this->points.push_back(glm::vec3(x, y, z));
        l = l.substr(l.find(";") + 1, l.length() - l.find(";") + 1);
        tmpFloat = l.substr(0, l.find(";"));
        if (tmpFloat.find(",") != std::string::npos)
            tmpFloat[tmpFloat.find(",")] = '.';
        r = stof(tmpFloat) / 255;
        l = l.substr(l.find(";") + 1, l.length() - l.find(";") + 1);
        tmpFloat = l.substr(0, l.find(";"));
        if (tmpFloat.find(",") != std::string::npos)
            tmpFloat[tmpFloat.find(",")] = '.';
        v = stof(tmpFloat) / 255;
        l = l.substr(l.find(";") + 1, l.length() - l.find(";") + 1);
        tmpFloat = l.substr(0, l.find(";"));
        if (tmpFloat.find(",") != std::string::npos)
            tmpFloat[tmpFloat.find(",")] = '.';
        b = stof(tmpFloat) / 255;
        this->colors.push_back(glm::vec3(r, v, b));
    }
    if (l[0] == '#') {
        readerSelector(f, l);
    }
}

