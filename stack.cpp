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
    
        ~Stack(){
            delete [] st;
        }

        void push(T data){
            if(ptr == len-1){
                cout << "Full stack" << endl;
                return;
            }
            st[++ptr] = data;
        }

        void pushmultiple(int cnt, ...){
            if(cnt > len - (ptr+1)){
                cout << "Invalid operation" << endl;
                return;
            }
            va_list elems;
            va_start(elems, cnt);
            for(int i = 0; i < cnt; i++){
                this->push(va_arg(elems, T));
            }
        }

        void popmultiple(int cnt){
            if (cnt > ptr+1){
                cout << "Invalid operation" << endl;
                return;
            }
            for(int i = 0; i < cnt; i++){
                this->pop();
            }
        }

        void pop(){
            if(ptr == -1){
                cout << "Empty stack" << endl;
                return;
            }
            ptr--;
        }

        T access(){
            if(ptr == -1){
                cout << "Empty stack" << endl;
                return 0;
            }
            return st[ptr];
        }

        vector<T> accessmultiple(int numelems){
            vector<T> ret;
            if(numelems > ptr+1){
                cout << "Too elements to access" << endl;
                return ret;
            }
            int fptr = ptr;
            for(int i = 0; i < numelems; i++){
                ret.push_back(st[fptr]);
                fptr--;
            }
            return ret; 
        }

};
