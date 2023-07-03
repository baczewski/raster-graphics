#include "doctest.h"
#include "Picture.h"
#include "Pixel.h"

TEST_CASE ("Creates valid P1 picture") {
    const int VALUE = 255;
    Picture p("p1.txt");
    CHECK(p.getName() == "p1.txt");
    enum Type type = P1;
    CHECK(p.getType() == type);
    std::vector<std::vector<Pixel*>> pixels;
    pixels = p.getPixels();
    for (std::vector<Pixel*> row : pixels) {
        for (Pixel* currentPixel : row) {
            REQUIRE(currentPixel->getPixel() == VALUE);
        }
    }
}
