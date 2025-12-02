#include <iostream>

using namespace std;

template <typename T>
void sum(T a, T b){
    static int c = 0;
    cout << "c = " << c++ << endl;
    cout << a + b << endl;
}

template <>
void sum(bool a, bool b){
    static int c = 0;
    cout << "c = " << c++ << endl;
    cout << a + b << endl;
}

int main(){
    sum(1,2);
    sum(true, true);
    sum((int)1.2, (int)2.2);
    return 0;
}