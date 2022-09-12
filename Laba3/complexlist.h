#ifndef COMPLEXLIST_H
#define COMPLEXLIST_H

#include "complex.h"
#include <initializer_list>
#include <stdexcept>


class ComplexList {
public:
    ComplexList();

    ComplexList(std::initializer_list<Complex> const& list);

    ~ComplexList();

    void push_back(Complex const& val);

    void push_front(Complex const& val);

    void remove(Complex const& val);

    Complex& operator[](size_t index);

    inline size_t size() const {
        return _size;
    }

private:
    struct Node {
        Node() :
            prev(nullptr),
            next(nullptr),
            data()
        { }

        Node(Node* prev, Node*next, Complex data) :
            prev(prev),
            next(next),
            data(data)
        { }

        Node* prev;
        Node* next;
        Complex data;
    };

    void remove(Node* item);


    Node* head;
    Node* tail;
    size_t _size;
};

#endif // COMPLEXLIST_H
