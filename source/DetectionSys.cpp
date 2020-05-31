/*
    File Name: DetectionSys.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "Face Detection Module" on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "DetectionSys.hpp"

using namespace cv;
using namespace std;
using namespace GeometricAux;

DetectionSys::DetectionSys()
{
    m_selection = 0;

    cout << "DetectionSys initialised. Loading default cascades now...\n";

    if( load_cascades() == 0 )
    {
         cout << "Default cascades succesfully loaded!" << endl;
    }
    else
    {
        cout << "Default cascades could not be loaded!\n";
        cout << "Default location: ./lbpcascades/ (face) and ./haarcascade/ (eyes) \n" ;
    }
}

int DetectionSys::load_cascades(const string& face_cascade_name , const string& eyes_cascade_name )
{
    if( !m_face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading\n"; return -1; };
    if( !m_eyes_cascade.load( eyes_cascade_name ) ){ cout << "--(!)Error loading\n"; return -1; };
    return 0;
}

vector<Mat> DetectionSys::getCAimages()
{
    return m_img_buffer;
}


void DetectionSys::changeSelection()
{
	/* focus on the next detected face */
    m_selection = (m_selection+1)%(1+m_num_faces);
}

void DetectionSys::processFrame(Mat original_frame)
{

    Mat gray_frame; // full frame to be processed (gray)
    vector<Rect> faces; // vector to store the detected face regions on the gray_frame
   // vector<Mat> croppedGrayFaces; // vector to store the processed faces obtained from the gray_frame
    Mat cgf_aux; // auxiliary frame buffer

    cvtColor( original_frame, gray_frame, CV_BGR2GRAY ); // get the gray frame from the original one
    equalizeHist( gray_frame, gray_frame );

    /* Detect faces on the gray_frame using cascade method */
    m_face_cascade.detectMultiScale( gray_frame, faces, 1.11, 4, 0, Size(45, 45));

	/* Get the number of pre-detected faces */
    m_num_faces = faces.size();
	/* Select which one of the pre-detected faces is going to be processed */
    m_selection = m_selection%(m_num_faces+1);

	/* Draw the rectangles on the faces that were detected but the one focused in */
    for( size_t i = 0; i < m_num_faces; i++ )
    if(i != m_selection)rectangle(original_frame,faces[i],Scalar(200,200,0),1,LINE_4,0);

    /* Process every face detected. Comment for loop to process only first face detected */
//  for( size_t i = 0; i < faces.size(); i++ )
//  {
        if(m_num_faces != 0)
        {
			/* Draw a highlighted rectangle on the detected face that is being processed */
            rectangle(original_frame,faces[m_selection],Scalar(0,255,1),4,LINE_4,0);

            /*  Get the detected face aligned and cropped from the gray_frame
                If the face could not be aligned/cropped an empty image is returned by
                the function getALignedFace */
            cgf_aux = getAlignedFace(gray_frame, faces[m_selection]);
        }

        /* Check if the face processed could be aligned and cropped */
        if(!cgf_aux.empty())
        {
            if(! m_img_buffer.empty())
            {
                m_img_buffer.clear();
            }
            /* If the face was successfully aligned and cropped it is added to
                the vector of processed faces */
             m_img_buffer.push_back(cgf_aux);

          //  imshow("CROPPED ", cgf_aux); // display cropped/aligned face

        }
  //}

}

Mat DetectionSys::getAlignedFace(Mat gray_frame, Rect2f face)
{
    /* Initialise rectangle which corresponds to the gray (full) frame */
    Rect frame_rect(0,0,gray_frame.cols,gray_frame.rows);

    /* Points needed to calculate rotation angle and cropping region */
    Point2f left_eye_centre, right_eye_centre, rotation_point, eyes_median_point;

    /* Auxiliary matrices to store temporary processed face */
    Mat cropFace, faceROI, rotated_frame;

    Mat R; // Rotation Matrix used to align face

    /* Auxiliary vector to store the regions of detected eyes */
    vector<Rect> eyes;

    double distance_eyes = 0, rot_angle = 0;

    faceROI = gray_frame( face ); // get the image of the area defined by the face (rectangle)

    /* Detects the eyes regions on the face using cascade method*/
    m_eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 3, 0 |CV_HAAR_SCALE_IMAGE, Size(10, 10) );

    /* Check if at least two eyes were detected on the face. If not, it is impossible to align and crop
        the image and therefore this function ends and returns an empty image */
    if(eyes.size() < 2)
    {
        return cropFace;
    }

    /* Get the points of the centre of right and left eye on the face region */
    lr_points( rectCentre(eyes[0]),rectCentre(eyes[1]),left_eye_centre,right_eye_centre);

    /* Find the middle point between the centres of the two eyes */
    eyes_median_point = median(left_eye_centre,right_eye_centre);

    /* Find the geometric distance between the centre of the two eyes */
    distance_eyes = point_distance(left_eye_centre,right_eye_centre);

    /* Find the angle between an horizontal line and the line segment that links
        the centre of the left eye to the centre of the right eye. This angle is
        the rotation angle required to align the image */
    rot_angle = lr_rot_angle(eyes_median_point,right_eye_centre);

    /* Find the rotation point on the full gray frame. The rotation point is
        the point on the gray frame that corresponds to the mid point beteen
        the centres of the two eyes */
    rotation_point = eyes_median_point + rect_basepoint(face);

    /* Generate a 2D rotation matrix with the rotation angle found */
    R = getRotationMatrix2D(rotation_point,rot_angle*180/PI,1);

    /* Apply the rotation to the gray frame in order to align the face being processed */
    warpAffine(gray_frame,rotated_frame,R,gray_frame.size());

    /* Get the region that corresponds to the face on the rotated frame */
    Rect2f face_area(rotation_point.x - distance_eyes*(0.5 + CROP_LEFT_PROP), rotation_point.y - distance_eyes*CROP_TOP_PROP,
     distance_eyes*(1+CROP_LEFT_PROP+CROP_RIGHT_PROP), distance_eyes*(CROP_TOP_PROP+CROP_BOTTOM_PROP) );

    /* Check if the face area to be cropped would be within the gray_frame. If it is not, the face can't be cropped and
        therefore the function ends returning an empty face image */
    if(containRect(frame_rect,face_area))
    {
        /* Draw a rectangle around the face area to be cropped on the gray frame */
        rectangle(rotated_frame, face_area,Scalar (255,0,0));

        /* Crop and get the aligned face from the rotated frame */
        cropFace = rotated_frame(face_area);

        /* Resize the cropped face so it has standardized dimensions */
        resize(cropFace,cropFace,Size(WIDTH,HEIGHT));

       // imshow("ROTATED", rotated_frame);

       /* Uncomment below to display the image of the cropped face */
       // imshow("FACE AREA", cropFace );
    }

    return cropFace; // returns the aligned and cropped face
}

