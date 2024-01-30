
#include "transform.hh"

namespace Yukiko{

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::Scale(glm::vec3 scalePara) {
	glm::mat4 trans = glm::mat4(1.0);
	for (int i = 0;i < 3;i++) {
		trans[i][i] *= scalePara[i];
	}
	return trans;
}

glm::mat4 Transform::Translate(glm::vec3 translatePara) {
	glm::mat4 trans = glm::mat4(1.0);
	for (int i = 0;i < 3;i++) {
		trans[3][i] += translatePara[i];
	}
	return trans;
}


glm::mat4 Transform::Rotate(glm::vec3 startPos, glm::vec3 direction, float angle) {

	
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rotateM = glm::mat4(1.0);
	direction = glm::normalize(direction);
	float a = direction.x;
	float b = direction.y;
	float c = direction.z;
	rotateM[0][0] = a * a + (1 - a * a) * std::cos(radians);
	rotateM[0][1] = a * b * (1 - std::cos(radians)) - c * std::sin(radians);
	rotateM[0][2] = a * c * (1 - std::cos(radians)) + b * std::sin(radians);
	rotateM[1][0] = a * b * (1 - std::cos(radians)) + c * std::sin(radians);
	rotateM[1][1] = b * b + (1 - b * b) * std::cos(radians);
	rotateM[1][2] = b * c * (1 - std::cos(radians)) - a * std::sin(radians);
	rotateM[2][0] = a * c * (1 - std::cos(radians)) - b * std::sin(radians);
	rotateM[2][1] = b * c * (1 - std::cos(radians)) + a * std::sin(radians);
	rotateM[2][2] = c * c + (1 - c * c) * std::cos(radians);

	glm::vec3 trans = glm::vec3(-startPos.x, -startPos.y, -startPos.z);
	glm::mat4 forwardTrans = Translate(trans);
	glm::mat4 backTrans = Translate(startPos);

    // 先平移到原点 ，然后绕过原点的任意轴旋转，最后平移回去 
	glm::mat4 rq = backTrans * rotateM * forwardTrans;

	return rq;
}

glm::mat4 Transform::Rotate_Z(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[0][0] = std::cos(radians);
	rq[1][0] = 0 - std::sin(radians);
	rq[0][1] = std::sin(radians);
	rq[1][1] = std::cos(radians);
	return rq;
}

glm::mat4 Transform::Rotate_Y(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[0][0] = std::cos(radians);
	rq[0][2] = 0 - std::sin(radians);
	rq[2][0] = std::sin(radians);
	rq[2][2] = std::cos(radians);
	return rq;
}

glm::mat4 Transform::Rotate_X(float angle) {
	float radians = (double)angle * PI / 180.0;
	glm::mat4 rq = glm::mat4(1.0);
	rq[1][1] = std::cos(radians);
	rq[2][1] = 0 - std::sin(radians);
	rq[1][2] = std::sin(radians);
	rq[2][2] = std::cos(radians);
	return rq;
}

/*
输入参数：
	近平面z轴坐标、远平面z轴坐标
*/
glm::mat4 Transform::Perspective(float n, float f) {
	glm::mat4 scal = glm::mat4(1.0);
	scal[2][2] = 2.0 / (n - f);
	glm::mat4 trans = glm::mat4(1.0);
	trans[3][2] = (n + f) / (-2.0);
	glm::mat4 persp = glm::mat4(0.0);
	persp[0][0] = n;
	persp[1][1] = n;
	persp[2][2] = n + f;
	persp[3][2] = -n * f;
	persp[2][3] = 1;
	glm::mat4 rq = scal * trans * persp;
	return rq;
}

}