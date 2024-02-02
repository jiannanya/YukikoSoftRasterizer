#ifndef RASTERIZER_HH
#define RASTERIZER_HH

#include "math.hh"
#include "framebuffer.hh"
#include "shader.hh"
#include "Triangle.hh"
#include "camera.hh"

namespace Fallment{


class Rasterizer{

public:
    virtual void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)=0;

};

class RasterizerLine: public Rasterizer{
public:
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;
private:
    void drawLine(int x1, int y1, int x2, int y2, const glm::vec4& color,Framebuffer& fb);
};

class RasterizerFill: public Rasterizer{
public:
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;
private:
    void drawFill(Triangle &tri,Shader& sh,Framebuffer& fb);
};

class RasterizerPhong: public Rasterizer{
public:
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;

    RasterizerPhong(const Rasterizer& r); // 类型转换构造函数

};

};


#endif 