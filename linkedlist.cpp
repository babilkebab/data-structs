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
class DoubleNode{
    public:
        DoubleNode* prec;
        T data;
        DoubleNode* succ;
        DoubleNode(T d){
            data = d;
            prec = nullptr;
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

        LinkedList() : len(0){}

        virtual void insert(T d, int pos = 0){
            Node<T>* newobj = new Node<T>(d);
            if(len == 0){
                head = newobj;
                len++;
                return;
            }
            pos = pos%len;
            Node<T>* node = head;
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
            this->len++;
        }

        T& accessData(int ind){
            ind = ind%len;
            Node<T>* node = head;
            for(int i = 0; i < ind; i++){
                node = node->succ;
            }
            return node->data;
        }

        Node<T>* accessNode(int ind){
            ind = ind%len;
            Node<T>* node = head;
            for(int i = 0; i < ind; i++){
                node = node->succ;
            }
            return node;
        }

        void changeData(int pos, T data){
            this->accessData(pos) = data;
        }

};


template<typename T>
class CircularLinkedList : public LinkedList<T>{
    public:
        CircularLinkedList(int n, T init) : LinkedList<T>(n, init){
            Node<T>* nodo = this->accessNode(n-1);
            nodo->succ = this->head;
        }

        CircularLinkedList() : LinkedList<T>(){}

        void insert(T d, int pos = 0) override{
            Node<T>* newobj = new Node<T>(d);
            if (this->len == 0){
                this->head = newobj;
                this->len++;
                return;
            }
            pos = pos%this->len;
            if (pos == 0){
                Node<T>* nodo = this->accessNode(this->len - 1);
                nodo->succ = newobj;
                newobj->succ = this->head;
                this->head = newobj;
                this->len++;
            }
            else{
                LinkedList<T>::insert(d, pos);
            }
        }
};

template<typename T>
class DoublyLinkedList{
    public:
        DoubleNode<T>* head;
        int len;
        DoublyLinkedList(int n, T init) : len(n){
            head = new DoubleNode<T>(init);
            DoubleNode<T>* p = head;
            DoubleNode<T>* s = head;
            for(int i = 0; i < n-1; i++){
                DoubleNode<T>* node = new DoubleNode<T>(init);
                s->succ = node;
                s = s->succ;
                s->prec = p;
                p = p->succ;
            }
            head->prec = s;
        }

        DoublyLinkedList() : len(0){}

        T& accessData(int ind){
            ind = ind%len;
            DoubleNode<T>* node;
            if(ind <= len/2){
                node = head;
                for(int i = 0; i < ind; i++){
                    node = node->succ;                    
                }
            }
            else{
                node = head->prec;
                for(int i = len-1; i > ind; i--){
                    node = node->prec;
                }
            }
            return node->data;
        }

        DoubleNode<T>* accessNode(int ind){
            ind = ind%len;
            DoubleNode<T>* node;
            if(ind < len/2){
                node = head;
                for(int i = 0; i < ind; i++){
                    node = node->succ;
                }    
            }
            else{
                node = head->prec;
                for(int i = len-1; i > ind; i--){
                    node = node->prec;
                }
            }
            return node;
        }

        void changeData(int pos, T data){
            this->accessData(pos) = data;
        }

        void insert(T d, int ind = 0) {
            DoubleNode<T>* node = new DoubleNode<T>(d);
            if(len == 0){
                head = node;
                len++;
                return;
            }
            ind = ind%len;
            DoubleNode<T>* it;
            if(ind < len/2 && ind != 0 && ind != len){
                it = head;
                for(int i = 0; i < ind; i++){
                    it = it->succ;
                }
                DoubleNode<T>* temp = it->succ;
                it->succ = node;
                node->prec = it;
                node->succ = temp;
                temp->prec = node;
            }
            else if (ind >= len/2 && ind != 0 && ind != len){
                it = head->prec;
                for(int i = len-1; i > ind; i--){
                    it = it->prec;
                }
                DoubleNode<T>* temp = it->prec;
                it->prec = node;
                node->prec = temp;
                node->succ = it;
                temp->succ = node;
            }
            else if(ind == 0){
                it = head;
                it->prec->succ = node;
                node->prec = it->prec;
                it->prec = node;
                head = node;
                head->succ = it;
            }
            else if(ind == len){
                it = head->prec;
                it->succ = node;
                node->prec = it;
                node->succ = head;
                head->prec = node;               
            }
            len++;
        }
};
