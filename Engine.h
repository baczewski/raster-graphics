#pragma once

#include <sstream>
#include <algorithm>

#include "Session.h"

class Engine{
private:

    static Engine* instance;

    static vector<Session> sessions;
    static Session* currentSession;
    static const vector<string> commands;
    Engine() = default;

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
public:

    static Engine* getInstance();

    static void addNewSession(const vector<string>& imagesPaths);
    static void switchTo(int sessionId);

    static void run();
    static void callCommand();

    class Commands{
    public:
        static void loadSession(vector<string> command);
        static void savePictures(vector<string> command);
        static void savePicturesTo(vector<string> command);
        static void addPictureToSession(vector<string> command);
        static void switchToSession(vector<string> command);
        static void addFilterToPictures(vector<string> command);
        static void rotatePictures(vector<string> command);
        static void flipPictures(vector<string> command);
        static void cropPictures(vector<string> command);
        static void undoTransformation(vector<string> command);
        static void displaySessionInfo(vector<string> command);
        static void help(vector<string> command);
        static void exit(vector<string> command);
    };
};