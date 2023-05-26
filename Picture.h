#pragma once

#include "Pixel.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <chrono>
using std::vector;
using std::string;
using std::ifstream;
using std::cerr;

enum class Type {
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

    void executeTransformations();
public:

    Picture(const string& filename);
    ~Picture();

    void addTransformation(const string& transformation);
    void undoTransformation();
    void clearTransformations();

    void save() const;
};



