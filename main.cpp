#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int mod = 1000000007;
struct QuadTree;
struct Union{
    unordered_set<QuadTree *> elements;
};
void mergeUnions(Union * u1, Union * u2){
    u1->elements.merge(u2->elements);
    delete u2;
}

struct SquareEdges{
    unordered_set<QuadTree *> up;
    unordered_set<QuadTree *> left;
    unordered_set<QuadTree *> right;
    unordered_set<QuadTree *> bot;
};

struct PathNode{
    PathNode(int type, QuadTree * nodeInQuadTree){
        this->type = type;
        this->nodeInQuadTree = nodeInQuadTree;
    }
    QuadTree * nodeInQuadTree;
    int type;
    PathNode * NW;
    PathNode * SW;
    PathNode * NE;
    PathNode * SE;
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


    void unionDFS(){

        cout<<"";
    }

private:

    PathNode * subRegions(){

        if(this->type == 4) {
            PathNode * NW = this->leftUp->subRegions();
            PathNode * SW = this->leftBot->subRegions();
            PathNode * NE = this->rightUp->subRegions();
            PathNode * SE = this->rightBot->subRegions();

            PathNode * p = new PathNode(4, this);
            if(NW != nullptr)
                p->NW = NW;
            if(SW != nullptr)
                p->SW = SW;
            if(NE != nullptr)
                p->NE = NE;
            if(SE != nullptr)
                p->SE = SE;



            return p;
        }else if(this->type == 1){
            return new PathNode(1, this);
        }
        return nullptr;
    }
};



int main() {
    int treeHeight;
    string treeDescription;
    cin >> treeHeight;
    cin >> treeDescription;

    int num = 0;
    QuadTree quadTree(num, treeDescription);
    quadTree.unionDFS();
    return 0;
}
