//LISTE DI ADIACENZA

template<typename T>
class Node{
public:
    Node<T>* succ;
    T data;
    Node(T dt) : data(dt), succ(nullptr){}
};

template<typename T>
class List{
    Node<T>* head;
public:
    List() : head(nullptr){}

    friend ostream& operator<< (ostream& out, List<T> l){
        Node<T>* iter = l.head;
        while(iter != nullptr){
            out << iter->data << " "; 
            iter = iter->succ;
        }
        return out;
    }

    void insert(T dt){
        Node<T>* newnode = new Node<T>(dt);
        if(head == nullptr){
            head = newnode;
            return;
        }
        Node<T>* iter = head;
        while(iter->succ != nullptr){
            iter = iter->succ;
        }
        iter->succ = newnode;
    }

    Node<T>* search(T dt){
        Node<T>* iter = head;
        while(iter != nullptr && iter->data != dt){
            iter = iter->succ;
        }
        return iter; 
    }

    void del(T dt){
        if(search(dt) == nullptr){
            cout << "Bre bre" << endl;
            return;
        }
        if(head->data == dt){
            delete head;
            head = nullptr;
        }
        Node<T>* iter = head;
        Node<T>* prec;
        while(iter->data != dt){
            prec = iter;
            iter = iter->succ;
        }
        prec->succ = iter->succ;
        delete iter;
    }

};

template<typename T>
class GraphNode{
public:
    List<T>* adj;
    GraphNode<T>* succ;
    T data;
    GraphNode(T dt) : data(dt), adj(nullptr), succ(nullptr){}
};


template <typename T>
class ListGraph{ //oriented graph with lists, as a list of nodes with adjlist pointer(graphnodes)
    GraphNode<T>* head;
public:
    ListGraph() : head(nullptr){}

    friend ostream& operator <<(ostream& out, ListGraph<T> lg){
        GraphNode<T>* iter = lg.head;
        while(iter != nullptr){
            if(iter->adj != nullptr)
                out << iter->data << " -> " << *(iter->adj) << endl;
            else
                out << iter->data << " -> "  << endl;
            iter = iter->succ;
        }
        return out;
    }

    void insertNode(T dt){
        GraphNode<T>* newnode = new GraphNode<T>(dt);
        if(head == nullptr){
            head = newnode;
            return;
        }
        GraphNode<T>* iter = head;
        while(iter->succ != nullptr){
            iter = iter->succ;
        }
        iter->succ = newnode;
    }

    GraphNode<T>* searchNode(T dt){
        GraphNode<T>* iter = head;
        while(iter != nullptr && iter->data != dt){
            iter = iter->succ;
        }
        return iter;
    }

    void connectNode(GraphNode<T>* n1, GraphNode<T>* n2){
        if(n1->adj == nullptr)
            n1->adj = new List<T>;
        if(n1->adj->search(n2->data) == nullptr){
            n1->adj->insert(n2->data);
        }
    }


};

int main(){
    ListGraph<int> lg1;
    lg1.insertNode(1);
    lg1.insertNode(2);
    lg1.insertNode(3);
    lg1.insertNode(4);
    lg1.insertNode(5);
    lg1.insertNode(6);
    lg1.connectNode(lg1.searchNode(1), lg1.searchNode(3));
    lg1.connectNode(lg1.searchNode(1), lg1.searchNode(5));
    lg1.connectNode(lg1.searchNode(1), lg1.searchNode(6));
    lg1.connectNode(lg1.searchNode(2), lg1.searchNode(1));
    lg1.connectNode(lg1.searchNode(4), lg1.searchNode(2));
    lg1.connectNode(lg1.searchNode(6), lg1.searchNode(4));
    cout << lg1 << endl;
}
