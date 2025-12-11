#include <algorithm>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class MathMatrix {
public:
    MathMatrix() = default;

    void parse_line(std::string_view line) {
        auto elems = split_row(line);

        if(elems.size() && (elems[0] == "+" || elems[0] == "*")) {
            operations_ = std::move(elems);
            return;
        }

        std::vector<uint64_t> nums;
        nums.reserve(elems.size());
        for(auto& e : elems) {
            nums.push_back(std::stoull(std::string(e)));
        }

        data_.push_back(std::move(nums));
    }
    uint64_t solve_problem_one() const {
        if(data_.empty())
            return 0;

        const size_t rows = data_.size();
        const size_t cols = data_[0].size();

        uint64_t result = 0;

        for(size_t x = 0; x < cols; ++x) {
            char operation = operations_[x][0];
            uint64_t col_result = (operation == '*') ? 1 : 0;

            for(size_t y = 0; y < rows; ++y) {
                if(operation == '*')
                    col_result *= data_[y][x];
                else
                    col_result += data_[y][x];
            }

            result += col_result;
        }

        return result;
    }

private:
    std::vector<std::string_view> split_row(const std::string_view line) {
        std::vector<std::string_view> elements;
        size_t start = 0;
        size_t end = 0;

        while(true) {
            end = line.find(' ', start);
            if(end == std::string_view::npos) {
                elements.push_back(line.substr(start));
                break;
            }

            if(end > start) {
                elements.push_back(line.substr(start, end - start));
            }
            start = end + 1;
        }

        return elements;
    }

private:
    std::vector<std::vector<uint64_t>> data_;
    std::vector<std::string_view> operations_;
};

int main() {
    std::string line;

    MathMatrix matrix;

    while(std::getline(std::cin, line)) {
        matrix.parse_line(line);
    }

    std::cout << "Result of problem one: " << matrix.solve_problem_one() << "\n";
}
