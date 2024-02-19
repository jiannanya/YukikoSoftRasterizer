
#include "shader.hh"

#include "spdlog/spdlog.h"

namespace Fallment{


    /**** Simple Shader ****/
    SimpleShader::SimpleShader():Shader{}{}
    
    void SimpleShader::vertex(VertexInData& _in, VertexOutData& _out) {

        auto& in = static_cast<VertexInDataSimple&>(_in);
        auto& out = static_cast<VertexOutDataSimple&>(_out);
        out.color = in.color;
        gl_Position = glm::vec4(in.position,1.0f);
        return;
    }

    void SimpleShader::fragment(FragmentInData& _in, FragmentOutData& _out) {
        auto& in = static_cast<FragmentInDataSimple&>(_in);
        //auto out = static_cast<FragmentOutdataSimple>(FragmentOutData);
        gl_FragColor = in.color;
        return;
    }


    /**** MVP transform Shader ****/
    TransformShader::TransformShader():Shader{}{}

    void TransformShader::vertex(VertexInData& _in, VertexOutData& _out) {
        auto& in = static_cast<VertexInDataTransform&>(_in);
        auto& out = static_cast<VertexOutDataTransform&>(_out);
        out.color = in.color;
        gl_Position = in.projectionMatrix * in.viewMatrix * in.modelMatrix * glm::vec4(in.position,1.0f); 
        return;
    }

    void TransformShader::fragment(FragmentInData& _in, FragmentOutData& _out) {
        auto& in = static_cast<FragmentInDataTransform&>(_in);
        gl_FragColor = in.color;
        return;
    }

    /**** Gouraud Shader****/
    GouraudShader::GouraudShader():Shader{}{}

    void GouraudShader::vertex(VertexInData& _in, VertexOutData& _out) {
        auto& in = static_cast<VertexInDataGouraud&>(_in);
        auto& out = static_cast<VertexOutDataGouraud&>(_out);

        gl_Position = in.projectionMatrix * in.viewMatrix * in.modelMatrix * glm::vec4(in.position,1.0f); //mvp transformation

        // 计算着色
        glm::vec3 ka = in.material.ka;
        glm::vec3 kd = in.material.kd;
        if(in.texture){
            kd = in.texture->sample(in.uv);
        }
        glm::vec3 ks = in.material.ks;
        glm::vec3 color(0.0f,0.0f,0.0f);
        //directional lights
        for(const auto& light:in.directionLights){
            glm::vec3 lightDir = glm::normalize(-light->_direction); // pos -> light
            glm::vec3 viewDir = glm::normalize(in.camPos - in.position); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量
            glm::vec3 L_a = light->_ambient * kd;
            glm::vec3 L_d = light->_diffuse * kd * std::max(0.0f,glm::dot(in.normal,lightDir));
            glm::vec3 L_s = light->_specular * ks * pow(std::max(0.0f,glm::dot(in.normal,half)),in.material.shininess);

            color += (L_a + L_d + L_s)*255.0f;
        }

        //point lights
        for(const auto& light:in.pointLights){
            glm::vec3 lightDir = glm::normalize(light->_position - in.position); // pos -> light
            glm::vec3 viewDir = glm::normalize(in.camPos - in.position); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量
            float distance = mth::square_distance(in.position,light->_position);
            glm::vec3 L_d = light->_diffuse * kd * std::max(0.0f,glm::dot(in.normal,lightDir));
            glm::vec3 L_s = light->_specular * ks * pow(std::max(0.0f,glm::dot(in.normal,half)),in.material.shininess);
            
            color += (L_d/distance + L_s/distance)*255.0f;
        }

        //color = glm::vec3(std::min(color[0],255.0f), std::min(color[1],255.0f),std::min(color[2],255.0f));
        out.color = glm::vec4(glm::clamp(color,glm::vec3(0,0,0),glm::vec3(255,255,255)),1.0f);

        return;
    }

    void GouraudShader::fragment(FragmentInData& _in, FragmentOutData& _out) {
        auto& in = static_cast<FragmentInDataGouraud&>(_in);
        gl_FragColor = in.color;
        return;
    }

    /**** Phong Shader****/
    PhongShader::PhongShader():Shader{}{}

    void PhongShader::vertex(VertexInData& _in, VertexOutData& _out) {
        auto& in = static_cast<VertexInDataPhong&>(_in);
        auto& out = static_cast<VertexOutDataPhong&>(_out);
        //spdlog::debug("phong shader vertex");
        gl_Position = in.projectionMatrix * in.viewMatrix * in.modelMatrix * glm::vec4(in.position,1.0f); //mvp transformation
        auto worldPos = in.modelMatrix * glm::vec4(in.position,1.0f);  // vec3 = vec4...
        out.worldPos = worldPos / worldPos.w;

        return;
    }

    void PhongShader::fragment(FragmentInData& _in, FragmentOutData& _out) {

        auto& in = static_cast<FragmentInDataPhong&>(_in);
        auto& out = static_cast<FragmentOutDataPhong&>(_out);


        glm::vec3 ka = in.material->ka;
        glm::vec3 kd = in.material->kd;
        if(in.texture){
            //spdlog::debug("shader in has texture");
            kd = in.texture->sample(in.uv);
        }
        glm::vec3 ks = in.material->ks;

        glm::vec3 color(0.0f,0.0f,0.0f);

        //directional lights
        for(const auto& light:in.directionLights){
            glm::vec3 lightDir = glm::normalize(-light->_direction); // pos -> light
            glm::vec3 viewDir = glm::normalize(in.camPos - in.worldPos); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量
            glm::vec3 L_a = light->_ambient * ka;
            glm::vec3 L_d = light->_diffuse * kd * std::max(0.0f,glm::dot(in.normal,lightDir));
            glm::vec3 L_s = light->_specular * ks * pow(std::max(0.0f,glm::dot(in.normal,half)),in.material->shininess);
            color += (L_a + L_d + L_s);
        }

        //point lights
        for(const auto& light:in.pointLights){
            glm::vec3 lightDir = glm::normalize(light->_position - in.worldPos); // pos -> light
            glm::vec3 viewDir = glm::normalize(in.camPos - in.worldPos); // pos -> view
            glm::vec3 half = glm::normalize(lightDir + viewDir); // 半程向量

            float distance = mth::square_distance(in.worldPos,light->_position);
            glm::vec3 L_a = light->_ambient * ka;
            glm::vec3 L_d = kd * std::max(0.0f,glm::dot(in.normal,lightDir));
            glm::vec3 L_s = ks * std::pow(std::max(0.0f,glm::dot(in.normal,half)),in.material->shininess);


            color += (L_a + L_d + L_s / distance);
            
        }
        //spdlog::debug("shader in {} {} {}",in.normal.x,in.normal.y,in.normal.z);
        
        //spdlog::debug("shader in {} {} {}",color.x,color.y,color.z);


        gl_FragColor = glm::vec4(glm::clamp(color,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(1.0f,1.0f,1.0f)),1.0f);
        //gl_FragColor = in.texture->sample(in.uv);
        return ;
    }


}