namespace mctk {

template <class T>
class Queue {
  protected:
    struct node {
        T data;
        node* next;
        node* prev;
    };
    node* head;
    node* tail;
    int count;
    public:
    void push(T data);
       T pop();
       T front();
    void clear();
    bool empty();
     int size();
     Queue();
     ~Queue();
};

template<class T>
Queue<T>::Queue()
{
    head = new node;
    tail = new node;
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
    count = 0;
}

template <class T>
Queue<T>::~Queue()
{
    clear();
    delete tail;
    delete head;
}

template <class T>
void Queue<T>::push(T data)
{
    node *t = new node;
    if (count == 0)
       tail->prev = t;
    t->data = data;
    t->next = head->next;
    t->next->prev = t;
    t->prev = head;
    head->next = t;
    count++;
}

template <class T>
T Queue<T>::pop()
{
  if (!empty()) {
    T ret = tail->prev->data;
    node* t;
    t = tail->prev;
    tail->prev = t->prev;
    t->prev->next = tail;
    delete (t);
    count--;
    return ret;
  }
}

template <class T>
T Queue<T>::front()
{
    if (!empty())
    return tail->prev->data;
}

template <class T>
bool Queue<T>::empty()
{
    return head->next == tail;
}

template <class T>
int Queue<T>::size()
{
    return count;
}

template <class T>
void Queue<T>::clear()
{
    while (!empty()) pop();
}

}
