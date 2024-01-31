#include "texture.hh"

namespace Yukiko{

void Texture::loadFile(const std::string& path) {
    data = stbi_load(path.c_str(), &width, &height, &channelCnt, 0);

    if(!data)
    {
        spdlog::error("Texture load failed at path: {}" , path);
    }else{
        spdlog::error("lod texture: {}, channel count: {}" , path,channelCnt);
    }
}

glm::vec4 Texture::sample(glm::vec2 uv) {
    uv.x = mth::frac(uv.x);
    uv.y = mth::frac(uv.y);

    int x = mth::clamp(int(width * (1.0f-uv.x)), 0, width - 1);
    int y = mth::clamp(int(height * (1.0f-uv.y)), 0, height - 1);

    return getColor(x, y);
}

glm::vec4 Texture::getColor(int x, int y) {
    glm::vec4 ret = {0.f,0.f,0.f,1.f};
    if(!data || x < 0 || y < 0 || x >= width || y >= height)
        return ret;

    int idx = (y * height + x) * channelCnt;

    // Gray
    if(channelCnt == 1) {    
        ret[0] = (float)data[idx];
    }
    // Gray Alpha
    else if(channelCnt == 2) {
        ret[0] = (float)data[idx];
        ret[3] = (float)data[idx + 1];
    }
    // RGB
    else if(channelCnt == 3) {
        ret[0] = (float)data[idx];
        ret[1] = (float)data[idx + 1];
        ret[2] = (float)data[idx + 2];
    }
    // RGBA
    else if(channelCnt == 4) {
        ret[0] = (float)data[idx];
        ret[1] = (float)data[idx + 1];
        ret[2] = (float)data[idx + 2];
        ret[3] = (float)data[idx + 3];
    }

    for(int i=0;i<channelCnt;i++){
        ret[i] = ret[i] / 255;
    }

    return ret;
}

};