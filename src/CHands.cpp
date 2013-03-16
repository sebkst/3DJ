//
//  CHands.cpp
//  Kinect_3DJ
//
//  Created by Li Jing on 2/30/13.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CHands.h"

CHands::CHands( CDataPoolSimple* datapool)
{
    m_datapool = datapool;
    // get the openNI device from CKinectData object, that means kinect object must be created before this operation.
    void *temp;
    m_datapool->getRefByName("ofxOpenNIDevice", temp);
    m_openNIDevice = (ofxOpenNI*)temp;
    m_slide = false;    
    m_slideTriggerPoint.x = 0;
    m_slideTriggerPoint.y = -250;
    m_slideTriggerPoint.z = 800;
    m_slideRadius = 200;    
    m_slideHand = JOINT_RIGHT_HAND;
    m_slideStart = false;
}

CHands::~CHands()
{
    
}

void CHands::drawCirclesOnHand(ofPoint &p, float radius)
{// draw cirle on hand
    ofPushMatrix();
    ofNoFill();
    ofSetLineWidth(5.f);

    ofCircle(p.x, p.y, p.z, radius);
    
    ofPopMatrix();
}

void CHands::getHands()
{
    int numUsers = m_openNIDevice->getNumTrackedUsers();
    if (numUsers) {
        m_mapHands.clear();
        for (int i = 0; i < numUsers; i++) {
            ofxOpenNIUser & user = m_openNIDevice->getTrackedUser(i);
            if (user.isTracking()) {
                
                //Get Left and right hand posisitons
                ofPoint rhp = m_openNIDevice->getTrackedUser(i).getJoint(JOINT_RIGHT_HAND).getWorldPosition();
                ofPoint lhp = m_openNIDevice->getTrackedUser(i).getJoint(JOINT_LEFT_HAND).getWorldPosition();;
               
                // this coordinator translating is for adapting to box view.
                rhp.y *= -2;  //flip in y direction
                lhp.y *= -2;  //flip in y direction    
                rhp.x *= 2;
                lhp.x *= 2;

                if ( lhp.z < m_slideTriggerPoint.z + m_slideRadius
                    &&lhp.z > m_slideTriggerPoint.z - m_slideRadius
                    &&lhp.y < m_slideTriggerPoint.y + m_slideRadius
                    &&lhp.z > m_slideTriggerPoint.y - m_slideRadius
                    &&lhp.x < m_slideTriggerPoint.x + m_slideRadius
                    &&lhp.x > m_slideTriggerPoint.x - m_slideRadius)
                {
                    cout<<"trigger left"<<endl;
                    m_slideUser = &user;
                    m_slideHand = JOINT_LEFT_HAND;
                    m_slideStart = true;
                }
                if ( rhp.z < m_slideTriggerPoint.z + m_slideRadius
                    &&rhp.z > m_slideTriggerPoint.z - m_slideRadius
                    &&rhp.y < m_slideTriggerPoint.y + m_slideRadius
                    &&rhp.z > m_slideTriggerPoint.y - m_slideRadius
                    &&rhp.x < m_slideTriggerPoint.x + m_slideRadius
                    &&rhp.x > m_slideTriggerPoint.x - m_slideRadius)
                {
                    cout<<"trigger right"<<endl;
                    m_slideUser = &user;
                    m_slideHand = JOINT_RIGHT_HAND;
                    m_slideStart = true;
                }

                // save hands point to map.
                handsPoint hp;
                hp.lhp = lhp;
                hp.rhp = rhp;
                m_mapHands[i] = hp;
            }
        }
    }
}

void CHands::draw()
{
    if ( m_slide ){
        if ( m_slideStart && m_slideUser->isTracking() )
        {
            ofPoint hp = m_slideUser->getJoint(m_slideHand).getWorldPosition();
            // this coordinator translating is for adapting to box view.
            hp.y *= -2;  //flip in y direction
            hp.x *= 2;
            if ( hp.z > 1400 )
            {
                m_slideStart = false;
                m_slideUser = 0;
                m_slideOffset = 0;
            }else{
                m_slideOffset = hp.x - m_slideTriggerPoint.x;
                drawCirclesOnHand(hp, m_slideRadius);            
            }
            m_datapool->createRef("slideOffset", &m_slideOffset);            
        }else{
            getHands();
            drawCirclesOnHand(m_slideTriggerPoint, m_slideRadius);
        }            
    }    
    //drawHands();
}

void CHands::triggerSlide()
{
    m_slide = true;
}

void CHands::drawHands()
{
    getHands();
    for ( map<int, handsPoint>::iterator iter = m_mapHands.begin(); iter != m_mapHands.end(); iter++)
    {
        //cout<< "left hand x:" << iter->second.lhp.x << "left hand y:" << iter->second.lhp.y << "left hand z:" << iter->second.lhp.z <<endl;
        //cout<< "left hand x:" << iter->second.rhp.x << "left hand y:" << iter->second.rhp.y << "left hand z:" << iter->second.rhp.z <<endl;
        drawCirclesOnHand( iter->second.lhp, 200);
        drawCirclesOnHand( iter->second.rhp, 100);
    }
}