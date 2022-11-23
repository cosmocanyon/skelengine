#include "Stopwatch.h"

#include <iostream>

using namespace moo;

const uint64_t Stopwatch::FREQUENCY_COUNT = SDL_GetPerformanceFrequency();
const uint64_t Stopwatch::COUNTSTEP15 = timeToCount(TIMESTEP15_US, MICRO_US);
const uint64_t Stopwatch::COUNTSTEP30 = timeToCount(TIMESTEP30_US, MICRO_US);
const uint64_t Stopwatch::COUNTSTEP60 = timeToCount(TIMESTEP60_US, MICRO_US);
const uint64_t Stopwatch::COUNTSTEP120 = timeToCount(TIMESTEP120_US, MICRO_US);

Stopwatch::Stopwatch() :
    startRealTime{SDL_GetPerformanceCounter()}, previousRealTime{startRealTime},  
    previousCount{0}, currentCount{0},
    previousUpdateMilliseconds{0}, currentUpdateMilliseconds{0},
    previousUpdateMicroseconds{0}, currentUpdateMicroseconds{0},
    previousUpdateSeconds{0.0f}, currentUpdateSeconds{0.0f},
    frame{0}
{}

Stopwatch::~Stopwatch() {}

uint64_t Stopwatch::getCurrentRealTime() const {
    return SDL_GetPerformanceCounter(); 
}

void Stopwatch::update() {
    uint64_t now = getCurrentRealTime();
    uint64_t delta = now - previousRealTime;
    previousRealTime = now;

    updateByCount(delta);
}

void Stopwatch::updateByCount(uint64_t amount) {
    previousCount = currentCount;
    currentCount += amount;

    previousUpdateMilliseconds = currentUpdateMilliseconds;
    currentUpdateMilliseconds = countToTime(currentCount, MILLI_MS);
    previousUpdateMicroseconds = currentUpdateMicroseconds;
    currentUpdateMicroseconds = countToTime(currentCount, MICRO_US);
    previousUpdateSeconds = currentUpdateSeconds;
    currentUpdateSeconds = countToTimeF(currentCount, 1);

    frame++;
}

void Stopwatch::updateByTimeStep(uint64_t timestep) {
    previousCount = currentCount;
    currentCount += timestep;

    previousUpdateMilliseconds = currentUpdateMilliseconds;
    currentUpdateMilliseconds = currentCount;
    previousUpdateMicroseconds = currentUpdateMicroseconds;
    currentUpdateMicroseconds = currentCount;
    previousUpdateSeconds = currentUpdateSeconds;
    currentUpdateSeconds = toSecondsF(currentCount, MICRO_US);

    frame++;
}

uint64_t Stopwatch::countToTime(uint64_t countAmount, uint64_t timeUnit) const {
    return (countAmount * timeUnit) / FREQUENCY_COUNT;
}

float Stopwatch::countToTimeF(uint64_t countAmount, uint64_t timeUnit) const {
    return (countAmount * timeUnit) * ( 1.0f / FREQUENCY_COUNT);
}

uint64_t Stopwatch::timeToCount(uint64_t time, uint64_t timeUnit) {
    return (time * FREQUENCY_COUNT) / timeUnit;
}

float Stopwatch::toSecondsF(uint64_t time, uint64_t timeUnit) const {
    return time * (1.0f / timeUnit);
}

void Stopwatch::timestamp() const {
    std::cout 
        << "frame: " << getCurrentFrame() << "; "
        << "time current: " << getCurrentTimeSeconds() << "; " 
        << "since update: " << getTimeElapsedSinceLastUpdate() << ";\n"
    ;
}