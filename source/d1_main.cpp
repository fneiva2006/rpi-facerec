/*
    File Name: d1_main.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Main Routine" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "ControlSystem.hpp"

using namespace std;
using namespace cv;

/* Initialise FrameRate calculator module */
FrameRate fps_counter;

int main(int argc, char **argv)
{
    /* ================== System Initialisation =============================== */

    SystemStructure System;
    /* Initialise System and all its modules */
    ControlSystem Control(&System);

    /* Start framerate counter & display */
    fps_counter.start(1);

   // system("./Reset_paths.sh -q");
   // system("./Playback_to_Lineout.sh -q");

    /* ====================================================================== */

    return Control.run();

    /* ======================== End of control loop ====================== */


}

