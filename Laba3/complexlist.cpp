#include "complexlist.h"

ComplexList::ComplexList() :
    head(nullptr),
    tail(nullptr),
    _size(0)
{ }

ComplexList::ComplexList(const std::initializer_list<Complex> &list) :
    ComplexList()
{
    if (list.size() == 0) {
        return;
    }

    for (auto const& val : list) {
        push_back(val);
    }
}

ComplexList::~ComplexList() {
    if(_size)
        for(auto cur = head->next; cur->next; cur = cur->next)
                delete cur->prev;

    delete tail;
}

void ComplexList::push_back(const Complex &val) {
    auto newNode = new Node(tail, nullptr, val);

    if(_size == 0)
        head = tail = newNode;
    else {
        tail->next = newNode;
        tail = newNode;
    }
    _size++;
}

void ComplexList::push_front(const Complex &val) {
    auto newNode = new Node(nullptr, head, val);

    if(_size == 0)
        head = tail = newNode;
    else {
        head->prev = newNode;
        head = newNode;
    }
    _size++;
}

void ComplexList::remove(const Complex &val) {
    if(_size != 0)
        for(auto cur = head; cur->next; cur = cur->next)
            if(cur->data == val){
                remove(cur);
                break;
            }
}

Complex &ComplexList::operator[](size_t index) {
    if (index >= _size)
        throw std::out_of_range("Index in ComplexList was out of memory!");

    auto cur = head;
    for (; index != 0; index--)
        cur = cur->next;

    return cur->data;
}

void ComplexList::remove(Node *item) {
    item->prev->next = item->next;
    item->next->prev = item->prev;
    _size--;
    delete item;
}
