#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;
// Define specializations for the Traits class template here.

template <typename T>
struct Traits 
{   
    static string name(int index);
};

template <>
string Traits<Fruit>::name(int index) {
    static string fruits[] = {"apple", "orange", "pear"};
    return (index < 3) ? fruits[index] : "unknown";
}

template <>
string Traits<Color>::name(int index) {
    static string color[] = {"red", "green", "orange"};
    return (index > -1 && index < 3) ? color[index] : "unknown";
}

int main()
{
	int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
