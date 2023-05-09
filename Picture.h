#pragma once

#include "Pixel.h"
#include <string>
#include <vector>
#include <stdexcept>
using std::vector;
using std::string;

enum class Type {
    invalid,
    P1,
    P2,
    P3
};

class Picture {
private:
    string name;
    Type type;
    short maxValue;
    vector<vector<Pixel*>> pixels;
    vector<string> transformation;

public:

    Picture(const string& filename) {
        // Read the file
        // Check if the file is valid
        // If it is valid, read the file and create the picture
        // If it is not valid, throw an exception and free the memory allocated for the pixels
        // with:  throw std::runtime_error("Some message");
    }

    ~Picture() {
        // Free the memory allocated for the pixels
    }

};



