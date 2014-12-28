#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	{
		std::vector<int> v = { 1, 2, 3, 3, 4, 4, 5, 6, 7 }; 
		auto l = std::lower_bound(v.begin(), v.end(), 4);
		auto u = std::upper_bound(v.begin(), v.end(), 4);
		cout << std::distance(v.begin(), l) << " : " << std::distance(v.begin(), u) << endl; 
	}
	{
		std::vector<int> v = { 1, 2, 3, 3, 4, 4, 5, 6, 7 }; 
		auto l = std::lower_bound(v.begin(), v.end(), 4); 
		auto u = std::upper_bound(l, v.end(), 4);
		cout << std::distance(v.begin(), l) << " : " << std::distance(v.begin(), u) << endl;
	}
	
	return 0;
}
