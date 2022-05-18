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



int main(){
    ListQueue<int> queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    queue.enqueue(400);
    queue.dequeue();
    cout << queue.front() << endl; //200
}