#include <iostream>
#include <vector>

template <typename T, typename cmp>
class Heap {
private:
    std::vector<T> data_;

    int Parent_(int child) {
        if (child % 2 == 0) {
            return child / 2 - 1;
        } else {
            return child / 2;
        }
    }

    size_t Left_(size_t parent) {
        return parent * 2 + 1;
    }

    size_t Right_(size_t parent) {
        return (parent + 1) * 2;
    }

    void swap_(int f, int s) {
        T temp;
        temp = data_[s];
        data_[s] = data_[f];
        data_[f] = temp;
    }

    void Hype_up() {
        int child = data_.size() - 1;
        int parent = Parent_(child);

        while (child >= 0 && parent >= 0 && cmp(data_[child], data_[parent]).check()) {
            swap_(child, parent);
            child = parent;
            parent = Parent_(child);
        }
    }

    void Hype_down() {
        size_t parent = 0;
        bool okay = false;
        while (!okay) {
            size_t left = Left_(parent);
            size_t right = Right_(parent);
            size_t size_ = data_.size();
            size_t big = parent;

            if (left < size_ && cmp(data_[left], data_[big]).check()) {
                big = left;
            }
            if (right < size_ && cmp(data_[right], data_[big]).check()) {
                big = right;
            }
            if (big != parent) {
                swap_(big, parent);
                parent = big;
            } else {
                okay = true;
            }
        }
    }

public:
    Heap() {}

    void Insert(T c) {
        data_.push_back(c);
        Hype_up();
    }

    T Extract() {
        size_t child = data_.size() - 1;
        swap_(child, 0);

        T max = data_.back();
        data_.pop_back();
        Hype_down();

        return max;
    }
};

template <typename T>
class Compare_max {
private:
    bool flag;
public:
    Compare_max(const T& first, const T& second) {
        flag = first > second;
    }

    bool check() const {
        return flag;
    }
};

template <typename T>
class Compare_min {
private:
    bool flag;
public:
    Compare_min(const T& first, const T& second) {
        flag = first < second;
    }

    bool check() const {
        return flag;
    }
};

int main() {
    Heap<int, Compare_max<int>> test_max;
    Heap<int, Compare_min<int>> test_min;
    for (size_t i = 0; i != 10; ++i) {
        test_max.Insert(i);
        test_min.Insert(i * 2);
    }
    for (size_t i = 0; i != 10; ++i) {
        std::cout << test_max.Extract() << ' ' << test_min.Extract() << '\n';
    }
}
