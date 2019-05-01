// Implementation here
#include "Stack.h"
#include "CardTypes.h"
#include <stdexcept>

using namespace std;

template <class T>
Stack<T>::Stack()
{
    this->S = vector<T> {};
}

template <class T>
Stack<T>::Stack(vector<T> s)
{
    this->S = s;
}

template <class T>
Stack<T> Stack<T>::push(T e)
{
    Stack<T> newStack(this->S);
    newStack.S.push_back(e);
    return newStack;
}

template <class T>
Stack<T> Stack<T>::pop()
{
    if (this->S.size() == 0)
        throw out_of_range("pop");
    Stack<T> newStack(this->S);
    newStack.S.pop_back();
    return newStack;
}

template <class T>
T Stack<T>::top()
{
    if (this->S.size() == 0)
        throw out_of_range("top");
    return this->S.back();
}

template <class T>
int Stack<T>::size()
{
    return this->S.size();
}

template <class T>
vector<T> Stack<T>::toSeq()
{
    return this->S;
}

// Keep this at bottom
template class Stack<CardT>;
