#include "Pixel.h"

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
