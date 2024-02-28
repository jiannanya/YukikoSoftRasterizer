#include "fpsControl.hh"

namespace Fallment{

FpsControls::FpsControls(std::unique_ptr<Camera>&& camera){
    m_camera = std::move(camera);
}


bool FpsControls::onInit(){

}
bool FpsControls::onUpdate(){
    
}

void FpsControls::onDestory(){

}

}