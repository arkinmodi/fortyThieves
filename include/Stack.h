/**
 *  \file Stack.h
 *  \author Arkin Modi
 *  \brief The Stack ADT
 *  \date March 12, 2019
 */

#ifndef A3_STACK_H_
#define A3_STACK_H_

#include <vector>

/**
 *  \brief Class representing a Stack
 */
template <class T>
class Stack
{
  private:
    /// the vector containing the elements in the stack
    std::vector<T> S = {};

  public:
    Stack();

    /**
     *  \brief Constructs a new Stack
     *  \param s The stack
     */
    Stack(std::vector<T> s);

    /**
     *  \brief Adds an element to the stack
     *  \param e The element to be added to the top of the stack
     *  \return A new stack with the added element
     */
    Stack push(T e);

    /**
     *  \brief Removes the top element on the stack
     *  \return A new stack with the top element removed
     */
    Stack pop();

    /**
     *  \brief Gets the value of the top element in the stack
     *  \return The value of the top element in the stack
     */
    T top();

    /**
     *  \brief Gets the size of the stack
     *  \return The size of the stack represented as an integer
     */
    int size();

    /**
     *  \brief Outputs the stack as a vector
     *  \return The stack as a vector
     */
    std::vector<T> toSeq();
};

#endif
