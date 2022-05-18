#include <iostream>
#include <list>
using namespace std;


template <typename T>
class ListStack{
    list<T>* liststk;
    //liststk->front() for SP (returns a ref)
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

        T pop(){
            if(!liststk->empty()){
                T ret = getTop();
                liststk->pop_front();
                return ret;
            }
            else
                cout << "Empty stack!" << endl;
                exit(-1);
        }

        T getTop(){
            if(liststk->front())
                return liststk->front();
            cout << "Empty stack!" << endl;
            exit(-1);
        }

};
