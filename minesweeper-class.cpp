#include <iostream>
#include <vector>

class Minesweeper {
 private:
    size_t M, N;
    std::vector<std::vector<int>> Table;

 public:
    Minesweeper(size_t m, size_t n) : M(m), N(n), Table(
            std::vector<std::vector<int>>(M, std::vector<int>(N, 0))) {
    }

    size_t Rows() const {
        return M;
    }

    size_t Columns() const {
        return N;
    }

    void SetMine(size_t i, size_t j) {
        Table[i][j] = -1;
    }

    int operator()(size_t i, size_t j) const {
        return Table[i][j];
    }

    void CheckForMinesAround() {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (Table[i][j] == -1) {
                    continue;
                }
                int counter = 0;
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (0 <= i + dx && i + dx < M &&
                            0 <= j + dy && j + dy < N &&
                            Table[i + dx][j + dy] == -1) {
                            ++counter;
                        }
                    }
                }
                Table[i][j] = counter;
            }
        }
    }
};

std::ostream &operator<<(std::ostream &out, const Minesweeper &ms) {
    for (size_t i = 0; i < ms.Rows(); ++i) {
        for (size_t j = 0; j < ms.Columns(); ++j) {
            if (ms(i, j) == -1) {
                out << '*';
            } else {
                out << ms(i, j);
            }
        }
        if (i != ms.Rows() - 1) {
            out << "\n";
        }
    }
    return out;
}
