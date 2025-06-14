#pragma once
#include "List.h"

template <typename T>
class CircularList : public List<T> {
public:
    CircularList() = default;

    void push_back(T data) {
        List<T>::push_back(data);
        if (!List<T>::empty()) {
            List<T>::tail->next = List<T>::head;
            List<T>::head->prev = List<T>::tail;
        }
    }

    void push_front(T data) {
        List<T>::push_front(data);
        if (!List<T>::empty()) {
            List<T>::tail->next = List<T>::head;
            List<T>::head->prev = List<T>::tail;
        }
    }

    typename List<T>::Node* getHead() {
        return List<T>::head;
    }

    typename List<T>::Node* getTail() {
        return List<T>::tail;
    }
    void traverse(std::function<void(T)> doIt, typename List<T>::Node* startNode) {
        if (List<T>::empty()) {
            return;
        }
        else {
            typename List<T>::Node* current = (startNode != nullptr) ? startNode : List<T>::head;
            typename List<T>::Node* first = current;

            do {
                doIt(current->data);
                current = current->next;
            } while (current != first);
        }
    }
};