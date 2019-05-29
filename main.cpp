#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <type_traits>
#include <iostream>

using namespace std;

enum TestEnum
{
    E_0,
    E_1,
    E_2
};

class Base
{
public:
    void tell() { cout << "base tell" <<endl; }
    const static TestEnum type = E_0;
};

class Der1
{
public:
    void tell() { cout << "der1 tell" <<endl; }
    const static  TestEnum type = E_1;
};

class Der2
{
public:
    void tell() { cout << "der2 tell" << endl; }
    const static  TestEnum type = E_2;
};

template <typename C0, typename C1, typename C2>
class HanlderManager
{
public:
    using EC0 = typename conditional<C0::type == E_0, C0, typename conditional<C1::type == E_0, C1, typename conditional<C2::type == E_0, C2, void>::type>::type>::type;
    using EC1 = typename conditional<C0::type == E_1, C0, typename conditional<C1::type == E_1, C1, typename conditional<C2::type == E_1, C2, void>::type>::type>::type;
    using EC2 = typename conditional<C0::type == E_2, C0, typename conditional<C1::type == E_2, C1, typename conditional<C2::type == E_2, C2, void>::type>::type>::type;

    static_assert(!is_same<EC0, void>::value, "EC0 TYPE ERROR");
    static_assert(!is_same<EC1, void>::value, "EC1 TYPE ERROR");
    static_assert(!is_same<EC2, void>::value, "EC2 TYPE ERROR");

    void handleCmd(TestEnum ev)
    {
        if     (ev == E_1) _handler1.tell();
        else if(ev == E_2) _handler2.tell();
        else               _handler0.tell();
    }
protected:
    EC0 _handler0;
    EC1 _handler1;
    EC2 _handler2;
};

int main(int argc, char* argv[])
{
    HanlderManager<Der2, Der1, Base> hm;

    hm.handleCmd(E_0);
    hm.handleCmd(E_1);
    hm.handleCmd(E_2);

    return 0;
}