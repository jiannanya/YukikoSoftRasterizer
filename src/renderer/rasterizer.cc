#include "rasterizer.hh"
#include "triangle.hh"

namespace Fallment{



void RasterizerLine::drawLine(int x1, int y1, int x2, int y2, const glm::vec4& color,Framebuffer& fb) {
    //std::cout << "drawLine :(" << x1 << "," << y1 << ") to (" << x2 << "," << y2 << ")" << std::endl;

    bool steep = false;
    // traverse by X or Y
    if(std::abs(x2 - x1) < std::abs(y2 - y1)){
        std::swap(x1, y1);
        std::swap(x2, y2);
        steep = true;
    }

    // traverse from smaller value
    if(x2 < x1){
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = y2 - y1;

    int de2 = std::abs(dy) * 2;
    int e2 = 0;
    int y = y1;
    for(int x = x1; x <= x2; ++x){
        (steep ? fb.setPixelColor(y,x,color) : fb.setPixelColor(x,y,color));
        e2 += de2;
        if(e2 > dx){
            y += (y2 > y1 ? 1 : -1);
            e2 -= dx*2;
        }
    }
}

void RasterizerLine::drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){
    glm::vec3 v1 = tri.avp();
    glm::vec3 v2 = tri.bvp();
    glm::vec3 v3 = tri.cvp();

    sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
    auto color = sh.gl_FragColor;

    drawLine(round(v1.x), round(v1.y), round(v2.x), round(v2.y), color, fb);
    drawLine(round(v1.x), round(v1.y), round(v3.x), round(v3.y), color, fb);
    drawLine(round(v3.x), round(v3.y), round(v2.x), round(v2.y), color, fb);
}

void RasterizerFill::drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){
    drawFill(tri,sh,fb);
}

void RasterizerFill::drawFill(Triangle &tri,Shader& sh,Framebuffer& fb) {

    glm::vec3 v1 = tri.avp();
    glm::vec3 v2 = tri.bvp();
    glm::vec3 v3 = tri.cvp();

    glm::vec2 bboxmin,bboxmax;

    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));

    glm::vec3 p;

    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            glm::vec3 bc = mth::barycentric3(v1, v2, v3, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            //depth test
            p.z = v1.z*bc.x + v2.z*bc.y + v3.z*bc.z;
            if(p.z<(fb.getZ(p.x,p.y)))
                continue;
            else 
                fb.setZ(p.x,p.y,p.z);

            sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
            auto color = sh.gl_FragColor;

            fb.setPixelColor(p.x,p.y,color);
        }
    }
}

void RasterizerPhong::drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){

    glm::vec3 v1 = tri.avp();
    glm::vec3 v2 = tri.bvp();
    glm::vec3 v3 = tri.cvp();

    glm::vec3 vw1 = tri.aw();
    glm::vec3 vw2 = tri.bw();
    glm::vec3 vw3 = tri.cw();

    glm::vec2 uv1 = tri.auv();
    glm::vec2 uv2 = tri.buv();
    glm::vec2 uv3 = tri.cuv();

    glm::vec3 nw1 = tri.anw();
    glm::vec3 nw2 = tri.bnw();
    glm::vec3 nw3 = tri.cnw();

    glm::vec4 c1 = tri.aco();
    glm::vec4 c2 = tri.bco();
    glm::vec4 c3 = tri.cco();


    glm::vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    glm::vec2 bboxmax(0, 0);

    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));

    glm::vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            glm::vec3 bc = mth::barycentric3(v1, v2, v3, p);
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            //depth test
            p.z = v1.z*bc.x + v2.z*bc.y + v3.z*bc.z;
            if(p.z<(fb.getZ(p.x,p.y)))
                continue;
            else 
                fb.setZ(p.x,p.y,p.z);

            //interpolate

            glm::vec3 vw;
            vw.x = vw1.x*bc.x + vw2.x*bc.y + vw3.x*bc.z;
            vw.y = vw1.y*bc.x + vw2.y*bc.y + vw3.y*bc.z;
            vw.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;

            glm::vec2 uv;
            uv.x = uv1.x*bc.x + uv2.x*bc.y + uv3.x*bc.z;
            uv.y = uv1.y*bc.x + uv2.y*bc.y + uv3.y*bc.z;

            glm::vec3 nw;
            nw.x = nw1.x*bc.x + nw2.x*bc.y + nw3.x*bc.z;
            nw.y = nw1.y*bc.x + nw2.y*bc.y + nw3.y*bc.z;
            nw.z = nw1.z*bc.x + nw2.z*bc.y + nw3.z*bc.z;

            glm::vec4 c;
            c.x = c1.x*bc.x + c2.x*bc.y + c3.x*bc.z;
            c.y = c1.y*bc.x + c2.y*bc.y + c3.y*bc.z;
            c.z = c1.z*bc.x + c2.z*bc.y + c3.z*bc.z;
            c.z = c1.w*bc.x + c2.w*bc.y + c3.w*bc.z;
            

            sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
            fb.setPixelColor(p.x,p.y,sh.gl_FragColor);
        }
    }
    
}

RasterizerPhong::RasterizerPhong(const Rasterizer& r){

}

};