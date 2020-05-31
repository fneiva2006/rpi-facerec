/*
    File Name: GeometricAux.hpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "AUxiliary Geometric Tools" used on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#ifndef GEOMETRICAUX_HPP
#define GEOMETRICAUX_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include "opencv2/core.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#define PI 3.14159265

using namespace cv;
using namespace std;

namespace GeometricAux
{
         /* =================== Auxiliary Functions ============================== */

        /* returns the geometric centre of the given Rectangle */
         Point2f rectCentre(Rect r);

        /* returns the geometric distance between two points */
         double point_distance(Point2f a, Point2f b);

        /* Checks which point is more to the left (smaller x coordinate). Stores
           the left point on 'left' and the right on 'right' */
         void lr_points(Point2f a, Point2f b, Point2f& left, Point2f& right);

        /* Calculates and returns the angle formed between the horizontal line and the line segment that
           links the left point 'lp' to the right point 'rp' */
         double lr_rot_angle(Point2f lp, Point2f rp);

        /* returns the median (middle point) of the two points */
         Point2f median(Point2f a, Point2f b);

        /* returns the base point of the given rectangle on the arg */
         Point2f rect_basepoint(Rect2f r);

        /* checks if the rectangle 'r2' is contained within rectangle 'r1' */
         bool containRect(Rect2f r1, Rect2f r2);

        /* ========================================================================== */

};

#endif
