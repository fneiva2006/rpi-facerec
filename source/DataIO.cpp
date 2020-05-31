/*
    File Name: DataIO.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Disk Data IO operations module" used on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "DataIO.hpp"
#include <ctype.h>
#include <string>

using namespace std;
using namespace cv;

DataIO::DataIO()
{
    struct stat st;

    /* Checking and creation of working folders if they do not exist */

    /* Cascades */
    if(stat("haarcascades",&st) != 0 )
        mkdir("haarcascades", S_IRWXU);
    if(stat("lbpcascades",&st) != 0 )
        mkdir("lbpcascades", S_IRWXU);

    /* Image Database */
    if(stat("imgdb",&st) != 0 )
        mkdir("imgdb", S_IRWXU);
    if(stat(WORKING_DIR.c_str(),&st) != 0)
        mkdir(WORKING_DIR.c_str(),S_IRWXU);
}

void DataIO::folder_grab(string dir_p,vector<string>* address_matrix){

    //method for grabbing all files with certain extensions from a directory
    string pgm = ".pgm"; //search files with extensions pgm and jpg
    string jpg = ".jpg";

    struct dirent *entry;
    DIR *dir;
    dir= opendir(dir_p.c_str() );
    while ((entry = readdir (dir)) != NULL) {
        string name =(entry->d_name);
        if ((name!="..") && (name!=".")) {  //Selects all directories excluding .. and .
            string subdir_p = dir_p;
            if (dir_p[dir_p.size()-1]=='/' || dir_p[dir_p.size()-1]=='\\'){ // stores the address of the current file/folder
                subdir_p = dir_p + name;
            }
            else {
                subdir_p = dir_p + "/" + name; // adds a '/' if there isn't one
            }

            if (entry->d_type == DT_DIR){
                folder_grab(subdir_p,address_matrix); // finds all files in the folders within the folder
            }
            else if (entry->d_type == DT_REG){ // SELECTES ALL FILES
                if ((name.find(pgm, (name.length() - pgm.length())) != string::npos) ||
                    (name.find(jpg, (name.length() - jpg.length())) != string::npos)){ // Selects all files with given extensions
                    string filepath = subdir_p;
                    address_matrix->push_back(filepath); // Appends the file address to the vector of strings
                }
            }
        }
    }
    closedir(dir); // closes the opened directory
    return;
}

void DataIO::loadImages(const string folder )
{
    m_images.clear();
    m_addresses.clear();
    m_numeric_labels.clear();
    Mat img_aux;

    folder_grab(folder,& m_addresses);

    /*  Populates the vector of image matrices.
        Each image in position i has an address in the address_matrix in position i   */
    for (size_t i=0;i<m_addresses.size();i++)
    {
        m_numeric_labels.push_back(i);
        img_aux = imread(m_addresses[i], CV_LOAD_IMAGE_GRAYSCALE);
        resize(img_aux,img_aux, DEFAULT_SIZE);
        m_images.push_back(img_aux);
    }
    return;
}

void DataIO::createFolder(string full_address)
{   // creates folder if such doesn't exist already
    // assumes father folder already exists, to be improved.###
    struct stat st;
    string command="mkdir "+full_address;
    if(stat(full_address.c_str(),&st) == 0) return; //returns if it exists
    else    system(command.c_str());                // executes command if not
    return;
}

void DataIO::saveImage(const string & label,const Mat image){

    /* Finds the comma in the istring input*/
    size_t found = label.find_last_of(",");

    /* If no comma is found, saves with an automatically generated name. */
    if (found==string::npos){
        string full_address;
        if (label[label.size()-1]!='/' && label[label.size()-1]!='\\'){
            full_address=label+'/';
        }
        else full_address=label;

        full_address = static_cast<string>(WORKING_DIR)+full_address.c_str();
        createFolder(full_address);
        vector<string> addresses;
        addresses.clear();
        folder_grab(full_address,&addresses);
        ostringstream convert;
        convert<<addresses.size();
		/* automatic naming the image file to be saved */
        string auto_name= label + "_AUTO_"+ convert.str()+".jpg"; 

        imwrite(full_address + auto_name , image );
        return;
    }

    /*  Splits input string into subject folder and image name
        Deletes any whitespaces found. */
    string address = static_cast<string>(WORKING_DIR) + label.substr(0,found).c_str();
    string name=label.substr(found+1,label.size()-1).c_str();
    string::iterator end_pos = remove(address.begin(), address.end(), ' ');
    address.erase(end_pos, address.end());
    end_pos = remove(name.begin(), name.end(), ' ');
    name.erase(end_pos, name.end());

    /*  Adds '/' to folder name if it's not written.
        Creates fodler if such doesn't exist.
        Saves the image as .jpg regardless of input. */
    if (address[address.size()-1]!='/' && address[address.size()-1]!='\\')
    {
        address=address+"/";
    }
    createFolder(address.c_str());
    found = name.find(".");
    if (found==string::npos){
        name=name+".jpg";
    }
    found = name.find(".");
    if (name.substr(found,name.size()-1)!=".jpg"){
        name=name.substr(0,found+1)+"jpg";
    }
    string file_address=address+name;

    imwrite( file_address, image );
    return;
}

string DataIO::string_to_lowercase(string input_string)
{
    if (input_string=="" || input_string.empty())
    {
        cerr<<"Error in function string_to_lowercase: Empty input"<<endl;
        return "";
        // Returns if empty input
    }

    else // If input is not empty, it is processed and retrurned
    {
        for (int i = 0; i< ((int)input_string.size()); i++ )
        {
                // Makes each character lowercase
                input_string[i]=(char)tolower(input_string[i]);
        }
    }
    return input_string;
}

void DataIO::output_txt(string text, string file_address)
{
    // Uses OUT_TXT by default.
    // OUT_TXT is defined in the definitions header
    ofstream myfile;
    // To be added : Check if address is valid ############ ####################################
    myfile.open(file_address);
    myfile<<text;
    myfile.close();
    // writes text into txt file and closes the file
    return;
}

string DataIO::input_txt(string file_address)
{
    // Returns "" if no such file, "No new input" if input is not new
    // Returns string with text in all other cases.

    // Uses IN_TXT by default.
    // IN_TXT is defined in the definitions header
    ifstream ifile;
    string x,sum="";
    // To be added : Check if address is valid ################################################
    ifile.open(file_address);
    if (!ifile) {
        // Checks if such file exists
        cerr << "Error in function input_txt: Unable to open file "<<file_address<<endl;;
        return "";
        // Returns empty string
    }

    while (ifile>>x){
        sum=sum+x+" ";
        // Adds a white space after the end of each word
    }
    sum = sum.substr(0,sum.size()-1);
    // Crops the last space
    ifile.close();
    // Sum now contains the text from the txt file.
    return sum;
    // Retruns string
}

void DataIO::speech_request( int number,string file_address){
    if (number > 4 || number < 0){
        cerr<< "Error in function speech_request: number out of range."<<endl;
        return;
    }
    ostringstream convert;
    convert<<number;
    output_txt(convert.str(),file_address);
    // 0 - no request, 1 - y/n OR q, 2 - name , 3 - command key, 4 - convo mode

    return;
}
string DataIO::name_from_address(string address){

    // Returns name of subject, e.g. from A/B/C/Dennis/3.jpg returns Dennis
    size_t found= address.find("/");
    size_t last_found= address.find_last_of("/");
    if (found==string::npos){
        cerr<<"Error in function name_from_address: Invalid address. Please input a valid addess"<<endl;
        return 0;
    }
    else if (found == last_found){return address.substr(0,found);}
    else {
        address=address.substr(found+1,address.length()-1);
        return name_from_address(address);
    }
}
