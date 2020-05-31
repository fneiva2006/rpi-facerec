/*
    File Name: RecognitionSys.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Face Recognition Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#ifndef RECOGNITIONSYS_HPP
#define RECOGNITIONSYS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "opencv2/face.hpp"

#include "definitions.hpp"

/*
#define LBPH_MODEL_NEIGHBOURS 8
#define LBPH_MODEL_XGRID 8
#define LBPH_MODEL_YGRID 8
#define LBPH_MODEL_RADIUS 1
*/

using namespace std;
using namespace cv;

class RecognitionSys
{
    public:
        RecognitionSys();
        ~RecognitionSys();

        void trainLBPH(const vector<Mat> images, const vector<int> labels);

        double findClosestMatch(const Mat& img, int& index);

        double m_closestMatchConfidence;
        int m_closestMatchIndex;

        bool trained();

    private:
        Ptr<face::LBPHFaceRecognizer> m_model;
        bool m_trained;
};

#endif
