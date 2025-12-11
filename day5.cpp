#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Ingredients {
public:
    Ingredients() = default;

        struct Range {
        uint64_t start;
        uint64_t end;
    };

    void parse_id_line(const std::string& line) {
        size_t dash_pos = line.find('-');
        if(dash_pos == std::string::npos)
            return;

        auto first = std::stoull(line.substr(0, dash_pos));
        auto second = std::stoull(line.substr(dash_pos + 1));

        fresh_ids_.emplace_back(first, second);
    }

    void parse_ingredient_line(const std::string& line) {
        auto id = std::stoull(line);

        for(const auto& range : fresh_ids_) {
            if(id >= range.start && id <= range.end) {
                ++fresh_ingredient_count_;
                break;
            }
        }
    }

    uint64_t fresh_ingredient_count() const {
        return fresh_ingredient_count_;
    }

private:
    std::vector<Range> fresh_ids_ = {};
    uint64_t fresh_ingredient_count_ = 0;
};

int main() {
    std::string line;
    Ingredients ingredients;

    bool reading_ranges = true;

    while(std::getline(std::cin, line)) {
        if(line.empty()) {
            reading_ranges = false;
            continue;
        }

        if(reading_ranges)
            ingredients.parse_id_line(line);
        else
            ingredients.parse_ingredient_line(line);
    }

    std::cout << "Answer 01: " << ingredients.fresh_ingredient_count() << '\n';
}
