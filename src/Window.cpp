#include "Window.h"

// std
#include <iostream>

using namespace moo;

Window::Window(std::string title, int width, int height) : 
    window{nullptr}, title{title},
    width{width}, height{height},
    bQuit{false} 
{
    uint32_t subsys = SDL_INIT_VIDEO;
    if(SDL_Init(subsys) < 0) {
        std::string error = SDL_GetError();
        throw std::runtime_error("Failed to initialize SDL. SDL Error: " + error);
    }

    uint32_t opt = SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, 
        opt
    );

    if(!window) {
        std::string error = SDL_GetError();
        throw std::runtime_error("Failed to create SDL Window. SDL Error: " + error);
    }

    SDL_SetWindowMinimumSize(window, 256, 144);
}

Window::~Window() {
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

void Window::handle(SDL_Event &e) {
    switch (e.type)
    {
    case SDL_QUIT:
        bQuit = true;
        break;
    
    default:
        break;
    }
}