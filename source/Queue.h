#ifndef QUEUE_H
#define QUEUE_H

#include "main.h"

class Queue
{
public:
    Queue();
    virtual ~Queue();

    void enqueue(u16 val);

    u16 operator[](u16 index);

    u16* getBuffer();
    u16 getHead();
    u16 getTail();
    u16 getLength();

private:
    u16 length;
    u16 buffer[TOPSCREEN_WIDTH];
    u16 head;

};

#endif // QUEUE_H
