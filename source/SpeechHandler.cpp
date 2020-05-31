/*
    File Name: SpeechHandler.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Speech Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "SpeechHandler.hpp"

using namespace cv;
using namespace std;

SpeechHandler::SpeechHandler()
{
    m_sendRequest = true;
}

const string SpeechHandler::getText()
{

    string received;
    /*  requests speech input of type request
        0 - no request, 1 - y/n or q, 2 - name
        3 - command key, 4 - convo mode */
    if(m_sendRequest)
    {
        cout<< endl<<m_sendRequest<<" "<<TEXT<<endl;
        DataIO::speech_request(TEXT, OUT_TXT);
        /*  Sends request only once */
        m_sendRequest = false;
    }

    received = DataIO::input_txt(IN_TXT);

    /* Debugging - check what it has received */
    if(received != string("no new input"))
        cout << endl << "Recieved a \t" << received<< endl << endl;

    /* Returns empty string if error or no new input */
    if (received==string(""))
    {
        cerr << "Error in function input_txt: Unable to open file "<<IN_TXT<<endl;
        return "";
    }
    else if (received==string("no new input"))
    {
        return "";
    }

    /*  If entering a name and last char is $, clearing input */
    if (received[received.size()-1]=='$' || received[received.size()-1]== '&' )
    {
        m_sendRequest = true;
        DataIO::output_txt("no new input",IN_TXT);
    }

    /* Converts to lowercase */
    received=DataIO::string_to_lowercase(received);

    /* Returns input*/
    return received;

}

const int SpeechHandler::getCommand()
{
    string received;
    /*  requests speech input of type request
        0 - no request, 1 - y/n or q, 2 - name
        3 - command key, 4 - convo mode */
    if(m_sendRequest)
    {
        cout<< endl<<m_sendRequest<<" "<<COMMAND<<endl;
        DataIO::speech_request(COMMAND, OUT_TXT);
        /*  Sends request only once */
        m_sendRequest = false;
    }

    received = DataIO::string_to_lowercase(DataIO::input_txt(IN_TXT));

    /* Debugging - check what it has received */
    if(received != string("no new input"))
        cout << endl << "Recieved a \t" << received<< endl << endl;

    /* Returns empty string if error or no new input */
    if (received == string(""))
    {
        cerr << "Error in function input_txt: Unable to open file "<<IN_TXT<<endl;
        return -1;
    }
    else if (received == string("no new input"))
    {
        return -1;
    }

    m_sendRequest = true;
    DataIO::output_txt("no new input",IN_TXT);

    return static_cast<int> (received[0]) ;
}

const int SpeechHandler::getYesNo()
{
    string received;
    /*  requests speech input of type request
        0 - no request, 1 - y/n or q, 2 - name
        3 - command key, 4 - convo mode */
    if(m_sendRequest)
    {
        cout<< endl<<m_sendRequest<<" "<<YES_NO<<endl;
        DataIO::speech_request(YES_NO, OUT_TXT);
        /*  Sends request only once */
        m_sendRequest = false;
    }

    received = DataIO::string_to_lowercase(DataIO::input_txt(IN_TXT));

    /* Debugging - check what it has received */
    if(received != string("no new input"))
        cout << endl << "Recieved a \t" << received<< endl << endl;

    /* Returns empty string if error or no new input */
    if (received == string(""))
    {
        cerr << "Error in function input_txt: Unable to open file "<<IN_TXT<<endl;
        return -1;
    }
    else if (received == string("no new input"))
    {
        return -1;
    }

    m_sendRequest = true;
    DataIO::output_txt("no new input",IN_TXT);

    return static_cast<int> (received[0]) ;

}
