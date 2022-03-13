template<typename T>
class Stack{
    T* st;
    int ptr;
    int len;
    public:
        Stack(int l) : len(l){
            st = new T[len];
            ptr = -1;
        }

        void push(T data){
            if(ptr == len){
                cout << "Stack pieno" << endl;
                return;
            }
            st[ptr+1] = data;
            ptr++;
        }

        void pop(){
            if(ptr == -1){
                cout << "Stack vuoto" << endl;
                return;
            }
            ptr--;
        }

        void access(){
            cout << st[ptr] << endl;
        }
};
