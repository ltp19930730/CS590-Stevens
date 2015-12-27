//  Created by Tianpei Luo on 12/19/15.
//  Copyright © 2015 TianpeiLuo. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

const int maxnum = 100;
const int maxint = 999999;

class Node {
public:
	int x_label;
	int y_label;
	int idNumber;
	int inNum;
	vector<pair<Node*, int>>edges;
	Node(int n) {
		idNumber = n;
		inNum = 0;
	}
	void addEdge(Node *n, int weight) {
		edges.push_back(make_pair(n, weight));
	}
};

class graph {
public:
	map<int, Node*> list;
public:
	void addNode(int n) {
		Node *a;
		if (list.count(n)) {
			a = list.at(n);
		}
		else {
			a = new Node(n);
			list[n] = a;
		}
	}
	void addEdge(int from, int weight, int to) {
		Node *a, *b;
		if (list.count(from)) {
			a = list.at(from);
		}
		else {
			a = new Node(from);
			list[from] = a;
		}
		if (list.count(to)) {
			b = list.at(to);
		}
		else {
			b = new Node(to);
			list[to] = b;
		}
		a->addEdge(b, weight);
	}
	void printNode() {
		for (auto it = list.begin(); it != list.end(); ++it) {
			cout << it->first << endl;
		}

	}
	void drawgraph() {
		char**pic;
		const int cod = 20 * list.size();

		pic = new char*[cod];
		for (int i = 0; i != cod; ++i) {
			pic[i] = new char[cod];
		}
		for (int i = 0; i<cod; i++) {
			for (int j = 0; j<cod; j++) {
				pic[i][j] = ' ';
			}
		}


		int n_cod = 10;
		for (auto it = list.begin(); it != list.end(); ++it) {
			pic[n_cod][n_cod] = it->first + '0';
			pic[n_cod][n_cod - 1] = '[';
			pic[n_cod][n_cod + 1] = ']';
			it->second->x_label = n_cod;
			it->second->y_label = n_cod;
			n_cod += 15;
		}
		for (auto it = list.begin(); it != list.end(); ++it) {
			for (vector<pair<Node*, int>>::iterator it_temp = it->second->edges.begin(); it_temp != it->second->edges.end(); it_temp++) {
				bool temp = true;
				int indenx = 3;
				int weight = it_temp->second;
				int x_to = it_temp->first->x_label;
				int y_to = it_temp->first->y_label;
				int x_from = it->second->x_label;
				int y_from = it->second->y_label;
				if (x_from<x_to) {
					//the from _ode is small than the to_node
					if (pic[x_to - 1][y_to] == ' ') {
						for (int i = y_from; i<y_to - 1; i++) {
							if (pic[x_from][i + 1] == ' ') {
								pic[x_from][i + 1] = '-';
							}
							else if (pic[x_from][i + 1] == '|') {
								pic[x_from][i + 1] = '=';
							}
						}
						for (int i = x_from; i<x_to; i++) {
							if (temp) {
								pic[x_from][y_to] = '+';
								pic[x_to - 1][y_to] = 'V';
								if (weight<10) {
									pic[x_to - 5][y_to] = weight + '0';
								}
								else {
									int y_temp = y_to;
									while (weight != 0) {
										pic[x_to - 5][y_temp + 1] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}
								temp = false;

							}
							else if (pic[i][y_to] == ' ') {
								pic[i][y_to] = '|';
							}
							else if (pic[i][y_to] == '-') {
								pic[i][y_to] = '=';
							}
						}
						//判断左边有没有路口
					}
					else if (pic[x_to][y_to - 2] == ' ') {
						for (int i = y_from; i<y_to - 2 * indenx; i++) {
							if (pic[x_from][i + 1] == ' ') {
								pic[x_from][i + 1] = '-';
							}
							else if (pic[x_from][i + 1] == '|') {
								pic[x_from][i + 1] = '=';
							}
						}
						for (int i = x_from; i<x_to; i++) {
							if (temp) {
								pic[x_from][y_to - 2 * indenx] = '+';
								pic[x_to][y_to - 2 * indenx] = '+';
								pic[x_to][y_to - 2] = '>';
								temp = false;
								if (weight<10) {
									pic[x_to - 5][y_to - 2 * indenx] = weight + '0';
								}
								else {
									int y_temp = y_to - 2 * indenx;
									while (weight != 0) {
										pic[x_to - 5][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}

							}
							else if (pic[i][y_to - 2 * indenx] == ' ') {
								pic[i][y_to - 2 * indenx] = '|';
							}
							else if (pic[i][y_to - 2 * indenx] == '-') {
								pic[i][y_to - indenx] = '=';
							}
						}

						for (int i = y_to - 2 * indenx; i<y_to; i++) {
							if (pic[x_to][i] == ' ') {
								pic[x_to][i] = '-';
							}
							else if (pic[x_to][i] == '|') {
								pic[x_to][i] = '=';
							}
						}
						//判断下面是否有路口
					}
					else if (pic[x_to + 1][y_to] == ' ') {
						for (int i = y_from; i<y_from + 2 * indenx; i++) {
							if (pic[x_from][i] == ' ') {
								pic[x_from][i] = '-';
							}
							else if (pic[x_from][i + 1] == '|') {
								pic[x_from][i] = '=';
							}
						}
						for (int i = x_from; i<x_to + 2 * indenx; i++) {
							if (temp) {
								pic[x_from][y_from + 2 * indenx] = '+';
								pic[x_to + 2 * indenx][y_from + 2 * indenx] = '+';
								pic[x_to + 2 * indenx][y_to] = '+';
								pic[x_to + 1][y_to] = '^';
								temp = false;
								if (weight<10) {
									pic[x_to + 3][y_to] = weight + '0';
								}
								else {
									int y_temp = y_to;
									while (weight != 0) {
										pic[x_to + 3][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}

							}
							else if (pic[i][y_from + 2 * indenx] == ' ') {
								pic[i][y_from + 2 * indenx] = '|';
							}
							else if (pic[i][y_from + 2 * indenx] == '-') {
								pic[i][y_from + 2 * indenx] = '=';
							}
						}
						for (int i = y_from + 2 * indenx; i<y_to; i++) {
							if (pic[x_to + 2 * indenx][i] == ' ') {
								pic[x_to + 2 * indenx][i] = '-';
							}
							else if (pic[x_to + 2 * indenx][i + 1] == '|') {
								pic[x_to + 2 * indenx][i] = '=';
							}
						}

						for (int i = x_to + 2 * indenx; i>x_to; i--) {
							if (pic[i][y_to] == ' ') {
								pic[i][y_to] = '|';
							}
							else if (pic[i][y_to] == '-') {
								pic[i][y_to] = '=';
							}
						}
						//判断右边有没有路口
					}
					else if (pic[x_to][y_to + 2] == ' ') {
						for (int i = y_from; i<y_to + 2 * indenx; i++) {
							if (pic[x_from][i] == ' ') {
								pic[x_from][i] = '-';
							}
							else if (pic[x_from][i] == '|') {
								pic[x_from][i] = '=';
							}
						}
						for (int i = x_from; i<x_to; i++) {
							if (temp) {
								pic[x_from][y_to + 2 * indenx] = '+';
								pic[x_to][y_to + 2 * indenx] = '+';
								pic[x_to][y_to + 2] = '<';
								temp = false;
								if (weight<10) {
									pic[x_to - 5][y_to + 2 * indenx] = weight + '0';
								}
								else {
									int y_temp = y_to + 2 * indenx;
									while (weight != 0) {
										pic[x_to - 5][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}

							}
							else if (pic[i][y_to + 2 * indenx] == ' ') {
								pic[i][y_to + 2 * indenx] = '|';
							}
							else if (pic[i][y_to + 2 * indenx] == '-') {
								pic[i][y_to + 2 * indenx] = '=';
							}
						}
						for (int i = y_to + 2 * indenx; i>y_to; i--) {
							if (pic[x_to][i] == ' ') {
								pic[x_to][i] = '-';
							}
							else if (pic[x_to][i + 1] == '|') {
								pic[x_to][i] = '=';
							}
						}
					}
				}
				else {
					//The from_node is bigger than the to_node
					//To check if the right side is available or not
					if (pic[x_to][y_to + 2] == ' ') {

						for (int i = y_from; i <= y_from + indenx; i++) {
							if (pic[x_from][i] == ' ') {
								pic[x_from][i] = '-';
							}
							else if (pic[x_from][i] == '|') {
								pic[x_from][i] = '=';
							}
						}
						for (int i = x_from; i >= x_to; i--) {
							if (temp) {
								pic[x_from][y_from + indenx + 1] = '+';
								pic[x_to][y_from + indenx + 1] = '+';
								pic[x_to][y_to + 2] = '<';
								temp = false;
								if (weight<10) {
									pic[x_to][y_to + 3 * indenx] = weight + '0';
								}
								else {
									int y_temp = y_to + 3 * indenx;
									while (weight != 0) {
										pic[x_to][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}

							}
							else if (pic[i][y_from + indenx + 1] == ' ') {
								pic[i][y_from + indenx + 1] = '|';
							}
							else if (pic[i][y_from + indenx + 1] == '-') {
								pic[i][y_from + indenx + 1] = '=';
							}
						}
						for (int i = y_from + indenx + 1; i >= y_to + 1; i--) {
							if (pic[x_to][i] == ' ') {
								pic[x_to][i] = '-';
							}
							else if (pic[x_to][i] == '|') {
								pic[x_to][i] = '=';
							}
						}
						//To check if the upper position is available or not
					}
					else if (pic[x_to - 1][y_to] == ' ') {
						for (int i = y_from; i <= y_from + 3 * indenx; i++) {
							if (pic[x_from][i] == ' ') {
								pic[x_from][i] = '-';
							}
							else if (pic[x_from][i] == '|') {
								pic[x_from][i] = '=';
							}
						}
						for (int i = x_from; i>x_to - 3 * indenx; i--) {
							if (temp) {
								pic[x_from][y_from + 3 * indenx] = '+';
								pic[x_to - 3 * indenx][y_from + 3 * indenx] = '+';
								pic[x_to - 3 * indenx][y_to] = '+';
								pic[x_to - 1][y_to] = 'V';
								temp = false;
								if (weight<10) {
									pic[x_to - 5][y_to] = weight + '0';
								}
								else {
									int y_temp = y_to;
									while (weight != 0) {
										pic[x_to - 5][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}

							}
							else if (pic[i][y_from + 3 * indenx] == ' ') {
								pic[i][y_from + 3 * indenx] = '|';
							}
							else if (pic[i][y_from + 3 * indenx] == '-') {
								pic[i][y_from + 3 * indenx] = '=';
							}
						}
						for (int i = y_from + 3 * indenx; i>y_to; i--) {
							if (pic[x_to - 3 * indenx][i] == ' ') {
								pic[x_to - 3 * indenx][i] = '-';
							}
							else if (pic[x_to - 3 * indenx][i] == '|') {
								pic[x_to - 3 * indenx][i] = '=';
							}
						}
						for (int i = x_to - 3 * indenx; i<x_to; i++) {
							if (pic[i][y_to] == ' ') {
								pic[i][y_to] = '|';
							}
							else if (pic[x_to - 3 * indenx][y_to] == '-') {
								pic[i][y_to] = '=';
							}
						}


						//to check the left side is available or not
					}
					else if (pic[x_to][y_to - 2] == ' ') {
						for (int i = y_from; i <= y_from + indenx; i++) {
							if (pic[x_from][i] == ' ') {
								pic[x_from][i] = '-';
							}
							else if (pic[x_from][i] == '|') {
								pic[x_from][i] = '=';
							}
						}
						for (int i = x_from; i>x_to - indenx; i--) {
							if (temp) {
								pic[x_from][y_from + indenx + 1] = '+';
								pic[x_to - indenx][y_from + indenx + 1] = '+';
								pic[x_to - indenx][y_to - 2 * indenx] = '+';
								pic[x_to][y_to - 2 * indenx] = '+';
								pic[x_to][y_to - 2] = '>';
								temp = false;
								if (weight<10) {
									pic[x_to - indenx][y_to + 2 * indenx] = weight + '0';
								}
								else {
									int y_temp = y_to + 2 * indenx;
									while (weight != 0) {
										pic[x_to - indenx][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}

							}
							else if (pic[i][y_from + indenx + 1] == ' ') {
								pic[i][y_from + indenx + 1] = '|';
							}
							else if (pic[i][y_from + indenx + 1] == '-') {
								pic[i][y_from + indenx + 1] = '=';
							}
						}
						for (int i = y_from + indenx + 1; i >= y_to - 2 * indenx; i--) {
							if (pic[x_to - indenx][i] == ' ') {
								pic[x_to - indenx][i] = '-';
							}
							else if (pic[x_to - indenx][i] == '|') {
								pic[x_to - indenx][i] = '=';
							}
						}
						for (int i = x_to - indenx; i <= x_to; i++) {
							if (pic[i][y_to - 2 * indenx] == ' ') {
								pic[i][y_to - 2 * indenx] = '|';
							}
							else if (pic[i][y_to - 2 * indenx] == '-') {
								pic[i][y_to - 2 * indenx] = '=';
							}
						}
						for (int i = y_to - 2 * indenx; i<y_to; i++) {
							if (pic[x_to][i] == ' ') {
								pic[x_to][i] = '-';
							}
							else if (pic[x_to][i] == '|') {
								pic[x_to][i] = '=';
							}
						}
						//To check if the under poisition is available
					}
					else if (pic[x_to + 1][y_to] == ' ') {
						for (int i = y_from; i <= y_from + indenx; i++) {
							if (pic[x_from][i] == ' ') {
								pic[x_from][i] = '-';
							}
							else if (pic[x_from][i] == '|') {
								pic[x_from][i] = '=';
							}
						}
						for (int i = x_from; i<x_from + 3 * indenx; i++) {
							if (temp) {
								pic[x_from][y_from + indenx + 1] = '+';
								pic[x_from + 3 * indenx][y_from + indenx + 1] = '+';
								pic[x_from + 3 * indenx][y_to] = '+';
								pic[x_to + 1][y_to] = '^';
								temp = false;
								if (weight<10) {
									pic[x_to + 10][y_to] = weight + '0';
								}
								else {
									int y_temp = y_to;
									while (weight != 0) {
										pic[x_to + 10][y_temp] = char(weight % 10 + '0');
										weight /= 10;
										y_temp--;
									}
								}


							}
							else if (pic[i][y_from + indenx + 1] == ' ') {
								pic[i][y_from + indenx + 1] = '|';
							}
							else if (pic[i][y_from + indenx + 1] == '-') {
								pic[i][y_from + indenx + 1] = '=';
							}
						}
						for (int i = y_from + indenx + 1; i >= y_to; i--) {
							if (pic[x_from + 3 * indenx][i] == ' ') {
								pic[x_from + 3 * indenx][i] = '-';
							}
							else if (pic[x_from + 3 * indenx][i] == '|') {
								pic[x_from + 3 * indenx][i] = '=';
							}
						}
						for (int i = x_from + 3 * indenx; i>x_to; i--) {
							if (pic[i][y_to] == ' ') {
								pic[i][y_to] = '|';
							}
							else if (pic[i][y_to] == '-') {
								pic[i][y_to] = '=';
							}
						}
					}
				}
			}
		}
		//draw the picture
		for (int i = 0; i<cod; i++) {
			for (int j = 0; j<cod; j++) {
				cout << pic[i][j];
			}
			cout << endl;
		}

	}
	//using the dijkstra to find the shortest path
	void Dijkstra() {
		int nodeNum = list.size();
		cout << nodeNum << endl;
		int c[99][99];
		int dist[99];
		int prev[99];
		bool s[99];
		for (int i = 1; i <= nodeNum; i++) {
			for (int j = 1; j <= nodeNum; j++) {
				c[i][j] = 99999;
			}
		}
		for (auto it = list.begin(); it != list.end(); ++it) {
			int p = it->first;
			for (auto it_temp = it->second->edges.begin(); it_temp != it->second->edges.end(); it_temp++) {
				int q = it_temp->first->idNumber;
				int weight = it_temp->second;
				c[p][q] = weight;
			}
		}

		for (int i = 1; i <= nodeNum; i++) {
			dist[i] = 99999;
		}
		int v;
		for (auto it = list.begin(); it != list.end(); ++it) {
			v = it->first;
			for (int i = 1; i <= nodeNum; ++i)
			{
				dist[i] = c[v][i];
				s[i] = 0;
				if (dist[i] == 99999) {
					prev[i] = 0;
				}
				else {
					prev[i] = v;
				}
			}
			dist[v] = 0;
			s[v] = 1;

			for (int i = 2; i <= nodeNum; ++i)
			{
				int tmp = 99999;
				int u = v;
				for (int j = 1; j <= nodeNum; ++j)
					if ((!s[j]) && dist[j]<tmp)
					{
						u = j;
						tmp = dist[j];
					}
				s[u] = 1;
				for (int j = 1; j <= nodeNum; ++j) {
					if ((!s[j]) && c[u][j]<99999)
					{
						int newdist = dist[u] + c[u][j];
						if (newdist < dist[j])
						{
							dist[j] = newdist;
							prev[j] = u;
						}
					}
				}
			}
			cout << "the shortest path from Node[" << it->first << "] to:" << endl;
			for (auto it_temp = list.begin(); it_temp != list.end(); ++it_temp) {
				if (dist[it_temp->first]<99999 && dist[it_temp->first]>0) {
					cout << "Node[" << it_temp->first << "] is " << dist[it_temp->first];
					//draw the path for the shortest path
					int path[maxnum];
					int tot = 1;
					path[tot] = it_temp->first;
					tot++;
					int tmp = prev[it_temp->first];
					while (tmp != v)
					{
						path[tot] = tmp;
						tot++;
						tmp = prev[tmp];
					}
					cout << " the path is:";
					path[tot] = v;
					for (int i = tot; i >= 1; --i)
						if (i != 1) {
							cout << path[i] << " ---> ";
						}
						else {
							cout << path[i] << endl;
						}
				}
			}
		}
	}
};



int main() {
	fstream file;
	file.open("graph.dat");
	string line;
	if (!file) {
		cout << "open file fail!!" << endl;
		return -1;
	}
	graph g;
	while (getline(file, line)) {
		istringstream ss(line);
		int node;
		ss >> node;
		g.addNode(node);
		int nextNode;
		int weight;
		while (ss >> nextNode >> weight) {
			g.addEdge(node, weight, nextNode);
		}
	}
	g.drawgraph();
	g.Dijkstra();
	return 0;
}