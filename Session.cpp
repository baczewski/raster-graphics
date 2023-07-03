#include "Session.h"

bool canBeApplied(const string&, const Picture&);

unsigned Session::IDCounter = 0;

Session::Session(const vector<string>& picturePaths){
    // create pictures from paths and add them to session
    for(int i = 0; i < picturePaths.size(); ++i){
        Picture newPicture(picturePaths[i]);
        sessionPictures.push_back(newPicture);
    }
    std::cout << "Session with ID: " << this->ID << " started\n";
}

unsigned Session::getID() const{
    return this->ID;
}

void Session::addTransformationInfoToPictures(const string& newTransformation){
    this->sessionTransformations.push_back(newTransformation);
    for(Picture picture : sessionPictures){
        if(canBeApplied(newTransformation, picture)){
            picture.addTransformation(newTransformation);
        }
    }
}

void Session::applyTransformationsToPictures(){
    for(Picture picture : sessionPictures){
        // call the transformation for picture
    }
}

void Session::addNewPictures(const vector<string>& picturePaths){
    for(int i = 0; i < picturePaths.size(); ++i){
        Picture newPicture(picturePaths[i]);
        sessionPictures.push_back(newPicture);
    }
}

void Session::optimizeTransformations(){
    int lenght = sessionTransformations.size();
    for(int i = 0; i < sessionTransformations.size()-1; ++i){
        // delete transformations rotate left next to rotate
        // right or vice versa as they cancel each other  
        if(sessionTransformations[i] == "rotate left" && 
            sessionTransformations[i+1] == "rotate right" || 
            sessionTransformations[i] == "rotate right" && 
            sessionTransformations[i+1] == "rotate left"){
                sessionTransformations.erase(sessionTransformations.begin()+i);
                sessionTransformations.erase(sessionTransformations.begin()+i);
                i = std::max(-1, i - 2);
                continue;
        }
        // two occurences of flip horizontal/vertical cancel each other
        if(sessionTransformations[i] == "flip horizontal" || 
            sessionTransformations[i] == "flip vertical"){
            for(int j = i + 1; j < sessionTransformations.size(); ++j){
                if(sessionTransformations[j] == sessionTransformations[i]){
                    sessionTransformations.erase(sessionTransformations.begin()+j);
                    sessionTransformations.erase(sessionTransformations.begin()+i);
                    break;
                }
            }
        }
    }
}

void Session::undoLastTransformation(){
    if(sessionTransformations.size() != 0){
        sessionTransformations.erase(sessionTransformations.end() - 1);
    }
}

void Session::savePictures(const string& path){
    for(Picture picture : sessionPictures){
        picture.save();
    }
    clearPicturesTransformations();
}

const string& Session::getSessionInfo() const{
    string infoText = "Name of images in session: "; 
    for(Picture picture : sessionPictures){
        infoText += picture.getName() + " ";
    }
    infoText += "\nTransformations: ";
    for(string transformation : sessionTransformations){
        infoText += transformation;
    }
    infoText += '\n';
    return infoText;
}

void Session::clearPicturesTransformations(){
    for(Picture picture : sessionPictures){
        picture.clearTransformations();
    }
}

// check if the filter can be applied on this type of picture
bool canBeApplied(const string& transformation, const Picture& picture){
    if(transformation == "greyscale" && picture.getType() != Type::P3){
        return false;
    }
        if(transformation == "monochrome" && picture.getType() == Type::P1){
        return false;
    }
    return true;
}

