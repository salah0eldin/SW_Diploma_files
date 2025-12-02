#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

class isBigger{
public:
    bool operator()(int a, int b) {
        return abs(a) < abs(b);
    }
};

int main() {
    std::vector<int> vec = {5, -3, 20, -8, 9, 2};

    std::sort(vec.begin(), vec.end(), isBigger());

    for (const auto& num : vec) {
        std::cout << num << std::endl;
    }
    return 0;
}