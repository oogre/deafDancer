#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sg = new SignalGenerator();
    this->parameters.add(sg->parameters);
    
    gui.setup();
    gui.add(this->parameters);
    gui.setPosition(0, 0);
    gui.setSize(201, 800);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    gui.setPosition(0, 0);
    sg->update();
    
   
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    gui.setPosition(0, 0);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
