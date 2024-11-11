/**
 * @file maxstack.cpp
 * @brief  Archivo de implementación del TDA MaxStack
 * @author Pablo Vargas Diaz Oscar Alfonso Mitillo López-Barajas
 */

#include "maxstack.h"

MaxStack::MaxStack(){
}

void MaxStack::push(int value) {

    int max = value;

    if (!max_values.empty() && max < max_values.top())
        max = max_values.top();

    element n_elem{value, max};
    elements.push(n_elem);
    max_values.push(max);
}

void MaxStack::pop() {
    if (elements.empty()) {
        throw std::out_of_range("Stack is empty");
    }

    queue<element> temp;
    while(elements.size() > 1) {
        temp.push(elements.front());
        elements.pop();
    }

    elements.swap(temp);
}

element MaxStack::top() {

    if (elements.empty()) {
        throw std::out_of_range("Max Stack is empty");
    }
    return elements.back();
}

const element MaxStack::top() const {
    if (elements.empty()) {
        throw std::out_of_range("Max Stack is empty");
    }
    return elements.back();
}

bool MaxStack::empty() const{

    bool vacio = false;
    if (elements.empty()) vacio=true;

    return vacio;
}

int MaxStack::size() const{
    return int(elements.size());
}
