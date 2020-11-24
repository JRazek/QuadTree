#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int mod = 1000000007;

struct Union;
struct QuadTree{
    int type;
    QuadTree * parent;

    QuadTree * leftUp;
    QuadTree * rightUp;
    QuadTree * leftBot;
    QuadTree * rightBot;

    Union * belongingUnion;

    QuadTree(int &numInTreeDescription, string & treeDescription, QuadTree * parent = nullptr){
        this->type = (treeDescription[numInTreeDescription]-'0');
        this->parent = parent;
        numInTreeDescription ++;
        if(this->type == 4){
            leftUp = new QuadTree(numInTreeDescription, treeDescription, this);
            rightUp = new QuadTree(numInTreeDescription, treeDescription, this);
            leftBot = new QuadTree(numInTreeDescription, treeDescription, this);
            rightBot = new QuadTree(numInTreeDescription, treeDescription, this);
        }
    }

    vector<Union *> findUnions{

    };

};

struct Union{
    unordered_set<QuadTree *> elements;
};

int main() {
    int treeHeight;
    string treeDescription;
    cin >> treeHeight;
    cin >> treeDescription;

    int num = 0;
    QuadTree quadTree(num, treeDescription);
    return 0;
}
