
#include "framebuffer.hh"
#include <windows.h>
#include <limits>

namespace Fallment{

Framebuffer::Framebuffer(int width, int height)
:m_color_mutex{},m_z_mutex{}
{
    m_Width = width;
    m_Height = height;
    m_Channel = 4; //RGBA
    m_PixelCount = width * height;

    m_ColorBuffer = new BYTE[m_PixelCount*m_Channel];
    std::unique_lock<std::mutex>(m_color_mutex);
    memset(m_ColorBuffer,0,m_PixelCount*m_Channel);

    std::unique_lock<std::mutex>(m_z_mutex);
    m_ZBuffer = new float[m_PixelCount];
    memset(m_ZBuffer,0,m_PixelCount);

  

};

Framebuffer::~Framebuffer() {};


BYTE*& Framebuffer::getColorBuffer() {
    return m_ColorBuffer;
};

float *Framebuffer::getZBuffer(){
    return m_ZBuffer;
}

float Framebuffer::getZ(unsigned int x, unsigned int y){
    UINT index = y * m_Width + x;
    return m_ZBuffer[index];
}

void Framebuffer::setZ(unsigned int x, unsigned int y, float value){
    std::unique_lock<std::mutex>(m_z_mutex);
    UINT index = y * m_Width + x;
    m_ZBuffer[index] = value;
}

int Framebuffer::getChannelNums()const{
    return m_Channel;
}


void Framebuffer::clearColorBuffer(glm::vec4 color) {
    //std::cerr<<"clearColorBuffer: "<< color.x<<", "<<color.y<<", "<<color.z<<", "<<color.w<<std::endl;
    std::unique_lock<std::mutex>(m_color_mutex);
    UINT index_limit = m_PixelCount * m_Channel;
    for(UINT index=0;index<index_limit;index+=m_Channel){
        m_ColorBuffer[index+0] = static_cast<BYTE>(color.x * 255);
        m_ColorBuffer[index+1] = static_cast<BYTE>(color.y * 255);
        m_ColorBuffer[index+2] = static_cast<BYTE>(color.z * 255);
        m_ColorBuffer[index+3] = static_cast<BYTE>(color.w * 255);
    }
    
};

void Framebuffer::clearZBuffer(){
    std::unique_lock<std::mutex>(m_z_mutex);
    memset(m_ZBuffer,std::numeric_limits<float>::lowest(),m_PixelCount);
    // for (int i=m_PixelCount-1;i>=0 ;i--)
    //     m_ZBuffer[i] = -(std::numeric_limits<float>::max)() ;
}


int Framebuffer::getWidth()const {
    return m_Width;
};


int Framebuffer::getHeight()const {
    return m_Height;
};


void Framebuffer::setPixelColor(unsigned int x, unsigned int y, glm::vec4 color) {
    if(x < 0 || x >= m_Width || y < 0 || y >= m_Height)
        return;

    std::unique_lock<std::mutex>(m_color_mutex);
    //std::cerr<<"set pixel color: "<<x<<", "<<y<<": "<< color.x<<", "<<color.y<<", "<<color.z<<", "<<color.w<<std::endl;

    UINT index = y * m_Width * m_Channel + x * m_Channel;

    // BGRA for windows creation
    m_ColorBuffer[index + 0] = static_cast<BYTE>(color.z * 255);
    m_ColorBuffer[index + 1] = static_cast<BYTE>(color.y * 255);
    m_ColorBuffer[index + 2] = static_cast<BYTE>(color.x * 255);
    m_ColorBuffer[index + 3] = static_cast<BYTE>(color.w * 255);
}

};