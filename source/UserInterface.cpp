/*
    File Name: UserInterface.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "User Interface Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "UserInterface.hpp"


using namespace std;
using namespace cv;

UserInterface::UserInterface()
{
    createWindow(CAFACE_WINDOW_NAME, MAIN_WINDOW_WIDTH, BAR_OFFSET, CAFACE_WINDOW_WIDTH,
        CAFACE_WINDOW_HEIGHT );

    createWindow(CLM_WINDOW_NAME,MAIN_WINDOW_WIDTH,CAFACE_WINDOW_HEIGHT + 2*BAR_OFFSET,
       CLM_WINDOW_WIDTH, CLM_WINDOW_HEIGHT );

    createWindow(MAIN_WINDOW_NAME, 0,0,MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT);
}

UserInterface::~UserInterface()
{
    destroyAllWindows();
}

void UserInterface::createWindow(const string& window_name, int pos_x, int pos_y , int width , int height)
{
    namedWindow(window_name, WINDOW_AUTOSIZE);
    moveWindow(window_name,pos_x,pos_y);
    resizeWindow(window_name,width,height);
}

void UserInterface::displayImage(const string& window_name, Mat frame)
{
    imshow(window_name, frame);
    resizeWindow(window_name,frame.cols,frame.rows);
}

int UserInterface::getWindowKey()
{
   m_cvkey = waitKey(1); /* waits for 1 microsec */
   return m_cvkey;
}

//string UserInterface::getSpeechCmd(string file_address)
//{
//    string command = ControlSystem::inputProcedure(file_address);
//    if(command != string(""))
//    {
//        return command;
//    }
//    return "";
//}

void UserInterface::speak(string speech){
    speech = "./TTS.sh \""+speech+"\"";
    system( speech.c_str() );
    return;
}

const string UserInterface::win(const Mat frame)
{
    // This will not be a part of final program!.....................
    int cvkey;
    Mat displayFrame = frame.clone();
    string text_buf {""};

    putFormatedWindowText(displayFrame, string("Save file: [subject,name]"));
    imshow(MAIN_WINDOW_NAME,displayFrame);
    speak("Please say your name");

    while(1)
    {
        cvkey = cv::waitKey(1);

        if(cvkey > 0)
        {
            if(cvkey%256 == '\n')
            {
                text_buf=DataIO::string_to_lowercase(text_buf);
                break;
            }
            else if(cvkey%256 == '\e')
            {
                return string("\e");
            }
            else if(cvkey%256 == '\b')
            {
                if(text_buf.size() != 0)
                    text_buf.erase(text_buf.end() - 1);
            }
            else if( ( (cvkey%256)<='z' && (cvkey%256)>= 'a') || ((cvkey%256)<= 'Z' && (cvkey%256)>= 'A') || ((cvkey%256)<= '9' && (cvkey%256)>='0') || (cvkey%256)==' ' || (cvkey%256)==',')
            {
                //as input is accepted only A-Z, a-z, 0-9, "," or " "
                text_buf = text_buf + static_cast<char>(cvkey%256);
            }

            putFormatedWindowText(displayFrame, string("Save file: [subject,name]") + string("\n") + text_buf);
            imshow(MAIN_WINDOW_NAME,displayFrame);
            displayFrame = frame.clone();

        }

    }
    return text_buf;
}

const string UserInterface::win(CameraSys* cam)
{
    // This will not be a part of final program!.....................
    int cvkey;
    Mat displayFrame = cam->getFrame(CAM_ROT_ANGLE);
    string text_buf {""};

    speak("Please say your name");

    while(1)
    {
        cvkey = cv::waitKey(1);

        if(cvkey > 0)
        {
            if(cvkey%256 == '\n')
            {
                text_buf=DataIO::string_to_lowercase(text_buf);
                break;
            }
            else if(cvkey%256 == '\e')
            {
                return string("\e");
            }
            else if(cvkey%256 == '\b')
            {
                if(text_buf.size() != 0)
                    text_buf.erase(text_buf.end() - 1);
            }
            else if( ( (cvkey%256)<='z' && (cvkey%256)>= 'a') || ((cvkey%256)<= 'Z' && (cvkey%256)>= 'A') || ((cvkey%256)<= '9' && (cvkey%256)>='0') || (cvkey%256)==' ' || (cvkey%256)==',')
            {
                //as input is accepted only A-Z, a-z, 0-9, "," or " "
                text_buf = text_buf + static_cast<char>(cvkey%256);
            }

        }
        putFormatedWindowText(displayFrame, string("Save file: [subject,name]")+ string("\n") + text_buf);
        imshow(MAIN_WINDOW_NAME,displayFrame);
        displayFrame = cam->getFrame(CAM_ROT_ANGLE);

    }
    return text_buf;
}

const string UserInterface::win(CameraSys* cam, const string& text)
{
    // This will not be a part of final program!.....................
    int cvkey;
    Mat displayFrame = cam->getFrame(CAM_ROT_ANGLE);
    string text_buf {""};

    //speak("Please say your name");

    while(1)
    {
        cvkey = cv::waitKey(1);

        if(cvkey > 0)
        {
            if(cvkey%256 == '\n')
            {
                text_buf=DataIO::string_to_lowercase(text_buf);
                break;
            }
            else if(cvkey%256 == '\e')
            {
                return string("\e");
            }
            else if(cvkey%256 == '\b')
            {
                if(text_buf.size() != 0)
                    text_buf.erase(text_buf.end() - 1);
            }
            else if( ( (cvkey%256)<='z' && (cvkey%256)>= 'a') || ((cvkey%256)<= 'Z' && (cvkey%256)>= 'A') || ((cvkey%256)<= '9' && (cvkey%256)>='0') || (cvkey%256)==' ' || (cvkey%256)==',')
            {
                //as input is accepted only A-Z, a-z, 0-9, "," or " "
                text_buf = text_buf + static_cast<char>(cvkey%256);
            }

        }
        //putFormatedWindowText(displayFrame, string("Save file: [subject,name]")+ string("\n") + text_buf);
        putFormatedWindowText(displayFrame,text);
        imshow(MAIN_WINDOW_NAME,displayFrame);
        displayFrame = cam->getFrame(CAM_ROT_ANGLE);

    }
    return text_buf;
}

const string UserInterface::spwin(const Mat frame, SpeechHandler* sp)
{
    // This will not be a part of final program!.....................
    int cvkey;
    Mat displayFrame = frame.clone();
    string text_buf {""};
    string speech_text {""};

    putFormatedWindowText(displayFrame, string("Save file: [subject,name]"));
    imshow(MAIN_WINDOW_NAME,displayFrame);
    speak("Please say your name");

    while(1)
    {
        cvkey = cv::waitKey(1);
        //speech_text = sp->getText();

        if(cvkey > 0)
        {
            if(cvkey%256 == '\n')
            {
                text_buf=DataIO::string_to_lowercase(text_buf);
                break;
            }
            else if(cvkey%256 == '\e')
            {
                return string("\e");
            }
            else if(cvkey%256 == '\b')
            {
                if(text_buf.size() != 0)
                    text_buf.erase(text_buf.end() - 1);
            }
            else if( ( (cvkey%256)<='z' && (cvkey%256)>= 'a') || ((cvkey%256)<= 'Z' && (cvkey%256)>= 'A') || ((cvkey%256)<= '9' && (cvkey%256)>='0') || (cvkey%256)==' ' || (cvkey%256)==',')
            {
                //as input is accepted only A-Z, a-z, 0-9, "," or " "
                text_buf = text_buf + static_cast<char>(cvkey%256);
            }

            putFormatedWindowText(displayFrame, string("Save file: [subject,name]") + string("\n") + text_buf);
            imshow(MAIN_WINDOW_NAME,displayFrame);
            displayFrame = frame.clone();

        }
//        else if( speech_text != string(""))
//        {
//            if(speech_text[speech_text.size()-1] == '$')
//            {
//                text_buf = speech_text;
//                text_buf.erase(text_buf.end() -1 );
//                break;
//            }
//            else if(speech_text[speech_text.size()-1] == '&')
//            {
//                return string("\e");
//            }
//            else
//            {
//                text_buf = speech_text;
//            }
//
//            putFormatedWindowText(displayFrame, string("Save file: [subject,name]") + string("\n") + text_buf);
//            imshow(MAIN_WINDOW_NAME,displayFrame);
//            displayFrame = frame.clone();
//
//        }

    }
    return text_buf;

}

const string UserInterface::spwin(CameraSys* cam, SpeechHandler* sp)
{
    // This will not be a part of final program!.....................
    int cvkey;
    Mat displayFrame = cam->getFrame(CAM_ROT_ANGLE);
    string text_buf {""};
    string speech_text {""};

    speak("Please say your name");

    while(1)
    {
        cvkey = cv::waitKey(1);
        speech_text = sp->getText();

        if(cvkey > 0)
        {
            if(cvkey%256 == '\n')
            {
                text_buf=DataIO::string_to_lowercase(text_buf);
                break;
            }
            else if(cvkey%256 == '\e')
            {
                return string("\e");
            }
            else if(cvkey%256 == '\b')
            {
                if(text_buf.size() != 0)
                    text_buf.erase(text_buf.end() - 1);
            }
            else if( ( (cvkey%256)<='z' && (cvkey%256)>= 'a') || ((cvkey%256)<= 'Z' && (cvkey%256)>= 'A') || ((cvkey%256)<= '9' && (cvkey%256)>='0') || (cvkey%256)==' ' || (cvkey%256)==',')
            {
                //as input is accepted only A-Z, a-z, 0-9, "," or " "
                text_buf = text_buf + static_cast<char>(cvkey%256);
            }

        }
        else if( speech_text != string(""))
        {
            if(speech_text[speech_text.size()-1] == '$')
            {
                text_buf = speech_text;
                text_buf.erase(text_buf.end() -1 );
                break;
            }
            else if(speech_text[speech_text.size()-1] == '&')
            {
                return string("\e");
            }
            else
            {
                text_buf =  speech_text;
            }
        }

        putFormatedWindowText(displayFrame, string("Save file: [subject,name]")+ string("\n") + text_buf);
        imshow(MAIN_WINDOW_NAME,displayFrame);
        displayFrame = cam->getFrame(CAM_ROT_ANGLE);

    }
    return text_buf;
}

void UserInterface::putFormatedWindowText(cv::Mat frame,const string& text)
{
    int i = 0;
    static const cv::Point pos0(15,30);
   // cv::Point pos(0,0);

    Tokenizer tokens(text,"\n");
    while(tokens.NextToken())
    {
        putText(frame,tokens.GetToken(),pos0 + Point(0,+30*i),3, 0.8,Scalar(0,200,204), 1,4);
        i++;
    }
}
