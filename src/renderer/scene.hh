#ifndef __SCENE_H
#define __SCENE_H

#include "mesh.hh"
#include <vector>
#include <memory>

namespace Fallment{

class Scene{
public:
    Scene();
    void addMesh(std::unique_ptr<Mesh> m);
    auto getMeshList();

private:

    std::vector<std::unique_ptr<Mesh>> _meshList;



};

}


#endif