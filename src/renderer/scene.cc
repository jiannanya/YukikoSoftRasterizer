
#include "scene.hh"

namespace Fallment{

Scene::Scene(){
    //_meshList = std::vector<std::unique_ptr<Mesh>>{};
}

void Scene::addMesh(std::unique_ptr<Mesh>&& m){
    _meshList.emplace_back(std::forward<std::unique_ptr<Mesh>>(m));
}


// void Scene::addMesh(Mesh* m){
//     _meshList.emplace_back(m);
// }

std::vector<std::unique_ptr<Mesh>>& Scene::getMeshList(){
    return _meshList;
}

}