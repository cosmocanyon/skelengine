#include "Application.h"

// std
#include <iostream>

int main(int argc, char *argv[]) {

    moo::Application game{argv[0]};

    try
    {
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}