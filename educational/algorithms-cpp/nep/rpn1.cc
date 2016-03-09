
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

enum operation_type
{
    power = 3,
    divide = 2,
    multiply = 2,
    minus = 1,
    plus = 1,
    null = 0
};


string fold_in_braces(const string& in)
{
    return "(" + in + ")";
}

bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while ((it != s.end() && isdigit(*it)) || *it == '.') ++it;
    return !s.empty() && it == s.end();
}

bool is_operation(const string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

operation_type get_operation_type(const string& token)
{
    if (is_number(token)) return operation_type::null;
    else if (token == "+" || token == "-") return operation_type::plus;
    else if (token == "*" || token == "/") return operation_type::multiply;
    else if (token == "^") return operation_type::power;
    else return operation_type::null;
}

operation_type get_lowest_operation(const string& line)
{
    if (is_number(line)) return operation_type::null;
    operation_type res = power;
    for (auto c : line)
    {
        if (c == '+' && res > operation_type::plus) res = operation_type::plus;
        else if (c == '-' && res > operation_type::minus) res = operation_type::minus;
        else if (c == '*' && res > operation_type::multiply) res = operation_type::multiply;
        else if (c == '/' && res > operation_type::divide) res = operation_type::divide;
        else if (c == '^' && res > operation_type::power) res = operation_type::power;
    }
    return res;
}

string get_infix_from_postfix(const vector<string>& tokens)
{
    stack<string> res;
    for (size_t i=0; i < tokens.size(); i++)
    {
        if (is_number(tokens[i]))
        {
            res.push(tokens[i]);
        }
        else if (is_operation(tokens[i]))
        {
            string one = res.top();
            res.pop();
            string two = res.top();
            res.pop();
            operation_type one_t = get_lowest_operation(one);
            if (one_t != operation_type::null && one_t < get_lowest_operation(tokens[i]))
            {
                one = fold_in_braces(one);
            }
            operation_type two_t = get_lowest_operation(two);
            if (two_t != operation_type::null && two_t < get_lowest_operation(tokens[i]))
            {
                two = fold_in_braces(two);
            }
            res.push(two + tokens[i] + one);
        }
    }
    return res.top();
}

vector<string> get_tokens(istream& is)
{
    vector<string> tokens;
    string input = "";
    while (input != ";") {
        is >> input;
        tokens.push_back(input);
    }
    tokens.pop_back();
    return tokens;
}

int main(int argc, char const *argv[])
{
    ifstream in("in.txt");
    vector<string> tokens;
    tokens = get_tokens(in);
    cout << get_infix_from_postfix(tokens) << endl;
    return 0;
}
