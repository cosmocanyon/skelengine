#pragma once

#include "Window.h"
#include "Stopwatch.h"

namespace moo {

class Application {
public:
    static constexpr int WIDTH = 1024;
    static constexpr int HEIGHT = 768;

    Application(const char *str);
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();

private:
    const char *execname;
    Window window;
    Stopwatch racer, checkpoint, test;

    void update(const Stopwatch &clock);
    void render(const float alpha);
};

}