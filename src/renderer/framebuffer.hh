#ifndef __FRAMEBUFFER_HH
#define __FRAMEBUFFER_HH

#include "math.hh"

#include <mutex>

namespace Fallment{

class Framebuffer {
public:
    Framebuffer(){}
    Framebuffer(int width, int height);
    ~Framebuffer();

    BYTE*& getColorBuffer();//需要返回引用用来创建windows窗口
    float *getZBuffer();
    float getZ(unsigned int x, unsigned int y);
    void setZ(unsigned int x, unsigned int y, float value);
    int getWidth()const;
    int getHeight()const;
    int getChannelNums()const;
    void clearColorBuffer(glm::vec4 color);
    void clearZBuffer();
    void setPixelColor(unsigned int x, unsigned int y, glm::vec4 color);

public:

    std::mutex m_color_mutex;
    std::mutex m_z_mutex;

private:
    int m_Width;
    int m_Height;
    int m_Channel;
    int m_PixelCount;
    BYTE* m_ColorBuffer;
    float* m_ZBuffer;


};

};


#endif