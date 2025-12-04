#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& s, char delim);
bool is_cooked_p1(const std::string& cookee);
bool is_cooked_p2(const std::string& cookee);

int main() {
    std::string line;

    while(std::getline(std::cin, line)) {
        if(line.empty())
            continue;

        long long answer_p1 = 0;
        long long answer_p2 = 0;
        auto parts = split(line, ',');

        for(const auto& part : parts) {
            auto range = split(part, '-');
            if(range.size() != 2) {
                std::cerr << "Bad range: " << part << "\n";
                continue;
            }

            long long left = std::stoll(range[0]);
            long long right = std::stoll(range[1]);

            std::string cookee;
            for(long long i = left; i <= right; ++i) {
                cookee = std::to_string(i);
                if(is_cooked_p1(cookee)) {
                    answer_p1 += i;
                }

                if(is_cooked_p2(cookee)) {
                    answer_p2 += i;
                }
            }
        }

        std::cout << "Answer: " << answer_p1 << '\n';
        std::cout << "Answer 2: " << answer_p2 << '\n';
    }
}

bool is_cooked_p1(const std::string& cookee) {
    size_t n = cookee.size();

    if(n % 2 != 0) return false;
    auto mid = n / 2;
    return cookee.substr(0, mid) == cookee.substr(mid);
}

bool is_cooked_p2(const std::string& cookee) {
    size_t n = cookee.size();

    for(size_t len = 1; len <= n / 2; ++len) {
        if(n % len != 0)
            continue;

        bool is_valid = true;
        for(size_t i = len; i < n; i += len) {
            if(cookee.compare(0, len, cookee, i, len) != 0) {
                is_valid = false;
                break;
            }
        }
        if(is_valid) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string cur;

    for(char c : s) {
        if(c == delim) {
            out.push_back(cur);
            cur.clear();
        } else {
            cur += c;
        }
    }
    out.push_back(cur);
    return out;
}