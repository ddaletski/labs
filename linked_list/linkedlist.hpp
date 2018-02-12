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
        _start = _end = nullptr;
        _size = 0;
    }

    LinkedList(const LinkedList<T>& from) {
        _start = _end = nullptr;
        _size = 0;
        for(NodePtr iter = from._end; iter; iter = iter->next) {
            push_front(iter->elem);
        }
    }

    LinkedList<T>& operator = (const LinkedList& from) {
        for(NodePtr iter = from._end; iter; iter = iter->next) {
            push_front(iter->elem);
        }
    }


    ~LinkedList() {
        while(_size > 0) {
            pop_back();
        }
    }


    size_t size() {
        return _size;
    }


    bool empty() {
        return _size == 0;
    }

    const T& front() {
        if(empty())
            throw EmptyList();
        return *_start;
    }

    const T& back() {
        if(empty())
            throw EmptyList();
        return *_end;
    }

    void push_back(const T& elem) {
        _end = new ListNode<T>(elem, _end);
        if (_size == 0)
            _start = _end;
        _size++;
    }

    void push_front(const T& elem) {
        NodePtr newStart = new ListNode<T>(elem, nullptr);
        if (_size == 0) {
            _start = _end = newStart;
        } else {
            _start->next = newStart;
            _start = newStart;
        }
        _size++;
    }

    T pop_back() {
        if (_size == 0) {
            throw EmptyList();
        }
        T elem = _end->elem;
        NodePtr toDelete = _end;

        _end = _end->next;

        delete toDelete;
        _size--;

        if (_size == 0)
            _start = _end = nullptr;

        return elem;
    }

    T pop_front() {
        if (_size == 0) {
            throw EmptyList();
        } else if (_size == 1) {
            T elem = _start->elem;
            delete _start;
            _start = _end = nullptr;
        } else {
            std::swap(_start->elem, _end->elem);
            return pop_back();
        }

        _size--;

        if (_size == 0)
            _start = _end = nullptr;
    }


    std::pair<int, T> find(const std::function<bool(const T&)>& predicate) const {
        if (_size == 0)
            throw NotFound();

        if (predicate(_end->elem))
            return std::make_pair(1, _end->elem);

        int operations = 1;
        for(NodePtr iter = _end->next; iter; iter = iter->next) {
            operations++;
            if (predicate(iter->elem))
                return std::make_pair(operations, iter->elem);
        }
        throw NotFound();
    }


    void find_and_del(const std::function<bool(const T&)>& predicate) {
        bool found = false;
        if (_size == 0)
            throw NotFound();

        if (predicate(_end->elem))
            pop_back();

        for(NodePtr iter = _end->next, prev = _end; iter; iter = iter->next, prev=prev->next) {
            if (predicate(iter->elem)) {
                prev->next = iter->next;
                delete iter;
                _size--;
                found = true;
            }
        }

        if (!found)
            throw NotFound();
    }

    void apply(const std::function<T(const T&)>& op) {
        for (NodePtr iter = _end; iter; iter=iter->next) {
            iter->elem = op(iter->elem);
        }
    }

    void for_each(const std::function<void(const T&)>& op) const {
        for (NodePtr iter = _end; iter; iter=iter->next) {
            op(iter->elem);
        }
    }


    void to_dot(std::ostream& stream,
            const std::function<std::string(const T&)> obj_to_str) {

        stream << "digraph g { \n";
        stream << "node [shape=rect];\n";

        int i = 0;
        for_each( [&](const T& elem) {
                stream << "node" << i << "[label=\"" << obj_to_str(elem) << "\"];\n";
                ++i;
        });

        stream << "nil[label=nil color=\"red\"];\n";
        stream << "node0 -> nil;\n";

        for (int j = 1; j < i; ++j) {
            stream << "node" << j << " -> node" << (j-1) << ";\n";
        }

        stream << "}";
    }


private:
    int _size;
    NodePtr _start;
    NodePtr _end;
};

}

#endif // LINKEDLIST_HPP
