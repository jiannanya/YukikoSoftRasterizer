
#include "appSSAO.hh"
#include "spdlog/spdlog.h"


int main(int argc, char**argv){

    Fallment::AppSSAO caseApp;
    if(caseApp.onInit()){
        caseApp.run();
    }else{
        spdlog::error("App init error!");
    }
    
    
    return 0;
}