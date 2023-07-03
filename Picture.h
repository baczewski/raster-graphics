#pragma once

#include "Pixel.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <chrono>
#include <filesystem>
#include <cassert>
#include <iterator>

using std::vector;
using std::string;
using std::ifstream;
using std::cerr;

enum Type {
    Invalid,
    P1,
    P2,
    P3
};

class Picture {
private:
    string name;
    Type type;
    struct Size {
        int width;
        int height;
    } size;
    unsigned char maxValue;
    vector<vector<Pixel*>> pixels;
    vector<string> transformations;

    struct DateTime {
        static const string& getDateTime();
    };

    void setName(const string& name);
    Type setType(const string& type);
    void setSize(const string& size);
    void setP1(ifstream& read);
    void setP2(ifstream& read);
    void setP3(ifstream& read);
    
    bool isComment(const string& line) const;
    const string& typeToString() const;

    // void executeTransformations();
public:

    Picture(const string& filename);
    Picture(const Picture& other);
    ~Picture();

    void addTransformation(const string& transformation);
    void undoTransformation();
    void clearTransformations();

    vector<vector<Pixel*>> getPixels() const;
    vector<string>& getTransformations();
    const Type& getType() const;
    const string& getName() const;
    const short getMaxValue() const;

    void print() const;
    void save(const string& filePath) const;
};



