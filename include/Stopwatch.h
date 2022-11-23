#pragma once

#include "SDL.h"

namespace moo {

class Stopwatch {
public: 
    static const uint64_t FREQUENCY_COUNT; // counts per seconds of the machine
    static constexpr uint64_t MILLI_MS {1000};
    static constexpr uint64_t MICRO_US {1000000};
    static constexpr uint64_t TIMESTEP15_US {66666}; // 1/15 = 15fps
    static constexpr uint64_t TIMESTEP30_US {33333}; // 1/30 = 30fps
    static constexpr uint64_t TIMESTEP60_US {16666}; // 1/60 = 60fps
    static constexpr uint64_t TIMESTEP120_US {8333}; // 1/120 = 120fps
    static const uint64_t COUNTSTEP15, COUNTSTEP30, COUNTSTEP60, COUNTSTEP120; // dependency on FREQUENCY_COUNT
    static constexpr float DELTATIME15 {TIMESTEP15_US * (1.0f / MICRO_US)};
    static constexpr float DELTATIME30 {TIMESTEP30_US * (1.0f / MICRO_US)};
    static constexpr float DELTATIME60 {TIMESTEP60_US * (1.0f / MICRO_US)};
    static constexpr float DELTATIME120 {TIMESTEP120_US * (1.0f / MICRO_US)};

private:
    const uint64_t startRealTime;
    uint64_t previousRealTime;
    uint64_t previousCount, currentCount;
    uint64_t previousUpdateMilliseconds, currentUpdateMilliseconds;
    uint64_t previousUpdateMicroseconds, currentUpdateMicroseconds;
    float previousUpdateSeconds, currentUpdateSeconds;

    uint64_t frame;

    inline static uint64_t countElapsedSinceLastUpdate = 0; 
    inline static float timeElapsedSinceLastUpdate = 0.0f;
    
public:
    Stopwatch();
    ~Stopwatch();

    void update();
    void updateByCount(uint64_t amount);
    void updateByTimeStep(uint64_t timestep);
    
    inline uint64_t getPreviousTimeMilliseconds() const { return previousUpdateMilliseconds; }
    inline uint64_t getCurrentTimeMilliseconds() const { return currentUpdateMilliseconds; }
    inline uint64_t getPreviousTimeMicroseconds() const { return previousUpdateMicroseconds; }
    inline uint64_t getCurrentTimeMicroseconds() const { return currentUpdateMicroseconds; }
    inline float getPreviousTimeSeconds() const { return previousUpdateSeconds; }
    inline float getCurrentTimeSeconds() const { return currentUpdateSeconds; }
    inline uint64_t getCurrentFrame() const { return frame; }

    inline uint64_t getCountElapsedSinceLastUpdate() const { return countElapsedSinceLastUpdate; }
    inline float getTimeElapsedSinceLastUpdate() const { return timeElapsedSinceLastUpdate; }
    inline void setTimestampSinceLastUdate(uint64_t time) { 
        timeElapsedSinceLastUpdate = toSecondsF(time, MICRO_US);
        countElapsedSinceLastUpdate = timeToCount(time, MICRO_US);
    }

    void timestamp() const;
    
    static uint64_t timeToCount(uint64_t time, uint64_t timeUnit);
    
private:
    uint64_t getCurrentRealTime() const; // system tick units
    uint64_t countToTime(uint64_t countAmount, uint64_t timeUnit) const;
    float countToTimeF(uint64_t countAmount, uint64_t timeUnit) const;
    float toSecondsF(uint64_t time, uint64_t timeUnit) const;    
};  

} // namespace moo