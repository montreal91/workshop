//
// Problem: https://leetcode.com/problems/some-problem/
// Author: montreal91
// Solved in 1:08
// Failed attempts: 0
//
using System;
using System.Diagnostics;
using System.Text;

using Utils;


namespace leetsharp {

abstract class Token {
  public static readonly string INTEGER = "INTEGER";
  public static readonly string PLUS = "PLUS";
  public static readonly string MINUS = "MINUS";
  public static readonly string MUL = "MUL";
  public static readonly string DIV = "DIV";
  public static readonly string EOF = "EOF";

  private string type;

  public Token(string type) {
    this.type = type;
  }

  public string GetTokenType() {
    return type;
  }
}

abstract class GenericToken<T> : Token {
  private T val;

  public GenericToken(string type, T val) : base(type) {
    this.val = val;
  }

  public T GetVal() {
    return val;
  }
}


class IntegerToken : GenericToken<long> {
  public IntegerToken(string type, long val) : base(type, val) {}
}


class OperatorToken : GenericToken<string> {
  public OperatorToken(string type, string val) : base(type, val) {}
}

class EofToken : GenericToken<string> {
  public EofToken() : base(Token.EOF, "") {}
}


class Lexer {
  private readonly string text;
  private int pos = 0;

  public Lexer(string text) {
    this.text = text;
  }

  public Token GetNextToken() {
    Skip();
    if (pos >= text.Length) {
      return new EofToken();
    }

    if (Char.IsDigit(text[pos])) {
      return ReadInteger();
    }
    else {
      return ReadOperator();
    }
  }

  private void Skip() {
    while (pos < text.Length && text[pos] == ' ') {
      pos++;
    }
  }

  private IntegerToken ReadInteger() {
    var sb = new StringBuilder();
    while (pos < text.Length && Char.IsDigit(text[pos])) {
      sb.Append(text[pos]);
      pos++;
    }
    return new IntegerToken(Token.INTEGER, Int64.Parse(sb.ToString()));
  }

  private OperatorToken ReadOperator() {
    OperatorToken res;
    if (text[pos] == '+') {
      res = new OperatorToken(Token.PLUS, "+");
    }
    else if (text[pos] == '-') {
      res = new OperatorToken(Token.MINUS, "-");
    }
    else if (text[pos] == '*') {
      res = new OperatorToken(Token.MUL, "*");
    }
    else if (text[pos] == '/') {
      res = new OperatorToken(Token.DIV, "/");
    }
    else {
      throw new Exception("Unexpected character.");
    }
    pos++;
    return res;
  }
}

class Calculator {
  private Lexer lexer;
  private Token currentToken;

  public Calculator(Lexer lexer) {
    this.lexer = lexer;
    currentToken = this.lexer.GetNextToken();
  }

  public long Calculate() {
    return Expr();
  }

  private long Expr() {
    var res = Operator();
    while (TokenIsPlusOrMinus()) {
      var op = currentToken;
      if (op.GetTokenType() == Token.PLUS) {
        Eat(Token.PLUS);
        res += Operator();
      }
      else if (op.GetTokenType() == Token.MINUS) {
        Eat(Token.MINUS);
        res -= Operator();
      }
      else {
        throw new Exception("Unexpected operation.");
      }
    }
    return res;
  }

  private long Operator() {
    var res = Factor();
    while (TokenIsMulOrDiv()) {
      var op = currentToken;
      if (op.GetTokenType() == Token.MUL) {
        Eat(Token.MUL);
        res *= Factor();
      }
      else if (op.GetTokenType() == Token.DIV) {
        Eat(Token.DIV);
        res /= Factor();
      }
      else {
        throw new Exception("Unexpected operation.");
      }
    }
    return res;
  }

  private long Factor() {
    var token = (IntegerToken)currentToken;
    Eat(Token.INTEGER);
    return token.GetVal();
  }

  private void Eat(string tokenType)  {
    if (currentToken.GetTokenType() == tokenType) {
      currentToken = lexer.GetNextToken();
    }
    else {
      throw new Exception("Unexpected token.");
    }
  }

  private bool TokenIsMulOrDiv() {
    if (currentToken.GetTokenType() == Token.MUL) {
      return true;
    }
    return currentToken.GetTokenType() == Token.DIV;
  }

  private bool TokenIsPlusOrMinus() {
    if (currentToken.GetTokenType() == Token.PLUS) {
      return true;
    }
    return currentToken.GetTokenType() == Token.MINUS;
  }
}

class Solution0227 {
  public int Calculate(string s) {
    if (s == null) {
      return 0;
    }
    var calc = new Calculator(new Lexer(s));
    return (int)calc.Calculate();
  }

  public static void TestSolution() {
    var S = new Solution0227();

    Debug.Assert(S.Calculate("0") == 0);
    Debug.Assert(S.Calculate("1 + 1") == 2);
    Debug.Assert(S.Calculate("1 - 1") == 0);
    Debug.Assert(S.Calculate("64 * 2") == 128);
    Debug.Assert(S.Calculate("64 / 2") == 32);
    Debug.Assert(S.Calculate("2 * 2 * 2 + 2 * 2 + 1") == 13);
    Console.WriteLine("All tests passed.");
  }
}


} // namespace leetsharp
