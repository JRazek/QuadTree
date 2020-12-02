#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <set>
using namespace std;

const int mod = 1e9+7;
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

struct Vector2F{
    float x, y;
    Vector2F(float x, float y){
        this->x = x, this->y = y;
    }
    static bool commonPart(Vector2F &v1, Vector2F &v2){
        int min = v1.x > v2.x ? v1.x : v2.x;
        int max = v1.y <= v2.y ? v1.y : v2.y;
        return min <= max;
    }
};
struct QuadTree{
    struct QuadNode{
        QuadNode(int id, int type, int level, Vector2F pos, QuadNode * p = NULL) : id(id), type(type), pos(pos), level(level){
            this->parent = p;
        };
        Vector2F pos;
        const int id;
        const int level;
        const int type;

        QuadNode * parent;

        QuadNode * NW;
        QuadNode * NE;
        QuadNode * SW;
        QuadNode * SE;

    };

    QuadNode * root;
    vector<QuadNode *> nodes ;
    const int depth;
    const string description;

    int deepestNodeHeight = 0;

    QuadTree(string description, int depth) : description(description), depth(depth){
        int currID = 0;
        this->root = new QuadNode(currID, this->description[0] - '0',  0, Vector2F(0,0));

        stack<pair<QuadNode *, int>> pq;
        pq.push(make_pair(root, 0));
        while(!pq.empty()){
            QuadNode * q = pq.top().first;
            int entryNum = pq.top().second;
            if(q->level > deepestNodeHeight)
                deepestNodeHeight = q->level;
            if(entryNum == 0){
                nodes.push_back(q);
            }
            if(q->type == 4) {
                QuadNode * child = new QuadNode(++currID, description[currID] - '0', q->level + 1, Vector2F(0,0), q);
                switch (entryNum) {
                    case 0:
                        q->NW = child;
                        break;
                    case 1:
                        q->NE = child;
                        break;
                    case 2:
                        q->SW = child;
                        break;
                    case 3:
                        q->SE = child;
                        break;
                }
                pq.top().second++;
                if (pq.top().second == 4) {
                    pq.pop();
                }
                pq.push(make_pair(child, 0));
            }else{
                pq.pop();
            }
        }
    }


    struct Edge{

    };

    void dfsMark(QuadNode * n){
        if(n->type == 4){
            dfsMark(n->NW);

            dfsMark(n->NE);
            dfsMark(n->SW);
            dfsMark(n->SE);
        }
    }
    ~QuadTree(){
        delete root;
    }

};



int main() {
    rlimit * f = new rlimit();
    f->rlim_cur = 200000000;
    f->rlim_max = 250000000;
    setrlimit(RLIMIT_STACK, f);

    int treeHeight;
    string treeDescription;
    cin >> treeHeight;
    cin >> treeDescription;
    int num = 0;
    cout<<"\n";

    QuadTree q = QuadTree(treeDescription, num);
    //quadTree.unionDFS();
    q.dfsMark(q.root);
    return 0;
}
