/*
    File Name: DetectionSys.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Face Detection Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/


#ifndef DETECTIONSYS_HPP
#define DETECTIONSYS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "GeometricAux.hpp"

#include "definitions.hpp"

/*

#define WIDTH 92    // Width of the face image
#define HEIGHT 112  // Height of the face image
#define DEFAULT_SIZE cv::Size(WIDTH,HEIGHT)

#define CROP_LEFT_PROP 0.8
#define CROP_RIGHT_PROP 0.8
#define CROP_BOTTOM_PROP 1.8
#define CROP_TOP_PROP 1.4

*/

using namespace std;
using namespace cv;
using namespace GeometricAux;

class DetectionSys
{
    public:
        DetectionSys(); /* Default Constructor */

        /* Loads the face and eye cascades with location given by the args */
        int load_cascades(const string& face_cascade_name = FACE_LBP_PATH,
                            const string& eyes_cascade_name = EYES_HAAR_PATH);

        /* Core function of */
        void processFrame(Mat original_frame);

        /* Read the cropped and aligned faces that were processed */
        vector<Mat> getCAimages();

        void changeSelection();
        size_t m_num_faces;

    private:
        size_t m_selection;

        /*  Checks if the given face of the image 'gray_frame' is alignable and croppable.
            If it is, returns the image of the aligned face. The alignment is based on
            eyes detection */
        Mat getAlignedFace(Mat gray_frame, Rect2f face );

        CascadeClassifier m_face_cascade;
        CascadeClassifier m_eyes_cascade;
        vector<Mat> m_img_buffer; // vector to store the processed faces obtained from the gray_frame
};

#endif
