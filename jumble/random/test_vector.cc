
#include <vector>
#include <iostream>

using namespace std;

struct Foo {
    bool l;
};

int main(int argc, char *argv[]) {
    vector<Foo> vec;
    for ( int i = 0; i < 7; i++ ) {
        Foo f;
        f.l = i % 2;
        vec.push_back(f);
    }

    for ( auto& v : vec ) {
        cout << v.l << endl;
    }

    for ( auto i = vec.begin(); i != vec.end(); ) {
        if ( i->l ) {
            i = vec.erase( i );
        } else {
            i++;
        }
    }
    vec.shrink_to_fit();

    cout << endl;
    for ( auto& v : vec ) {
        cout << v.l << endl;
    }

    for ( int i = 0; i < 7; i++ ) {
        Foo f;
        f.l = i % 2;
        vec.push_back(f);
    }

    for ( auto& v : vec ) {
        cout << v.l << endl;
    }



    return 0;
}
