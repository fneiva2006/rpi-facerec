/*
    File Name: RecognitionSys.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Face Recognition Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "RecognitionSys.hpp"

using namespace std;
using namespace cv;

RecognitionSys::RecognitionSys()
{
    m_trained = false;
    m_model = face::createLBPHFaceRecognizer(LBPH_MODEL_RADIUS,LBPH_MODEL_NEIGHBOURS,LBPH_MODEL_XGRID,LBPH_MODEL_YGRID);
}

RecognitionSys::~RecognitionSys()
{
    m_model.release();
}

void RecognitionSys::trainLBPH(const vector<Mat> images, const vector<int> labels)
{
    m_model->train(images,labels);
    m_trained = true;
}

double RecognitionSys::findClosestMatch(const Mat& img, int& index)
{
    double confidence = 0;

    m_model->predict(img,index,confidence);

    m_closestMatchConfidence = confidence;
    m_closestMatchIndex = index;

    return confidence;
}

bool RecognitionSys::trained()
{
    return m_trained;
}

