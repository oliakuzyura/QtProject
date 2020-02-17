#ifndef LIST_H
#define LIST_H

#include<iostream>

template<class T>
class List
{
private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *head;
    Node *last;

    int length;
public:
    class Iterator
    {
    private:
        Node *head;
    public:
        Iterator(Node *head) { this->head = head; }
        Iterator operator++(int) { Iterator itr = *this; head = head->next; return itr; }
        T& operator*() { return head->data; }
        bool operator==(const Iterator &itr) { return head->data == itr.head->data; }
        bool operator!=(const Iterator &itr) { return head->data != itr.head->data; }
    };

    List()
    {
        head   = NULL;
        length = 0;
    }

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(last); }

    void push(const T &data);

    void push_end(const T &data);

    T pop();

    void print();

    int size();

};

#endif
