#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

class Relevant {
public:
    int step;
    std::pair<int, int> hw_start;
    int c = 0;
    std::vector<std::vector<std::vector<int>>> data;
    std::vector<std::vector<int>> colors;

    Relevant() = default;

    Relevant(int s) {
        step = s;
    }

    Relevant& operator =(Relevant const& other) = default;

    bool operator ==(const Relevant& other) const {
        return step == other.step && data == other.data && colors == other.colors;
    }

    bool operator !=(const Relevant& other) const {
        return !(*this == other);
    }

    bool operator <(const Relevant& other) const {
        return data < other.data;
    }
};

bool compare(const std::pair<Relevant, int>& f, const std::pair<Relevant, int>& s) {
    return f.second > s.second;
}

int main() {
    std::ifstream input;
    std::map<std::pair<int, int>, int> xy_freq;
    std::map<Relevant, int> library;
    std::vector<Relevant> t;
    std::vector<int> steps(38);
    input.open("C:\\Users\\birsh\\Desktop\\output.txt");
    for (int i = 0; i != 5059; ++i) {
        int cycle_step, step, x, y, color;
        input >> cycle_step >> step >> x >> y;
        xy_freq[{x, y}] += 1;
        steps[cycle_step - 1] += 1;
        Relevant temp(cycle_step);
        temp.hw_start.first = x;
        temp.hw_start.second = y;
        temp.colors.resize(3, std::vector<int>(3));
        for (int j = 0; j != 3; ++j) {
            for (int k = 0; k != 3; ++k) {
                input >> temp.colors[j][k];
            }
        }
        int lines, brakes;
        input >> lines >> brakes;
        temp.data.resize(brakes);
        for (int line = 0; line != lines; ++line) {
            input >> x >> y >> color;
            if (x == 0 && y == 0 && color == 9) {
                ++temp.c;
            } else {
                std::vector<int> cell = {x, y, color};
                if (!cell.empty()) {
                    temp.data[temp.c].push_back(cell);
                }
            }
        }
        t.push_back(temp);
    }
    input.close();
    for (int i = 0; i != 38; ++i) {
        std::cout << "Step\t" << i + 1 << ":\t" << steps[i] << '\n';
    }
    std::cout << '\n';
    for (auto elem :xy_freq) {
        std::cout << "From x = " << elem.first.first << " and y = " << elem.first.second << ":\t" << elem.second << '\n';
    }
    for (auto elem : t) {
        library[elem] += 1;
    }
    std::vector<std::pair<Relevant, int>> ans;
    for (auto elem : library) {
        ans.emplace_back(elem);
    }
    std::pair<Relevant, int> max1, max2, max3;
    for (auto elem : ans) {
        if (elem.second >= max1.second) {
            max3.second = max2.second;
            max3.first = max2.first;
            max2.first = max1.first;
            max2.second = max1.second;
            max1.second = elem.second;
            max1.first = elem.first;
        } else if (elem.second >= max2.second) {
            max3.first = max2.first;
            max3.second = max2.second;
            max2.first = elem.first;
            max2.second = elem.second;
        } else if (elem.second >= max3.second) {
            max3.second = elem.second;
            max3.first = elem.first;
        }
    }
    for (auto elem : {max1, max2, max3}) {
        std::cout << '\n' << "Highway has started over the step " << elem.first.step << '\n';
        std::cout << elem.second << " times" << '\n' << '\n';
        std::map<std::pair<int, int>, int> field;
        for (int i = 0; i != 3; ++i) {
            for (int j = 0; j != 3; ++j) {
                field[{i - 1, j - 1}] = elem.first.colors[i][j];
            }
        }
        for (int i = -6; i <= 6; ++i) {
            for (int j = -6; j <= 6; ++j) {
                if (field.find({i, j}) != field.end()) {
                    std::cout << field[{i, j}];
                } else {
                    if (i == 0) {
                        std::cout << '-';
                    } else if (j == 0) {
                        std::cout << '|';
                    } else {
                        std::cout << ' ';
                    }
                }
                std::cout << ' ';
            }
            std::cout << '\n' << '\n';
        }
        std::cout << "Starting field is marked with 7" << '\n';
        for (int k = 0; k != elem.first.c; ++k) {
            if (k == elem.first.c - 1) {
                std::cout << "Highway has started from x = " << elem.first.hw_start.first << " and y = " << elem.first.hw_start.second << ", is pointed with color 9" << '\n';
            }
            std::cout << "Out/in № " << k + 1 << '\n';
            field.clear();
            field[elem.first.hw_start] = 9;
            int max_x = 5, max_y = 5;
            for (int i = 0; i != 3; ++i) {
                for (int j = 0; j != 3; ++j) {
                    field[{i - 1, j - 1}] = 7;
                }
            }
            for (auto el : elem.first.data[k]) {
                field[{el[0], el[1]}] = el[2];
                if (abs(el[0]) > max_x) {
                    max_x = abs(el[0]);
                }
                if (abs(el[1]) > max_y) {
                    max_y = abs(el[1]);
                }
            }
            for (int i = -max_x - 2; i <= max_x + 2; ++i) {
                for (int j = -max_y - 2; j <= max_y + 2; ++j) {
                    if (field.find({i, j}) != field.end()) {
                        std::cout << field[{i, j}];
                    } else {
                        if (i == 0) {
                            std::cout << '-';
                        } else if (j == 0) {
                            std::cout << '|';
                        } else {
                            std::cout << ' ';
                        }
                    }
                    std::cout << ' ';
                }
                std::cout << '\n' << '\n';
            }
        }
    }
}
