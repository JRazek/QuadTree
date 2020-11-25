#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int mod = 1000000007;
struct QuadTree;
struct Union{
    unordered_set<QuadTree *> elements;
};

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
    vector<Union *> unionDFS(int side = -1){
        if(type == 1){
            Union * u = new Union();
            u->elements.insert(this);
            return {u};
        }
        else if(type == 4){
            vector<Union *> unions;
            if(leftUp->type == 1 || leftUp->type == 4 && leftBot->type == 1 || leftBot->type == 4) {
                leftBot->unionDFS(0);
                
            }
        }
        return {};
    }
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
