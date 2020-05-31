/*
    File Name: ControlSystem.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Controller" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "ControlSystem.hpp"
#include <string>

using namespace std;
using namespace cv;

extern FrameRate fps_counter;

//SystemStructure::SystemStructure()
//{
//    /* Start camera module */
//    cam = new CameraSys();
//    if( cam->start(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT,30))
//        exit(1);
//
//     /* Start Detection module */
//    det = new DetectionSys();
//    if( det->load_cascades() == 0 )
//        cout << "Cascades loaded !" << endl;
//    else
//    {
//        cout << "Program terminating...\n"; exit(2);
//    }
//
//    /* Initialise DataIO module */
//    data = new DataIO();
//    /* Load Images */
//    data->loadImages();
//
//     /* Start Recognition module */
//    rec = new RecognitionSys();
//    /* Create LBP recognition model with the loaded images */
//    if(!data->m_images.empty())
//        rec->trainLBPH(data->m_images,data->m_numeric_labels);
//
//    /* Initialise UserInterfcae */
//    interface = new UserInterface();
//
//    /* Initialise SpeechHandler */
//    speech = new SpeechHandler();
//
//}
//
//SystemStructure::~SystemStructure()
//{
//    delete det;
//    delete rec;
//    delete data;
//    delete interface;
//    delete speech;
//}

ControlSystem::ControlSystem(SystemStructure* System)
{
    m_System = System;
    cout << "Control System Initialised !" << endl;
}

int ControlSystem::run()
{
     /* Variables used in the control routine */
    int cvkey;
    vector<Mat> CAface;
    Mat frame;
    int sp_cmd;
  //  string name,temp="";

    /* ================== Main Control Routine of the program ============== */
    for (;;)
    {
		/* Get a new frame from camera */
        frame = m_System->cam->getFrame(CAM_ROT_ANGLE);

		/* Processes the captured frame */
        m_System->det->processFrame(frame);

        /* Get the face extracted from the camera */
        CAface = m_System->det->getCAimages();
		/* If there is a extracted face available, display it on the detected face window */
        if(!CAface.empty())
            m_System->interface->displayImage(CAFACE_WINDOW_NAME,CAface[0]);

        fps_counter.count_frame();
        /* Update the framerate calculator */

        m_System->interface->displayImage(MAIN_WINDOW_NAME,frame);

        /* Simply captures any key typed  */
        cvkey = m_System->interface->getWindowKey();

        /* Requests speech input of type=3, returns string*/
        //sp_cmd = m_System->speech->getCommand();

        /* Captured window key treatment */
        if ( cvkey > 0)
        {
            if(cvkey%256 == 'c') /* Focus on next detected face */
            {
                m_System->det->changeSelection();
            }
            else if(cvkey%256 == 's') /* Save the cropped/aligned image to database */
            {
                fps_counter.stop();
                saveProcedure(CAface,frame, string(""));
                fps_counter.start(1);
            }
            else if(cvkey%256 == 'r') /* Recognise the face (try to find the closest match) */
            {
                fps_counter.stop();
                recognitionProcedure(CAface);
                fps_counter.start(1);
                m_System->interface->displayImage(CLM_WINDOW_NAME, BLACK_FRAME);
            }
            else if(cvkey%256 == '\e') /* if esc is pressed the program ends */
            {
                fps_counter.stop(); // Stops the framerate calculator
                UserInterface::speak("Exiting Program");
               // DataIO::output_txt(string("0"), OUT_TXT);
                return 0;
            }
            else if(cvkey%256 == 'l') /* Reloads Images */
            {
                m_System->data->loadImages();
                m_System->rec->trainLBPH(m_System->data->m_images, m_System->data->m_numeric_labels);
            }

        }
/* Speech detection signal treatment */
//        else if( sp_cmd > 0)
//        {
//            if( sp_cmd%256 == 'c') /* Focus on next detected face */
//            {
//                m_System->det->changeSelection();
//            }
//            else if( sp_cmd%256  == 's')
//            {
//                saveProcedure(CAface,frame, string(""));
//            }
//            else if(sp_cmd%256  == 'r')
//            {
//                recognitionProcedure(CAface);
//            }
//            else if(sp_cmd%256  == '\e' || sp_cmd == '&')
//            {
//                fps_counter.stop(); // Stops the framerate calculator
//                DataIO::output_txt(string("0"), OUT_TXT);
//                return 0;
//            }
//            else if(sp_cmd%256  == 'l')
//            {
//                m_System->data->loadImages();
//                m_System->rec->trainLBPH(m_System->data->m_images, m_System->data->m_numeric_labels);
//            }
//
//        }
    }
}

int ControlSystem::saveProcedure(const vector<Mat>& CAface, Mat frame, const string& name)
{
    string saveFileName = name;

    cout << endl<<"SAVEFILE NAME " << saveFileName << endl << endl;

    if(!CAface.empty()) /* Check if any face has been properly detected and cropped */
    {

        if(!saveFileName.empty())
        {
            cout << endl<<"SAVEFILE NAME 2:" << saveFileName << endl << endl;
            m_System->data->saveImage(saveFileName,CAface[0]);/* save the image*/

            m_System->data->loadImages();/* reload the images */
			/* Retrain recognition module */
            m_System->rec->trainLBPH(m_System->data->m_images,m_System->data->m_numeric_labels);

            UserInterface::speak("Image saved !");
            m_System->interface->win(m_System->cam,"Image saved!\nPress Enter to continue...");

            return 1;
        }
		/* If the file name was not previously given, start name capture process */
        while(saveFileName.empty())
        {
			/* Get name from what user types on main window screen */
            if (name==string ("")) saveFileName = m_System->interface->win(m_System->cam );

			/* Get name from speech recognition */
            //if (name==string ("")) saveFileName = m_System->interface->spwin(m_System->cam, m_System->speech);

			/* If esc is pressed the saving process is cancelled. Program returns to the main loop (detection) */
            if(saveFileName == string("\e"))
            {
                UserInterface::speak("Image not saved !");
                m_System->interface->win(m_System->cam,"Image not saved!\nPress Enter to continue...");
                return 0;
            }

            if(!saveFileName.empty())
            {
                cout << endl<<"SAVEFILE NAME 2:" << saveFileName << endl << endl;
                m_System->data->saveImage(saveFileName,CAface[0]);/* save the image*/

                m_System->data->loadImages();/* reload the images */
				/* Retrain recognition module */
                m_System->rec->trainLBPH(m_System->data->m_images,m_System->data->m_numeric_labels);

                UserInterface::speak("Image saved !");
                m_System->interface->win(m_System->cam,"Image saved!\nPress Enter to continue...");
                return 1;
            }
            else
            {
                cerr << "Error in saveProcedure: Name input is empty.\nPlease enter a name or esc to cancel" << endl;
                UserInterface::speak("Name input is empty. Please enter a name or esc to cancel");
                m_System->interface->win(m_System->cam,"Name input is empty.\nPlease enter a name or esc to cancel.\nPress Enter to continue...");

            }
        }
    }
    else
    {
        cerr << "Error in saveProcedure: No faces cropped/aligned yet!" << endl;
        m_System->interface->win(m_System->cam,"No faces cropped/aligned yet!\nPress Enter to continue...");
        UserInterface::speak("No faces cropped nor aligned yet!");
    }

    return 0;
}

void ControlSystem::recognitionProcedure(const vector<Mat>& CAface)
{
    static string guess;
    static bool known_face;
    static Mat frame;

    if(!CAface.empty()) /* Check if any face has been properly detected and cropped */
    {
        if( m_System->rec->trained())
        {
            int predictedIndex;
            double confidence = m_System->rec->findClosestMatch(CAface[0],predictedIndex);
            cout << endl << confidence << " confidence, "  << predictedIndex << " PREDICTED INDEX" << endl;
            guess = DataIO::name_from_address(m_System->data->m_addresses[predictedIndex]);

            known_face = (confidence < THRESHOLD_REC ); /* Check confidence Threshold */
            if(known_face)
            {
                m_System->interface->displayImage(CLM_WINDOW_NAME,m_System->data->m_images[predictedIndex]);
                knownFaceProcedure(CAface, guess);
                return;
            }
            else
            {
                unknownFaceProcedure(CAface);
                return;
            }

        }
        else
        {
            cerr << "Error in recognitionProcedure: Training Set is empty. Please save any image to database." << endl;
            UserInterface::speak("Training Set is empty. Please save any image to database.");
            m_System->interface->win(m_System->cam,"Training Set is empty.\nPlease save any image to database.\nPress Enter to continue...");
        }

    }
    else
    {
        cerr << "Error in recognitionProcedure: No faces cropped nor aligned yet!" << endl;
        UserInterface::speak("No faces cropped nor aligned yet!");
        m_System->interface->win(m_System->cam,"No faces cropped nor aligned yet!\nPress Enter to continue...");
    }

    m_System->interface->displayImage(CLM_WINDOW_NAME, BLACK_FRAME);
    return;
}

void ControlSystem::unknownFaceProcedure(const vector<Mat>& CAface)
{
    UserInterface::speak("Unrecognized face. Would you like to register new person?");

    int key, sp_in = -1;
    Mat frame;

    while(1)
    {
        key = m_System->interface->getWindowKey()%256;
        //sp_in = m_System->speech->getYesNo();

        frame = m_System->cam->getFrame(CAM_ROT_ANGLE);

        if( key == '\e' || key == 'n' || sp_in == '&' || sp_in == 'n') return;

        if(key == 'y' || sp_in == 'y')
        {
            saveProcedure(CAface,frame,string("") );
            return;
        }

        UserInterface::putFormatedWindowText(frame,"Unrecognized face\nWould you like to register new person?");
        m_System->interface->displayImage(MAIN_WINDOW_NAME,frame);
    }
}

void ControlSystem::knownFaceProcedure(const vector<Mat>& CAface, string guess)
{
    UserInterface::speak("The recognised face belongs to," + guess);
    UserInterface::speak("Was my guess correct?");

    Mat frame;
    static int key;
    int sp_in = -1;

    // First loop, Expected input Y/N/Q
    while(1)
    {
        //sp_in = m_System->speech->getYesNo();
        key =  m_System->interface->getWindowKey()%256;

        if  (key == 'n' || sp_in == 'n')
        {
            unknownFaceProcedure(CAface);
            return;
        }
        /* Proceed to unknown face if guess is wrong */
        if  (key == '\e'|| sp_in == '&') return;
        /* Stop procedure if quit input */
        if(key == 'y' || sp_in == 'y') break;
        /* Continue to saving if correct guess */

        frame = m_System->cam->getFrame(CAM_ROT_ANGLE);

        UserInterface::putFormatedWindowText(frame,"The recognised face belongs to " + guess + "\nWas my guess correct?");
        m_System->interface->displayImage(MAIN_WINDOW_NAME,frame);

    }

    UserInterface::speak("Would you like to save the new face image ?");
    // Second loop, expected input Y/N/Q
    while(1)
    {
        //sp_in = m_System->speech->getYesNo();
        key =  m_System->interface->getWindowKey()%256;

        /* Return if input is N or Q */
        if(key =='\e'||key=='n'||sp_in == '&'||sp_in == 'n')
        {
            return;
        }

        frame = m_System->cam->getFrame(CAM_ROT_ANGLE);

        /* Save if input is Y */
        if(key == 'y' || sp_in == 'y')
        {
            saveProcedure(CAface,frame, guess) ;
            /* Requests conversation mode */
            //DataIO::output_txt("3");
            return;
        }

        UserInterface::putFormatedWindowText(frame,"The recognised face belongs to " + guess + ".\nWould you like to save the image ? [y/n]");

        m_System->interface->displayImage(MAIN_WINDOW_NAME,frame);
    }
}
//
//string ControlSystem::inputProcedure(int request, string output_file,string input_file){
//
//    static bool send_request = true;
//    string received;
//    /*  requests speech input of type request
//        0 - no request, 1 - y/n or q, 2 - name
//        3 - command key, 4 - convo mode */
//    if(send_request)
//    {
//        cout<< endl<<send_request<<" "<<request<<endl;
//        DataIO::speech_request(request, output_file);
//    }
//
//
//    /*  Sends request only once */
//    send_request = false;
//
//    /*  Input string is not needed for mode 4,
//        Prefferably should be called via speech_request() */
//    if (request==4) return "";
//
//    received=DataIO::input_txt(input_file);
//
//    /* Debugging - check what it has received */
//    if(received != string("No new input"))
//        cout << endl << "Recieved a \t" << received<< endl << endl;
//
//    /* Returns empty string if error or no new input */
//    if (received==string(""))
//    {
//        cerr << "Error in function input_txt: Unable to open file "<<input_file<<endl;
//        return "";
//    }
//    else if (received==string("No new input"))
//    {
//        return "";
//    }
//
//    /*  Clears text from txt file and writes default text
//        unless dynamically entering name */
//    /*  If it is ready for a new request changes send_request */
//    if (request!=2)
//    {
//        cout<<"received1"<<endl;
//        send_request = true;
//        DataIO::output_txt("No new input",input_file);
//    }
//    /*  If entering a name and last char is $, clearing input */
//    else if (received[received.size()-1]=='$')
//    {
//        cout<<"received2"<<endl;
//        send_request = true;
//        DataIO::output_txt("No new input",input_file);
//    }
//    else if (received[received.size()-1]=='%')
//    {
//        cout<<"received3"<<endl;
//        send_request = true;
//        DataIO::output_txt("No new input",input_file);
//        return "%";
//    }
//
//    /* Converts to lowercase */
//    received=DataIO::string_to_lowercase(received);
//
//    /* Returns input*/
//    return received;
//}

