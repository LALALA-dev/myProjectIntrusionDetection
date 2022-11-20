#include "camera.h"
extern int flag,intrusion_flag;
int rst = 0;
camera::camera(int i): camId(i),vc(i){
    vc.read(background);
    imageProcess(background);
};

void camera::imageProcess(Mat& image){
    cvtColor(image,image,COLOR_BGR2GRAY);
    GaussianBlur(image,image,Size(5,5),0);
    threshold(image,image,30,255,THRESH_BINARY);
    erode(image,image,0);
    dilate(image,image,0);
}

Mat camera::getCameraFrame(){
    Mat result;
    if(!vc.isOpened()){
        printf("Camera fails to open!!!");
        return result;
    }
    
    if(!vc.read(result)){
        printf("Camera fails to capture frame");
    }
    return result;
}

camera::~camera(){
    vc.release();
    destroyAllWindows();
    std::cout << "All windoes and camera destoried!\n";
}

void camera::displayCameraFrame(){
    Mat temp,temp1;
    while(vc.isOpened()){
        int diff = 0;
        rst > 0 ? rst--: rst = 0;
        vc >> temp;
        Mat store{temp};
        //imshow("Camera",temp);
        imageProcess(temp);
        absdiff(background,temp,temp1);
        threshold(temp1,temp1,30,255,THRESH_BINARY);
        for(int i = 0; i < temp1.rows;i++){
            for(int j = 0; j < temp1.cols;j++){
                if(temp.at<int>(i,j) == 0xff){
                    diff++;
                }
            }
        }
        
        //std::cout<<"size: " <<temp.total()<<std::endl;
        if(diff > med && rst == 0){
            std::cout<<"Something Detected"<<std::endl;
            intrusion_flag = 1;
            saveFrame(store);
            rst = 10;
        }
        imshow("Camera",temp1);
        waitKey(100);
    }
}

void camera::saveFrame(Mat& frame){
    imwrite("../img/test.jpg",frame);
}

void camera::setCamera(int i){
    camId = i;
    vc.open(i);
}