/**
 * @file maxqueue.cpp
 * @brief  Archivo de implementación del TDA MaxQueue
 * @author
 */

#include <maxqueue.h>

/*--------------------------------------------------------------------------------------------------------------------*/

ostream& operator<< (ostream& os, Element element) {
    os << to_string(element.value) << "|" << to_string(element.maximum);
    return os;
}

/*--------------------------------------------------------------------------------------------------------------------*/

MaxQueue::MaxQueue() = default;

/*--------------------------------------------------------------------------------------------------------------------*/

bool MaxQueue::empty() const
{
    return elements.empty();
}

/*--------------------------------------------------------------------------------------------------------------------*/

int MaxQueue::size() const
{
    return static_cast<int>(elements.size());
}

/*--------------------------------------------------------------------------------------------------------------------*/

const Element &MaxQueue::front() const
{
    return elements.front();
}

/*--------------------------------------------------------------------------------------------------------------------*/

const Element &MaxQueue::back() const
{

    return elements.back();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void MaxQueue::push(int newValue)
{
    Element newElement{newValue, newValue};
    int max = elements.back().maximum;

    if(max > newValue) {
        newElement.maximum = max;
    }
    else{
        for(Element e : elements) {
            e.maximum = newValue;
        }
    }
    elements.push_back(newElement);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void MaxQueue::pop()
{
    elements.pop_front();
}

/*--------------------------------------------------------------------------------------------------------------------*/

void MaxQueue::swap(MaxQueue& newQueue)
{
    elements.swap(newQueue.elements);
}

/*--------------------------------------------------------------------------------------------------------------------*/

ostream &MaxQueue::operator<<(ostream &salida) const
{
    for(Element e: elements) {
        salida << e;
    }
    return salida;
}

/*--------------------------------------------------------------------------------------------------------------------*/
