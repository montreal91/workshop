
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

enum Action {
  buy = -1,
  sell = 1,
  do_nothing = 0
};

int action_to_int(Action a) {
  switch (a) {
    case Action::buy: return -1;
    case Action::sell: return 1;
    case Action::do_nothing: return 0;
  }
}

class Stock {
public:
  Stock() {
    this->value = 0;
    this->day = 0;
    this->action = Action::do_nothing;
  }

  Stock(int value, int day) {
    this->value = value;
    this->day = day;
    this->action = Action::do_nothing;
  }

  int get_value() const {
    return this->value;
  }

  int get_day() const {
    return this->day;
  }

  Action get_action() const {
    return this->action;
  }

  void set_action(Action action) {
    this->action = action;
  }

  int evaluate_stock() const {
    return action_to_int(this->action) * this->value;
  }

private:
  int value;
  int day;
  Action action;
};

bool stock_comparator(const Stock& s1, const Stock& s2) {
  return s1.get_value() > s2.get_value();
}

bool is_deal_good(const Stock& big_stock, const Stock& small_stock) {
  bool c1 = big_stock.get_value() > small_stock.get_value();
  bool c2 = big_stock.get_day() > small_stock.get_day();
  bool c3 = small_stock.get_action() == Action::do_nothing;
  return c1 && c2 && c3;
}

int function(istream& in, ostream& out) {
  int n;
  in >> n;
  vector<Stock> stocks;

  int s;
  for (int i = 0; i < n; i++) {
    in >> s;
    Stock stock(s, i);
    stocks.push_back(stock);
  }

  sort(stocks.begin(), stocks.end(), stock_comparator);

  int border = n / 2 + 1;

  for (int i=0; i<border; i++) {
    Stock big_stock = stocks[i];
    for (int j=n-1; j>=border; j--) {
      Stock small_stock = stocks[j];
      if (is_deal_good(big_stock, small_stock)) {
        stocks[i].set_action(Action::sell);
        stocks[j].set_action(Action::buy);
        break; 
      }
    }
  }

  int sum = 0;
  for (Stock el : stocks) {
    sum += el.evaluate_stock();
    // out << el.evaluate_stock() << endl;
  }
  out << sum << endl;
  return 0;
}

int main() {
  ifstream in("data/stocks.in");
  function(cin, cout);
  return 0;
}
