#include <iostream>
#include "Picture.h"

int main() {
    Pixel *pixel = new RGBPixel(0, 0, 0, 2);
    delete pixel;
    std::cout << "Hello, World!" << std::endl;

    return 0;
}