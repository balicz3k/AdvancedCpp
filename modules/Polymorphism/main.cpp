#include <bits/stdc++.h>

class Shape
{
public:
    virtual void name()
    {
        std::println("Shape");
    }
    virtual ~Shape()
    {
        std::println("Shape Destructor");
    };
    void **getVTablePtr()
    {
        return reinterpret_cast<void **>(this);
    }
};

class Cycle : public Shape
{
    void name() override
    {
        std::println("Cycle");
    }
};

class Square : public Shape
{
    void name() override
    {
        std::println("Square");
    }
};

int main()
{
    std::vector<Shape *> v = {new Cycle, new Square};

    for (auto shape : v)
    {
        void **ptrToVptr = shape->getVTablePtr();
        void **vtable = reinterpret_cast<void **>(*ptrToVptr);

        std::println("Shape: {} vptr: {}", static_cast<void *>(shape), *ptrToVptr);

        for (int i = 0; i < 4; ++i)
        {
            std::println("  slot[{}]: {}", i, vtable[i]);
        }

        /* MAY CAUSE UNEXPECTED BEHAVIOUR*/

        using Fn = void (*)(Shape *);
        Fn name = reinterpret_cast<Fn>(vtable[0]); // first [0] element of vTable is ptr to name method, it doesn't have
                                                   // to be like this on different compiler
        name(shape);

        /* MAY CAUSE UNEXPECTED BEHAVIOUR */
    }

    for (const auto shape : v)
    {
        delete shape;
    }
}