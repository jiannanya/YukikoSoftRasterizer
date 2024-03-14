#include "rasterizer.hh"
#include "triangle.hh"

namespace Fallment{



void RasterizerLine::drawLine(int x1, int y1, int x2, int y2, const glm::vec4& color,Framebuffer& fb) {

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

    // sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
    auto color = sh.gl_FragColor;

    drawLine(std::round(v1.x), std::round(v1.y), std::round(v2.x), std::round(v2.y), color, fb);
    drawLine(std::round(v1.x), std::round(v1.y), std::round(v3.x), std::round(v3.y), color, fb);
    drawLine(std::round(v3.x), std::round(v3.y), std::round(v2.x), std::round(v2.y), color, fb);
}

void RasterizerFill::drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){
    drawFill(tri,sh,fb);
}

void RasterizerFill::drawFill(Triangle &tri,Shader& sh,Framebuffer& fb) {

    glm::vec3 v1 = tri.avp();
    glm::vec3 v2 = tri.bvp();
    glm::vec3 v3 = tri.cvp();

    glm::vec3 vw1 = tri.aw();
    glm::vec3 vw2 = tri.bw();
    glm::vec3 vw3 = tri.cw();

    // spdlog::info("drawTriangle 4 vw1 {} {} {}", vw1.x,vw1.y,vw1.z);
    // spdlog::info("drawTriangle 4 vw2 {} {} {}", vw2.x,vw2.y,vw2.z);
    // spdlog::info("drawTriangle 4 vw3 {} {} {}", vw3.x,vw3.y,vw3.z);
    glm::vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    glm::vec2 bboxmax(0, 0);

    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));
    //spdlog::info("drawTriangle 5");
    glm::vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            //glm::vec3 bc = mth::barycentric3(v1, v2, v3, p);
            glm::vec3 bc = mth::barycentric2D(v1,v2,v3,p);
            //bc = glm::bar
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            
             //透视矫正插值 https://www.researchgate.net/publication/2893969_Perspective-Correct_Interpolation
            //float z_reciprocal = bc.x*(1.0f/vw1.z) + bc.y*(1.0f/vw2.z) + bc.z*(1.0f/vw3.z); 
            //p.z = 1.0f/z_reciprocal;
            p.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;
            //depth test
            if(p.z<(fb.getZ(p.x,p.y)))
                continue;
            else 
                fb.setZ(p.x,p.y,p.z);

            glm::vec3 vw;
            vw.x = vw1.x*bc.x + vw2.x*bc.y + vw3.x*bc.z;
            vw.y = vw1.y*bc.x + vw2.y*bc.y + vw3.y*bc.z;
            vw.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;


            auto& in = static_cast<FragmentInDataTransform&>(*sh._fragmentIn);

            in.color = glm::vec4(1.0f,1.0f,1.0f,1.0f);

            sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
            //spdlog::info("drawTriangle ssao 4 {} {} {} {}",sh.gl_FragColor.x, sh.gl_FragColor.y, sh.gl_FragColor.z,sh.gl_FragColor.w);
            fb.setPixelColor(p.x,p.y,sh.gl_FragColor);
        }
    }
}

void RasterizerSSAO::drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){
    drawFill(tri,sh,fb);
}

void RasterizerSSAO::drawFill(Triangle &tri,Shader& sh,Framebuffer& fb) {

    glm::vec3 v1 = tri.avp();
    glm::vec3 v2 = tri.bvp();
    glm::vec3 v3 = tri.cvp();

    glm::vec3 vw1 = tri.aw();
    glm::vec3 vw2 = tri.bw();
    glm::vec3 vw3 = tri.cw();

    // spdlog::info("drawTriangle 4 vw1 {} {} {}", vw1.x,vw1.y,vw1.z);
    // spdlog::info("drawTriangle 4 vw2 {} {} {}", vw2.x,vw2.y,vw2.z);
    // spdlog::info("drawTriangle 4 vw3 {} {} {}", vw3.x,vw3.y,vw3.z);
    glm::vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    glm::vec2 bboxmax(0, 0);

    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));
    //spdlog::info("drawTriangle 5");
    glm::vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            //glm::vec3 bc = mth::barycentric3(v1, v2, v3, p);
            glm::vec3 bc = mth::barycentric2D(v1,v2,v3,p);
            //bc = glm::bar
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            
             //透视矫正插值 https://www.researchgate.net/publication/2893969_Perspective-Correct_Interpolation
            //float z_reciprocal = bc.x*(1.0f/vw1.z) + bc.y*(1.0f/vw2.z) + bc.z*(1.0f/vw3.z); 
            //p.z = 1.0f/z_reciprocal;
            p.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;
            //depth test
            if(p.z<(fb.getZ(p.x,p.y)))
                continue;
            else 
                fb.setZ(p.x,p.y,p.z);

            //spdlog::info("drawTriangle ssao 4 {}",p.z);
        }
    }
}

void RasterizerSSAO::postprocessTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){
    glm::vec3 v1 = tri.avp();
    glm::vec3 v2 = tri.bvp();
    glm::vec3 v3 = tri.cvp();

    glm::vec3 vw1 = tri.aw();
    glm::vec3 vw2 = tri.bw();
    glm::vec3 vw3 = tri.cw();

    // spdlog::info("drawTriangle 4 vw1 {} {} {}", vw1.x,vw1.y,vw1.z);
    // spdlog::info("drawTriangle 4 vw2 {} {} {}", vw2.x,vw2.y,vw2.z);
    // spdlog::info("drawTriangle 4 vw3 {} {} {}", vw3.x,vw3.y,vw3.z);
    glm::vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    glm::vec2 bboxmax(0, 0);

    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));
    //spdlog::info("drawTriangle 5");
    glm::vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            //glm::vec3 bc = mth::barycentric3(v1, v2, v3, p);
            glm::vec3 bc = mth::barycentric2D2(v1,v2,v3,p);
            //bc = glm::bar
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            
             //透视矫正插值 https://www.researchgate.net/publication/2893969_Perspective-Correct_Interpolation
            float z_ = 1.0f / (bc.x*(1.0f/vw1.z) + bc.y*(1.0f/vw2.z) + bc.z*(1.0f/vw3.z)); 
            // p.z = 1.0f/z_reciprocal;
            //p.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;
            //p.z = v1.z*bc.x + v2.z*bc.y + v3.z*bc.z;
            float z_interpolated = z_* (bc.x*(v1.z/vw1.z) + bc.y*(v2.z/vw2.z) + bc.z*(v3.z/vw3.z)); 
            p.z = z_interpolated;
            //depth test
            if(p.z>(fb.getZ(p.x,p.y)))
                continue;


            auto& in = static_cast<FragmentInDataSSAO&>(*sh._fragmentIn);
            in.color = glm::vec4(1.0f,1.0f,1.0f,1.0f);

            sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
            //spdlog::info("drawTriangle ssao 4 {} {} {} {}",sh.gl_FragColor.x, sh.gl_FragColor.y, sh.gl_FragColor.z,sh.gl_FragColor.w);

            //计算 AO
            float total = 0;
            for (float a=0; a<mth::PI*2-1e-4; a += mth::PI/4) {
                total += mth::PI/2 - maxElevationAngle(fb, {p.x,p.y}, {cos(a), sin(a)});
            }
            total /= (mth::PI/2)*8;
            total = pow(total, 100.f);
            //spdlog::info("drawTriangle ssao 4 {}",total);
            fb.setPixelColor(p.x,p.y,sh.gl_FragColor * total);

            // // float z = fb.getZ(p.x,p.y);
            //spdlog::info("drawTriangle ssao 4 {}",p.z);
            // fb.setPixelColor(p.x,p.y, {p.z,p.z,p.z,1.0});
        }
    }
}

float RasterizerSSAO::maxElevationAngle(Framebuffer& fb,glm::vec2 p, glm::vec2 dir){
    float maxangle = 0;
    float* zbuffer = fb.getZBuffer();
    int width = fb.getWidth();
    int height = fb.getHeight();
    for (float t=0.; t<10.; t+=1.) {
        glm::vec2 cur = p + dir*t;
        if (cur.x>=width || cur.y>=height || cur.x<0 || cur.y<0) return maxangle;

        float distance = glm::length(p-cur);
        if (distance < 1.f) continue;
        float elevation = zbuffer[int(cur.x)+int(cur.y)*width]-zbuffer[int(p.x)+int(p.y)*width];
        maxangle = std::max(maxangle, atanf(elevation/distance));
    }
    return maxangle;    
}



  
float LinearizeDepth(float depth) 
{
    float n = 0.1; 
    float f  = 10.0; 
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * n * f) / (f + n - z * (f - n));	
}

void RasterizerPhong::drawTriangle(Triangle &tri,Shader& sh,Framebuffer& fb){
    // spdlog::info("drawTriangle 3");
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

    //spdlog::info("drawTriangle 4 {} {} {}", c1.x,c1.y,c1.z);
    glm::vec2 bboxmin(fb.getWidth() - 1, fb.getHeight() - 1);
    glm::vec2 bboxmax(0, 0);

    bboxmin.x = std::max(0.f, std::min(v1.x, std::min(v2.x, v3.x)));
    bboxmin.y = std::max(0.f, std::min(v1.y, std::min(v2.y, v3.y)));
    bboxmax.x = std::min((float)(fb.getWidth() - 1), std::max(v1.x, std::max(v2.x, v3.x)));
    bboxmax.y = std::min((float)(fb.getHeight() - 1), std::max(v1.y, std::max(v2.y, v3.y)));
    //spdlog::info("drawTriangle 5");
    glm::vec3 p;
    for(p.x = bboxmin.x; p.x <= bboxmax.x; p.x++){
        for(p.y = bboxmin.y; p.y <= bboxmax.y; p.y++){

            //glm::vec3 bc = mth::barycentric3(v1, v2, v3, p);
            glm::vec3 bc = mth::barycentric3(v1,v2,v3,p);
            //bc = glm::bar
            if(bc.x < 0 || bc.y < 0 || bc.z < 0) 
                continue;

            
             //透视矫正插值 https://www.researchgate.net/publication/2893969_Perspective-Correct_Interpolation
            //float z_reciprocal = bc.x*(1.0f/vw1.z) + bc.y*(1.0f/vw2.z) + bc.z*(1.0f/vw3.z); 
            //p.z = 1.0f/z_reciprocal;
            p.z = vw1.z*bc.x + vw2.z*bc.y + vw3.z*bc.z;
            // float z_ = 1.0f / (bc.x/vw1.z + bc.y/vw2.z + bc.z/vw3.z); 
            // float z_interpolated = z_* (bc.x*(v1.z/vw1.z) + bc.y*(v2.z/vw2.z) + bc.z*(v3.z/vw3.z)); 
            // p.z = z_interpolated;
            //depth test
            if(p.z<(fb.getZ(p.x,p.y)))
                continue;
            else 
                fb.setZ(p.x,p.y,p.z);


            //glm::vec3 vw = mth::interpolate(vw1,vw2,vw3,bc,v1.z,v2.z,v3.z,z_reciprocal);
            //glm::vec2 uv = mth::interpolate(uv1,uv2,uv3,bc,v1.z,v2.z,v3.z,z_reciprocal);
            //glm::vec3 nw = mth::interpolate(nw1,nw2,nw3,bc,v1.z,v2.z,v3.z,z_reciprocal);
            //glm::vec4 c  = mth::interpolate(c1,c2,c3,bc,v1.z,v2.z,v3.z,z_reciprocal);

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
            c.w = c1.w*bc.x + c2.w*bc.y + c3.w*bc.z;


            // glm::vec3 vw;
            // vw.x = z_* (bc.x*(vw1.x/vw1.z) + bc.y*(vw2.x/vw2.z) + bc.z*(vw3.x/vw3.z));
            // vw.y = z_* (bc.x*(vw1.y/vw1.z) + bc.y*(vw2.y/vw2.z) + bc.z*(vw3.y/vw3.z));
            // vw.z = z_* (bc.x*(vw1.z/vw1.z) + bc.y*(vw2.z/vw2.z) + bc.z*(vw3.z/vw3.z));

            // glm::vec2 uv;
            // uv.x = z_* (bc.x*(uv1.x/vw1.z) + bc.y*(uv2.x/vw2.z) + bc.z*(uv3.x/vw3.z));
            // uv.y = z_* (bc.x*(uv1.y/vw1.z) + bc.y*(uv2.y/vw2.z) + bc.z*(uv3.y/vw3.z));

            // glm::vec3 nw;
            // nw.x = z_* (bc.x*(nw1.x/vw1.z) + bc.y*(nw2.x/vw2.z) + bc.z*(nw3.x/vw3.z));
            // nw.y = z_* (bc.x*(nw1.y/vw1.z) + bc.y*(nw2.y/vw2.z) + bc.z*(nw3.y/vw3.z));
            // nw.z = z_* (bc.x*(nw1.z/vw1.z) + bc.y*(nw2.z/vw2.z) + bc.z*(nw3.z/vw3.z));

            // glm::vec4 c;
            // c.x = z_* (bc.x*(c1.x/vw1.z) + bc.y*(c2.x/vw2.z) + bc.z*(c3.x/vw3.z));
            // c.y = z_* (bc.x*(c1.y/vw1.z) + bc.y*(c2.y/vw2.z) + bc.z*(c3.y/vw3.z));
            // c.z = z_* (bc.x*(c1.z/vw1.z) + bc.y*(c2.z/vw2.z) + bc.z*(c3.z/vw3.z));
            // c.w = z_* (bc.x*(c1.w/vw1.z) + bc.y*(c2.w/vw2.z) + bc.z*(c3.w/vw3.z));

            auto& in = static_cast<FragmentInDataPhong&>(*sh._fragmentIn);

            in.worldPos = vw;
            in.uv = uv;
            in.normal = nw;
            in.color = c;

            sh.fragment(*sh._fragmentIn,*sh._fragmentOut);
            //spdlog::info("drawTriangle 4 {} {} {} {}",sh.gl_FragColor.x, sh.gl_FragColor.y, sh.gl_FragColor.z,sh.gl_FragColor.w);
            fb.setPixelColor(p.x,p.y,sh.gl_FragColor);
            // float z0 = LinearizeDepth(p.z);
            // fb.setPixelColor(p.x,p.y,{z0,z0,z0,1.0f});
            //fb.setPixelColor(p.x,p.y,{p.z,p.z,p.z,1.0f});
            //spdlog::info("drawTriangle 4 {}", z0);
        }
    }
    
}

RasterizerPhong::RasterizerPhong(const Rasterizer& r){

}

};