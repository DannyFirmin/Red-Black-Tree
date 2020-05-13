#include<iostream>
#include<fstream>
#include<string>
#include "rbtree.h"
using namespace std;
int startArr[50000000];
int endArr[50000000];

int main(int argc,char **argv){
	if (argc!=2){
		cout<<"Error: Input file not specified or too many arguments"<<endl<<"Usage: Program FileName"<<endl;
		return -1;
	}
	ifstream fin(argv[1]);
	// Check if file has been opened properly
	if (!fin.is_open()){
		cout<<"Error: input file cannot be opened"<<endl;
		return -1;
	}

	// Your program
    RBTree<int, int> *tree = new RBTree<int, int>();
    int N;
    fin >> N;

    for (int n = 0; n<N; n++){
        int id;
        int startTime;
        int endTime;
        fin >> id;
        fin >> startTime;
        fin >> endTime;
        startArr[n] = startTime;
        endArr[n] = endTime;
        tree->insert(startTime, id, 1);
        tree->insert(endTime, id, -1);
        }
    Node<int,int> *root = tree->getRoot();

    cout << root->o << " " << root->m << endl;
    for (int i = 0; i < N; i++){
        if (root->o >= startArr[i] && root->o < endArr[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;

    tree->destroy();
    return 0;
}


