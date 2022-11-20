#include <opencv2/opencv.hpp>
#define low 300
#define med 500
#define high 700
using namespace cv;

class camera{
    public:
    camera(int i = 0);
    Mat getCameraFrame();
    void saveFrame(Mat& frame);
    void displayCameraFrame();
    void setCamera(int i);
    ~camera();
    private:
    int camId = 0;
    VideoCapture vc;
    Mat background;
    void imageProcess(Mat& image);
};