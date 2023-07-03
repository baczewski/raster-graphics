#include <iostream>
#include "Engine.h"
#include "Picture.h"
#include "Transformation.h"

int main() {
    Engine* engine = Engine::getInstance();
    engine->run();

    return 0;
}