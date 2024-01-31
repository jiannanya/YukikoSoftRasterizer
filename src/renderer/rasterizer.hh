#ifndef RASTERIZER_HH
#define RASTERIZER_HH

#include "math.hh"
#include "framebuffer.hh"
#include "shader.hh"
#include "Triangle.hh"
#include "camera.hh"

namespace Yukiko{

class Rasterizer{

public:
    Rasterizer(){}
    ~Rasterizer(){}

    void drawPixel(float x, float y, const glm::vec4& color,Framebuffer& fb);
    void drawPixel(Fragmentdata& fg,Shader& sh,Framebuffer& fb);

    void drawTriangleLine(Triangle &tri, const glm::vec4& color,Framebuffer& fb);
    void drawTriangle(Triangle &tri, const glm::vec4& color,Framebuffer& fb);
    void drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb, Camera& cam);
    
    void drawLine(int x1, int y1, int x2, int y2, const glm::vec4& color,Framebuffer& fb);


};

};


#endif 