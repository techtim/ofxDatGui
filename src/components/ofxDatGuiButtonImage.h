/*
 Copyright (C) 2017 Timofey Tavlintsev [http://tvl.io]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once
#include "ofxDatGuiComponent.h"

class ofxDatGuiButtonImage : public ofxDatGuiButton {
    unique_ptr<ofImage> image;
    unique_ptr<ofImage> imageClick;
    bool bChangeBackgroundOnMouse;

public:
    ofxDatGuiButtonImage(const string &label, string imagePath, string imageClickPath = "")
        : ofxDatGuiButton(label)
        , bChangeBackgroundOnMouse(false)
    {
        mType = ofxDatGuiType::BUTTON_IMAGE;
        image = make_unique<ofImage>();
        bool bLoad = image->load(imagePath);
        assert(bLoad);
        if (imageClickPath == "") {
            bChangeBackgroundOnMouse = true;
            imageClick = make_unique<ofImage>();
            bLoad = imageClick->load(imagePath);
        }
        else {
            imageClick = make_unique<ofImage>();
            bLoad = imageClick->load(imageClickPath);
        }

        assert(bLoad);
        setTheme(ofxDatGuiComponent::getTheme());
    }

    void setTheme(const ofxDatGuiTheme *theme)
    {
        setComponentStyle(theme);
        mStyle.stripe.color = theme->stripe.button;
        mStyle.height = ofxDatGuiIsRetina() ? image->getHeight() / 2 : image->getHeight();
        setWidth(image->getWidth(), theme->layout.labelWidth);
    }

    void setWidth(int width, float labelWidth = 1)
    {
        ofxDatGuiComponent::setWidth(width, labelWidth);
        mLabel.x = getWidth();
        mLabel.width = mStyle.width;
        mLabel.rightAlignedXpos = mLabel.width - mLabel.margin;
        //        ofxDatGuiComponent::positionLabel();
    }

    void draw()
    {
        if (mVisible) {
            // anything that extends ofxDatGuiButton has the same rollover effect //
            ofPushStyle();
            if (mStyle.border.visible)
                drawBorder();
            ofFill();
            ofDisableAlphaBlending();
            if (bChangeBackgroundOnMouse) {
                (mMouseOver || mMouseDown) ? ofSetColor(255) : ofSetColor(200);
                ofDrawRectangle(x, y, getWidth(), getHeight());
            }

            if (mFocused && mMouseDown) {
                imageClick->draw(x, y);
            }
            else if (mMouseOver) {
                image->draw(x, y);
                drawLabel();
            }
            else {
                image->draw(x, y);
            }
            if (mStyle.stripe.visible)
                drawStripe();
            ofPopStyle();
        }
    }

    static ofxDatGuiButton *getInstance() { return new ofxDatGuiButton("X"); }

protected:
    void onMouseRelease(ofPoint m)
    {
        ofxDatGuiButton::onMouseRelease(move(m));
    }
};

class ofxDatGuiToggleImage : public ofxDatGuiToggle {
    unique_ptr<ofImage> image;
    unique_ptr<ofImage> imageClick;
    bool bChangeBackgroundOnMouse;

public:
    ofxDatGuiToggleImage(const string &label, string imagePath, string imageClickPath = "")
        : ofxDatGuiToggle(label)
        , bChangeBackgroundOnMouse(false)
    {
        mType = ofxDatGuiType::BUTTON_TOGGLE;
        image = make_unique<ofImage>();
        bool bLoad = image->load(imagePath);
        assert(bLoad);
        if (imageClickPath == "") {
            bChangeBackgroundOnMouse = true;
            imageClick = make_unique<ofImage>();
            bLoad = imageClick->load(imagePath);
        }
        else {
            imageClick = make_unique<ofImage>();
            bLoad = imageClick->load(imageClickPath);
        }

        assert(bLoad);
        setTheme(ofxDatGuiComponent::getTheme());
    }

    void setTheme(const ofxDatGuiTheme *theme)
    {
        setComponentStyle(theme);
        mStyle.stripe.color = theme->stripe.button;
        mStyle.height = ofxDatGuiIsRetina() ? image->getHeight() / 2 : image->getHeight();
        setWidth(image->getWidth(), theme->layout.labelWidth);
    }

    void setWidth(int width, float labelWidth = 1)
    {
        ofxDatGuiComponent::setWidth(width, labelWidth);
        mLabel.x = getWidth();
        mLabel.width = mStyle.width;
        mLabel.rightAlignedXpos = mLabel.width - mLabel.margin;
        //        ofxDatGuiComponent::positionLabel();
    }
    void draw()
    {
        if (ofxDatGuiToggle::mVisible) {
            // anything that extends ofxDatGuiButton has the same rollover effect //
            ofPushStyle();
            if (ofxDatGuiToggle::mStyle.border.visible)
                ofxDatGuiToggle::drawBorder();
            ofFill();
            ofDisableAlphaBlending();
            if (bChangeBackgroundOnMouse) {
                (ofxDatGuiToggle::mMouseOver || ofxDatGuiToggle::mMouseDown
                    || ofxDatGuiToggle::getChecked())
                    ? ofSetColor(255)
                    : ofSetColor(200);
                ofDrawRectangle(ofxDatGuiToggle::x, ofxDatGuiToggle::y, ofxDatGuiToggle::getWidth(),
                    ofxDatGuiToggle::getHeight());
            }

            if ((ofxDatGuiToggle::mFocused && ofxDatGuiToggle::mMouseDown)
                || ofxDatGuiToggle::getChecked()) {
                imageClick->draw(ofxDatGuiToggle::x, ofxDatGuiToggle::y);
            }
            else if (ofxDatGuiToggle::mMouseOver) {
                image->draw(ofxDatGuiToggle::x, ofxDatGuiToggle::y);
                ofxDatGuiToggle::drawLabel();
            }
            else {
                image->draw(ofxDatGuiToggle::x, ofxDatGuiToggle::y);
            }
            if (ofxDatGuiToggle::mStyle.stripe.visible)
                ofxDatGuiToggle::drawStripe();
            ofPopStyle();
        }
    }

    static ofxDatGuiToggle *getInstance() { return new ofxDatGuiToggle("X"); }

protected:
    void onMouseRelease(ofPoint m)
    {
        ofxDatGuiToggle::onMouseRelease(move(m));
    }
};
