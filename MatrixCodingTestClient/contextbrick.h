#ifndef CONTEXTBRICK_H
#define CONTEXTBRICK_H

#define DEBUG 1

typedef unsigned char byte_t;

class ContextBrick
{
public:
    ContextBrick();

    ContextBrick(byte_t content, byte_t mask);

    bool hasMatch(ContextBrick *otherBrick);

    void printContextBrick();

    byte_t content;
    byte_t mask;
};

#endif // CONTEXTBRICK_H
