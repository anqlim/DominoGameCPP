#include "profile.h"

Profiler g_profiler;

Profiler::Scope::Scope(Profiler& profiler, const std:: string& name)
        : profiler_(profiler), name_(name), start_(Profiler::Clock::now()) {}

Profiler::Scope::~Scope() {
    auto end = Profiler::Clock::now();
    double duration = std::chrono::duration<double>(end - start_).count();
    profiler_.record(name_, duration);
}

void Profiler::record(const std::string& name, double duration_sec) {
    entries_[name].total_time += duration_sec;
    entries_[name].calls++;
}

void Profiler::print() {
    if (entries_.empty()) return;
    std::cout << "\n=== PROFILING RESULTS ===\n";
    for (const auto& [name, entry] : entries_) {
        double avg_ms = (entry.total_time / entry.calls) * 1000.0;
        std::cout << std::left << std::setw(15) << name
                  << " | total: " << std::fixed << std::setprecision(6) << std::setw(10) << entry.total_time << " s"
                  << " | calls: " << std::setw(5) << entry.calls
                  << " | avg: " << std::setw(10) << avg_ms << " ms\n";
    }
}

void Profiler::reset() {
    entries_.clear();
}