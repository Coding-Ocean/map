#include<iostream>
#include<set>
using namespace std;

int main() {
	set<int> data;

	data.emplace(5);
	data.emplace(3);
	data.emplace(2);
	data.emplace(1);
	data.emplace(4);

	for (const auto& d : data) {
		cout << d << " ";
	}

	system("pause>0");
}