#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

class Dial {
public:
    Dial() {}

    void parse_instruction(const std::string& instruction) {
        char direction = instruction[0];
        int amount = std::stoi(instruction.substr(1));

        if(amount == 0) {
            return;
        }

        for(int rotation = 0; rotation < amount; ++rotation) {
            if(direction == 'L') {
                _current_position = (_current_position - 1 + _max_position) % _max_position;
            } else if(direction == 'R') {
                _current_position = (_current_position + 1) % _max_position;
            }
            if(_current_position == 0) {
                ++_password;
            }
        }
    }

    int get_position() const {
        return _current_position;
    }

    int get_password() const {
        return _password;
    }

private:
    int _current_position = 50;
    int _max_position = 100;
    int _password = 0;
};

int main() {
    std::string line;
    Dial dial{};

    while(std::getline(std::cin, line)) {
        if(line.empty())
            continue;

        dial.parse_instruction(line);
    }

    std::cout << "Final Position: " << dial.get_position() << std::endl;
    std::cout << "Password: " << dial.get_password() << std::endl;
}
