#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX
#include <iostream>
#include <vector>
#include <string>
using namespace std;


struct text {
	string word;
	int occur;
	vector<int> pages;
};

struct Node{
	text txt;
	Node* next[16];
};  


Node *head = new Node;
int MAX_HEIGHT = 16;
Node* update[16];

void find(string word, int lnumber);
void insert(string word, int lnumber);
void printInOrder(ostream & output);