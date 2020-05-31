/*
    File Name: GeometricAux.cpp
    Author(s): Felipe Neiva Montalvão Melo and Dennis Hadjivelichkov
    July 2016

    This file corresponds to the "AUxiliary Geometric Tools" used on the Face Detection & Recognition System.
    It was developed in an undergraduate academic project at The University of Manchester
    during the months of July and August 2016.

    For more information, please consult the documentation file (FaceRecDocumentation.pdf).

*/

#include "GeometricAux.hpp"

/* ==================================================================================== */

Point2f GeometricAux::rectCentre(Rect r)
{
    return Point2f( r.x + r.width*0.5, r.y + r.height*0.5);
}

double GeometricAux::point_distance(Point2f a, Point2f b)
{
    return (sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y) ) );
}

void GeometricAux::lr_points(Point2f a, Point2f b, Point2f& left, Point2f& right)
{
    if(a.x <= b.x)
    {
       // cout << "A is left" << endl;
        left = a;
        right = b;
    }
    else
    {
        //cout << "B is left" << endl;
        right = a;
        left = b;
    }
}

double GeometricAux::lr_rot_angle(Point2f lp, Point2f rp)
{
    return ( atan2( rp.y - lp.y, rp.x - lp.x ));
}

Point2f GeometricAux::median(Point2f a, Point2f b)
{
    return (Point2f( (a.x+b.x)/2 , (a.y+b.y)/2    ));

}

Point2f GeometricAux::rect_basepoint(Rect2f r)
{
    return (Point2f(r.x,r.y));
}

bool GeometricAux::containRect(Rect2f r1, Rect2f r2)
{
    return (r1.contains(Point2f(r2.x,r2.y))
    && r1.contains(Point2f(r2.x+r2.width, r2.y + r2.height)));

}

