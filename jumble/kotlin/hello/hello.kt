// 2021.01.24

val INTEGER: String = "INTEGER"
val PLUS = "PLUS"
val MINUS = "MINUS"
val EOF = "EOF"


data class Token(val type: String, val value: Int?)


class Interpreter(
    private val input: String
  ) {

  private var currentToken: Token
  private var pos: Int = 0

  init {
    currentToken = getNextToken()
  }

  fun expr(): Int {
    Eat(INTEGER)
    val left = currentToken
    nextChar()
    currentToken = getNextToken()
    val op = Eat(PLUS)
    nextChar()
    currentToken = getNextToken()
    val right = Eat(INTEGER)
    if (left.value == null || right.value == null) {
      throw Exception("Syntax error.")
    }
    return left.value + right.value
  }

  private fun getNextToken(): Token = when {
    pos >= input.length -> Token(type=EOF, value=null)
    input[pos].isDigit() -> Token(type=INTEGER, value=input[pos].getIntValue())
    input[pos].equals('+') -> Token(type=PLUS, value=null)
    input[pos].equals('-') -> Token(type=MINUS, value=null)
    else -> Token(type=EOF, value=null)
  }

  private fun nextChar() {
    pos++;
  }

  private fun error(): Nothing {
    throw Exception("Syntax error.")
  }

  private fun Eat(token_type: String): Token {
    if (currentToken.type == token_type) {
      return getNextToken()
    }
    else {
      error()
    }
  }
}

fun Char.getIntValue() = this.toString().toInt()


fun printAnswer(n: Int, answer:  Int)  {
  println("Out[$n]: $answer\n")
}


fun main() {
  println("Write 'q' to quit.")
  var counter = 1
  while (true) {
    print("In [$counter]: ")
    val text: String = readLine()!!
    if (text.equals("q")){
      break
    }
    val i = Interpreter(text)
    printAnswer(counter, i.expr())
    counter++
  }
}
