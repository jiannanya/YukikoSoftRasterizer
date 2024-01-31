#ifndef __MESH_H
#define __MESH_H

#include <vector>
#include <string>
#include "math.hh"

namespace Yukiko{

class Mesh
{
public:
    std::vector<glm::vec3> vertexs;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec3> normals;

    std::vector<int> facet_vert;
    std::vector<int> facet_texcoord;
    std::vector<int> facet_norm;

    Mesh(){}
    Mesh(const std::string& filename);

    int faceNum() const;
    glm::vec3 getVertex(const int i) const;
    glm::vec3 getVertex(const int face_idx, const int offset) const;
    glm::vec2 getTexcoord(const int face_idx, const int offset) const;
    glm::vec3 getNormal(const int face_idx, const int offset) const;
};

};

#endif