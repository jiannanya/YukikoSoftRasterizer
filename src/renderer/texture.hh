#ifndef __TEXTURE_H
#define __TEXTURE_H

#include<string>
#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "spdlog/spdlog.h"

#include "math.hh"


namespace Fallment{

class Texture
{
public:
    unsigned char* data;
    int width, height, channelCnt;

    Texture() {}
    Texture(const std::string& path) { loadFile(path); }
     ~Texture() { stbi_image_free(data); }

    void loadFile(const std::string& path);
    glm::vec4 sample(glm::vec2 uv);
private:

    glm::vec4 getColor(int x, int y);

   
};

}

#endif