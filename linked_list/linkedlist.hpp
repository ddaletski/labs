#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <exception>
#include <algorithm>
#include <utility>
#include <functional>

namespace LList {

class EmptyList : std::exception {
public:
    virtual const char* what() const throw() {
        return "list is empty";
    }
};

class NotFound : std::exception {
public:
    virtual const char* what() const throw() {
        return "element have not been found in list";
    }
};


template <class T>
class ListNode {
public:
    ListNode(const T& elem, ListNode<T>* next = nullptr):
        elem(elem), next(next) {}
    ListNode<T>* next;
    T elem;
};


template <class T>
class LinkedList {
typedef ListNode<T>* NodePtr;

public:
    LinkedList() {
        start = end = nullptr;
        size = 0;
    }

    LinkedList(const LinkedList<T>& from) {
        start = end = nullptr;
        size = 0;
        for(NodePtr iter = from.end; iter; iter = iter->next) {
            push_front(iter->elem);
        }
    }

    LinkedList<T>& operator = (const LinkedList& from) {
        for(NodePtr iter = from.end; iter; iter = iter->next) {
            push_front(iter->elem);
        }
    }


    ~LinkedList() {
        while(size > 0) {
            pop_back();
        }
    }

    void push_back(const T& elem) {
        end = new ListNode<T>(elem, end);
        if (size == 0)
            start = end;
        size++;
    }

    void push_front(const T& elem) {
        NodePtr newStart = new ListNode<T>(elem, nullptr);
        if (size == 0) {
            start = end = newStart;
        } else {
            start->next = newStart;
            start = newStart;
        }
        size++;
    }

    T pop_back() {
        if (size == 0) {
            throw EmptyList();
        }
        T elem = end->elem;
        NodePtr toDelete = end;

        end = end->next;

        delete toDelete;
        size--;

        if (size == 0)
            start = end = nullptr;

        return elem;
    }

    T pop_front() {
        if (size == 0) {
            throw EmptyList();
        } else if (size == 1) {
            T elem = start->elem;
            delete start;
            start = end = nullptr;
        } else {
            std::swap(start->elem, end->elem);
            return pop_back();
        }

        size--;

        if (size == 0)
            start = end = nullptr;
    }


    std::pair<int, T> find(const std::function<bool(const T&)>& predicate) const {
        if (size == 0)
            throw NotFound();

        if (predicate(end->elem))
            return std::make_pair(1, end->elem);

        int operations = 1;
        for(NodePtr iter = end->next; iter; iter = iter->next) {
            operations++;
            if (predicate(iter->elem))
                return std::make_pair(operations, iter->elem);
        }
        throw NotFound();
    }


    void find_and_del(const std::function<bool(const T&)>& predicate) {
        bool found = false;
        if (size == 0)
            throw NotFound();

        if (predicate(end->elem))
            pop_back();

        for(NodePtr iter = end->next, prev = end; iter; iter = iter->next, prev=prev->next) {
            if (predicate(iter->elem)) {
                prev->next = iter->next;
                delete iter;
                size--;
                found = true;
            }
        }

        if (!found)
            throw NotFound();
    }

    void apply(const std::function<T(const T&)>& op) {
        for (NodePtr iter = end; iter; iter=iter->next) {
            iter->elem = op(iter->elem);
        }
    }

    void for_each(const std::function<void(const T&)>& op) const {
        for (NodePtr iter = end; iter; iter=iter->next) {
            op(iter->elem);
        }
    }

private:
    int size;
    NodePtr start;
    NodePtr end;
};

}

#endif // LINKEDLIST_HPP
