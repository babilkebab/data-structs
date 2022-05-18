#include <iostream>
#include <list>
using namespace std;

template <typename T>
class ListQueue{
    list<T>* lst;
    public:
        ListQueue(){
            lst = new list<T>;
        }

        ~ListQueue(){
            delete lst;
        }

        void enqueue(T data){
            lst->push_back(data);
        }

        void dequeue(){
            if(!lst->empty())
                lst->pop_front();
            else
                cout << "Empty queue!" << endl;
        }

        T front(){
            return lst->front();
        }
};
