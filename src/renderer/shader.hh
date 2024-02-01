#ifndef __SHADER_H
#define __SHADER_H


#include <iostream>

#include "spdlog/spdlog.h"

#include "light.hh"
#include "material.hh"
#include "texture.hh"

namespace Yukiko{

    // ******** base in out data ************
    struct VertexInData{};
    struct VertexOutData{};
    struct FragmentInData{};
    struct FragmentOutData{};

    // ******** simple shader in out data ************
    struct VertexInDataSimple:public VertexInData{
        glm::vec3 position; 
        glm::vec4 color;
    };

    struct VertexOutDataSimple:public VertexOutData{
        glm::vec4 color;
    };

    struct FragmentInDataSimple:public FragmentInData{
        glm::vec4 color;
    };
        
    struct FragmentOutDataSimple:public FragmentOutData{
        //glm::vec4 color;
    };


    // ******** Mvp shader in out data ************
    struct VertexInDataTransform:public VertexInData{
        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        glm::vec4 color;
    };

    struct VertexOutDataTransform:public VertexOutData{
        glm::vec4 color;
    };

    struct FragmentInDataTransform:public FragmentInData{
        glm::vec4 color;
    };
        
    struct FragmentOutDataTransform:public FragmentOutData{
        //glm::vec4 color;
    };

    // ******** Gouraud shader in out data ************
    struct VertexInDataGouraud:public VertexInData{
        glm::mat4   modelMatrix;
        glm::mat4   viewMatrix;
        glm::mat4   projectionMatrix;
        Texture*    texture;
        Material    material;
        glm::vec3   camPos;
        glm::vec3   position;
        glm::vec3   normal;
        glm::vec2   uv;
        // multiple lights
        std::vector<std::unique_ptr<DirectionLight>> directionLights; 
        std::vector<std::unique_ptr<PointLight>> pointLights;
    };

    struct VertexOutDataGouraud:public VertexOutData{
        glm::vec4 color;
    };

    // 和VertexOutDataPhong一样
    struct FragmentInDataGouraud:public FragmentInData{
        glm::vec4 color;
    };
        
    struct FragmentOutDataGouraud:public FragmentOutData{
        //glm::vec4 color;
    };

    
    // ******** Phong shader in out data ************
    struct VertexInDataPhong:public VertexInData{
        VertexInDataPhong(){

        }

        VertexInDataPhong(glm::mat4 _M, glm::mat4 _V, glm::mat4 _P, glm::vec3 _POS)
        :   modelMatrix{_M},
            viewMatrix{_V},
            projectionMatrix{_P},
            position{_POS}{
            
        }

        // 类型转换构造函数
        VertexInDataPhong(VertexInData& _data){

        }
        

        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 position;

    };

    struct VertexOutDataPhong:public VertexOutData{

        VertexOutDataPhong(){

        }

        VertexOutDataPhong(VertexOutData& _data){

        }

        glm::vec3 worldPos; //世界坐标
        glm::vec3 normal;
        glm::vec4 color;
        glm::vec2  uv;
    };


    struct FragmentInDataPhong:public FragmentInData{

        FragmentInDataPhong(){}

        FragmentInDataPhong(glm::vec3 _W_POS, glm::vec3 _NORMAL, glm::vec3 _CAM_POS,
                            glm::vec4 _COLOR, glm::vec2 _UV,std::unique_ptr<Texture> _TEX,
                            std::unique_ptr<Material> _MATERAIL)
                            :worldPos{_W_POS},normal{_NORMAL},camPos{_CAM_POS}
                            ,color{_COLOR},uv{_UV},texture{std::move(_TEX)}
                            ,material{std::move(_MATERAIL)}{

                            }

        FragmentInDataPhong(FragmentInData& _data){

        }

        glm::vec3 worldPos;
        glm::vec3 normal;
        glm::vec3 camPos;
        glm::vec4 color;
        glm::vec2 uv;
        std::unique_ptr<Texture>  texture;
        std::unique_ptr<Material> material;
        
        // multiple lights
        std::vector<std::unique_ptr<DirectionLight>> directionLights{}; 
        std::vector<std::unique_ptr<PointLight>> pointLights{};
    };
        
    struct FragmentOutDataPhong:public FragmentOutData{
        //glm::vec4 color;
    };

    class Shader {
    public:
        virtual void  vertex(VertexInData& in, VertexOutData& out)=0; 
        virtual void  fragment(FragmentInData& in, FragmentOutData& out)=0;

    public:
        glm::vec4 gl_Position;
        glm::vec4 gl_FragColor;

    public:
        std::unique_ptr<VertexInData>      _vertexIn;
        std::unique_ptr<VertexOutData>     _vertexOut;
        std::unique_ptr<FragmentInData>    _fragmentIn;
        std::unique_ptr<FragmentOutData>   _fragmentOut;
    };

    /**
     *  simple vertex shader just pass the value
     */

    class SimpleShader: public Shader{
    public:
        SimpleShader();
        void  vertex(VertexInData& in, VertexOutData& out) override;
        void  fragment(FragmentInData& in, FragmentOutData& out) override;
    };

    /**
     * 3d shader, implement mvp transformation for vertex shader, fragment shader just pass color
     */
    class TransformShader: public Shader{
    public:
        TransformShader();
        void  vertex(VertexInData& in, VertexOutData& out) override;
        void  fragment(FragmentInData& in, FragmentOutData& out) override;
    };

    /**
     * Gouraud shader, DO NOT interpolate normal, so calculate color at vertexShader stage and interpolate color
     */
    class GouraudShader : public Shader{
    public:
        GouraudShader();
        void  vertex(VertexInData& in, VertexOutData& out) override;
        void  fragment(FragmentInData& in, FragmentOutData& out) override;
    };

    /**
     * Phong shader, DO interpolate normal, and calculate color at fragmentShader stage
     */
    class PhongShader : public Shader{
    public:
        PhongShader();
        void  vertex(VertexInData& in, VertexOutData& out) override;
        void  fragment(FragmentInData& in, FragmentOutData& out) override;

    public:

    };


}



#endif //__SHADER_H

