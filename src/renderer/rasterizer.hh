#ifndef RASTERIZER_HH
#define RASTERIZER_HH

#include "math.hh"
#include "framebuffer.hh"
#include "shader.hh"
#include "triangle.hh"
#include "camera.hh"

namespace Fallment{


class Rasterizer{

public:
    virtual void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)=0;
    virtual ~Rasterizer(){}

};

class RasterizerLine: public Rasterizer{
public:
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;
    virtual ~RasterizerLine(){}
private:
    void drawLine(int x1, int y1, int x2, int y2, const glm::vec4& color,Framebuffer& fb);
};

class RasterizerFill: public Rasterizer{
public:
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;
    virtual ~RasterizerFill(){}
private:
    void drawFill(Triangle &tri,Shader& sh,Framebuffer& fb);
};

class RasterizerSSAO: public Rasterizer{
public:
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;
    void postprocessTriangle(Triangle &tri,Shader& sh,Framebuffer& fb);
    virtual ~RasterizerSSAO(){}
private:
    void drawFill(Triangle &tri,Shader& sh,Framebuffer& fb);
    float maxElevationAngle(Framebuffer& fb,glm::vec2 p, glm::vec2 dir);
};

class RasterizerPhong: public Rasterizer{
public:
    RasterizerPhong(){}
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb)override;
    virtual ~RasterizerPhong(){}
    RasterizerPhong(const Rasterizer& r); // 类型转换构造函数

};

};


#endif 