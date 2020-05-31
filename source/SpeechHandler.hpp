/*
    File Name: SpeechHandler.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Speech Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#ifndef SPEECHHANDLER_HPP
#define SPEECHHANDLER_HPP

#include "common_headers.hpp"
#include "definitions.hpp"

#include "DataIO.hpp"

using namespace std;
using namespace cv;

class SpeechHandler
{
    private:
        bool m_sendRequest;
        string m_txt_buffer;

    public:
        SpeechHandler();

        const string getText();

        const int getCommand();

        const int getYesNo();

};


#endif
