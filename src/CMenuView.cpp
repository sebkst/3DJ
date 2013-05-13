//
//  CMenuView.cpp
//  3DJ
//
//  Created by  on 9/1/12.
//

#include <iostream>
#include "CMenuView.h"

CMenuView::CMenuView()
{
    setupGUI();
}

CMenuView::~CMenuView()
{
    delete m_canvas1;
}

void CMenuView::setupGUI()
{
    int heightOffset = 32;
    int canvas_w = 200;
    int canvas_h = 260;   //ofGetScreenHeight() - heightOffset;
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = canvas_w-(xInit*2);
    float buttonLength = length; //(length-xInit)*.5;
    
  
    m_canvas1 = new ofxUICanvas(0,heightOffset,canvas_w, canvas_h);
  
    ofColor m_3DJ_Green_Light = ofColor(152,202,86);
    ofColor m_3DJ_Green_Dark = ofColor(108,129,100);
    m_canvas1->setColorPaddedOutline(m_3DJ_Green_Light);
    m_canvas1->setPadding(true);
    m_canvas1->setColorBack(m_3DJ_Green_Dark);
    
    //m_canvas1->addWidgetDown(new ofxUIImageButton(0, 0, length, length, false, "icons/3DJ_Logo_Small.png", ""));
    m_canvas1->addWidgetDown(new ofxUILabelButton(0, 20, buttonLength, false, "Start Session"));
    m_canvas1->addWidgetDown(new ofxUILabelButton(0,0,buttonLength, false, "Sets"));
    m_canvas1->addWidgetDown(new ofxUILabelButton(0,0, buttonLength, false, "Get Sounds"));
    m_canvas1->addWidgetDown(new ofxUILabelButton(0, 0, buttonLength, false, "Save Setup"));
    m_canvas1->addWidgetDown(new ofxUILabelButton(0, 0, buttonLength, false, "Help"));
}


void CMenuView::saveSettings()
{
    
}

void CMenuView::loadSettings()
{
    
}

void CMenuView::setColorTheme(int theme)
{
    
}

void CMenuView::showCanvases(bool show)
{
    m_canvas1->setVisible(show);
    m_canvasesVisible = show;
}






