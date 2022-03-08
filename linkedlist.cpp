#include <iostream>
using namespace std;


template<typename T>
class Node{
    public:
        T data;
        Node* succ;
            Node(T d){
                data = d;
                succ = nullptr;
            }

};


template<typename T>
class LinkedList{
    public:
        int len;
        Node<T>* head;
        LinkedList(int n, T init) : len(n){
            head = new Node<T>(init);
            Node<T>* loop = head;
            for(int i = 0; i < n-1; i++){
                Node<T>* nodo = new Node<T>(init);
                loop->succ = nodo;
                loop = nodo;
            }
            loop->succ = nullptr;
        }

        virtual void insert(int pos, T d){
            Node<T>* node = head;
            Node<T>* newobj = new Node<T>(d);
            for(int i = 0; i < pos+1; i++){
                if(i == pos-1){
                    node->succ = newobj;
                    continue;
                }
                if (pos == 0){
                    newobj->succ = this->head;
                    this->head = newobj;
                    return;
                } 
                node = node->succ;
            }
            newobj->succ = node;
        }

        T& access(int ind){
            Node<T>* node = head;
            for(int i = 0; i < ind; i++){
                node = node->succ;
            }
            return node->data;
        }

        Node<T>* accessNode(int ind){
            Node<T>* node = head;
            for(int i = 0; i < ind; i++){
                node = node->succ;
            }
            return node;
        }

        void changeData(int pos, T data){
            this->access(pos) = data;
        }

};


template<typename T>
class CircularLinkedList : public LinkedList<T>{
    public:
        CircularLinkedList(int n, T init) : LinkedList<T>(n, init){
            Node<T>* nodo = this->accessNode(n-1);
            nodo->succ = this->head;
        }

        void insert(int pos, T d) override{
            if (pos == 0){
                Node<T>* nodo = this->accessNode(this->len - 1);
                Node<T>* newobj = new Node<T>(d);
                nodo->succ = newobj;
                newobj->succ = this->head;
                this->head = newobj;
            }
            else{
                LinkedList<T>::insert(pos, d);
            }
        }
};


int main(){

    LinkedList<int> list(5, 10);
    cout << list.access(0) << endl;
    list.insert(5, 30);
    cout << list.access(5) << endl;
    CircularLinkedList<int> list2(10, 23);
    Node<int>* circ = list2.accessNode(9);
    list2.changeData(0, 500);
    cout << (circ->succ)->data << endl;


}