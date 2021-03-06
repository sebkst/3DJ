//
//  CBoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 8/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Kinect_3DJ_ControlBoxButton_h
#define Kinect_3DJ_ControlBoxButton_h

#include "BoxButton.h"

class CLoopBoxButton: public CBoxButton{
public:
    CLoopBoxButton(string boxName, float centerX, float centerY, float centerZ, int boxSize,
        float redVal, float greenVal, float blueVal, float alphaVal, string soundName, float rotation)
        :CBoxButton(boxName,  centerX, centerY, centerZ, boxSize, redVal, greenVal, blueVal, alphaVal, soundName, rotation)
    {}

    bool isLoopBox();
};

#endif
