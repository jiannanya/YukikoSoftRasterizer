#include "renderpass.hh"


namespace Fallment{

void RenderPass::setContext(std::shared_ptr<Context> _ctx){
     m_ctx = _ctx;
}


RenderPassPhong::RenderPassPhong(){

}

RenderPassPhong::~RenderPassPhong(){

}

void RenderPassPhong::onInit(){

}
void RenderPassPhong::onUpdate(){
    auto& PhongVertexIn = static_cast<VertexInDataPhong&>(*(m_ctx->m_shader->_vertexIn));
    PhongVertexIn.viewMatrix = m_ctx->m_camera->getViewMatrix();
    PhongVertexIn.projectionMatrix = m_ctx->m_camera->getProjectionMatrix();

}
void RenderPassPhong::onFrame(){
    m_ctx->m_framebuffer->clearColorBuffer(m_ctx->m_clearColor);
    m_ctx->m_framebuffer->clearZBuffer();

    glm::mat4 n_matrix = transpose(inverse(m_ctx->m_modelMatrix));// normal transform matrix
    
    auto& mesh_list = m_ctx->m_scene->getMeshList();

    //render per face
    for(auto&mesh: mesh_list)
    for(int i = 0; i < mesh->faceNum(); ++i) {
        //spdlog::info("drawTriangle 0 {}", mesh->faceNum());
        Triangle tri = Triangle();

        // 1. get face vertexs attributes & primitive assemble
        for(int j = 0; j < 3; ++j){
            tri._ve[j] = mesh->getVertex(i, j);
            tri._vuv[j] = mesh->getTexcoord(i,j);
            tri._vn[j] = mesh->getNormal(i,j);
            tri._vco[j] = m_ctx->m_frameColor;
            tri._vnw[j] = n_matrix * glm::vec4(tri._vn[j],1.0f);
             
        }

        unsigned discardCount = 0;
        auto& PhongVertexIn = static_cast<VertexInDataPhong&>(*(m_ctx->m_shader->_vertexIn));
        auto& PhongVertexOut = static_cast<VertexOutDataPhong&>(*(m_ctx->m_shader->_vertexOut));        
        for(int k = 0; k < 3; ++k){

            PhongVertexIn.position = tri._ve[k];

            // 2. transform to clip coordinates using vertex shader
            m_ctx->m_shader->vertex(*(m_ctx->m_shader->_vertexIn),*(m_ctx->m_shader->_vertexOut));

            glm::vec4& vertexClip = m_ctx->m_shader->gl_Position;

             // 3. clip
            float w = vertexClip.w;
            if(vertexClip.z < -w || vertexClip.z > w || vertexClip.x < -w || vertexClip.x > w || vertexClip.y < -w || vertexClip.y > w)
            {
                discardCount++;
                
            }
            // perspective division, normalized to (-1, 1)
            vertexClip = vertexClip / w;  

            // 4. viewport transform
            tri._vp[k] = m_ctx->m_viewportMatrix * vertexClip;

            tri._vp[k].x = int((vertexClip.x + 1.f) * m_ctx->m_framebuffer->getWidth() * 0.5f); //need cast to int for preventing gap between triangles
            tri._vp[k].y = int((1.f - vertexClip.y) * m_ctx->m_framebuffer->getHeight() * 0.5f);
            tri._vp[k].z = vertexClip.z;

            tri._vw[k] = PhongVertexOut.worldPos;

        }

         // all three points of a Triangle outside is clipped, otherwise keep rendering
        if(discardCount==3)
            continue;


        auto& in = static_cast<FragmentInDataPhong&>(*m_ctx->m_shader->_fragmentIn);
        in.camPos = m_ctx->m_camera->getPos();

        // render primitive
        auto& rasterizer = static_cast<RasterizerPhong&>(*m_ctx->m_rasterizer);
        //m_ctx->m_shader->gl_FragColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        rasterizer.drawTriangle(tri,*m_ctx->m_shader,*m_ctx->m_framebuffer);

        

    }
}
void RenderPassPhong::onDestory(){

}



RenderPassLine::RenderPassLine(){

}

RenderPassLine::~RenderPassLine(){

}

void RenderPassLine::onInit(){

}
void RenderPassLine::onUpdate(){

    auto& PhongVertexIn = static_cast<VertexInDataPhong&>(*(m_ctx->m_shader->_vertexIn));
    PhongVertexIn.viewMatrix = m_ctx->m_camera->getViewMatrix();
    PhongVertexIn.projectionMatrix = m_ctx->m_camera->getProjectionMatrix();

}
void RenderPassLine::onFrame(){
    m_ctx->m_framebuffer->clearColorBuffer(m_ctx->m_clearColor);
    m_ctx->m_framebuffer->clearZBuffer();

    glm::mat4 n_matrix = transpose(inverse(m_ctx->m_modelMatrix));// normal transform matrix
    
    auto& mesh_list = m_ctx->m_scene->getMeshList();
    //render per face
    for(auto&mesh: mesh_list)
    for(int i = 0; i < mesh->faceNum(); ++i) {
        Triangle tri = Triangle();

        // 1. get face vertexs attributes & primitive assemble
        for(int j = 0; j < 3; ++j){
            tri._ve[j] = mesh->getVertex(i, j);

        }

        unsigned discardCount = 0;
        auto& PhongVertexIn = static_cast<VertexInDataPhong&>(*(m_ctx->m_shader->_vertexIn));
        auto& PhongVertexOut = static_cast<VertexOutDataPhong&>(*(m_ctx->m_shader->_vertexOut));
        for(int k = 0; k < 3; ++k){

            PhongVertexIn.position = tri._ve[k];

            // 2. transform to clip coordinates using vertex shader
            m_ctx->m_shader->vertex(*(m_ctx->m_shader->_vertexIn),*(m_ctx->m_shader->_vertexOut));

            glm::vec4& vertexClip = m_ctx->m_shader->gl_Position;
             // 3. clip
            float w = vertexClip.w;
            if(vertexClip.z < -w || vertexClip.z > w || vertexClip.x < -w || vertexClip.x > w || vertexClip.y < -w || vertexClip.y > w)
            {
                discardCount++;
                
            }

            vertexClip = vertexClip / w;  

            // 4. viewport transform
            tri._vp[k] = m_ctx->m_viewportMatrix * vertexClip;

            tri._vp[k].x = int((vertexClip.x + 1.f) * m_ctx->m_framebuffer->getWidth() * 0.5f); //need cast to int for preventing gap between triangles
            tri._vp[k].y = int((1.f - vertexClip.y) * m_ctx->m_framebuffer->getHeight() * 0.5f);
            tri._vp[k].z = vertexClip.z;

            tri._vw[k] = PhongVertexOut.worldPos;

        }

         // all three points of a Triangle outside is clipped, otherwise keep rendering
        if(discardCount==3)
            continue;

        // render primitive
        auto& rasterizer = static_cast<RasterizerLine&>(*m_ctx->m_rasterizer);
        m_ctx->m_shader->gl_FragColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
        //spdlog::info("go");
        rasterizer.drawTriangle(tri,*m_ctx->m_shader,*m_ctx->m_framebuffer);
        

    }
}
void RenderPassLine::onDestory(){

}



}