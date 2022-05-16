#include <iostream>
using namespace std;


template<typename T>
class circularQueue{
    int head = 0;
    int tail = -1;
    T* circArr;
    int dimQueue;
    int count = 0;
    public:
        circularQueue(int dim) : dimQueue(dim){
            circArr = new T[dimQueue];
        }

        ~circularQueue(){delete [] circArr;}               

        bool isEmpty(){
            return count == 0;
        }

        bool isFull(){
            return count == dimQueue;
        }

        void enqueue(T data){
            if(!isFull()){
                tail = (++tail)%dimQueue;
                circArr[tail] = data;
                cout << "I'm inserting: " << circArr[tail] << endl;
                count++;
            }
            else{
                cout << "Full queue!" << endl;
            }
        }

        void dequeue(){
            if(!isEmpty()){
                cout << "I'm removing: " << circArr[head] << endl;
                head = ((++head)%dimQueue);
                count--;
            }
            else{
                cout << "Empty queue!" << endl;
            }
        }

        T front(){
            return circArr[head];
        }

};



int main(){
    /*
    circularQueue<int> queue1(5);
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);
    queue1.enqueue(4);
    queue1.enqueue(5);
    queue1.dequeue();
    queue1.dequeue();
    queue1.enqueue(3);
    queue1.enqueue(4);
    queue1.dequeue();
    queue1.dequeue();
    queue1.dequeue();
    queue1.dequeue();
    queue1.dequeue();
    queue1.dequeue();
    */
}