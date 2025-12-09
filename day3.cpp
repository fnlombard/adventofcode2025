#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>

inline uint8_t digit(char c) {
    return static_cast<uint8_t>(c - '0');
}

/**
 * Extract largest `range` digits while preserving relative order.
 * (Greedy sliding window)
 */
template <typename T = uint64_t> T calculate_joltage_dynamic(const std::string& line, uint8_t range) {
    const size_t n = line.size();
    size_t pos = 0;
    T value = 0;

    for(uint8_t cursor = 0; cursor < range; ++cursor) {
        size_t choices_left = range - 1 - cursor;
        size_t end = n - choices_left;

        uint8_t best = 0;
        size_t best_idx = pos;

        for(size_t i = pos; i < end; ++i) {
            uint8_t d = digit(line[i]);
            if(d > best) {
                best = d;
                best_idx = i;
            }
        }

        value = value * 10 + best;
        pos = best_idx + 1;
    }

    return value;
}

int main() {
    std::string line;

    long long problem_one = 0, problem_two = 0;
    const uint8_t range_one = 2, range_two = 12;

    while(std::getline(std::cin, line)) {
        if(line.empty())
            continue;

        problem_one += calculate_joltage_dynamic(line, range_one);
        problem_two += calculate_joltage_dynamic(line, range_two);
    }

    std::cout << "Answer 01: " << problem_one << '\n';
    std::cout << "Answer 02: " << problem_two << '\n';
}
