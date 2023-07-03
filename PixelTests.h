#include "doctest.h"
#include "Pixel.h"
#include <vector>

TEST_CASE ("Creates valid RGB pixel") {
    const int VALUE = 3, MAX_VAL = 250;
    RGBPixel p(VALUE,VALUE,VALUE,MAX_VAL);
    std::vector<unsigned char> pixelValues;
    pixelValues = p.getPixel();
    for (unsigned char currentValue : pixelValues) {
        REQUIRE(currentValue == VALUE);
    }    
    SUBCASE("Resetting values") {
        const int NEW_VALUE = 255, NEW_MAX = 255;
        p.setRed(NEW_VALUE,NEW_MAX);
        p.setGreen(NEW_VALUE,NEW_MAX);
        p.setBlue(NEW_VALUE,NEW_MAX);
        std::vector<unsigned char> pixelValues;
        pixelValues = p.getPixel();
        for (unsigned char currentValue : pixelValues) {
            CHECK_EQ(currentValue,NEW_VALUE);
        } 
    }
    SUBCASE("Catching incorrectly set values") {
        const int NEW_VALUE = 256, NEW_MAX = 255, BAD_LOW = -5;
        CHECK_THROWS_WITH(p.setRed(NEW_VALUE,NEW_MAX),"Red value greater than max value");
        CHECK_THROWS_WITH(p.setRed(NEW_VALUE,BAD_LOW),"Red value less than 0");
        CHECK_THROWS_WITH(p.setGreen(NEW_VALUE,NEW_MAX),"Green value greater than max value");
        CHECK_THROWS_WITH(p.setGreen(NEW_VALUE,BAD_LOW),"Green value less than 0");
        CHECK_THROWS_WITH(p.setBlue(NEW_VALUE,NEW_MAX),"Blue value greater than max value");
        CHECK_THROWS_WITH(p.setBlue(NEW_VALUE,BAD_LOW),"Blue value less than 0");
        std::vector<unsigned char> pixelValues;
        pixelValues = p.getPixel();
        for (unsigned char currentValue : pixelValues) {
            CHECK_EQ(currentValue,0);
        } 
    }
}

TEST_CASE ("Creates valid Grayscale pixel") {
    const int VALUE = 8, MAX_VAL = 100;
    GrayPixel p(VALUE,MAX_VAL);
    std::vector<unsigned char> pixelValues;
    pixelValues = p.getPixel();
    for (unsigned char currentValue : pixelValues) {
        REQUIRE(currentValue == VALUE);
    }    
    SUBCASE("Resetting values") {
        const int NEW_VALUE = 255, NEW_MAX = 255;
        std::vector<unsigned char> pixelValues;
        pixelValues = p.getPixel();
        for (unsigned char currentValue : pixelValues) {
            CHECK_EQ(currentValue,NEW_VALUE);
        } 
    }
    SUBCASE("Catching incorrectly set values") {
        const int NEW_VALUE = 256, NEW_MAX = 255, BAD_LOW = -5;
        CHECK_THROWS_WITH(p.setIntensity(NEW_VALUE,NEW_MAX),"Gray value greater than max value");
        CHECK_THROWS_WITH(p.setIntensity(NEW_VALUE,BAD_LOW),"Gray value less than 0");

        std::vector<unsigned char> pixelValues;
        pixelValues = p.getPixel();
        for (unsigned char currentValue : pixelValues) {
            CHECK_EQ(currentValue,0);
        } 
    }
}

TEST_CASE ("Creates valid BW pixel") {
    const bool BLACK = true;
    BWPixel p(BLACK);
    std::vector<unsigned char> pixelValues;
    pixelValues = p.getPixel();
    for (unsigned char currentValue : pixelValues) {
        REQUIRE(currentValue == 255);
    }    
    SUBCASE("Resetting values") {
        const bool BLACK = false;
        std::vector<unsigned char> pixelValues;
        pixelValues = p.getPixel();
        for (unsigned char currentValue : pixelValues) {
            CHECK_EQ(currentValue,0);
        } 
    }
}

