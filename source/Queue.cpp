#include "Queue.h"

Queue::Queue(u16 len)
{
    length = len;
    buffer = new u16[len];
    for(u16 i = 0; i < length; i++) buffer[i] = 0;
    head = 0;
}


Queue::~Queue()
{
    delete[] buffer;
}

void Queue::enqueue(u16 val)
{
    (head == 0) ? (head = length - 1) : (head--);

    buffer[head] = val;
}


u16 Queue::operator[](u16 index)
{
    return buffer[ (head + index) % length ];
}

u16* Queue::getBuffer()
{
    return buffer;
}
u16 Queue::getHead()
{
    return head;
}

u16 Queue::getLength()
{
    return length;
}
