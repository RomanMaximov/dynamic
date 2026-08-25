#include <math.h>
#include "test/testarraylist.h"
#include "test/testlinkedlist.h"
#include "test/testset.h"
#include "test/teststring.h"

typedef struct Point Point;

typedef struct Point {
    int x, y;
    Point* (*move)(struct Point*, int, int);
    Point* (*scale)(struct Point*, int);
    Point* (*print)(struct Point*);
} Point;

Point* move(Point* self, int dx, int dy) {
    self->x += dx;
    self->y += dy;
    return self;
}

Point* scale(Point* self, int s) {
    self->x *= s;
    self->y *= s;
    return self;
}

Point* print(Point* self) {
    printf("Point(%d, %d)\n", self->x, self->y);
    return self;
}

Point* newPoint(int x, int y) {
    Point* p = malloc(sizeof(Point));
    p->x = 0;
    p->y = 0;
    p->move = move;
    p->scale = scale;
    p->print = print;
    return p;
}


int main()
{
    /*Point* p = newPoint(1, 2);

    p->move(p, 3, 4)
        ->scale(p, 2)
        ->print(p);
    puts("");*/


    testArrayList();
    //testLinkedList();
    //testSet();
    //testString();

    return 0;
}
