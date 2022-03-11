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

        virtual void insert(int pos, T d){
            this->len++;
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

        T& accessData(int ind){
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

        void insert(int pos, T d) override{
            if (pos == 0){
                Node<T>* nodo = this->accessNode(this->len - 1);
                Node<T>* newobj = new Node<T>(d);
                nodo->succ = newobj;
                newobj->succ = this->head;
                this->head = newobj;
                this->len++;
            }
            else{
                LinkedList<T>::insert(pos, d);
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
        T& accessData(int ind){
            if(ind < len){
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
                return node->data;
            }
            else{
                cout << "Non esiste, return head" << endl;
            }
            return head->data;
        }

        DoubleNode<T>* accessNode(int ind){
            DoubleNode<T>* node;
            if(ind < len){
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
            else{
                cout << "Non esiste, return head" << endl;
            }
            return head;
        }

        void changeData(int pos, T data){
            this->accessData(pos) = data;
        }

        void insert(int ind, T d) {
            DoubleNode<T>* node = new DoubleNode<T>(d);
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


int main(){

    LinkedList<int> list(5, 10);
    cout << list.accessData(4) << endl;
    list.insert(5, 30);
    cout << list.accessData(5) << endl;
    CircularLinkedList<int> list2(10, 23);
    Node<int>* circ = list2.accessNode(9);
    list2.changeData(0, 500);
    cout << (circ->succ)->data << endl;
    DoublyLinkedList<string> list3(7, "Hello");
    list3.changeData(3, "World");
    list3.insert(7, "String");
    list3.insert(7, "Another string");
    cout << list3.accessData(3) << " " << list3.accessData(7) << " " << list3.accessData(8) << endl;
    
}
