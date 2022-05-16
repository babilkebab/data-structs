#include <iostream>
#include <list>
using namespace std;


template <typename T>
class ListStack{
    list<T>* liststk;
    //liststk.front() for SP (this is a ref)
    public:
        ListStack(){
            liststk = new list<T>;
        }

        ~ListStack(){
            delete liststk;
        }

        void push(T data){
            liststk->push_front(data);
        }

        void pop(){
            if(!liststk->empty())
                liststk->pop_front();
            else
                cout << "Empty stack!" << endl;
        }

        T getTop(){
            return liststk->front();
        }

};
