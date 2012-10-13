//
//  BoxButton.h
//  Kinect_3DJ
//
//  Created by LJ on 9/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef Kinect_3DJ_BoxView_h
#define Kinect_3DJ_BoxView_h

#include "ofMain.h"
#include "DataPool.h"
#include "Interface.h"
#include "Common.h"
using namespace DataPool;
using namespace Interface;
using namespace Common;

class CBoxView: public IView{
    struct SBoxInfo{
        string name;
        ofSoundPlayer* soundPlayer;
    };

public:
    CBoxView(CDataPoolSimple* DataPool);    

    bool init();

    void animation( vector<SBoxInfo>::iterator it );
    void render( vector<SBoxInfo>::iterator it );

    void drawBox( float red, float green, float blue, float alpha, float centerX, float complexor, float centerY, float centerZ, int boxSize );

    bool isCurrentlyHit( string val );
    float percentIncluded( string val );
    float swellAnimation( string val );

    vector<SBoxInfo> m_boxInfo;
    int m_complexor;
};

#endif
