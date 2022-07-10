//L'ESSENZA DI PROG2 IN UN SOLO SORGENTE

#include <iostream>
using namespace std;

//ORDINAMENTO E RICERCA

template <typename T>
void swap(T* n1, T* n2){
    T temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

template <typename T>
void printarr(T* arr, int n){
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

template <typename T>
void bubblesort(T* arr, int n){
    bool sorted = false;
    while(sorted==false){
        sorted = true;
        for(int i = 0; i < n-1; i++){
            if(arr[i] > arr[i+1]){
                swap(&arr[i], &arr[i+1]);
                sorted = false;
            }
        }
    }
}

template <typename T>
void inssort(T* arr, int n){
    for(int i = 1; i < n; i++){
        int j = i;
        T aux = arr[i];
        while(arr[j] >= aux && j >= 0){
            arr[j] = arr[j-1];
            j--; 
        }
        arr[j+1] = aux;
    }
}

template <typename T>
void swapinssort(T* arr, int n){ //come piace a me
    for(int i = 1; i < n; i++){
        int j = i;
        while(arr[j] < arr[j-1] && j > 0){
            swap(arr[j], arr[j-1]);
            j--;
        }
    }
}

template <typename T>
void selsort(T* arr, int n){
    for(int i = 0; i < n-1; i++){
        T min = arr[i];
        int posmin = i;
        for(int j = i+1; j < n; j++){
            if(arr[j] < min){
                min = arr[j];
                posmin = j;
            }
        }
        swap(arr[posmin], arr[i]);
    }
}

template <typename T>
void merge(T* arr, int sx, int m, int dx){
    int n1 = m-sx+1;
    int n2 = dx-m;
    T arr1[n1], arr2[n2];
    int j = 0;
    for(int i = sx; i <= m; i++){
        arr1[j] = arr[i]; 
        j++;
    }
    j = 0;
    for(int i = m+1; i <= dx; i++){
        arr2[j] = arr[i]; 
        j++;
    }
    int i = 0, k = sx;
    j = 0;
    while(i < n1 && j < n2){
        if(arr1[i] < arr2[j]){
            arr[k] = arr1[i];
            i++;
        }
        else{
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }
    if(i == n1){
        while(j < n2){
            arr[k] = arr2[j];
            j++;
            k++;
        }
    }
    else{
        while(i < n1){
            arr[k] = arr1[i];
            i++;
            k++;
        }
    }
}

template <typename T>
void mergesort(T* arr, int sx, int dx){
    if(sx < dx){
        int m = (sx+dx)/2;
        mergesort(arr, sx, m);
        mergesort(arr, m+1, dx);
        merge(arr, sx, m, dx);
    }
}

template <typename T>
void mergesort(T* arr, int n){ //MERGESORT MASK
    mergesort(arr, 0, n-1);
}

template <typename T>
int partition(T* arr, int sx, int dx){
    int i = sx-1;
    int j = sx;
    while(j < dx){
        if(arr[j] < arr[dx]){ //arr[dx] È IL PIVOT
            i++;
            swap(arr[i], arr[j]);
        }
        j++;
    }
    swap(arr[i+1], arr[dx]);
    return i+1;
}

template <typename T>
void quicksort(T* arr, int sx, int dx){
    if(sx < dx){    
        int m = partition(arr, sx, dx);
        quicksort(arr, sx, m-1);
        quicksort(arr, m+1, dx);
    }
}

template <typename T>
void quicksort(T* arr, int n){ //QUICKSORT MASK
    quicksort(arr, 0, n-1);
}

template <typename T>
int search(T* arr, int n, T elem){
    for(int i = 0; i < n; i++){
        if(arr[i] == elem)
            return i;
    }
    return -1; //SE NON TROVA NIENTE
}

template <typename T>
int iterbinsearch(T* arr, int n, T elem){
    int l = 0, r = n-1, m;
    while(l <= r){
        m = (l+r)/2;
        if(arr[m] == elem)
            return m;
        else if(arr[m] > elem)
            r = m-1;
        else
            l = m+1;
    }
    return -1; //SE NON TROVA NIENTE
}

template <typename T>
int recbinsearch(T* arr, int sx, int dx, T elem){
    if(sx <= dx){
        int m = (sx+dx)/2;
        if(arr[m] == elem)
            return m;
        else if(arr[m] > elem)
            return recbinsearch(arr, sx, m-1, elem);
        else
            return recbinsearch(arr, m+1, dx, elem);
    }
    return -1; //SE NON TROVA NIENTE
}

template <typename T>
int recbinsearch(T* arr, int n, T elem){ //BINSEARCH MASK
    return recbinsearch(arr, 0, n-1, elem);
}







// STRUTTURE DATI

template <typename T>
class LNode{ //NODO PER LISTE SEMPLICI
public:
    T data;
    LNode<T>* succ;
    LNode(T dt) : data(dt), succ(nullptr){}
};

template <typename T>
class DLNode{ //NODO PER LISTE DOPPIAMENTE LINKATE
public:
    T data;
    DLNode<T>* succ;
    DLNode<T>* prec;
    DLNode(T dt) : data(dt), succ(nullptr), prec(nullptr){}
};

template <typename T>
class BSTNode{ //NODO PER ALBERI
public:
    T data;
    BSTNode<T>* sx;
    BSTNode<T>* dx;
    BSTNode<T>* dad;
    BSTNode(T dt) : data(dt), sx(nullptr), dx(nullptr), dad(nullptr){}
};





template <typename T>
class SList{ //Lista linkata
    LNode<T>* head;
public:
    SList() : head(nullptr){}

    friend ostream& operator <<(ostream& out, SList<T>& l){
        LNode<T>* iter = l.head;
        while(iter != nullptr){
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out;
    }

    void headinsert(T dt){ //PER INSERIRE PRIMO ELEMENTO USARE headinsert
        LNode<T>* newnode = new LNode<T>(dt);
        newnode->succ = head;
        head = newnode;
    }

    void tailinsert(T dt){
        LNode<T>* newnode = new LNode<T>(dt);
        LNode<T>* iter = head;
        while(iter->succ != nullptr){
            iter = iter->succ;
        }
        iter->succ = newnode;
    }

    //pos != head, tail PER INSERIMENTI IN TESTA E CODA CI SONO tailinsert ed headinsert
    void posinsert(T dt, int pos){ //pos 0-index
        LNode<T>* newnode = new LNode<T>(dt);
        LNode<T>* iter = head;
        int cnt = 0;
        while(iter != nullptr && cnt < pos-1){
            iter = iter->succ;
            cnt++;
        }
        if(iter == nullptr){
            cout << "Posizione errata" << endl;
            return;
        }
        newnode->succ = iter->succ;
        iter->succ = newnode;
    }

    LNode<T>* search(T dt){
        LNode<T>* iter = head;
        while(iter != nullptr){
            if(iter->data == dt)
                return iter;
            iter = iter->succ;
        }
        return nullptr; //SE NON TROVA NIENTE
    }

    void del(T dt){
        LNode<T>* nodetodel = search(dt);
        if(nodetodel != nullptr){
            if(nodetodel == head){
                head = nodetodel->succ;
                delete nodetodel;
                return;
            }
            LNode<T>* iter = head;
            while(iter->succ != nodetodel)
                iter = iter->succ;
            iter->succ = nodetodel->succ;
            delete nodetodel;
            return;
        }
        cout << "L'elemento da eliminare non esiste" << endl;
    }

};


template <typename T>
class CList{ //lista linkata circolare
    LNode<T>* head;
public:
    CList() : head(nullptr){}

    friend ostream& operator <<(ostream& out, CList<T>& l){
        LNode<T>* iter = l.head;
        bool ishead = true;
        while(iter != l.head || ishead == true){ //all'inizio e alla fine iter == head, ma alla seconda volta significa che abbiamo girato tutta la lista
            ishead = false;
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out;
    }

    void headinsert(T dt){ //PER INSERIRE PRIMO ELEMENTO USARE headinsert
        LNode<T>* newnode = new LNode<T>(dt);
        newnode->succ = head;
        head = newnode;
        if(head->succ == nullptr){
            head->succ = head;
            return;
        }
        LNode<T>* iter = head;
        do{
            iter = iter->succ;
        }while(iter->succ != newnode->succ); //lista circolare, la coda punta alla testa (newnode->succ è la testa vecchia, la coda prima punta alla vecchia testa)
        iter->succ = head;
    }

    void tailinsert(T dt){
        LNode<T>* newnode = new LNode<T>(dt);
        LNode<T>* iter = head;
        while(iter->succ != head){
            iter = iter->succ;
        }
        iter->succ = newnode;
        newnode->succ = head;
    }

    //pos != head, tail PER INSERIMENTI IN TESTA E CODA CI SONO tailinsert ed headinsert
    void posinsert(T dt, int pos){ //pos 0-index
        LNode<T>* newnode = new LNode<T>(dt);
        LNode<T>* iter = head;
        int cnt = 0;
        while(iter != head && cnt < pos-1){
            iter = iter->succ;
            cnt++;
        }
        if(iter == nullptr){
            cout << "Posizione errata" << endl;
            return;
        }
        newnode->succ = iter->succ;
        iter->succ = newnode;
    }

    LNode<T>* search(T dt){
        LNode<T>* iter = head;
        bool ishead = true;
        while(iter != head || ishead == true){ //all'inizio e alla fine iter == head, ma alla seconda volta significa che abbiamo girato tutta la lista
            ishead = false;
            if(iter->data == dt)
                return iter;
            iter = iter->succ;
        }
        return nullptr; //SE NON TROVA NIENTE
    }

    void del(T dt){
        LNode<T>* nodetodel = search(dt);
        if(nodetodel != nullptr){
            if(nodetodel == head){
                head = nodetodel->succ;
                LNode<T>* iter = head;
                while(iter->succ != nodetodel) //collegare coda con testa nuova
                    iter = iter->succ;
                iter->succ = head;
                delete nodetodel;
                return;
            }
            else if(nodetodel->succ == head){ //cioè è la coda
                LNode<T>* iter = head;
                while(iter->succ->succ != head) //collegare coda nuova (elem precedente) con la testa
                    iter = iter->succ;
                iter->succ = head;
                delete nodetodel;
                return;
            } 
            LNode<T>* iter = head;
            while(iter->succ != nodetodel)
                iter = iter->succ;
            iter->succ = nodetodel->succ;
            delete nodetodel;
            return;
        }
        cout << "L'elemento da eliminare non esiste" << endl;
    }
};

template <typename T>
class OrdList{ //lista ordinata
        LNode<T>* head;
public:
    OrdList() : head(nullptr){}

    friend ostream& operator <<(ostream& out, OrdList<T>& l){
        LNode<T>* iter = l.head;
        while(iter != nullptr){
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out;
    }

    void insert(T dt){ //inserisce gli elementi in ordine
        LNode<T>* newnode = new LNode<T>(dt);
        if(head == nullptr){
            head = newnode;
            return;
        }
        LNode<T>* iter = head;
        while(iter->succ != nullptr && iter->succ->data < dt)
            iter = iter->succ;
        if(iter == head && dt < head->data){
            newnode->succ = head;
            head = newnode;
            return;
        }
        newnode->succ = iter->succ;
        iter->succ = newnode;
    }

    LNode<T>* search(T dt){
        LNode<T>* iter = head;
        while(iter != nullptr){
            if(iter->data == dt)
                return iter;
            iter = iter->succ;
        }
        return nullptr; //SE NON TROVA NIENTE
    }

    void del(T dt){
        LNode<T>* nodetodel = search(dt);
        if(nodetodel != nullptr){
            if(nodetodel == head){
                head = nodetodel->succ;
                delete nodetodel;
                return;
            }
            LNode<T>* iter = head;
            while(iter->succ != nodetodel)
                iter = iter->succ;
            iter->succ = nodetodel->succ;
            delete nodetodel;
            return;
        }
        cout << "L'elemento da eliminare non esiste" << endl;
    }

};

template <typename T>
class DList{ //lista doppiamente linkata
    DLNode<T>* head;
public:
    DList() : head(nullptr){}

    friend ostream& operator <<(ostream& out, DList<T>& l){
        DLNode<T>* iter = l.head;
        while(iter != nullptr){
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out;
    }

    void headinsert(T dt){ //per il primo elemento usare headinsert
        DLNode<T>* newnode = new DLNode<T>(dt);
        if(head == nullptr){
            head = newnode;
            return;
        }
        newnode->succ = head;
        head->prec = newnode;
        head = newnode;
    }

    void tailinsert(T dt){
        DLNode<T>* newnode = new DLNode<T>(dt);
        DLNode<T>* iter = head;
        while(iter->succ != nullptr){
            iter = iter->succ;
        }
        newnode->prec = iter;
        iter->succ = newnode;
    }

    void posinsert(T dt, int pos){ //come per la lista singolarmente linkata
        DLNode<T>* newnode = new DLNode<T>(dt);
        DLNode<T>* iter = head;
        int cnt = 0;
        while(iter->succ != nullptr && cnt < pos-1){
            iter = iter->succ;
        }
        newnode->prec = iter;
        newnode->succ = iter->succ;
        iter->succ->prec = newnode;
        iter->succ = newnode;
    }

    DLNode<T>* search(T dt){
        DLNode<T>* iter = head;
        while(iter != nullptr){
            if(iter->data == dt)
                return iter;
            iter = iter->succ;
        }
        return nullptr; //SE NON TROVA NIENTE
    }

    void del(T dt){
        DLNode<T>* nodetodel = search(dt);
        if(nodetodel != nullptr){
            if(nodetodel == head){
                head = head->succ;
                head->prec = nullptr;
            }
            else if(nodetodel->succ == nullptr){ //cioè nodetodel è la coda
                nodetodel->prec->succ = nullptr;
            }
            else{
                DLNode<T>* iter = head;
                while(iter->succ != nullptr && iter->data != dt)
                    iter = iter->succ;
                iter->prec->succ = iter->succ;
                iter->succ->prec = iter->prec;
            }
            delete nodetodel;
            return;
        }
        cout << "Elemento da cancellare non esiste" << endl;
    }

};

template <typename T>
class CDList{ //lista doppiamente linkata circolare
    DLNode<T>* head;
public:
    CDList() : head(nullptr){}

    friend ostream& operator <<(ostream& out, CDList<T>& l){
        DLNode<T>* iter = l.head;
        bool ishead = true;
        while(iter != l.head || ishead != false){
            ishead = false;
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out;
    }

    void headinsert(T dt){ //per il primo elemento usare headinsert
        DLNode<T>* newnode = new DLNode<T>(dt);
        if(head == nullptr){
            head = newnode;
            head->succ = head;
            head->prec = head;
            return;
        }
        newnode->succ = head;
        newnode->prec = head->prec;
        newnode->prec->succ = newnode;
        head = newnode;
    }

    void tailinsert(T dt){
        DLNode<T>* newnode = new DLNode<T>(dt);
        DLNode<T>* iter = head;
        do{
            iter = iter->succ;
        }while(iter->succ != head);
        newnode->prec = iter;
        iter->succ = newnode;
        newnode->succ = head;
        head->prec = newnode;
    }

    void posinsert(T dt, int pos){ //come per la lista singolarmente linkata
        DLNode<T>* newnode = new DLNode<T>(dt);
        DLNode<T>* iter = head;
        int cnt = 0;
        while(iter->succ != nullptr && cnt < pos-1){
            iter = iter->succ;
        }
        newnode->prec = iter;
        newnode->succ = iter->succ;
        iter->succ->prec = newnode;
        iter->succ = newnode;
    }

    DLNode<T>* search(T dt){
        DLNode<T>* iter = head;
        bool ishead = true;
        while(iter != head || ishead != false){
            ishead = false;
            if(iter->data == dt)
                return iter;
            iter = iter->succ;
        }
        return nullptr; //SE NON TROVA NIENTE
    }

    void del(T dt){
        DLNode<T>* nodetodel = search(dt);
        if(nodetodel != nullptr){
            if(nodetodel == head){
                head = head->succ;
                head->prec = nodetodel->prec;
                head->prec->succ = head;
            }
            else if(nodetodel->succ == nullptr){ //cioè nodetodel è la coda
                nodetodel->prec->succ = head;
                head->prec = nodetodel->prec;
            }
            else{
                DLNode<T>* iter = head;
                while(iter->succ != nullptr && iter->data != dt)
                    iter = iter->succ;
                iter->prec->succ = iter->succ;
                iter->succ->prec = iter->prec;
            }
            delete nodetodel;
            return;
        }
        cout << "Elemento da cancellare non esiste" << endl;
    }

};

template <typename T>
class ArrStack{
    T* arr;
    int SP, dim;
public:
    ArrStack(int d) : SP(-1), dim(d){
        arr = new T[dim];
    }

    friend ostream& operator << (ostream& out, ArrStack s){
        out << "CIMA" << endl;
        for(int i = s.SP; i >= 0; i--){
            out << s.arr[i] << endl;
        }
        return out << "FONDO";
    }

    void push(T dt){
        if(SP != dim-1){
            arr[++SP] = dt;
            return;
        }
        cout << "Stack pieno!";
    }

    T pop(){
        if(SP != -1)
            return arr[SP--];
        cout << "Stack vuoto!";
        return -1;
    } 

};


template <typename T>
class ListStack{
    LNode<T>* head;
    LNode<T>* SP;
public:
    ListStack() : head(nullptr), SP(nullptr){}

    friend ostream& operator << (ostream& out, ListStack s){
        out << "FONDO ";
        LNode<T>* iter = s.head;
        while(iter != s.SP){
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out << iter->data << " CIMA";
    }

    void push(T dt){
        LNode<T>* newnode = new LNode<T>(dt);
        if(head == nullptr){
            head = newnode;
            SP = head;
            return;
        }
        SP->succ = newnode;
        SP = SP->succ;
    }    

    LNode<T>* pop(){
        if(SP != nullptr){
            LNode<T>* iter = head;
            while(iter->succ != SP)
                iter = iter->succ;
                LNode<T>* ret = SP;
            SP = iter;
            return ret;
        }
        cout << "Stack vuoto" << endl;
        return nullptr;
    }
};


template <typename T>
class ArrQueue{ //coda con array circolare
    T* arr;
    int dim, cnt, head, tail;
public:
    ArrQueue(int n) : dim(n), cnt(0), head(0), tail(-1){
        arr = new T[dim];
    }

    friend ostream& operator <<(ostream& out, ArrQueue<T> q){
        out << "TESTA  ";
        for(int i = q.head%q.dim; i != q.tail%q.dim; i = (i+1)%q.dim)
            out << q.arr[i] << " ";
        return out << q.arr[q.tail%q.dim] << " CODA" << endl;
    }

    bool isEmpty(){
        return cnt == 0;
    }

    bool isFull(){
        return cnt == dim;
    }

    void enqueue(T dt){
        if(!isFull()){
            arr[(++tail)%dim] = dt;
            cnt++;
            return;
        }
        cout << "Coda piena" << endl;
    }

    T dequeue(){
        if(!isEmpty()){
            cnt--;
            return arr[(head++)%dim];
        }
        cout << "Coda vuota" << endl;
        exit(-1);
    }
};


template <typename T>
class ListQueue{
    LNode<T>* head;
    LNode<T>* tail;
public:
    ListQueue() : head(nullptr), tail(nullptr){}

    friend ostream& operator <<(ostream& out, ListQueue<T>& lq){
        LNode<T>* iter = lq.head;
        while(iter != nullptr){
            out << iter->data << " ";
            iter = iter->succ;
        }
        return out;
    }

    void enqueue(T dt){
        LNode<T>* newnode = new LNode<T>(dt);
        if(head == nullptr){
            head = newnode;
            tail = newnode;
            return;
        }
        tail->succ = newnode;
        tail = newnode;
    }

    T dequeue(){
        if(head != nullptr){
            T dq = head->data;
            LNode<T>* del = head;
            head = head->succ;
            delete del;
            return dq;
        }
        cout << "Coda vuota" << endl;
        exit(-1);
    }

};

template <typename T>
class BST{
    BSTNode<T>* root;

    BSTNode<T>* minimo(BSTNode<T>* rt){
        BSTNode<T>* iter = rt;
        while(iter->sx != nullptr || iter->dx != nullptr)
            iter = iter->sx;
        return iter;
    }

    BSTNode<T>* massimo(BSTNode<T>* rt){
        BSTNode<T>* iter = rt;
        while(iter->dx != nullptr || iter->dx != nullptr)
            iter = iter->dx;
        return iter;
    }

    BSTNode<T>* predecessore(BSTNode<T>* rt){
        if(rt->sx != nullptr){
            BSTNode<T>* iter = rt->sx;
            return massimo(iter);
        }
        else{ //se non ha figlio sinistro, è il suo primo antenato il cui figlio destro è anch'esso un antenato (rt può essere antenato di sè stesso)
            BSTNode<T>* iter = rt, iterson = nullptr;
            while(iterson != iter->dx){ //iterson è un antenato di rt
                iterson = iter;
                iter = iter->dad;
            }
            return iter; 
        }
    }

    BSTNode<T>* successore(BSTNode<T>* rt){
        if(rt->dx != nullptr){
            BSTNode<T>* iter = rt->dx;
            return minimo(iter);
        }
        else{ //se non ha figlio destro, è il suo primo antenato il cui figlio sinistro è anch'esso un antenato (rt può essere antenato di sè stesso)
            BSTNode<T>* iter = rt;
            BSTNode<T>* iterson = nullptr;
            while(iterson != iter->sx){ //iterson è un antenato di rt
                iterson = iter;
                iter = iter->dad;
            }
            return iter; 
        }
    }

    void inorder(BSTNode<T>* rt){
        if(rt != nullptr){
            inorder(rt->sx);
            cout << rt->data << " ";
            inorder(rt->dx);
        }
    }

    void preorder(BSTNode<T>* rt){
        if(rt != nullptr){
            cout << rt->data << " ";
            preorder(rt->sx);
            preorder(rt->dx);
        }
    }

    void postorder(BSTNode<T>* rt){
        if(rt != nullptr){
            postorder(rt->sx);
            postorder(rt->dx);
            cout << rt->data << " ";
        }
    }

    void levelorder(BSTNode<T>* rt, int lv){
        if(rt!=nullptr && lv>0){
            levelorder(rt->sx, lv-1);
            levelorder(rt->dx, lv-1);
        }
        if(rt!=nullptr && lv == 0){
            cout << rt->data << " ";
        }
    }

    int depth(BSTNode<T>* rt){
        if(rt != nullptr){
            int sxh = depth(rt->sx);
            int dxh = depth(rt->dx);
            if(sxh > dxh)
                return sxh+1;
            return dxh+1;
        }
        return -1;
    }

public:
    BST() : root(nullptr){}

    friend ostream& operator <<(ostream& out, BST<T>& t){
        int dp = t.depth();
        for(int i = 0; i <= dp; i++){
            cout << "Level " << i << ": ";
            t.levelorder(i);
            cout << endl;
        }
        return out;
    }

    void insert(T dt){
        BSTNode<T>* newnode = new BSTNode<T>(dt);
        if(root == nullptr){
            root = newnode;
            return;
        }
        BSTNode<T>* iter = root;
        BSTNode<T>* iterdad;
        while(iter != nullptr){
            iterdad = iter;
            if(dt < iter->data)
                iter = iter->sx;
            else
                iter = iter->dx;
        }
        if(dt < iterdad->data)
            iterdad->sx = newnode;
        else
            iterdad->dx = newnode;
        newnode->dad = iterdad;
    }

    BSTNode<T>* search(T dt){
        BSTNode<T>* iter = root;
        while(iter != nullptr){
            if(iter->data == dt)
                return iter;
            else if(dt < iter->data)
                iter = iter->sx;
            else
                iter = iter->dx;
        }
        return nullptr;
    }

    void transplant(BSTNode<T>* a, BSTNode<T>* b){
        //piazzo un nodo al posto di un altro, con tutto il sottoalbero
        //attacco padre di a al sostituto di a (b)
        if(a->dad == nullptr) //a è radice (quindi la nuova radice è b)
            root = b;
        else if(a == a->dad->sx){ //a è un figlio sinistro
            a->dad->sx = b;
        }
        else{ //a è un figlio destro
            a->dad->dx = b;
        }
        if(b != nullptr)
            b->dad = a->dad; //il nuovo padre di b è a, dato che b è al posto di a adesso
    }

    BSTNode<T>* minimo(){ //MASK
        return minimo(root);
    }

    BSTNode<T>* massimo(){ //MASK
        return massimo(root);
    }

    BSTNode<T>* successore(){ //MASK
        return successore(root);
    }

    BSTNode<T>* predecessore(){ //MASK
        return predecessore(root);
    }

    void inorder(){ //MASK
        inorder(root);
    }

    void preorder(){ //MASK
        preorder(root);
    }

    void postorder(){ //MASK
        postorder(root);
    }

    void levelorder(int lv){ //MASK
        levelorder(root, lv);
    }

    int depth(){ //MASK
        return depth(root);
    }

    void del(T dt){
        BSTNode<T>* nodetodel = search(dt);
        if(nodetodel->sx == nullptr){ //ha solo figlio destro
            transplant(nodetodel, nodetodel->dx);
        }
        else if(nodetodel->dx == nullptr){ //ha solo figlio sinistro
            transplant(nodetodel, nodetodel->sx);
        }
        else{ // ha due figli, lo trapiantiamo col successore
            BSTNode<T>* succ = successore(nodetodel);
            if(succ != nodetodel->dx){ // SE SUCC NON è FIGLIO (DESTRO, PERCHE' PUO' ESSERE SOLO FIGLIO DESTRO ESSENDO SUCCESSORE) DI NODETODEL
                transplant(succ, succ->dx); //successore non ha figli sinistri (devo spostare succ->dx al posto di succ, così succ lo metto a posto di nodetodel)
                succ->dx = nodetodel->dx; //il figlio destro di succ adesso è il figlio destro di nodetodel
                succ->dx->dad = succ; //ovviamente suo padre è succ adesso
            }
            //SE SUCC è FIGLIO DI NODETODEL, SUCC DX E' GIA' NODETODEL DX, QUINDI BASTA MODIFICARE FIGLIO SINISTRO
            transplant(nodetodel, succ); 
            succ->sx = nodetodel->sx;
            succ->sx->dad = succ;
        }
    }

};


int main(){

    //TEST RICERCA E ORDINAMENTO

    //int array[10] = {43,51,12,10,6,14,22,17,30,21};
    //bubblesort(array, 10);
    //inssort(array,10);
    //swapinssort(array, 10);
    //selsort(array, 10);
    //mergesort(array, 10);
    //quicksort(array, 10);
    //cout << search(array, 10, 22) << endl;
    //cout << iterbinsearch(array, 10, 22) << endl;
    //cout << recbinsearch(array, 10, 12) << endl;
    //printarr(array, 10);

    // TEST LISTA LINKATA

    /*
    SList<int> l1;
    l1.headinsert(10);
    l1.headinsert(5);
    l1.headinsert(25);
    l1.tailinsert(40);
    l1.tailinsert(15);
    l1.tailinsert(12);
    l1.posinsert(37, 1);
    l1.del(25);
    cout << l1 << endl;
    */

    // TEST LISTA LINKATA CIRCOLARE

    /*
    CList<int> l2;
    l2.headinsert(10);
    cout << l2 << endl;
    l2.headinsert(5);
    cout << l2 << endl;
    l2.headinsert(25);
    cout << l2 << endl;
    l2.tailinsert(40);
    cout << l2 << endl;
    l2.tailinsert(15);
    cout << l2 << endl;
    l2.tailinsert(12);
    cout << l2 << endl;
    l2.posinsert(37, 1);
    cout << l2 << endl;
    l2.del(25);
    cout << l2 << endl;
    */

    // TEST LISTA LINKATA ORDINATA
    
    /*
    OrdList<int> l3;
    l3.insert(25);
    l3.insert(17);
    l3.insert(30);
    l3.insert(9);
    l3.insert(14);
    l3.del(17);
    cout << l3 << endl;
    */

    // TEST LISTA DOPPIAMENTE LINKATA

    /*
    DList<int> l4;
    l4.headinsert(10);
    l4.headinsert(5);
    l4.headinsert(25);
    l4.tailinsert(40);
    l4.tailinsert(15);
    l4.tailinsert(12);
    l4.posinsert(37, 1);
    l4.del(25);
    cout << l4 << endl;
    */

    // TEST LISTA DOPPIAMENTE LINKATA CIRCOLARE

    /*
    CDList<int> l5;
    l5.headinsert(10);
    cout << l5 << endl;
    l5.headinsert(5);
    cout << l5 << endl;
    l5.headinsert(25);
    cout << l5 << endl;
    l5.tailinsert(40);
    cout << l5 << endl;
    l5.tailinsert(15);
    cout << l5 << endl;
    l5.tailinsert(12);
    cout << l5 << endl;
    l5.posinsert(37, 1);
    cout << l5 << endl;
    l5.del(25);
    cout << l5 << endl;
    */

    // TEST STACK CON ARRAY

    /*
    ArrStack<int> stk(5);
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    stk.push(60);
    cout << stk << endl;
    cout << stk.pop() << endl << stk << endl;
    */

    // TEST STACK CON LISTE

    /*
    ListStack<int> stk2;
    stk2.push(10);
    stk2.push(20);
    stk2.push(30);
    stk2.push(40);
    stk2.push(50);
    stk2.push(60);
    cout << stk2 << endl;
    cout << stk2.pop()->data << endl << stk2 << endl;
    */

    //TEST CODA CON ARRAY CIRCOLARE

    /*
    ArrQueue<int> quu1(5);
    quu1.enqueue(10);
    quu1.enqueue(20);
    quu1.enqueue(30);
    quu1.enqueue(40);
    quu1.enqueue(50);
    cout << quu1 << endl;
    quu1.enqueue(60);
    quu1.dequeue();
    quu1.dequeue();
    quu1.dequeue();
    cout << quu1 << endl;
    quu1.dequeue();
    cout << quu1 << endl;
    quu1.enqueue(70);
    cout << quu1 << endl;
    quu1.enqueue(80);
    cout << quu1 << endl;
    */

    //TEST CODA CON LISTA

    /*
    ListQueue<int> quu2;
    quu2.enqueue(10);
    quu2.enqueue(20);
    quu2.enqueue(30);
    quu2.enqueue(40);
    quu2.enqueue(50);
    cout << quu2 << endl;
    quu2.enqueue(60);
    quu2.dequeue();
    quu2.dequeue();
    quu2.dequeue();
    cout << quu2 << endl;
    quu2.dequeue();
    quu2.enqueue(70);
    cout << quu2 << endl;
    quu2.enqueue(80);
    cout << quu2 << endl;
    */

    //TEST BST

    /*
    BST<int> bst1;
    bst1.insert(10);
    bst1.insert(9);
    bst1.insert(21);
    bst1.insert(15);
    bst1.insert(7);
    bst1.insert(8);
    bst1.insert(11);
    bst1.insert(5);
    cout << bst1 << endl;
    bst1.del(15);
    cout << bst1 << endl;
    bst1.inorder();
    cout << endl;
    bst1.preorder();
    cout << endl;
    bst1.postorder();
    cout << endl;
    */
}