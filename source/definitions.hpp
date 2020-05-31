/*
    File Name: definitions.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Definitions and macros" used on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/


#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

//#include "common_headers.hpp"

/* Working dir from where the program starts looking for the images to load */
#define WORKING_DIR static_cast<string>("imgdb/subjects/")

/* LBPH model parameters */
#define LBPH_MODEL_NEIGHBOURS 8
#define LBPH_MODEL_XGRID 8
#define LBPH_MODEL_YGRID 8
#define LBPH_MODEL_RADIUS 1

/* Face images default dimensions */
#define WIDTH 92    // Width of the face image
#define HEIGHT 112  // Height of the face image
#define DEFAULT_SIZE cv::Size(WIDTH,HEIGHT)

/* Proportions of the face used to crop the face out of the detected frame */
#define CROP_LEFT_PROP 0.75
#define CROP_RIGHT_PROP 0.75
#define CROP_BOTTOM_PROP 1.8
#define CROP_TOP_PROP 1.4

/* Recognition confidence threshold */
#define THRESHOLD_REC 100.00

/* ====================== UserInterface window size and position =============================*/

/* Main camera display window */
#define MAIN_WINDOW_HEIGHT 480
#define MAIN_WINDOW_WIDTH 640
#define MAIN_WINDOW_NAME string("Display")

/* Cropped/Aligned face display window */
#define CAFACE_WINDOW_WIDTH static_cast<int>(WIDTH)
#define CAFACE_WINDOW_HEIGHT static_cast<int>(HEIGHT)
#define CAFACE_WINDOW_NAME string("Cropped Face")

/* Closest match face display window */
#define CLM_WINDOW_WIDTH static_cast<int>(WIDTH)
#define CLM_WINDOW_HEIGHT static_cast<int>(HEIGHT)
#define CLM_WINDOW_NAME string("Closest Match")

/* Window bar size offset used to adjust the position of the windows on the screen */
#define BAR_OFFSET 35

/* ========================================================================================== */

/* Text input/output file addresses */
#define OUT_TXT "InputOutput/image_to_speech.txt"
#define IN_TXT "InputOutput/speech_to_image.txt" // to be changed when input is implemented

//#define FACE_HAAR_PATH ""
#define FACE_LBP_PATH "lbpcascades/lbpcascade_frontalface.xml"
#define EYES_HAAR_PATH "haarcascades/haarcascade_eye_tree_eyeglasses.xml"


#define BLACK_FRAME cv::Mat(DEFAULT_SIZE, CV_8UC1, Scalar(0,0,0))

#define CAM_ROT_ANGLE 180

#define EMPTY_STR string("")

    /*  requests speech input of type request
        0 - no request, 1 - y/n or q, 2 - name
        3 - command key,*/

enum speech_modes {IDLE = 0, YES_NO , TEXT, COMMAND};

#endif // DEFINITIONS_HPP
