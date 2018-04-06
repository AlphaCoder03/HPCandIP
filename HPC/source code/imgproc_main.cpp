


#include <string>
#include <sys/time.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "imgproc.h"

int main(int argc, char** argv)
{
    // open a web camera
    cv::VideoCapture camera(0);
    cv::Mat   frame;
    if(!camera.isOpened())
    return -1;
    camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    camera >> frame;
    
    // create gpu/cpu shared images - one for initial and one for result
    cv::Mat sGray(frame.size(),
                  CV_8U,
                  createImageBuffer(frame.size().width * frame.size().height));
    cv::Mat dGray(frame.size(),
                  CV_8U,
                  createImageBuffer(frame.size().width * frame.size().height));
    cv::Mat eGray(frame.size(),
                  CV_8U,
                  createImageBuffer(frame.size().width * frame.size().height));
    cv::cvtColor(frame, dGray, CV_BGR2GRAY);
    cv::cvtColor(frame, eGray, CV_BGR2GRAY);
    
    // create the capture windows
    cv::namedWindow("source");
    cv::namedWindow("Greyscale");
    cv::namedWindow("Blurred");
    cv::namedWindow("Sobel");
    //  loop while capturing images
    while(1)
    {
        // capure the image and store the grey version for the gpu
        camera >> frame;
        cv::cvtColor(frame, sGray, CV_BGR2GRAY);
        
        // perform the gpu based blur
        struct timeval tv;
        struct timezone tz;
        struct tm *tm;
        gettimeofday(&tv, &tz);
        tm=localtime(&tv.tv_sec);
        printf("%d:%02d:%02d %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
        boxfilter(frame.size().width, frame.size().height, sGray.data, dGray.data, 3, 3);
        sobelfilter(frame.size().width, frame.size().height, dGray.data, eGray.data);
        gettimeofday(&tv, &tz);
        tm=localtime(&tv.tv_sec);
        printf("%d:%02d:%02d %d \n", tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
        
        // show the results
        cv:: imshow("source", frame);
        cv:: imshow("Greyscale", sGray);
        cv:: imshow("Blurred", dGray);
        cv:: imshow("Sobel", eGray);
    }
    
    // exit
    destroyImageBuffer(sGray.data);
    destroyImageBuffer(dGray,data);
    
    return 0;
}