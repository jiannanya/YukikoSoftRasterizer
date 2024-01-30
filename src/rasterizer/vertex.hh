#ifndef __VERTEX_H
#define __VERTEX_H

namespace Yukiko{

/*
	Vertex：
	一个顶点所需要的数据：
	vec4 position	---顶点位置
	vec4 color	---顶点颜色
	vec2 texcoord	---纹理坐标
	vec3 normal	---顶点法向量
*/

#include"glm/glm.hpp"

#include<iostream>
#include<vector>

class Vertex {
public:
	Vertex(){}
	Vertex(glm::vec4 position,glm::vec4 color,glm::vec3 normal):_position(position),_color(color),_normal(normal){}
	Vertex(glm::vec4 position, glm::vec2 texcoord, glm::vec3 normal) :_position(position), _texcoord(texcoord), _normal(normal) {}
	Vertex(glm::vec4 position, glm::vec4 color, glm::vec3 normal, glm::vec2 texcoord) :_position(position), _color(color), _normal(normal), _texcoord(texcoord) {}

	void setPosition(glm::vec4 position);
	void setColor(glm::vec4 color);
	void setNormal(glm::vec3 normal);
	void setTexcoord(glm::vec2 texcoord);

	glm::vec4 getPosition();
	glm::vec4 getColor();
	glm::vec3 getNormal();
	glm::vec2 getTexcoord();
private:
	glm::vec4 _position = glm::vec4(0, 0, -99, 0);
	glm::vec4 _color = glm::vec4(0, 0, 0, 0);
	glm::vec3 _normal = glm::vec3(0, 0, 0);
	glm::vec2 _texcoord = glm::vec2(0, 0);
};



}


#endif