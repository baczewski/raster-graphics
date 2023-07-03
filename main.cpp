#include <iostream>
#include "Picture.h"
#include "Transformation.h"

int main() {
    Picture* pic = new Picture("C:\\Users\\Martin\\Desktop\\raster-cpp\\raster-graphics\\pic.pbm");
    auto pixels = pic->getPixels();

    // Transformation::horizontal(pixels);
    // Transformation::monochrome(pixels, 1, Type::P1);

    for (int i = 0; i < pixels.size(); i++)
    {
        for (int j = 0; j < pixels[i].size(); j++)
        {
            pixels[i][j]->print();
        }

        std::cout << std::endl;
    }

    return 0;
}