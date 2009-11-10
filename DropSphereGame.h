// -*- c++ -*-
// Copyright 2008 Isis Innovation Limited
//
// DropSphereGame.h
// Declares the DropSphereGame class
// DropSphereGame is a trivial AR app which draws some 3D graphics
// Draws a bunch of 3d eyeballs remniscient of the 
// AVL logo
//
#ifndef __DropSphereGame_H
#define __DropSphereGame_H
#include <TooN/TooN.h>
using namespace TooN;
#include <vector>
#include "OpenGL.h"
#include "EyeGame.h"

class DropSphereGame : public EyeGame {
public:
    DropSphereGame();
    virtual void DrawStuff(Vector<3> v3CameraPos);
    virtual void Reset();
    virtual void Init();

protected:
    std::vector< Vector<3> > balls;

};


#endif
