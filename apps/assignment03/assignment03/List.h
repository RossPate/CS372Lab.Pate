#include <cstddef>
#include <algorithm>
#include <functional>
#include <stdexcept>

template <typename T>
class List {
protected:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;

        Node(T val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t numElements = 0;

    void deleteListContents();
    void setupList();

public:
    List();
    List(T newData);
    List(const List& rhs);
    ~List();
    List& operator=(const List& rhs);
    List(List&& rhs);
    List& operator=(List&& rhs);
    bool empty() const;
    void push_front(T data);
    void push_back(T data);
    T front() const;
    T back() const;
    void pop_back();
    void pop_front();
    void traverse(std::function<void(T data)> doIt);
    size_t size() const;
// This took some googling to implement but it kind of worked.
    template <typename U> friend class CircularList;
};

template <typename T>
void List<T>::deleteListContents() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    numElements = 0;
}

template <typename T>
void List<T>::setupList() {
    head = nullptr;
    tail = nullptr;
    numElements = 0;
}

template <typename T>
List<T>::List() {
    setupList();
}

template <typename T>
List<T>::List(T newData) {
    setupList();
    push_back(newData);
}

template <typename T>
List<T>::List(const List<T>& rhs) {
    setupList();
    Node* current = rhs.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

template <typename T>
List<T>::~List() {
    deleteListContents();
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs) {
    if (this != &rhs) {
        List<T> temp(rhs);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(numElements, temp.numElements);
    }
    return *this;
}

template <typename T>
List<T>::List(List<T>&& rhs)
    : head(rhs.head),
    tail(rhs.tail),
    numElements(rhs.numElements) {
    rhs.head = nullptr;
    rhs.tail = nullptr;
    rhs.numElements = 0;
}

template <typename T>
List<T>& List<T>::operator=(List<T>&& rhs) {
    if (this != &rhs) {
        deleteListContents();

        head = rhs.head;
        tail = rhs.tail;
        numElements = rhs.numElements;

        rhs.head = nullptr;
        rhs.tail = nullptr;
        rhs.numElements = 0;
    }
    return *this;
}

template <typename T>
bool List<T>::empty() const {
    return numElements == 0;
}

template <typename T>
void List<T>::push_front(T data) {
    Node* newNode = new Node(data);
    if (empty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    numElements++;
}

template <typename T>
void List<T>::push_back(T data) {
    Node* newNode = new Node(data);
    if (empty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    numElements++;
}

template <typename T>
T List<T>::front() const {
    if (empty()) {
        throw std::out_of_range("List is empty in front()");
    }
    return head->data;
}

template <typename T>
T List<T>::back() const {
    if (empty()) {
        throw std::out_of_range("List is empty in back()");
    }
    return tail->data;
}

template <typename T>
void List<T>::pop_back() {
    if (empty()) {
        return;
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node* temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
    }
    numElements--;
}

template <typename T>
void List<T>::pop_front() {
    if (empty()) {
        return;
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        Node* temp = head;
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }
    numElements--;
}

template <typename T>
void List<T>::traverse(std::function<void(T data)> doIt) {
    Node* current = head;
    while (current != nullptr) {
        doIt(current->data);
        current = current->next;
    }
}

template <typename T>
size_t List<T>::size() const {
    return numElements;
}