#include <stdio.h>
#include "camera.h"
#include "internet.h"
int flag = 0;
int intrusion_flag = 0;
int main(int argc, char** argv){
    //camera ca(0);
    //ca.displayCameraFrame();
    camera ca(0);
    std::thread t1{ &camera::displayCameraFrame,&ca};
    std::thread t2{ server::setupConnection};
    while(1){
            if(flag == 1){
            ca.~camera();
            break;
        }
    }
    t1.join();
    t2.join();
    //server::setupConnection();
}