#pragma once
#include "Picture.h"

class Session{
private:
    vector<Picture> sessionPictures;
    vector<string> sessionTransformations;

    static unsigned IDCounter;
    const int ID = IDCounter++;

public:

    Session(const vector<string>& picturePaths);

    unsigned getID() const;

    void addTransformationInfoToPictures(const string& transformation);
    void applyTransformationsToPictures();
    void optimizeTransformations();
    void addNewPictures(const vector<string>& picturePath);
    void undoLastTransformation();
    void savePictures(const string& path) const;

    const string& getSessionInfo() const;
};