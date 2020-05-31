#include "SystemStructure.hpp"

SystemStructure::SystemStructure()
{
    /* Start camera module */
    cam = new CameraSys();
    if( cam->start(MAIN_WINDOW_WIDTH,MAIN_WINDOW_HEIGHT,30))
        exit(1);

     /* Start Detection module */
    det = new DetectionSys();
    if( det->load_cascades() == 0 )
        cout << "Cascades loaded !" << endl;
    else
    {
        cout << "Program terminating...\n"; exit(2);
    }

    /* Initialise DataIO module */
    data = new DataIO();
    /* Load Images */
    data->loadImages();

     /* Start Recognition module */
    rec = new RecognitionSys();
    /* Create LBP recognition model with the loaded images */
    if(!data->m_images.empty())
        rec->trainLBPH(data->m_images,data->m_numeric_labels);

    /* Initialise UserInterfcae */
    interface = new UserInterface();

}

SystemStructure::~SystemStructure()
{
    delete det;
    delete rec;
    delete data;
    delete interface;
}
