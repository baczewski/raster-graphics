#include "Session.h"
#include "Transformation.h"

bool canBeApplied(const string&, const Picture&);

unsigned Session::IDCounter = 0;

Session::Session(const vector<string>& picturePaths){
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
    std::cout << sessionPictures.size();
    for(Picture picture : sessionPictures){
        auto pixels = picture.getPixels();

        if (Transformation::transform(picture.getTransformations(), pixels, picture.getType(), picture.getMaxValue()))
        {
            picture.save("");
            picture.clearTransformations();
        }
    }
}

void Session::addNewPictures(const vector<string>& picturePaths){
    for(int i = 0; i < picturePaths.size(); ++i){
        // Picture newPicture;
        // try{
            Picture newPicture(picturePaths[i]);
        // }catch(...){
            // std::cout << "\nInvalid image, won't be added to the session!\n";
            // return;
        // }
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
        for(Picture picture : sessionPictures){
            picture.undoTransformation();
        } 
    }
}

void Session::savePictures(const string& path){
    for(Picture picture : sessionPictures){
        picture.save(path);
    }
    clearPicturesTransformations();
}

const string Session::getSessionInfo() const {
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

bool canBeApplied(const string& transformation, const Picture& picture){
    if(transformation == "greyscale" && picture.getType() != Type::P3){
        return false;
    }
        if(transformation == "monochrome" && picture.getType() == Type::P1){
        return false;
    }
    return true;
}

