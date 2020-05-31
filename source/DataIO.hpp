/*
    File Name: DataIO.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Disk Data IO operations module" used on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/


#ifndef DATAIO_HPP
#define DATAIO_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <ctype.h>
#include <fstream>

#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include "definitions.hpp"

/*
#define WORKING_DIR "imgdb/subjects2/"

#define WIDTH 92    // Width of the face image
#define HEIGHT 112  // Height of the face image
#define DEFAULT_SIZE cv::Size(WIDTH,HEIGHT)
*/

using namespace std;
using namespace cv;

class DataIO
{
    private:
        void folder_grab(string dir_p,vector<string>* address_matrix);

        void createFolder(string full_address);

    public:
        DataIO();

        static string name_from_address(string address);

        void loadImages(const string folder = WORKING_DIR);

        void saveImage(const string & label,const Mat image);

        static string string_to_lowercase(string input);

        static string input_txt(string file_address=IN_TXT);

        static void output_txt(string text, string file_address=OUT_TXT);

        static void speech_request(int number=0,string file_address=OUT_TXT);

        vector<Mat> m_images;
        vector<int> m_numeric_labels;
        vector<string> m_addresses;
};

#endif
