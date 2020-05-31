/*
    File Name: CameraSys.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Camera Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/


#ifndef CAMERASYS_HPP
#define CAMERASYS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

class CameraSys
{
    public:
        Mat m_frame;

        CameraSys()
        {
            system("sudo modprobe bcm2835-v4l2");
        }

        int start(const double width = 320, const double height = 240, const double fps = 12)
        {
             // Open camera
            cout << "Opening camera..." << endl;
            m_Camera.open(0);
            if (!m_Camera.isOpened())
            {
                cerr << "Failed to open a video device or video file!\n" << endl;
                return 1;
            }

            // Set camera params
            m_Camera.set(CV_CAP_PROP_FRAME_WIDTH, width);
            m_Camera.set(CV_CAP_PROP_FRAME_HEIGHT,height);
            m_Camera.set(CV_CAP_PROP_FPS, fps);

            return 0;

        }

        cv::Mat getFrame(double rot_angle = 0)
        {
            /* Get a new frame from camera */
            m_Camera >> m_frame;

            if(rot_angle != 0)
            CameraSys::rotate_90n(m_frame,m_frame, rot_angle ); /* Flip image */
            return m_frame;
        }

        static void rotate_90n(cv::Mat &src, cv::Mat &dst, int angle)
        {
            dst.create(src.size(), src.type());
            if(angle == 270 || angle == -90){
                // Rotate clockwise 270 degrees
                cv::transpose(src, dst);
                cv::flip(dst, dst, 0);
            }else if(angle == 180 || angle == -180){
                // Rotate clockwise 180 degrees
                cv::flip(src, dst, -1);
            }else if(angle == 90 || angle == -270){
                // Rotate clockwise 90 degrees
                cv::transpose(src, dst);
                cv::flip(dst, dst, 1);
            }else if(angle == 360 || angle == 0){
                if(src.data != dst.data){
                    src.copyTo(dst);
                }
            }
        }

        ~CameraSys()
        {
            cout << "\nStopping camera.." << endl;
            m_Camera.release();   // stops camera
        }

    private:
        VideoCapture m_Camera;


};

#endif // CAMERASYS_HPP
