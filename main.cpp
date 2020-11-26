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
struct Quartet{
    unordered_set<QuadTree *> up;
    unordered_set<QuadTree *> left;
    unordered_set<QuadTree *> right;
    unordered_set<QuadTree *> bot;
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
        Quartet q = subRegions();
        cout<<"";
    }

private:
    Quartet subRegions(){

        Quartet q = Quartet();

        if(this->type == 4) {
            Quartet tmpLeftUp = leftUp->subRegions();

            Quartet tmpRightUp = rightUp->subRegions();

            Quartet tmpLeftBot = leftBot->subRegions();

            Quartet tmpRightBot = rightBot->subRegions();

            unordered_set<QuadTree *> upperEdge = tmpLeftUp.up;
            upperEdge.insert(tmpRightUp.up.begin(), tmpRightUp.up.end());

            unordered_set<QuadTree *> leftEdge = tmpLeftUp.left;
            leftEdge.insert(tmpLeftBot.left.begin(), tmpLeftBot.left.end());


            unordered_set<QuadTree *> botEdge = tmpLeftBot.bot;
            botEdge.insert(tmpRightUp.bot.begin(), tmpRightUp.bot.end());

            unordered_set<QuadTree *> rightEdge =  tmpRightUp.right;
            rightEdge.insert(tmpRightBot.right.begin(), tmpRightBot.right.end());


            q.up = upperEdge;
            q.left = leftEdge;
            q.right = rightEdge;
            q.bot = botEdge;
        }
        else if(this->type == 1){
            q.up.insert(this);
            q.left.insert(this);
            q.bot.insert(this);
            q.right.insert(this);
        }
    return q;
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
