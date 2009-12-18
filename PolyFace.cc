/* 
 * File:   PolyFace.cc
 * Author: majorerror
 * 
 * Created on 08 December 2009, 18:16
 */

#include <algorithm>
#include "PolyFace.h"
#include "Point.h"

using namespace std;

PolyFace::PolyFace( Point* a, Point* b, Point* c ) : 
        p1( min( a, min( b, c ) ) ),
        p3( max( a, max( b, c ) ) ),
        textureViewpoint( SO3<>(), makeVector( numeric_limits<double>::max(), numeric_limits<double>::max(), numeric_limits<double>::max() ) ),
        texture( ImageRef( 640, 480 ), Rgb<byte>( 255, 0, 0 ) ){
    p2 = p1 == a ? (p3 == b ? c : b) : (p3 == a ? b : a);
};

Point* PolyFace::getP1() {
    return p1;
};

Vector<2> PolyFace::getP1Coord( ATANCamera* cam ) {
    Vector<3> v = textureViewpoint.get_rotation().inverse() * (p1->getPosition() - textureViewpoint.get_translation());

    Vector<2> out = cam->Project( makeVector( v[0]/v[2], v[1]/v[2] ) );
    out[0] /= cam->GetImageSize()[0];
    out[1] /= cam->GetImageSize()[1];
    return out;
};

Point* PolyFace::getP2() {
    return p2;
};

Vector<2> PolyFace::getP2Coord( ATANCamera* cam ) {
    Vector<3> v = textureViewpoint.get_rotation().inverse() * (p2->getPosition() - textureViewpoint.get_translation());

    Vector<2> out = cam->Project( makeVector( v[0]/v[2], v[1]/v[2] ) );
    out[0] /= cam->GetImageSize()[0];
    out[1] /= cam->GetImageSize()[1];
    return out;
};

Point* PolyFace::getP3() {
    return p3;
};

Vector<2> PolyFace::getP3Coord( ATANCamera* cam ) {
    Vector<3> v = textureViewpoint.get_rotation().inverse() * (p3->getPosition() - textureViewpoint.get_translation());

    Vector<2> out = cam->Project( makeVector( v[0]/v[2], v[1]/v[2] ) );
    out[0] /= cam->GetImageSize()[0];
    out[1] /= cam->GetImageSize()[1];
    return out;
};

void PolyFace::setTexture( Image< Rgb< byte > > t, SE3<> vp ) {
    texture.copy_from( t );
    textureViewpoint = vp;
};

SubImage< Rgb< byte > >& PolyFace::getTexture() {
    return texture;
};

SE3<>& PolyFace::getTextureViewpoint() {
    return textureViewpoint;
};

Vector<3> PolyFace::getFaceCentre() {
    Vector<3> out = p1->getPosition() + p2->getPosition() + p3->getPosition();
    out /= 3;
    return out;
};

bool PolyFace::operator()( PolyFace* a, PolyFace* p ) const {
    return a->p1 < p->p1 || a->p2 < p->p2 || a->p3 < p->p3;
};