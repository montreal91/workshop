#include <fstream>

using namespace std;

long SumTwoNumbers() {
    long a, b;
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> a >> b;
    out << a + b; 
}

int main(int argc, char const *argv[])
{
    SumTwoNumbers();
    return 0;
}