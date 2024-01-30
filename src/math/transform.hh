#ifndef __TRANSFORM_H
#define __TRANSFORM_H

namespace Yukiko{

#include"glm/glm.hpp"

#include<iostream>
#include<vector>
#include<math.h>

constexpr const float PI = 3.1415926;

class Transform
{
public:
	Transform();
	Transform(glm::mat4 transform) :_transform(transform) {}
	~Transform();

	glm::mat4 Scale(glm::vec3 scalePara); 
	
	glm::mat4 Translate(glm::vec3 translatePara); 

	glm::mat4 Rotate(glm::vec3 startPos, glm::vec3 direction, float angle); // 旋转函数：接收的参数为 旋转角度、旋转轴向

	glm::mat4 Perspective(float nearZ, float farZ);

	glm::mat4 Rotate_Z(float angle);

	glm::mat4 Rotate_Y(float angle);

	glm::mat4 Rotate_X(float angle);

private:
	glm::mat4 _transform;
};






}


#endif