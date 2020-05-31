/*
    File Name: UserInterface.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "User Interface Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <thread>

#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "definitions.hpp"

#include "DetectionSys.hpp"
#include "FrameRate.hpp"
#include "CameraSys.hpp"
#include "RecognitionSys.hpp"
#include "DataIO.hpp"
#include "SpeechHandler.hpp"

#include "Tokenizer.hpp"
/*
#define WIDTH 92    // Width of the face image
#define HEIGHT 112  // Height of the face image
#define DEFAULT_SIZE cv::Size(WIDTH,HEIGHT)

#define MAIN_WINDOW_HEIGHT 480
#define MAIN_WINDOW_WIDTH 640
#define MAIN_WINDOW_NAME string("Display")

#define CAFACE_WINDOW_WIDTH static_cast<int>(WIDTH)
#define CAFACE_WINDOW_HEIGHT static_cast<int>(HEIGHT)
#define CAFACE_WINDOW_NAME string("Cropped Face")

#define CLM_WINDOW_WIDTH static_cast<int>(WIDTH)
#define CLM_WINDOW_HEIGHT static_cast<int>(HEIGHT)
#define CLM_WINDOW_NAME string("Closest Match")

#define BAR_OFFSET 35
*/


using namespace std;
using namespace cv;

class UserInterface
{
    public:
        UserInterface();

        ~UserInterface();

        /* Interface setup */
        void createWindow(const string& window_name, int pos_x = 0, int pos_y = 0, int width = 100, int height = 100);

        /* Screen Output functions */

        void displayImage(const string& window_name, Mat frame);

        /* Speech Output functions */

        static void speak(string speech);

        /* Keyboard input fucntions */

        int getWindowKey();

        const string win(const Mat frame);

        const string win(CameraSys* cam);

        const string win(CameraSys* cam, const string& text);

        const string spwin(const Mat frame, SpeechHandler* sp);

        const string spwin( CameraSys* cam, SpeechHandler* sp);

        static void putFormatedWindowText( cv::Mat frame, const string& text );

        int m_cvkey;

        //string getSpeechCmd(string file_address=IN_TXT);

        /* */

    private:


};

#endif
