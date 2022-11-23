#include "Application.h"

#include <iostream>
#include <chrono>
#include <thread>

using namespace moo;

Application::Application(const char *str) : 
    execname{str}, window{execname, WIDTH, HEIGHT} 
{}

Application::~Application() {}

void Application::run() {
    SDL_Event e;

    while(!window.isClosing())
    {
        racer.update();
        racer.setTimestampSinceLastUdate(racer.getCurrentTimeMicroseconds() - checkpoint.getCurrentTimeMicroseconds());

        racer.timestamp(); //TODELETE
        checkpoint.timestamp(); //TODELETE

        while(SDL_PollEvent(&e) != 0)
        {
            window.handle(e);
            // player1.handle(e);
            // player2.handle(e);
            // etc...
        }

        int count = 0; //TODELETE
        
        while (racer.getCurrentTimeMicroseconds() - checkpoint.getCurrentTimeMicroseconds() > Stopwatch::TIMESTEP30_US)
        {
            // update physics
            update(checkpoint);

            //TODELETE
            if(count == 0) {
                std::this_thread::sleep_for(std::chrono::microseconds(rand() % 33333 + 16666));
                count++;
            }

            //checkpoint.updateByCount(Stopwatch::COUNTSTEP30); //TODELETE
            checkpoint.updateByTimeStep(Stopwatch::TIMESTEP30_US);
        }

        //TODO(): store interpolation in an object state to pass to render???
        uint64_t currentTime = racer.getCurrentTimeMicroseconds();
        uint64_t currentUpdateTime = checkpoint.getCurrentTimeMicroseconds();
        uint64_t nextupdate = (checkpoint.getCurrentTimeMilliseconds() + Stopwatch::TIMESTEP30_US);
        float interpolation = ((currentTime - currentUpdateTime) * 1) * (1.0f / Stopwatch::TIMESTEP30_US);

        // render
        render(interpolation); 
    }
}

void Application::update(const Stopwatch &clock) {
    std::cout << "updating...\n"; //TODELETE
}

void Application::render(const float alpha) {
    std::cout << "interpolation value: " << alpha << "\n"; //TODELETE
}