/*
    File Name: ControlSystem.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Controller" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/


#ifndef CONTROLSYSTEM_HPP
#define CONTROLSYSTEM_HPP

#include "common_headers.hpp"
#include "definitions.hpp"

#include "FrameRate.hpp"

//#include "DetectionSys.hpp"
//#include "CameraSys.hpp"
//#include "RecognitionSys.hpp"
//#include "DataIO.hpp"
//#include "UserInterface.hpp"
#include "SystemStructure.hpp"

/*
class SystemStructure
{
    public:
        DetectionSys* det;
        RecognitionSys* rec;
        CameraSys* cam;
        DataIO* data;
        UserInterface* interface;
        SpeechHandler* speech;

        SystemStructure();
        ~SystemStructure();

};
*/
class ControlSystem
{
    private:
        SystemStructure* m_System;

    public:
        ControlSystem(SystemStructure* System);

        int saveProcedure(const vector<Mat>& CAface, Mat frame, const string& name);

        bool verify_password();

        void create_password();

        int run();

        void recognitionProcedure(const vector<Mat>& CAface);

        void unknownFaceProcedure(const vector<Mat>& CAface);

        void knownFaceProcedure(const vector<Mat>& CAface, string guess);

        /* Text input and output functions */

        string inputProcedure(int request, string output_file=OUT_TXT,string input_file=IN_TXT);


};

#endif
