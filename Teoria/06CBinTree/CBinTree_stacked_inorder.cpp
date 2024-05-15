#include <iostream>
#include <stack>
using namespace std;

struct Node {
    int value;
    Node* nodes[2];

    Node(int);
};

struct BinTree {
    Node* root;
    bool switcher;

    BinTree();
    bool find(int, Node**&);
    bool insert(int);
    bool remove(int);
    Node** closest_replace(Node**);
    void print_inorder();
    void inorder(Node*);
    void print_stacked_inorder();
    void staked_inorder(Node*);
};

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

int main() {
    BinTree tree;

    tree.insert(50); tree.insert(30); tree.insert(60);
    tree.insert(80); tree.insert(55); tree.insert(11);
    tree.insert(33); tree.insert(5); tree.insert(14);
    tree.insert(31); tree.insert(48);
    tree.print_inorder();
    tree.print_stacked_inorder();

    tree.remove(33); tree.remove(5); tree.remove(14);
    tree.print_inorder();
    tree.print_stacked_inorder();

    return 0;
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------

Node::Node(int v) {
    value = v;
    nodes[0] = nodes[1] = nullptr;
}

//*********************************************************************************************

BinTree::BinTree() {
    root = nullptr;
    switcher = 0;
}

bool BinTree::find(int v, Node**& p) {
    for (p = &root; *p && (*p)->value != v; p = &(*p)->nodes[v > (*p)->value]);
    return *p;
}

bool BinTree::insert(int v) {
    Node** p = nullptr;

    if (find(v, p))
        return false;

    *p = new Node(v);
    return true;
}

bool BinTree::remove(int v) {
    Node** p = nullptr;

    if (!find(v, p))
        return false;

    //Case 2
    if ((*p)->nodes[0] != nullptr && (*p)->nodes[1] != nullptr) {
        Node** q = closest_replace(p);
        (*p)->value = (*q)->value;
        delete* q;
        *q = nullptr;
        return true;
    }

    //Case 0 - 1
    Node* tree = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == nullptr];
    delete tree;
    return true;
}

Node** BinTree::closest_replace(Node** p) {
    for (p = &(*p)->nodes[switcher]; (*p)->nodes[!switcher] != nullptr; p = &(*p)->nodes[!switcher]);
    return p;
}

void BinTree::print_inorder() {
    inorder(root);
    cout << endl;
}

void BinTree::inorder(Node* p) {
    if (!p)
        return;

    inorder(p->nodes[0]);
    cout << "  " << p->value;
    inorder(p->nodes[1]);
}

void BinTree::print_stacked_inorder() {
    staked_inorder(root);
    cout << endl;
}

void BinTree::staked_inorder(Node* p) {
    if (p == nullptr)
        return;
    
    stack<pair<Node*, int>> container;
    container.push({p, 0});
    
    while (!container.empty()) {        
        if (container.top().first == nullptr)
            container.pop();

        switch (container.top().second) {
            case 0:
                container.top().second = 1;
                container.push({ container.top().first->nodes[0], 0});
                break;
            case 1:
                container.top().second = 2;
                cout << "  " << container.top().first->value;
                break;
            case 2:
                container.top().second = 3;
                container.push({ container.top().first->nodes[1], 0 });
                break;
            case 3:
                container.pop();
                break;
        }
    }
}