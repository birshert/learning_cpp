#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

std::vector<std::pair<std::string, int>> turns;
std::vector<std::vector<int>> direction_highway;

class Node {
public:

    int color = 0;
    int x = 0;
    int y = 0;

    Node() = default;

    Node(int c, int x_, int y_) {
        color = c;
        x = x_;
        y = y_;
    }

    void ch_color() {
        color = (color + 1) % 6;
    }

    Node& operator =(Node& other) = default;

    bool operator ==(Node& other) {
        return (x == other.x && y == other.y && color == other.color);
    }
};

class Ant {
public:

    int direction = 0;
    int x = 0;
    int y = 0;

    void ch_direction(Node& n) {
        if (n.color < 3) {
            direction = (3 + direction) % 4;
            turns.emplace_back(std::make_pair("left", (n.color + 1) % 6));
        } else {
            direction = (direction + 1) % 4;
            turns.emplace_back(std::make_pair("right", (n.color + 1) % 6));
        }
    }

    void change_direction(Node& n) {
        if (n.color < 3) {
            direction = (3 + direction) % 4;
        } else {
            direction = (direction + 1) % 4;
        }
    }

    void new_xy() {
        int new_x, new_y;
        if (direction % 2 == 0) {
            new_x = x;
            if (direction != 2) {
                new_y = y + 1;
            } else {
                new_y = y - 1;
            }
        } else {
            new_y = y;
            if (direction != 3) {
                new_x = x + 1;
            } else {
                new_x = x - 1;
            }
        }
        x = new_x;
        y = new_y;
    };
};

class Coloring {
public:
    int counter;
    int max_counter;
    int len;
    std::vector<int> data;

    Coloring(int l, int max) {
        counter = 0;
        max_counter = max;
        len = l;
        data.resize(len);
    }

    int next() {
        if (counter < max_counter) {
            std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
            std::uniform_int_distribution colors(0,5);
            for (int i = 0; i != len; ++i) {
                data[i] = colors(generator);
            }
            ++counter;
            return 1;
        } else {
            return 0;
        }
    }

    int get_color(int x, int y, int n) {
        return data[x + y * n];
    }
};

std::vector<std::pair<std::string, int>> find_cycle(std::vector<std::pair<std::string, int>>& path) {
    std::pair<std::string, int> start, curr;
    int len;
    start = *path.begin();
    for (int i = 10; i != 100; ++i) {
        curr = *(path.begin() + i);
        if (start == curr) {
            std::vector<std::pair<std::string, int>> first(path.begin(), path.begin() + i);
            std::vector<std::pair<std::string, int>> second(path.begin() + i, path.begin() + i * 2);
            if (first == second) {
                return first;
            }
        }
    }
};

std::map<std::pair<int, int>, Node> field;

inline bool band(Node curr, Node check, int direction) {}



inline int if_highway(Node curr, std::vector<std::vector<std::map<std::pair<int, int>, int>>>& future, int direction, int pos) {
    int step = -1;
    bool flag = false;
    for (int i = 0; i != 38; ++i) {
        step = i;
        for (auto elem : future[direction][i]) {
            if (field.find({elem.first.first + curr.x, elem.first.second + curr.y}) == field.end()) {
                if (elem.second != 0) {
                    step = -1;
                }
            } else if (field[{elem.first.first + curr.x, elem.first.second + curr.y}].color != elem.second) {
                step = -1;
            }
        }
        if (step == i) {
            flag = true;
            break;
        }
    }
    if (flag) {
        int max_xp = 0, max_yp = 0;
        for (auto elem : future[direction][step]) {
            if (elem.first.first > max_xp) {
                max_xp = elem.first.first;
            }
            if (elem.first.second > max_yp) {
                max_yp = elem.first.second;
            }
        }
        curr.x += max_xp + 1;
        curr.y += max_yp + 1;
        for (int i = 0; i != pos/2; ++i) {
            for (int j = -7; j != 7; ++j) {
                if (field[{curr.x + j, curr.y + i}].color != 0) {
                    return -1;
                } else {
                    field.erase({curr.x + j, curr.y + i});
                }
            }
            int highway = direction_highway[step][direction];
            if (highway >= 2) {
                curr.y += 1;
            } else {
                curr.y -= 1;
            }
            if (highway == 1 || highway == 2) {
                curr.x -= 1;
            } else {
                curr.x += 1;
            }
        }
        return step + 1;
    } else {
        return -1;
    }
}


int main() {
    int max_yp = 0, max_xp = 0;
    int max_yn = 0, max_xn = 0;
    Ant langton;
    for (int i = 0; i != 800; ++i) {
        int cur_x = langton.x, cur_y = langton.y;
        if (cur_x > max_xp) {
            max_xp = cur_x;
        }
        if (cur_y > max_yp) {
            max_yp = cur_y;
        }
        if (cur_x < max_xn) {
            max_xn = cur_x;
        }
        if (cur_y < max_yn) {
            max_yn = cur_y;
        }
        Node curr;
        if (field.find({cur_x, cur_y}) != field.end()) {
            curr = field[std::make_pair(cur_x, cur_y)];
        } else {
            curr.color = 0;
            curr.x = cur_x;
            curr.y = cur_y;
        }
        langton.ch_direction(curr);
        curr.ch_color();
        field[{cur_x, cur_y}] = curr;
        langton.new_xy();
    }
    std::cout << "Picture for 0-colored field ant travel at 800 steps\n";
    std::cout << "Start is at intersection of lines\n";
    for (int i = max_xn - 5; i <= max_xp + 5; ++i) {
        for (int j = max_yn - 5; j <= max_yp + 5; ++j) {
            if (field.find({i, j}) != field.end()) {
                std::cout << field[{i, j}].color;
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
        std::cout << '\n';
    }
    std::vector<std::pair<std::string, int>> path(turns.begin() + 500, turns.end());
    std::vector<std::pair<std::string, int>> temp = find_cycle(path);
    int len = temp.size();
    std::cout << '\n';
    std::vector<std::pair<std::string, int>> path1(turns.begin(), turns.begin() + 500), check;
    std::reverse(path1.begin(), path1.end());
    std::reverse(temp.begin(), temp.end());
    int pos1;
    for (int i = 0; i != 500/len; ++i) {
        std::vector<std::pair<std::string, int>> curr(path1.begin() + len * i, path1.begin() + len * (i + 1));
        if (curr != temp) {
            pos1 = len * i;
            check = curr;
            break;
        }
    }
    int pos;
    for (int i = 0; i <= len; ++i) {
        if (temp[i] != check[i]) {
            pos = i;
            pos1 += i;
            break;
        }
    }
    std::vector<std::pair<std::string, int>> start(temp.begin(), temp.begin() + pos), end(temp.begin() + pos, temp.end());
    std::reverse(start.begin(), start.end());
    std::reverse(end.begin(), end.end());
    for (auto elem : end) {
        start.emplace_back(elem);
    }
    std::vector<std::vector<std::vector<Node>>> future(4, std::vector<std::vector<Node>>(len, std::vector<Node>(len)));
    pos1 = 500 - pos1;
    direction_highway.resize(len, std::vector<int>(4));
    std::vector<std::vector<std::pair<int, int>>> ce(4);
    for (int dir = 0; dir != 4; ++dir) {
        field.clear();
        Ant checking_ant;
        checking_ant.direction = dir;
        for (int i = 0; i != pos1; ++i) {
            int cur_x = checking_ant.x, cur_y = checking_ant.y;
            Node curr;
            if (field.find({cur_x, cur_y}) != field.end()) {
                curr = field[std::make_pair(cur_x, cur_y)];
            } else {
                curr.color = 0;
                curr.x = cur_x;
                curr.y = cur_y;
            }
            checking_ant.ch_direction(curr);
            curr.ch_color();
            field[{cur_x, cur_y}] = curr;
            checking_ant.new_xy();
        }
        for (int i = 0; i != len; ++i) {
            ce[dir].push_back({checking_ant.x, checking_ant.y});
            int x_start, y_start, curr_dir;
            for (int j = 0; j != 2 * len; ++j) {
                int cur_x = checking_ant.x, cur_y = checking_ant.y;
                Node curr;
                if (field.find({cur_x, cur_y}) != field.end()) {
                    curr = field[std::make_pair(cur_x, cur_y)];
                } else {
                    curr.color = 0;
                    curr.x = cur_x;
                    curr.y = cur_y;
                }
                if (j == i) {
                    x_start = cur_x;
                    y_start = cur_y;
                    curr_dir = checking_ant.direction;
                }
                if (j >= i && j < len + i) {
                    direction_highway[i][curr_dir] = dir;
                    future[curr_dir][i][j - i].color = curr.color;
                    future[curr_dir][i][j - i].x = curr.x - x_start;
                    future[curr_dir][i][j - i].y = curr.y - y_start;
                }
                checking_ant.ch_direction(curr);
                curr.ch_color();
                field[{cur_x, cur_y}] = curr;
                checking_ant.new_xy();
            }
        }

    }
    std::vector<std::vector<std::map<std::pair<int, int>, int>>> cells(4, std::vector<std::map<std::pair<int, int>, int>>(len));
    for (int dir = 0; dir != 4; ++dir) {
        for (int i = 0; i != len; ++i) {
            for (int j = 0; j != len; ++j) {
                Node curr = future[dir][i][j];
                if (cells[dir][i].find({curr.x, curr.y}) == cells[dir][i].end()) {
                    cells[dir][i][{curr.x, curr.y}];
                    cells[dir][i][{curr.x, curr.y}] = curr.color;
                }
            }
        }
    }
    std::vector<std::vector<std::pair<std::vector<int>, std::vector<int>>>> stats(len);
    Coloring field_color(9, 10000);
    bool flag;
    int total_highway = 0;
    Node pause;
    pause.color = 9;
    std::ofstream out;
    int max = 0;
    out.open("C:\\Users\\birsh\\Desktop\\output.txt");
    while (field_color.next()) {
        std::cout << field_color.counter << '\n' << '\n';
        field.clear();
        flag = true;
        for (int i = -1; i != 2; ++i) {
            for (int j = -1; j != 2; ++j) {
                Node curr;
                curr.x = i;
                curr.y = j;
                curr.color = field_color.get_color(i + 1, j + 1, 3);
                field[{i, j}] = curr;
            }
        }
        Ant stat;
        std::vector<Node> turns(3000);
        std::vector<int> poses;
        for (int step = 0; step != 3000; ++step) {
            int x = stat.x, y = stat.y;
            if ((abs(x) > 1 || abs(y) > 1) && abs(turns[step - 1].x) <= 1 && abs(turns[step - 1].y) <= 1) {
                poses.push_back(step);
            }
            if (step && abs(x) <= 1 && abs(y) <= 1 && (abs(turns[step - 1].x) > 1 || abs(turns[step - 1].y) > 1)) {
                poses.push_back(step);
            }
            Node curr;
            if (field.find({x, y}) == field.end()) {
                curr.x = x;
                curr.y = y;
                curr.color = 0;
            } else {
                curr = field[{x, y}];
            }
            int g;
            if (flag) {
                g = if_highway(curr, cells, stat.direction, step);
            }
            if (g != -1 && flag) {
                if (step > max) {
                    max = step;
                }
                out << g << '\t' << step << '\t' << x << '\t' << y << '\t' << direction_highway[stat.direction][g] + 1 <<'\n';
                ++total_highway;
                for (int i = 0; i != 3; ++i) {
                    for (int j = 0; j != 3; ++j) {
                        out << field_color.data[i + j * 3] << ' ';
                    }
                    out << '\n';
                }
                if (!poses.empty()) {
                    poses.push_back(step);
                    int lines = 0;
                    for (int i = 0; i < poses.size() - 1; i += 2) {
                        lines += poses[i + 1] - poses[i] + 1;
                    }
                    out << lines << ' ' << poses.size() << '\n';
                    for (int i = 0; i < poses.size() - 1; i += 2) {
                        for (int j = poses[i]; j != poses[i + 1]; ++j) {
                            out << turns[j].x << '\t' << turns[j].y << '\t' << turns[j].color << '\n';
                        }
                        out << 0 << '\t' << 0 << '\t' << 9 << '\n';
                    }
                }
                break;
            }
            stat.change_direction(curr);
            curr.ch_color();
            field[{x, y}] = curr;
            stat.new_xy();
            turns[step] = curr;
        }
    }
    out.close();
    std::cout << total_highway << ' ' << max;
}
