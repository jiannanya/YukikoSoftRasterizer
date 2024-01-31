#include "renderpass.hh"


namespace Yukiko{

RenderPass::RenderPass(){
    onInit();
}

RenderPass::RenderPass(std::unique_ptr<Context> _ctx){
    m_ctx = std::move(_ctx);
}

RenderPass::~RenderPass(){
    onDestory();
}

void RenderPass::onInit(){

}
void RenderPass::onUpdate(){

}
void RenderPass::onFrame(){
    m_ctx->m_framebuffer->clearColorBuffer(m_ctx->m_clearColor);
    m_ctx->m_framebuffer->clearZBuffer();

    glm::mat4 n_matrix = transpose(inverse(m_ctx->m_modelMatrix));// normal transform matrix
    
    auto mesh_list = m_ctx->m_scene->getMeshList();
    

    //render per face
    for(auto&mesh: mesh_list)
    for(int i = 0; i < mesh->faceNum(); ++i) {

        Triangle tri = Triangle();

        // 1. get face vertexs 
        glm::vec2 uv[3];
        glm::vec4 col[3];
        glm::vec3 localVerts[3], nor[3], nw[3];
        for(int j = 0; j < 3; ++j){
            localVerts[j] = mesh->getVertex(i, j);
            uv[j] = mesh->getTexcoord(i,j);
            nor[j] = mesh->getNormal(i,j);
            col[j] = m_ctx->m_frameColor;

            glm::vec4 tn = glm::vec4(nor[j].x,nor[j].y,nor[j].z,0.0);
            glm::vec4 tnn = n_matrix * tn;
            nw[j] = glm::vec3(tnn.x, tnn.y, tnn.z);
        }

        
        tri.setVertices(localVerts);
        tri.setTexCords(uv);
        tri.setNormals(nor);
        tri.setWorldNormals(nw);
        tri.setColors(col);


        // 2. transform to clip coordinates using vertex shader
        glm::vec4 clipPos[3], worldPosH[3];
        for(int k = 0; k < 3; ++k)
            m_ctx->m_shader->vert(localVerts[k],worldPosH[k], clipPos[k]); 

        // 3. clip
        UINT discardCount = 0;
        glm::vec3 worldPos[3];
        for(int k = 0; k < 3; ++k)
        {
            glm::vec4& vertex = clipPos[k];
            float w = vertex.w;
            if(vertex.z < -w || vertex.z > 0.f || vertex.x < -w || vertex.x > w || vertex.y < -w || vertex.y > w)
            {
                discardCount++;
            }
            // perspective division, normalized to (-1, 1)
            vertex = vertex / w;  

            glm::vec4& vw = worldPosH[k];
            vw = vw/vw.w;
            worldPos[k] = glm::vec3(vw.x,vw.y,vw.z);
        }

        tri.setWorldVertices(worldPos);

        // all three points of a Triangle outside is clipped, otherwise keep rendering
        if(discardCount==3)
            continue;

        // 4. viewport
        glm::vec3 viewportPos[3];
        for(int k = 0; k < 3; ++k)
        {
            viewportPos[k].x = int((clipPos[k].x + 1.f) * m_ctx->m_Width * 0.5f); //need cast to int for preventing gap between triangles
            viewportPos[k].y = int((1.f - clipPos[k].y) * m_ctx->m_Height * 0.5f);
            viewportPos[k].z = clipPos[k].z;
        }

        tri.setViewPortVertices(viewportPos);

        // render framewire
        if(m_ctx->m_isDrawWireFrame)
        {
            m_ctx->m_rasterizer->drawTriangleLine(tri,m_ctx->m_frameColor,*m_ctx->m_framebuffer);
        }else{
            //m_rasterizer->drawTriangle(tri,m_frameColor,*m_framebuffer);
            m_ctx->m_rasterizer->drawTriangle(tri,*m_ctx->m_shader,*m_ctx->m_framebuffer,*m_ctx->m_camera);
        }
    }
}
void RenderPass::onDestory(){

}

}