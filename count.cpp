#include	<iostream>
#include	<utility>
#include	<string>
#include	<vector>
#include	<map>
#include	<fstream>
#include	<set>
#include	<queue>

#define		SIZE_OF_PAGES	1483277
#define		SIZE_OF_LINKS	52973671

using namespace std;

map<int, string> pages;
vector<vector<int>> links;
vector<int> sited;

void read_pages() {
	ifstream ifs("pages.txt");
	if (ifs.fail()) {
		cerr << "Can not open pages.txt" << endl;
		exit(1);
	}
	int num;
	string str;
	ifs >> num >> str;
	while (!ifs.eof()) {
		pages.insert(map<int, string>::value_type(num, str));
		ifs >> num >> str;
	}
}

void read_links() {
	ifstream ifs("links.txt");
	if (ifs.fail()) {
		cerr << "Can not open links.txt" << endl;
		exit(1);
	}
	int from;
	int to;
		
	ifs >> from >> to;

	//メモリ節約のために最初にまとめて確保する
	links.resize(SIZE_OF_PAGES);
	sited.assign(SIZE_OF_PAGES, 0);
	for (int i = 0; i < SIZE_OF_PAGES; i++) {
		vector<int> vec;
		while (i == from && !ifs.eof()) {
			vec.push_back(to);
			sited[to]++;
			ifs >> from >> to;
		}
		links[i]=vec;
	}
}

void read() {
	read_pages();
	read_links();
}

void test_read_pages() {
	//for (int i = 0; i < 10; i++) {
	//	cout << "(" << i << ", " << pages[i] << ")" << endl;
	//}
}

void test_read_links() {
	cout << "(0, " << links[0][0] << ")" << endl;
	cout << "(1, " << links[1][0] << ")" << endl;
}


int main() {
	read_links();
	int max = 0;
	
	vector<int> dist;

	dist.assign(217672, 0);

	ofstream ofs_notsited;
	ofs_notsited.open("notsited.txt", ios::out);

	for (int i = 0; i < sited.size(); i++) {
		if (sited[max] < sited[i]) {
			max = i;
		}
		if (sited[i] == 0) {
			ofs_notsited << i << endl;
		}
		dist[sited[i]]++;
	}

	cout << "一番参照されているページ" << endl;
	cout << max << ", " << sited[max] << endl;

	ofstream ofs_dist;
	ofs_dist.open("dist.txt", ios::out);

	for (int i = 0; i < dist.size(); i++) {
		ofs_dist << i << " " << dist[i] << endl;
	}


	return 0;
}
