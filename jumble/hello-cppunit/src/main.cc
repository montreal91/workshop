
#include <iostream>

#include "my_class.h"


using namespace std;

int main(int argc, char *argv[]) {
    MyClass my_object = MyClass(4);
    cout << my_object.GetX() << endl;
    return 0;
}
