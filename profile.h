#ifndef PROFILE_H
#define PROFILE_H

#include <string>
#include <chrono>
#include <unordered_map>
#include <iostream>
#include <iomanip>

class Profiler {
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    class Scope {
    public:
        Scope(Profiler& profiler, const std::string& name);
        ~Scope();

    private:
        Profiler& profiler_;
        std::string name_;
        TimePoint start_;
    };

    void record(const std::string& name, double duration_sec);
    void print();
    void reset();

private:
    struct Entry {
        double total_time = 0.0;
        int calls = 0;
    };
    std::unordered_map<std::string, Entry> entries_;
};

extern Profiler g_profiler;

#define PROFILE_SCOPE(name) Profiler::Scope __profiler_scope(g_profiler, name)

#endif
