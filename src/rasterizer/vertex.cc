
#include "vertex.hh"

namespace Yukiko{
    
void Vertex::setPosition(glm::vec4 position) {
	_position = position;
}

void Vertex::setColor(glm::vec4 color) {
	_color = color;
}

void Vertex::setNormal(glm::vec3 normal) {
	_normal = normal;
}

void Vertex::setTexcoord(glm::vec2 texcoord) {
	_texcoord = texcoord;
}

glm::vec4 Vertex::getPosition() {
	return _position;
}

glm::vec4 Vertex::getColor() {
	return _color;
}

glm::vec3 Vertex::getNormal() {
	return _normal;
}

glm::vec2 Vertex::getTexcoord() {
	return _texcoord;
}

}