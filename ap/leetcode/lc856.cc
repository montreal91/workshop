
//
// Problem: https://leetcode.com/problems/score-of-parentheses/description/
// Author: montreal91
// Solved this solution in 2:10
// Solution is accepted from the first attempt
// Solution is super-fast
// (beats 100% of C++ solutions at the moment)
//

#include <iostream>
#include <stack>
#include <string>


using namespace std;


class Solution {
public:
  int scoreOfParentheses(string S) {
    for (auto i=0; i<S.size(); i++) {
      if (S[i] == '(') {
        score.push(0);
      }
      else if (S[i] == ')' && S[i-1] == '(') {
        incTop();
        squashTop();
      }
      else if (S[i] == ')' && S[i-1] == ')') {
        doubleTop();
        squashTop();
      }
    }
    return score.top();
  }

private:
  stack<int> score;

  void incTop() {
    auto p = score.top();
    p++;
    score.pop();
    score.push(p);
  }

  void doubleTop() {
    auto p = score.top();
    p *= 2;
    score.pop();
    score.push(p);
  }

  void squashTop() {
    if (score.size() < 2) {
      return;
    }
    auto p1 = score.top();
    score.pop();
    auto p0 = score.top();
    score.pop();
    score.push(p0 + p1);
  }
};

int main(int argc, char const *argv[]) {
  Solution s;
  cout << s.scoreOfParentheses("()(()(()))(())") << endl;;
  return 0;
}
