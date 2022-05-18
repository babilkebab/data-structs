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
        }

        T getTop(){
            return liststk->front();
        }

};





int main(){
    ListStack<int> stk;
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.pop();
    stk.push(300);
    cout << stk.getTop() << endl; //300
}