#include "smart_ptr.h"
#include<iostream>


class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    ~circle() { puts("~circle()"); }
};

int main()
{
    smart_ptr<circle> ptr1(new circle());
    printf("use count of ptr1 is %ld\n",
        ptr1.use_count());
    smart_ptr<shape> ptr2;
    printf("use count of ptr2 was %ld\n",
        ptr2.use_count());
    ptr2 = ptr1;
    printf("use count of ptr2 is now %ld\n",
        ptr2.use_count());
    if (ptr1) {
        puts("ptr1 is not empty");
    }
}