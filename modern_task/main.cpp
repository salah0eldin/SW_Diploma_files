#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <climits>

using namespace std;

tuple<int,int,int,int> findBoth(const vector<int>& v){
    map<int,int> m;
    for (size_t i = 0; i < v.size(); ++i) {
        m[v[i]] = static_cast<int>(i);
    }

    // If there are fewer than 2 distinct values, no consecutive pair exists
    if (m.size() < 2) {
        return make_tuple(0, -1, 0, -1);
    }

    // Iterate through the ordered keys in the map to find the largest consecutive pair
    int best_first = INT_MIN;
    int best_first_idx = -1;
    int best_second = INT_MIN;
    int best_second_idx = -1;
    auto prev = m.begin();
    for (auto it = next(m.begin()); it != m.end(); ++it) {
        if (it->first - prev->first == 1) {
            if (prev->first > best_first) {
                best_first = prev->first;
                best_first_idx = prev->second;
                best_second = it->first;
                best_second_idx = it->second;
            }
        }
        prev = it;
    }

    if (best_first_idx == -1) {
        return make_tuple(0, -1, 0, -1);
    }

    return make_tuple(best_first, best_first_idx, best_second, best_second_idx);
}

int main(){
    vector<int> v = {1, 2, 8, 10, 18, 19, 22, 24, 33, 35};
    auto [firstnum, firstindex, secondnum, secondindex] = findBoth(v);
    if (firstindex == -1) {
        cout << "No consecutive pair found" << endl;
    } else {
        cout << "The largest pair of consecutive integers is: " << firstnum << " and " << secondnum
             << " at indices " << firstindex << " and " << secondindex << endl;
    }

    return 0;
}