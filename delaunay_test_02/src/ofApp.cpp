#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    countFrames = 100;
    saveFrames = false;
    
    ofSetFrameRate(30);
    
    framePad = 1.25;
    countPoints = 1000;
    noiseResolution = 2;
    offsetRadius = 0;
    minZoom = 1;
    maxZoom = 3;
    
    img.load("images/image_01.png");
    ofPixels pixelData = img.getPixels();
    myTexture.allocate(pixelData);
    myTexture.bind();
    
    for (int i = 0; i < countPoints; i++) {
        float x = framePad * ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
        float y = framePad * ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
        triangulation.addPoint(ofPoint(x,y));
    }
    triangulation.triangulate();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    sceneRatio = (float(ofGetFrameNum()) - 1) / countFrames;
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    vector<ofMeshFace> faces = triangulation.triangleMesh.getUniqueFaces();
    
    ofSetColor(255);
    for (int i = 0; i < faces.size(); i++) {
        
        ofMeshFace face = faces[i];
        ofPoint p0 = face.getVertex(0);
        ofPoint p1 = face.getVertex(1);
        ofPoint p2 = face.getVertex(2);
        
        ofPoint centroid = ofPoint((p0.x + p1.x + p2.x) / 3, (p0.y + p1.y + p2.y) / 3) * 1.25;
        
        ofPoint transTexToCenter = ofPoint(ofGetWidth() / 2, ofGetHeight() / 2);
        
        float thetaNoise = 3 * PI * ofxeasing::map(ofSignedNoise(p0.x / (noiseResolution * ofGetWidth()), p0.y / (noiseResolution * ofGetHeight())), -1, 1, -1, 1, ofxeasing::linear::easeInOut);
        ofPoint randOffset = ofPoint(offsetRadius * cos(thetaNoise + 2 * PI * sceneRatio), offsetRadius * sin(thetaNoise + 2 * PI * sceneRatio));
        
        float scale = ofMap(sin(thetaNoise + 2 * PI * sceneRatio), -1, 1, minZoom, maxZoom);
        float rotate = 0 * thetaNoise;
        ofPoint t0 = (p0 - centroid).rotateRad(rotate, ofVec3f(0, 0, 1)) * scale + centroid;
        ofPoint t1 = (p1 - centroid).rotateRad(rotate, ofVec3f(0, 0, 1)) * scale + centroid;
        ofPoint t2 = (p2 - centroid).rotateRad(rotate, ofVec3f(0, 0, 1)) * scale + centroid;
        
        ofMesh newFace;
        newFace.addVertex(p0);
        newFace.addTexCoord(t0 + randOffset + transTexToCenter + ofPoint(100, 100));
        newFace.addVertex(p1);
        newFace.addTexCoord(t1 + randOffset + transTexToCenter + ofPoint(100, 100));
        newFace.addVertex(p2);
        newFace.addTexCoord(t2 + randOffset + transTexToCenter + ofPoint(100, 100));
        newFace.draw();
    }
    
    if (saveFrames) {
        if (ofGetFrameNum() < countFrames) {
            ofSaveViewport(ofToString(ofGetFrameNum() + 0 * countFrames, 4, '0') + ".png");
            ofSaveViewport(ofToString(ofGetFrameNum() + 1 * countFrames, 4, '0') + ".png");
            ofSaveViewport(ofToString(ofGetFrameNum() + 2 * countFrames, 4, '0') + ".png");
            ofSaveViewport(ofToString(ofGetFrameNum() + 3 * countFrames, 4, '0') + ".png");
        }
        else exit();
    }
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
