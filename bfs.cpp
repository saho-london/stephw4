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
	for (int i = 0; i < SIZE_OF_PAGES; i++) {
		vector<int> vec;
		while (i == from && !ifs.eof()) {
			vec.push_back(to);
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

int bfs(int from, int to, vector<vector<int>> &graph, pair<int, int> &farthest) {
	set<int> visited;
	queue<pair<int, int>> que;
	pair<int, int> last;

	visited.insert(from);
	que.push(make_pair(from, 0));	
	while (!que.empty()) {
		pair<int, int> t = que.front();
		que.pop();
		if (t.first == to) {
			return t.second;
		}
		for (auto element: graph[t.first]) {
			auto iter = visited.find(element);
			if (iter == visited.end()) {
				visited.insert(element);
				que.push(make_pair(element, t.second + 1));
			}
		}
		last = t;
	}
	farthest = last;
	return -1;
}

void test_bfs() {
	vector<int> ex0 = {1};
	vector<int> ex1 = {2, 4};
	vector<int> ex2 = {3};
	vector<int> ex3;
	vector<int> ex4 = {5};
	vector<int> ex5 = {6};
	vector<int> ex7 = {0};

	vector<vector<int>> vec;
	vec.push_back(ex0);
	vec.push_back(ex1);
	vec.push_back(ex2);
	vec.push_back(ex3);
	vec.push_back(ex4);
	vec.push_back(ex5);
	vec.push_back(ex3);
	vec.push_back(ex7);


	pair<int, int> farthest;
	//-1, (3, 1)
	cout << bfs(2, -1, vec, farthest) << endl;
	cout << "(" << farthest.first << ", " << farthest.second << ")" << endl;

	//-1, (6, 3)
	cout << bfs(1, -1, vec, farthest) << endl;
	cout << "(" << farthest.first << ", " << farthest.second << ")" << endl;
	
	//-1, (6, 4)
	cout << bfs(0, 7, vec, farthest) << endl;
	cout << "(" << farthest.first << ", " << farthest.second << ")" << endl;

	//1
	cout << bfs(0, 1, vec, farthest) << endl;
	
	//3
	cout << bfs(0, 5, vec, farthest) << endl;
	
	//4
	cout << bfs(7, 3, vec, farthest) << endl;
}

void test_bfs_on_links() {
}

//pathも保存しておく。その分空間が必要
vector<int> bfs2(int from, int to, vector<vector<int>> &graph, pair<int, vector<int>> &farthest) {
	set<int> visited;
	queue<pair<int, vector<int>>> que;
	pair<int, vector<int>> last;
	vector<int> empty;
	
	vector<int> start;
	start.push_back(from);

	visited.insert(from);
	que.push(make_pair(from, start));	

	while (!que.empty()) {
		pair<int, vector<int>> t = que.front();
		que.pop();
		if (t.first == to) {
			return t.second;
		}
		for (auto element: graph[t.first]) {
			auto iter = visited.find(element);
			if (iter == visited.end()) {
				visited.insert(element);
				vector<int> temp = t.second;
				temp.push_back(element);
				que.push(make_pair(element, temp));
			}
		}
		last = t;
	}
	farthest = last;
	return empty;
}

void print_bfs2(vector<int> &returnValue, pair<int, vector<int>> &farthest) {
	if (returnValue.size() != 0) {
		cout << "path found :";
		for (int i = 0; i < returnValue.size() - 1; i++) {
			cout << returnValue[i] << ",";
		}
		cout << returnValue[returnValue.size() - 1] << endl;
	} else {
		cout << "path couldn't found" << endl << "farthest :";
		cout << farthest.first << endl;
		cout << "path :";
		for (int i = 0; i < farthest.second.size() - 1; i++) {
			cout << farthest.second[i] << ",";
		}
		cout << farthest.second[farthest.second.size() - 1] << endl;
	}
}

void test_bfs2() {
	vector<int> ex0 = {1};
	vector<int> ex1 = {2, 4};
	vector<int> ex2 = {3};
	vector<int> ex3;
	vector<int> ex4 = {5};
	vector<int> ex5 = {6};
	vector<int> ex7 = {0};

	vector<vector<int>> vec;
	vec.push_back(ex0);
	vec.push_back(ex1);
	vec.push_back(ex2);
	vec.push_back(ex3);
	vec.push_back(ex4);
	vec.push_back(ex5);
	vec.push_back(ex3);
	vec.push_back(ex7);


	pair<int, vector<int>> farthest;
	vector<int> p;

	cout << "test1" << endl;
       	p = bfs2(2, -1, vec, farthest);
	print_bfs2(p, farthest);

	cout << "test2" << endl;
	p = bfs2(1, -1, vec, farthest);
	print_bfs2(p, farthest);
	
	cout << "test3" << endl;
	p = bfs2(0, 7, vec, farthest);
	print_bfs2(p, farthest);

	cout << "test4" << endl;
	p = bfs2(0, 1, vec, farthest);
	print_bfs2(p, farthest);
	
	cout << "test5" << endl;
	p = bfs2(0, 5, vec, farthest);
	print_bfs2(p, farthest);
	
	cout << "test6" << endl;
	p = bfs2(7, 3, vec, farthest);
	print_bfs2(p, farthest);
}

void find_path(int from, int to) {
	pair<int, vector<int>> farthest;
	vector<int> p = bfs2(from, to, links, farthest);
	print_bfs2(p, farthest);
}

void test_find_path() {
	find_path(0, 1);
	find_path(0, 284171);
	find_path(1417711, 457783); //東京ディズニーランドからGoogle
	find_path(457783, 1417711); //Googleから東京ディズニーランド
	
	//発見できないパターンが強制終了になります
	//find_path(0, -1); 
}


int main() {
	int from, to;

	read_links();
	test_find_path();

	cout << "enter 2 integers" << endl;
	cout << "enter -1 -1 to quit" << endl;
	cout << "> ";
	
	cin >> from >> to;

	while (from != -1 || to != -1) {
		find_path(from, to);
		cout << "> ";
		cin >> from >> to;
	}

	return 0;
}
