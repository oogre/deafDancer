//
//  signalGenerator.hpp
//  signalGenerator
//
//  Created by Vincent Evrard on 19/04/18.
//

#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345


class SignalGenerator{
    float changeAt = 0;
    float oldRandom = 0;
    ofxOscSender sender;
    
    public :
        ofParameterGroup parameters;
        ofParameter<float> monthday;
        ofParameter<float> weekday;
        ofParameter<float> hour;
        ofParameter<float> minutes;
        ofParameter<float> seconds;
        ofParameter<float> millis;
        ofParameter<float> winX;
        ofParameter<float> winY;
    
        ofParameter<float> random;
        ofParameter<float> linearRandom;
        ofParameter<float> squareRandom;
        ofParameter<float> rootRandom;
        ofParameter<float> easeRandom;
    
        ofParameter<float> noise;
        ofParameter<float> fractNoise;
    
        ofParameter<float> sinus;
        ofParameter<float> sinusStep;
        ofParameter<float> cosinus;
    
        SignalGenerator(){
            parameters.setName("Time");
            parameters.add(monthday.set("MonthDay", 0.f, 0.f, 1.f));
            parameters.add(weekday.set("WeekDay", 0.f, 0.f, 1.f));
            parameters.add(hour.set("Hours", 0.f, 0.f, 1.f));
            parameters.add(minutes.set("Minutes", 0.f, 0.f, 1.f));
            parameters.add(seconds.set("Seconds", 0.f, 0.f, 1.f));
            
            
            parameters.add(millis.set("Millis", 0.f, 0.f, 1.f));
            
            parameters.add(winX.set("winX", 0.f, 0.f, 1.f));
            parameters.add(winY.set("winY", 0.f, 0.f, 1.f));
            
            parameters.add(random.set("Random", ofRandom(0.f, 1.f), 0.f, 1.f));
            parameters.add(linearRandom.set("LinearSmooth", 0.f, 0.f, 1.f));
            parameters.add(squareRandom.set("SquareSmooth", 0.f, 0.f, 1.f));
            parameters.add(rootRandom.set("RootSmooth", 0.f, 0.f, 1.f));
            
            parameters.add(noise.set("Noise", 0.f, 0.f, 1.f));
            parameters.add(fractNoise.set("fractNoise", 0.f, 0.f, 1.f));
            
            parameters.add(sinus.set("Sin", 0.f, 0.f, 1.f));
            parameters.add(cosinus.set("Cos", 0.f, 0.f, 1.f));
            
            parameters.add(sinusStep.set("sinusStep", 0.f, 0.f, 1.f));
            sender.setup(HOST, PORT);
        }
    
    void update(){
        string timeStamp = ofGetTimestampString();
        float m = (float)ofToInt(timeStamp.substr(20, 3)) * 0.001f;
        float s = (ofGetSeconds() + m )/60.0f;
        float M = (ofGetMinutes() + s)/60.0f;
        float h = (ofGetHours() + M)/24.0f;
        float wd = (ofGetWeekday() + h)/7.0f;
        float md = (ofGetDay() + h)/31.0f;
        float wX = ofMap(ofGetWindowPositionX(), -ofGetWindowWidth(), ofGetScreenWidth(), 0, 1);
        float wY = ofMap(ofGetWindowPositionY(), 0, ofGetScreenHeight(), 0, 1);
        if(monthday.get() != md){
            monthday = md;
            monthday.setName("MonthDay : " + ofToString(ofGetDay()));
        }
        if(weekday.get() != wd){
            weekday = wd;
            weekday.setName("WeekDay : " + ofToString(ofGetWeekday()));
        }
        if(hour.get() != h){
            hour = h;
            hour.setName("Hours : " + ofToString(ofGetHours()));
        }
        if(minutes.get() != M){
            minutes = M;
            minutes.setName("Minutes : " + ofToString(ofGetMinutes()));
        }
        if(seconds.get() != s){
            seconds = s;
            seconds.setName("Seconds : " + ofToString(ofGetSeconds()));
        }
        millis = m;
        
        if(winX.get() != wX){
            winX = wX;
        }
        
        if(winY.get() != wX){
            winY = wY;
        }
        
        if(ofGetElapsedTimef() - changeAt >= 1){
            oldRandom = random.get();
            random = ofRandom(0.f, 1.f);
            changeAt = ofGetElapsedTimef();
        }
        
        float linear = (ofGetElapsedTimef() - changeAt);
        
        linearRandom = ofLerp(oldRandom, random.get(), linear);
        squareRandom = ofLerp(oldRandom, random.get(), linear * linear);
        rootRandom = ofLerp(oldRandom, random.get(), pow(abs(linear), 0.5f));
        noise = ofNoise(ofGetElapsedTimef());
        fractNoise = (
                      noise
                      + (ofNoise(pow(1.5f, 1) * ofGetElapsedTimef()) * pow(0.5f, 1))
                      + (ofNoise(pow(1.5f, 2) * ofGetElapsedTimef()) * pow(0.5f, 2))
                      + (ofNoise(pow(1.5f, 3) * ofGetElapsedTimef()) * pow(0.5f, 3))
                      + (ofNoise(pow(1.5f, 4) * ofGetElapsedTimef()) * pow(0.5f, 4))
                      + (ofNoise(pow(1.5f, 5) * ofGetElapsedTimef()) * pow(0.5f, 5))
                      + (ofNoise(pow(1.5f, 6) * ofGetElapsedTimef()) * pow(0.5f, 6))
                      + (ofNoise(pow(1.5f, 7) * ofGetElapsedTimef()) * pow(0.5f, 7))
                    ) / (1 + pow(0.5f, 1) + pow(0.5f, 2) + pow(0.5f, 3) + pow(0.5f, 4) + pow(0.5f, 5) + pow(0.5f, 6) + pow(0.5f, 7)) ;
        
        sinus = sin(m * TWO_PI) * 0.5f + 0.5f;
        sinusStep = sin(floor( m * TWO_PI / 1.22) ) * 0.5f + 0.5f;
        cosinus = cos(m * TWO_PI) * 0.5f + 0.5f;
        ofxOscMessage mOSC;
        mOSC.setAddress("/deafDancer");
        auto it = parameters.begin();
        while(it != parameters.end()){
            mOSC.addFloatArg(parameters.getFloat((*it)->getName()));
            it++;
        }
        sender.sendMessage(mOSC, false);
    }
    
};
