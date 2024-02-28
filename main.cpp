#include<iostream>
#include<map>
using namespace std;

//pair型表示用、挿入演算子のオーバーロード
template<typename T1, typename T2>
ostream& operator<<(ostream& s, const pair<T1, T2>& p) {
	return s << p.first << ":" << p.second;
}

//どのコンテナもこれで全部表示できる
template<class C>
void show(const C& data) {
	for (const auto& d : data) {
		cout << d << endl;
	}
	cout << endl;
}

int main() {
	//平衡2分木データの入れ物
	map<string, int> price;
	//データ構築
	price["ぎょうざ"] = 100;
	price["らーめん"] = 200;
	price["ちゃーはん"] = 300;
	price["えびまよ"] = 400;
	show(price);
	//探索
	string key = "さーめん";
	cout << key << ' ';
	auto it = price.find(key);
	if (it != price.end()) {
		cout << it->second << "えん";
	}
	else {
		cout << "ない";
	}

	system("pause>0");
}