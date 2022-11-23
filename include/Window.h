#pragma once

#include <SDL.h>

//std
#include <string>

namespace moo {

class Window {
private:
    SDL_Window* window;
    std::string title;
    int width, height;
    bool bQuit;

public:
    Window(std::string title, int width, int height);
    ~Window();

    void handle(SDL_Event &e);

    inline bool isClosing() { return bQuit; }
};

}