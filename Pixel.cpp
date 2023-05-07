#include "Pixel.h"

// RGBPixel

RGBPixel::RGBPixel(unsigned char r, unsigned char g, unsigned char b, const unsigned char maxVal) {
    try {
        setRed(r, maxVal);
        setGreen(g, maxVal);
        setBlue(b, maxVal);
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

void RGBPixel::setRed(unsigned char r, const unsigned char maxVal) {
    if (r > maxVal) {
        red = maxVal;
        throw std::out_of_range("Red value greater than max value");
    }
    if (r < 0) {
        red = 0;
        throw std::out_of_range("Red value less than 0");
    }
    red = r;
}

void RGBPixel::setGreen(unsigned char g, const unsigned char maxVal)  {
    if (g > maxVal) {
        green = maxVal;
        throw std::out_of_range("Green value greater than max value");
    }
    if (g < 0) {
        green = 0;
        throw std::out_of_range("Green value less than 0");
    }
    green = g;
}

void RGBPixel::setBlue(unsigned char b, const unsigned char maxVal)  {
    if (b > maxVal) {
        blue = maxVal;
        throw std::out_of_range("Blue value greater than max value");
    }
    if (b < 0) {
        blue = 0;
        throw std::out_of_range("Blue value less than 0");
    }
    blue = b;
}

void RGBPixel::print() const {
    std::cout << (int)red << " " << (int)green << " " << (int)blue << '\t';
}

std::vector<unsigned char> RGBPixel::getPixel() const {
    std::vector<unsigned char> pixel;
    pixel.push_back(red);
    pixel.push_back(green);
    pixel.push_back(blue);
    return pixel;
}

std::ostream& RGBPixel::operator<<(std::ostream& os) const {
    os << (int)red << " " << (int)green << " " << (int)blue << " ";
    return os;
}

// GrayscalePixel

GrayPixel::GrayPixel(unsigned char i, const unsigned char maxVal) {
    try {
        setIntensity(i, maxVal);
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}

void GrayPixel::setIntensity(unsigned char i, const unsigned char maxVal) {
    if (i > maxVal) {
        intensity = maxVal;
        throw std::out_of_range("Gray value greater than max value");
    }
    if (i < 0) {
        intensity = 0;
        throw std::out_of_range("Gray value less than 0");
    }
    intensity = i;
}

void GrayPixel::print() const {
    std::cout << (int)intensity << '\t';
}

std::vector<unsigned char> GrayPixel::getPixel() const {
    std::vector<unsigned char> pixel;
    pixel.push_back(intensity);
    return pixel;
}

std::ostream& GrayPixel::operator<<(std::ostream& os) const {
    os << (int)intensity << " ";
    return os;
}

// BWPixel

BWPixel::BWPixel(bool black) {
    setBlack(black);
}

void BWPixel::setBlack(bool black) {
    isBlack = black;
}

void BWPixel::print() const {
    std::cout << isBlack << '\t';
}

std::vector<unsigned char> BWPixel::getPixel() const {
    std::vector<unsigned char> pixel;
    pixel.push_back(isBlack ? 0 : 255);
    return pixel;
}

std::ostream& BWPixel::operator<<(std::ostream& os) const {
    os << isBlack << " ";
    return os;
}
