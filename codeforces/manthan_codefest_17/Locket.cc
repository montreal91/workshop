
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <cmath>

using namespace std;

typedef pair<long long, long long> pair_of_ints;

vector<int> convert_number_in_base(long long number, int base) {
  vector<int> res;
  int remnant = 0, div_result = number;
  while (div_result >= base) {
    remnant = div_result % base;
    div_result /= base;
    res.push_back(remnant);
  }
  res.push_back(div_result);
  return res;
}

long long convert_number_to_decimal(const vector<int> num, int base) {
  long long res = 0;
  for (int i = 0; i < num.size(); i++) {
    res += num[i] * pow(base, i);
  }
  return res;
}

long get_quantity_of_magic_numbers(int base, const vector<int>& num) {
  int digits = num.size();
  if (digits == 0 || digits % 2 !=0) {
    return 0;
  }
  if (digits == 2) {
    if (num[1] <= num[0]) {
      return num[1];
    } else {
      return num[1] - 1;
    }
  }
  return -1;
}

long get_quantity_of_magic_numbers(int digits, int base) {
  if (digits == 0 || digits % 2 != 0) {
    return 0;
  }
  if (digits == 2) {
    return base - 1;
  }

  // else
  long mag = get_quantity_of_magic_numbers(digits - 2, base);
  long power = pow(base, digits-3);
  return mag * base + 2 * ((base - 1) * power - mag);
}

void print_num(const vector<int>& num, ostream& out) {
  for (auto n : num) {
    out << n;
  }
}

bool is_number_magic(const vector<int>& number, int base) {
  for (int i=0; i < base; i++) {
    int count = 0;
    for (int n : number) {
      if (n == i) {
        count++;
      }
    }
    if (count % 2 != 0) {
      return false;
    }
  }
  return true;
}

int function(istream& in, ostream& out) {
  int q;
  in >> q;
  vector<pair_of_ints> pairs;
  vector<int> bases;

  int base;
  long long first, second;
  for (int i = 0; i < q; i++) {
    in >> base >> first >> second;
    pair_of_ints t(first, second);
    bases.push_back(base);
    pairs.push_back(t);
  }

  vector<int> num;
  for (int i=0; i<q; i++) {
    int magic = 0;
    for (int j=pairs[i].first; j<=pairs[i].second; j++) {
      num = convert_number_in_base(j, bases[i]);
      // out << j << " ";
      // print_num(num, out);
      // out << " " << is_number_magic(num, bases[i]) << endl;
      if ( is_number_magic(num, bases[i])) {
        magic++;
      }
    }
    out << magic << endl;
  }
  out << endl;
  // for (int i=1; i<20; i++) {
  //   num = convert_number_in_base(i, 4);
  //   print_num(num, out);
  //   out << " " << get_quantity_of_magic_numbers(3, num) << endl;
  //   // out << i << " " <<  get_quantity_of_magic_numbers(i, 4) << endl;
  // }
  return 0;
}

int main() {
  ifstream in("data.in");
  function(in, cout);
  return 0;
}
