
#include "Scene.hh"

namespace Fallment{

Scene::Scene(){
    _meshList = std::vector<std::unique_ptr<Mesh>>();
}

void Scene::addMesh(std::unique_ptr<Mesh> m){
    _meshList.emplace_back(std::move(m));
}

auto Scene::getMeshList(){
    return _meshList;
}

}