#include <iostream>
#include <functional>
#include "complexlist.h"

using namespace std;


void testComplex() {
    Complex a(1, 2), b(3, 4);

    cout << "a = " << a
         << "\nb = " << b
         << "\na + b = " << a + b
         << "\na - b = " << a - b
         << "\na * b = " << a * b
         << "\na / b = " << a / b
         << endl;
}

void tryWrapper(std::function<void(void)> const& f) {
    try{
        f();
    }
    catch(const std::out_of_range& e) {
        cout << "\nException has thrown!\ne.what(): " << e.what()
             << endl;
    }
}

void testComplexList() {
    ComplexList list{
        {1, 2},
        {3, 4},
        {5, 6},
        {7, 8},
        {9, 0},
    };

    list.push_front({-1, -2});
    list.push_back({1.5, 2.5});
    list.remove({3, 4});

    for(size_t i = 0; i != list.size() + 1; i++) {
        tryWrapper([&list, i]()
        {
            auto val = list[i];
            cout << "list[" << i << "] = " << val << endl;
        });
    }
}

int main()
{
    testComplex();
    testComplexList();
    return 0;
}
