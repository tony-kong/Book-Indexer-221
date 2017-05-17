#include "skippedlist.h"
using namespace std;

Node *head = new Node;
Node *update[MAX_HEIGHT];

int randBit(void) {             // return a "random" bit
  static int bitsUpperBd=0;
  static int bits;              // store bits returned by rand()
  if( bitsUpperBd == 0 ) {      // refresh store when empty
    bitsUpperBd = RAND_MAX;
    bits = rand();
  }
  int b = bits & 1;
  bits >>= 1;
  bitsUpperBd >>= 1;
  return b;
}

void find(string word, int lnumber){
    int pg = lnumber/40 + 1;
	for (int h = MAX_HEIGHT -1; h>=0; h--){
        Node *prev = head;
		while(prev->next[h] != NULL && prev->next[h]->txt.word<word){
			prev = prev->next[h];
		}
        update[h] = prev;
		if (prev->next[h] != NULL && prev->next[h]->txt.word == word){
			prev->next[h]->txt.occur++;
			for (vector<int>::iterator it = prev->next[h]->txt.pages.begin(); it != prev->next[h]->txt.pages.end(); ++it){
				if (*it==pg) return;
			}
			prev->next[h]->txt.pages.push_back(pg);
			return;
		}
	}
	insert(word, pg);
}

void insert(string word, int lnumber){
	text newText;
	newText.word = word;
	newText.occur = 1;
	newText.pages.push_back(lnumber);
	Node *newNode = new Node;
	newNode->txt = newText;
    int height = 1;
	for(int i=1; i<MAX_HEIGHT; ++i) {
		if( randBit() == 1 ) break;
        height = i;
	}
	for (int h = 0; h < height; ++h){
		newNode->next[h] = update[h]->next[h];
		update[h]->next[h]=newNode;
	}
}

void printInOrder(ostream & output){
	Node *prev = head->next[0];
	while (prev != NULL){
		output <<prev->txt.word << " ";
		output << '(' <<prev->txt.occur << ')' << " ";
        int currNum = prev->txt.pages[0] ;
        int startNum = prev->txt.pages[0];
        int prevNum;
        int i = 0;
        for (vector<int>::iterator it = prev->txt.pages.begin(); it != prev->txt.pages.end(); ++it){
            currNum = *it;
            if (currNum - startNum == i){
                i++;
                prevNum = currNum;
            }
            //all the different possible cases for consecutive and non consecutive numbers
            else if (i>1 && it == --prev->txt.pages.end()){
                output << startNum << '-' << prevNum << ',' << currNum;
                i = 0;
            }
            else if (i>1) {
                    output << startNum << '-' << prevNum << ',';
                    i = 1;
                    startNum = currNum;
                }
            else if (i==1 && it == --prev->txt.pages.end()){
                output << startNum << ',' << currNum;
                i = 0;
            }
            else if (i == 1){
                output << startNum << ",";
                startNum = currNum;
            }
            }
        // if entire list of page numbers is consecutive
        if (i>1) output << startNum << '-' << currNum;
        // if there is only one page
        else if (i == 1) output << currNum;
		output << endl;
        prev = prev->next[0];
	}
}