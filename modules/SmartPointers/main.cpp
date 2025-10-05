#include <bits/stdc++.h>

class DummyClass
{
public:
    DummyClass()
    {
        for (auto &i : data)
        {
            i = rand() % 10 + 1;
        }
        std::println("Dummy Class Constructor, generated data: {}", data);
    }
    ~DummyClass()
    {
        std::println("Dummy Class Destructor");
    }
    void checkAccess()
    {
        std::println("Right access!, data: {}", data);
    }

private:
    std::array<uint8_t, 4> data;
};

void unique_ptr_demo()
{
    std::println("Unique ptr demo");
    auto createUnique = []() {
        auto ptr = std::make_unique<DummyClass>();
        return ptr;
    };
    auto ptr = createUnique();
    // auto secondPtr = ptr; impossible, only one ptr to object in the proper time
    auto newPtr = std::move(ptr); // transfer of ownership

    // ptr->checkAccess(); runtime error, old ptr is nullptr after move

    newPtr->checkAccess();
}

struct NodeBad
{
    std::shared_ptr<NodeBad> next;
    std::shared_ptr<NodeBad> prev;
    NodeBad()
    {
        std::println("NodeBad Constructor");
    }
    ~NodeBad()
    {
        std::println("NodeBad Destructor");
    }
};

struct NodeGood
{
    std::shared_ptr<NodeGood> next;
    std::weak_ptr<NodeGood> prev;
    NodeGood()
    {
        std::println("NodeGood Constructor");
    }
    ~NodeGood()
    {
        std::println("NodeGood Destructor");
    }
};

void shared_ptr_demo()
{
    std::println("Shared ptr demo");
    auto a = std::make_shared<NodeBad>();
    auto b = std::make_shared<NodeBad>();
    a->next = b;
    b->prev = a;
    std::println("a.use_count: {}, b.use_count: {}", a.use_count(), b.use_count());

    auto deref = *(b->prev); // possible
    // no destructors calls! memory leak!
}

void weak_ptr_demo()
{
    std::println("Weak ptr demo");
    auto a = std::make_shared<NodeGood>();
    auto b = std::make_shared<NodeGood>();
    a->next = b;
    b->prev = a;
    std::println("a.use_count: {}, b.use_count: {}", a.use_count(), b.use_count());

    // auto deref = *(b->prev); impossible
    auto deref = (b->prev).lock(); // auto = shared_ptr
}

void auto_ptr_demo()
{
    std::println("Auto ptr was removed with C++17.");
}

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    unique_ptr_demo();
    std::println("-----------------------\n");
    shared_ptr_demo();
    std::println("-----------------------\n");
    weak_ptr_demo();
    std::println("-----------------------\n");
    auto_ptr_demo();
}