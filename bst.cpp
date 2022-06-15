#include <iostream>
#include <cstdlib>
using namespace std;


template<typename T>
class BSTNode{
public:
    BSTNode<T>* father;
    BSTNode<T>* l;
    BSTNode<T>* r;
    T data;
    BSTNode(T dt) : data(dt), father(nullptr), l(nullptr), r(nullptr){}
};



template <typename T>
class BST{
    BSTNode<T>* root;

    BSTNode<T>* minimum(BSTNode<T>* rt){
        BSTNode<T>* iter = root;
        while(iter->r != nullptr || iter->l != nullptr){
            iter = iter->l;
        }
        return iter;
    }

    BSTNode<T>* maximum(BSTNode<T>* rt){
        BSTNode<T>* iter = rt;
        while(iter->r != nullptr || iter->l != nullptr){
            iter = iter->r;
        }
        return iter;
    }

    void inorder(BSTNode<T>* root){
        if(root != nullptr){
            inorder(root->l);
            cout << root->data << " ";
            inorder(root->r);
        }
    }

    void preorder(BSTNode<T>* root){
        if(root != nullptr){
            cout << root->data << " ";
            preorder(root->l);
            preorder(root->r); 
        }
    }

    void postorder(BSTNode<T>* root){
        if(root != nullptr){
            postorder(root->l);
            postorder(root->r);
            cout << root->data << " ";
        }
    }

    void levelorder(BSTNode<T>* rt, int level){  
        if(rt && level > 0){
            levelorder(rt->l, level-1);
            levelorder(rt->r, level-1);
        }
        if(rt && level == 0)
            cout << rt->data << "\t";
        else if(!rt && level == 0)
            cout << "\t";
    }

    void transplant(BSTNode<T>* z, BSTNode<T>* y){
        if(!z->father) //transplant root
            root = y;
        else if(z->father->l == z) //transplant left subtree
            z->father->l = y;
        else //transplant right subtree
            z->father->r = y;
        if(y) //if y isn't null his new father is z's father
            y->father = z->father;
    }

public:
    BST() : root(nullptr){}

    friend ostream& operator<< (ostream& out, BST& tree){
        int lv = tree.depth(tree.root);
        for(int i = 0; i <= lv; i++){
            tree.levelorder(i);
            cout << endl;
        }
        return out;
    }

    BSTNode<T>* minimum(){
        return minimum(root);
    }

    BSTNode<T>* maximum(){
        return maximum(root);
    }
    

    BSTNode<T>* predecessor(BSTNode<T>* node){
        if(node->l != nullptr){ //exists left subtree of parameter
            node = node->l;
            node = maximum(node);
            return node;
        }

        //else
        BSTNode<T>* dad = node->father;
        while(dad != nullptr && node == dad->l){
            node = dad;
            dad = dad->father;
        }
        return dad;
    }

    BSTNode<T>* successor(BSTNode<T>* node){
        if(node->r != nullptr){ //exists right subtree of parameter
            node = node->r;
            node = minimum(node);
            return node;
        }

        //else
        BSTNode<T>* dad = node->father;
        while(dad != nullptr && node == dad->r){
            node = dad;
            dad = dad->father;
        }
        return dad;
    }

    BSTNode<T>* search(T dt){
        BSTNode<T>* iter = root;
        while(iter && iter->data != dt){
            if(iter->data < dt)
                iter = iter->r;
            else
                iter = iter->l;
        }
        if(iter)
            return iter;
        cout << "Element isn't in this BST" << endl;
        exit(-1);
    }


    void inorder(){  //MASKS FOR PRIVATE ONES (ROOT PARAMETER IS PRIVATE, DON'T ACCESS FROM OUTSIDE THE CLASS)
        inorder(root);
    }

    void preorder(){  //MASKS FOR PRIVATE ONES (ROOT PARAMETER IS PRIVATE, DON'T ACCESS FROM OUTSIDE THE CLASS)
        preorder(root);
    }

    void postorder(){  //MASKS FOR PRIVATE ONES (ROOT PARAMETER IS PRIVATE, DON'T ACCESS FROM OUTSIDE THE CLASS)
        postorder(root);
    }

    void levelorder(int level){  //MASKS FOR PRIVATE ONES (ROOT PARAMETER IS PRIVATE, DON'T ACCESS FROM OUTSIDE THE CLASS)
        levelorder(root, level);
    }

    int depth(BSTNode<T>* rt){
        if(!rt) return 0;
        
        int lh = depth(rt->l);
        int rh = depth(rt->r);

        if(lh > rh) return lh+1;
        else return rh+1;

    }

    void insert(T dt){
        BSTNode<T>* newelem = new BSTNode<T>(dt);

        if(!root){
            root = newelem;
            return;
        }

        BSTNode<T>* iter = root;
        BSTNode<T>* iterdad;

        while(iter){
            iterdad = iter;
            if(dt < iter->data)
                iter = iter->l;
            else
                iter = iter->r;
        }

        iter = newelem;
        iter->father = iterdad;

        (dt < iterdad->data) ? iterdad->l = newelem : iterdad->r = newelem;
    }

    bool del(T dt){ //1 if deletion is successful, 0 otherwise
        BSTNode<T>* del_node = search(dt);
        if(!del_node){ //node not found
            cout << "Node not found, 404 =(";
            return 0;
        }
        else if(!del_node->r){ //node has only left subtree
            transplant(del_node, del_node->l);
        }
        else if(!del_node->l){ //node has only right subtree
            transplant(del_node, del_node->r);
        }
        else{ //node has two subtrees
            BSTNode<T>* succ = successor(del_node); //replace delnode with his successor
            cout << succ->data << endl;
            if(succ != del_node->r){ // if successor isn't delnode's son(succ is in right subtree)
                transplant(succ, succ->r); //successor is replaced with his right subtree (successor hasn't left subtree, because it's successor)
                succ->father = del_node->father; //new succ's father is delnode's father
                succ->r->father = succ; //and delnode's right subtree is now succ's right subtree

            }
            transplant(del_node, succ); //main subsitution. Delnode was substituted with successor
            succ->l = del_node->l; //new succ's left subtree is delnode's left subtree
            succ->l->father = succ; //and delnode's left subtree is now succ's left subtree

        }
        delete del_node;
        return 1;  
    }

};




int main(){
    srand(5649812);
    BST<int> mytree;

    mytree.insert(10);
    mytree.insert(8);
    mytree.insert(13);
    mytree.insert(15);
    mytree.insert(14);
    mytree.insert(7);
    mytree.insert(9);
    mytree.insert(16);
    mytree.del(13);
    mytree.del(9);

    cout << mytree;
    cout << mytree.minimum()->data << endl;
    cout << mytree.search(40)->data << endl;
}