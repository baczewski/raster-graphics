#include "Engine.h"
Engine* Engine::instance = nullptr;
vector<Session> Engine::sessions = vector<Session>();
Session* Engine::currentSession = nullptr;
const vector<string> Engine::commands = vector<string>{"help", "save", "saveas", "load", "add", "switch", 
                                                        "monochrome", "grayscale", "negative", "rotate", 
                                                        "flip", "undo", "crop", "session info", "exit"};

void tokenizeCommand(vector<string>&, const std::string&);
void toLowerCase(const string&);
bool isInVector(const string&, const vector<string>&);
const vector<string> getValidPicturePaths(const vector<string>&);
bool isInNetpbmFormat(const string&);
bool isValidFilename(const string&);

Engine* Engine::getInstance(){
  // make sure only one instance of the class is created
    if(instance == nullptr){
        instance = new Engine();
    }
    return instance;
}

void Engine::addNewSession(const vector<string>& picturePaths){
    Session newSession(picturePaths);
    sessions.push_back(newSession);
    currentSession = &newSession;
} 

void Engine::switchTo(int sessionID){
    for(Session session : sessions){
        if(session.getID() == sessionID){
            currentSession = &session;
            return;
        }
    }
    std::cout << "\n There is no session with this ID\n";
}

void Engine::run(){
    std::cout << "\n| Welcome to raster image editor! |\n------------------------------------";
    while(true){
        std::cout << "\nEnter your command (type help for the list of commands):\n";
        try{
            callCommand();
        }catch(char* msg){
            break;
        }
    }
}

void Engine::callCommand(){
    // read user's console input
    string commandText;
    std::getline(std::cin, commandText);

    vector<string> command;
    tokenizeCommand(command, commandText);

    if(command[0] == "help"){
        Commands::help(command);
    }
    else if(command[0] == "load"){
        Commands::loadSession(command);
    }
    else if(command[0] == "exit"){
        Commands::exit(command);
    }
    else if(command[0] != "help" && 
            command[0] != "load" &&  
            isInVector(command[0], commands)){
                if(currentSession == nullptr){
                    std::cout << "\nError! You must load a session first!\n";
                    return;
                }
    }
    else if(command[0] == "save"){
        Commands::savePictures(command);
    }
    else if(command[0] == "saveas"){
        Commands::savePicturesTo(command);
    }
    else if(command[0] == "add"){
        Commands::addPictureToSession(command);
    }
    else if(command[0] == "switch"){
        Commands::switchToSession(command);
    }
    else if(command[0] == "monochrome" ||
            command[0] == "grayscale" ||
            command[0] == "negative"){
        Commands::addFilterToPictures(command);           
    }
    else if(command[0] == "flip"){
        Commands::flipPictures(command);
    }
    else if(command[0] == "rotate"){
        Commands::rotatePictures(command);
    }
    else if(command[0] == "crop"){
        Commands::cropPictures(command);
    }
    else if(command[0] == "undo"){
        Commands::undoTransformation(command);
    }
    else if(command[0] == "session"){
        Commands::displaySessionInfo(command);
    }
    else{
        std::cout << "\nUnrecognized command! Type help for the list of commands!\n";
    }
}

void Engine::Commands::loadSession(vector<string> command){
    if(command.size() == 1){
        std::cout << "\nEmpty session cannot be started! Must write file names\n";
        return;
    }
    vector<string> picturePaths(&command[1], &command[command.size()]);
    vector<string> validPicturePaths = getValidPicturePaths(picturePaths);
    Engine::addNewSession(validPicturePaths);
}

void Engine::Commands::savePictures(vector<string> command){
    if(command.size() != 1){
        std::cout << "\nInvalid command! If you are trying to specify path, choose 'saveas'\n";
        return;
    }
    currentSession->optimizeTransformations();
    currentSession->applyTransformationsToPictures();
    currentSession->savePictures("");
}

void Engine::Commands::savePicturesTo(vector<string> command){
    if(command.size() == 1){
        std::cout << "\nInvalid command! If you don't want to specify path, choose 'save'\n";
        return;
    }
    string path = command[1];
    currentSession->optimizeTransformations();
    currentSession->applyTransformationsToPictures();
    currentSession->savePictures(path);
}

void Engine::Commands::addPictureToSession(vector<string> command){
    if(command.size() == 1){
        std::cout << "\nYou should specify image paths\n";
        return;
    }
    vector<string> paths(&command[1], &command[command.size()]);
    vector<string> validPaths = getValidPicturePaths(paths);
    currentSession->addNewPictures(validPaths);
}

void Engine::Commands::switchToSession(vector<string> command){
    if(command.size() == 1){
        std::cout << "\nInvalid command! You should specify Session ID!\n";
        return;
    }
    int sessionID;
    try{
        sessionID = std::stoi(command[1]);
    }catch(std::invalid_argument){
        std::cout << "\nInvalid session ID!\n";
        return;
    }
    Engine::switchTo(sessionID);
}

void Engine::Commands::addFilterToPictures(vector<string> command){
    if(command.size() != 1){
        std::cout << "\nInvalid command! Do you mean 'grayscale'/'monochrome'/'negative'\n";
        return;
    }
    currentSession->addTransformationInfoToPictures(command[0]);
}

void Engine::Commands::flipPictures(vector<string> command){
        if(command.size() == 1 ||
            command[1] != "horizontal" && 
            command[1] != "vertical"){
            std::cout << "\nUnrecognized command! Do you mean 'flip horizontal/vertical'?\n";
            return;
        }
        // the command if formed of the words 'flip' + 'horizontal'/'vertical' 
        string transformation = command[0] + " " + command[1];
        currentSession->addTransformationInfoToPictures(transformation);
}

void Engine::Commands::rotatePictures(vector<string> command){
    if(command[1] != "right" && command[1] != "left"){
        std::cout << "\nUnrecognized command! Do you mean 'rotate right/left'?\n";
        return;
    }
    // the command consists of 'rotate' + 'right'/'left' 
    string transformation = command[0] + " " + command[1];
    currentSession->addTransformationInfoToPictures(transformation);
}

void Engine::Commands::cropPictures(vector<string> command){
    if(command.size() != 5){
        std::cout << "\nInvalid parameters for crop command! You should specify coordinates, width and height\n";
        return;
    }
  // the parameters of crop function are added to the command string
    string cropWithParams = command[0] + " " + command[1] + " " + command[2] + " " + command[3] + " " + command[4];
    std::cout << cropWithParams << std::endl;
    currentSession->addTransformationInfoToPictures(cropWithParams);
}

void Engine::Commands::undoTransformation(vector<string> command){
    if(command.size() != 1){
        std::cout << "\nInvalid command! Do you mean undo?\n";
        return;
    }
    currentSession->undoLastTransformation();
}

void Engine::Commands::displaySessionInfo(vector<string> command){
    if(command[1] != "info"){
        std::cout << "\nUnrecognized command! Do you mean 'session info'?\n";
        return;
    }
    std::cout << currentSession->getSessionInfo() << std::endl;
}

void Engine::Commands::exit(vector<string> command){
    if(command.size() != 1){
        std::cout << "\nInvalid command! Do you mean 'exit'?\n";
        return;
    }
    delete currentSession;
    throw "stop programme";
}

void Engine::Commands::help(vector<string> command){
    if(command.size() != 1){
        std::cout << "\nInvalid command! Do you mean 'help'\n";
        return;
    }
    std::cout << "\nSupported commands:\nhelp - prints the whole list of supported commands\n" <<
    "load <image1 image2 image3 ...> - creates a new session with the specified images\n" <<
    "save - saves the images at the current directory\n" <<
    "saveas <path> - saves the images at the specified directory\n" <<
    "add <image1 image2 image3 ...> - adds new pictures to the current session" <<
    "switch <session ID> - switches to another session\n" <<
    "grayscale - applies grayscale filter to the images in the current session" <<
    "monochrome - applies black and white filter to the images in the current session" <<
    "negative - inverts the colors of the images in the current session" <<
    "rotate left - rotates the images from the current session 90 degrees to the left" <<
    "rotate right - rotates the images from the current session 90 degrees to the right" <<
    "lip horizontal - flips the images from the current session horizontally" <<
    "lip vertical - flips the images from the current session vertically" <<
    "crop <x> <y> <width> <height> - crops the current image from the specified\n" <<
    "top left corner (x,y) to the specified width and height" <<
    "undo - undoes the last change to the current image\n" <<
    "session info - prints the information about the current session\n"
    "exit - exits the programme\n";
}

void tokenizeCommand(vector<string>& splitCommand, const string& command){
    // create string stream from command 
    std::stringstream commandStream(command);

    // split string by spaces
    string commandPart;
    while(std::getline(commandStream, commandPart, ' ')){
        toLowerCase(commandPart);
        splitCommand.push_back(commandPart);
    }
}

void toLowerCase(const string& str){
    for(char c : str){
        if(c >= 'A' && c <= 'Z')
            c += 32;
    }
}

bool isInVector(const string& element, const vector<string>& vect){
    return std::find(vect.begin(), vect.end(), element) != vect.end();
}

const vector<string> getValidPicturePaths(const vector<string>& picturePaths){
  // extract only the valid picture paths
    vector<string> validPicturePaths;
    for(string path : picturePaths){
        if(!isValidFilename(path)){
            std::cout << "\nInvalid filename for: " << path << '\n';
            continue;
        }
        if(!isInNetpbmFormat(path)){
            std::cout << "\nInvalid format for: " << path << " Only .pbm, .pgm and .ppm are supported.\n";
            continue;
        }
        validPicturePaths.push_back(path);
    }
    return validPicturePaths;
}

bool isInNetpbmFormat(const string& imageName){
    string imageExtension = imageName.substr(imageName.rfind('.') + 1);
    return imageExtension == "pbm" || imageExtension == "pgm" || imageExtension == "ppm";
}

bool isValidFilename(const string& filename){
    return filename.find('.') != string::npos;
}
