
#include <filesystem>
#include <iostream>

using namespace std;

void test_filesystem();


int main() {
  cout << "Hello World!" << endl;
  test_filesystem();
  return 0;
}

void test_filesystem() {
  string path(".gitignore");
  filesystem::path file_path(path);
  if (filesystem::exists(file_path)) {
    cout << "The file exists. Yay!" << endl;
    return;
  }
  cout << "The file does not exist." << endl;
}
