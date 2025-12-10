#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Grid {
public:
    Grid() = default;

    std::size_t width() const {
        return width_;
    }
    std::size_t height() const {
        return height_;
    }

    void parse_line(const std::string& line) {
        if(width_ == 0) {
            width_ = line.size();
        }

        std::vector<bool> row;

        for(const char c : line) {
            row.push_back(c == '@');
        }

        data_.push_back(row);
        ++height_;
    }

    std::string to_string() const {
        std::string output;

        for(const auto& row : data_) {
            for(const bool cell : row) {
                output += cell ? '@' : '.';
            }
            output += '\n';
        }

        return output;
    }

    /**
     * Return the number of valid @ cells with 3 or fewer adjacent @ cells.
     */
    std::size_t count_valid_cells(std::size_t max_adjacent, bool remove_cells = false) {
        std::size_t valid_cells_n = 0;
        auto coordinates_to_remove = std::vector<std::pair<std::size_t, std::size_t>>{};

        auto in_bounds = [&](std::size_t x, std::size_t y) { return x >= 0 && x < width_ && y >= 0 && y < height_; };

        for(std::size_t y = 0; y < height_; ++y) {
            for(std::size_t x = 0; x < width_; ++x) {
                if(!data_[y][x])
                    continue;

                std::size_t adjacent_count = 0;

                for(int dy = -1; dy <= 1; ++dy) {
                    for(int dx = -1; dx <= 1; ++dx) {
                        if(dx == 0 && dy == 0)
                            continue;

                        auto nx = x + dx;
                        auto ny = y + dy;

                        if(in_bounds(nx, ny) && data_[ny][nx])
                            ++adjacent_count;
                    }
                }

                if(adjacent_count <= max_adjacent) {
                    ++valid_cells_n;
                    if(remove_cells) {
                        coordinates_to_remove.emplace_back(x, y);
                    }
                }
            }
        }

        if(remove_cells) {
            for(const auto& [x, y] : coordinates_to_remove) {
                data_[y][x] = false;
            }
        }

        return valid_cells_n;
    }

    std::size_t count_removable_cells(std::size_t max_adjacent) {
        size_t total_removed = 0;
        while(true) {
            auto removed_cells = count_valid_cells(max_adjacent, true);
            if(removed_cells == 0)
                break;

            total_removed += removed_cells;
        }
        return total_removed;
    }

private:
    std::size_t width_ = 0;
    std::size_t height_ = 0;
    std::vector<std::vector<bool>> data_ = {};
};

int main() {
    std::string line;

    long long problem_two = 0;
    Grid grid;

    while(std::getline(std::cin, line)) {
        if(line.empty())
            continue;

        grid.parse_line(line);
    }

    std::cout << "Answer 01: " << grid.count_valid_cells(3) << '\n';
    std::cout << "Answer 02: " << grid.count_removable_cells(3) << '\n';
}
