#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template <typename T>
class Stack {
private:
    int tot;
     T* ary;
    int hed;

public:
    Stack();
    Stack(Stack<T> &x);

    Stack<T>& operator=(Stack<T> &x);

    void push(const T &x);
    void pop();
    void popALL();

    const T& top();
    bool empty();
    int size();

    void display();

    ~Stack();

private:
    void overflow();
};

template <typename T>
Stack<T>::Stack() {
    tot = 2;
    ary = new T[tot];
    hed = -1;
}

template <typename T>
Stack<T>::Stack(Stack<T> &x) {
    tot = x.tot;
    hed = x.hed;
    ary = new T[tot];
    for ( int i=0 ; i<=hed ; ++i )
        { ary[i] = x.ary[i];
        }
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> &x) {
    delete [] ary;
    tot = x.tot;
    hed = x.hed;
    ary = new T[tot];
    for ( int i=0 ; i<=hed ; ++i )
        { ary[i] = x.ary[i];
        }
    return *this;
}

template <typename T>
void Stack<T>::push(const T &x) {
    if ( hed==tot-1 )
        overflow();
    ++hed;
    ary[hed] = x;
}

template <typename T>
void Stack<T>::pop() {
    if ( empty() )
       { cout << "error" << endl;
         return;
       }
    --hed;
}

template <typename T>
void Stack<T>::popALL() {
    hed = -1;
}

template <typename T>
const T& Stack<T>::top() {
    if ( empty() )
       { static T t;
         cout << "error" << endl;
         return t;
       }
    return ary[hed];
}

template <typename T>
bool Stack<T>::empty() {
    if ( hed==-1 )
        return true;
    return false;
}

template <typename T>
int Stack<T>::size() {
    return hed+1;
}

template <typename T>
void Stack<T>::display() {
    for ( int i=0 ; i<=hed ; ++i )
        { cout << ary[i] << " ";
        }
    cout << endl;
}

template <typename T>
Stack<T>::~Stack() {
    delete [] ary;
}

template <typename T>
void Stack<T>::overflow() {
    int tmpTot = tot * 2;
    T* tmpAry = new T[tmpTot];
    for ( int i=0 ; i<=hed ; ++i )
        { tmpAry[i] = ary[i];
        }
    delete [] ary;
    ary = tmpAry;
    tot = tmpTot;
}

#endif // STACK_H_INCLUDED
