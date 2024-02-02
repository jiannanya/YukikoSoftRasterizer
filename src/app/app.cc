#include "app/app.hh"

namespace Fallment{

void App::run(){
    while(onUpdate()){
        onFrame();
    }
}


}