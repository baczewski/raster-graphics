#include "Picture.h"

Picture::Picture(const string& filename) {

    setName(filename);

    try
    {
        // Check if the file exists
        if (!std::filesystem::exists(filename)) {
            throw std::invalid_argument("File does not exist.");
        }

        // Create a file stream object
        std::ifstream file(filename);

        // Check if the file stream object is in a good state
        if (!file.good()) {
            throw std::invalid_argument("File is not in a good state.");
        }
    } catch(const std::exception& e) {
        type = Type::Invalid;
        cerr << e.what() << '\n';
        return;
    }
    // Open the file
    std::ifstream file(filename);
    string line;

    getline(file, line);
    type = setType(line);
    if (type == Type::Invalid) {
        cerr << "Invalid type" << '\n';
        return;
    }

    while (getline(file, line)) {
        if (isComment(line)) {
            continue;
        }
        if (line.empty()) {
            continue;
        }
        if(line.find(" ") != string::npos) {
            setSize(line);
            break;
        }
    }

    assert(this->size.width >= 0 && this->size.height >= 0);

    switch (type)
    {
    case Type::P1:
        setP1(file);
        break;
    case Type::P2:
        setP2(file);
        break;
    case Type::P3:
        setP3(file);
        break;
    default:
        cerr << "Invalid type" << '\n';
        break;
    }
}

Picture::Picture(const Picture& other) {
    this->name = other.name;
    this->type = other.type;
    this->size = other.size;
    this->maxValue = other.maxValue;
    this->pixels = other.getPixels();
    this->transformations = other.transformations;
}

Picture::~Picture() {
    if (type != Type::Invalid) {
        for (auto rowIt = pixels.begin(); rowIt != pixels.end(); ++rowIt) {
            for (auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
                delete *colIt;
            }
        }
    }
    pixels.clear();
}

void Picture::setName(const string& name) {
    try {
        if(name.empty())
            throw std::invalid_argument("Name is empty.");
    } catch(const std::exception& e) {
        cerr << e.what() << '\n';
        this->name = "invalidName";
        return;
    }
    this->name = name;
}

Type Picture::setType(const string& name) {
    if (name == "P1") {
        return Type::P1;
    }
    else if (name == "P2") {
        return Type::P2;
    }
    else if (name == "P3") {
        return Type::P3;
    }
    else {
        return Type::Invalid;
    }
}

void Picture::setSize(const string& size) {
    try {
        this->size.width = stoi(size.substr(0, size.find(" ")));
        this->size.height = stoi(size.substr(size.find(" ")));
    } catch(const std::exception& e) {
        e.what();
        this->size.width = 0;
        this->size.height = 0;
        return;
    }
}

void Picture::setP1(ifstream& file) {
    string line;
    while (getline(file, line))
    {
        vector<Pixel *> row;
        for (char c : line) {
            if (c == '0') {
                row.push_back(new BWPixel(false));
            }
            else if (c == '1') {
                row.push_back(new BWPixel(true));
            }
            else if (c == ' ') {
                continue;
            } else {
                cerr << "Invalid pixel value: " << c << '\n';
            }
        }
        pixels.push_back(row);
    }
    assert(pixels.size() == size.height);
    assert(pixels[0].size() == size.width);
}

void Picture::setP2(ifstream& file) {
    string line;

    getline(file, line);
    maxValue = static_cast<unsigned char>(stoi(line));

    while (getline(file, line)) {
        // The following line split a string into a vector of string
        std::stringstream ss(line);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

        vector<Pixel *> row;
        for (string s : vstrings) {
            row.push_back(new GrayPixel(static_cast<unsigned char>(stoi(s)), maxValue));
        }
        pixels.push_back(row);
    }
    assert(pixels.size() == size.height);
    assert(pixels[0].size() == size.width);
}

void Picture::setP3(ifstream& file) {
    string line;

    getline(file, line);
    maxValue = static_cast<unsigned char>(stoi(line));

    while (getline(file, line)) {
        // The following line split a string into a vector of string
        std::stringstream ss(line);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vstrings(begin, end);
        std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

        vector<Pixel *> row;
        for (int i = 0; i < vstrings.size() - 2; i += 3) {
            row.push_back(new RGBPixel(static_cast<unsigned char>(stoi(vstrings[i])),
                                         static_cast<unsigned char>(stoi(vstrings[i + 1])),
                                         static_cast<unsigned char>(stoi(vstrings[i + 2])),
                                         maxValue));
        }
        pixels.push_back(row);
    }
    assert(pixels.size() == size.height);
    assert(pixels[0].size() == size.width);
}

void Picture::addTransformation(const string& transformation) {
    transformations.push_back(transformation);
}

void Picture::undoTransformation() {
    if(!transformations.empty()) {
        transformations.pop_back();
    }
}

void Picture::clearTransformations() {
    if(!transformations.empty()) {
        transformations.clear();
    }
}

bool Picture::isComment(const string& line) const {
    return line[0] == '#';
}

const string& Picture::typeToString() const {
    switch(type) {
        case Type::P1:
            return "P1";
        case Type::P2:
            return "P2";
        case Type::P3:
            return "P3";
        default: 
            return "NULL";
    }
}

const string& Picture::DateTime::getDateTime() {
    auto now = std::chrono::system_clock::now();
    
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&currentTime), "%Y-%m-%d_%H-%M-%S");
    static std::string dateTimeString = "_" + ss.str();
    
    return dateTimeString;
}

vector<vector<Pixel*>> Picture::getPixels() const {
    // make a copy of the pixels as now if we return pixels it will still point at the same location in memory
    vector<vector<Pixel*>> copyPixels;
    for(vector<Pixel*> row : pixels) {
        vector<Pixel*> copyRow;
        for(Pixel* pixel : row) {
            copyRow.push_back(pixel->clone());
        }
        copyPixels.push_back(copyRow);
    }

    return copyPixels;
}

vector<string>& Picture::getTransformations() {
    return transformations;
}

const Type& Picture::getType() const {
    return type;
}

const string& Picture::getName() const {
    return name;
}

const short Picture::getMaxValue() const {
    return maxValue;
}

void Picture::print() const {
    for(vector<Pixel*> row : pixels) {
        for(Pixel* pixel : row) {
            pixel->print();
        }
        std::cout << '\n';
    }
}

void Picture::save(const string& filePath = "") const {

    if(type == Type::Invalid){
        cerr << "Picture: " << name << " has invalid type and will not be saved!." << '\n';
        return;
    }

    string newName = filePath + name + DateTime::getDateTime();

    if (std::filesystem::exists(newName)) {
        cerr << "File already exists!" << '\n';
        return;
    }

    std::ofstream file(newName);

    try
    {
        if (!file.good())
        {
            throw std::invalid_argument("File is not in a good state.");
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
        file.close();
        return;
    }

    file << typeToString() << '\n';
    file << size.width << " " << size.height << '\n';
    if(type == Type::P2 || type == Type::P3) {
        file << maxValue << '\n';
    }
    
    for(vector<Pixel*> row : pixels) {
        for(Pixel* pixel : row) {
            file << pixel << ' ';
        }
        file << '\n';
    }
    file.close();
}
