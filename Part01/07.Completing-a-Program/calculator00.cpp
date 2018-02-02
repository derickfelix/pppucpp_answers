/*
    Simple calculator

    Revision history:

        Revised by Derick Felix December 2017
        Revised by Derick Felix January 2018
        Revised by Derick Felix February 2018
        Originally written by Derick Felix
            (mail@example.com) Summer 2017

    This program implements a basic expression calculator.
    Input from cin; output from cout.
    The grammar for input is:

        Statement:
            Expression
            Print
            Quit

        Print:
            ;

        Quit
            q

        Expression:
            Term
            Expression + term
            Expression - term
        Term:
            Primary
            Term * primary
            Term / primary
            Term % primary
        Primary
            Number
            ( Expression )
            + Primary
            - Primary
        Number:
            floating-point-literal

        Input comes from cin through the Token_stream called ts.

*/
#include "../std_lib_facilities.h"

const char c_number = '8';    // we use '8' to represent a number
const char c_quit = 'q';
const char c_print = ';';

const string prompt = "> ";
const string result = "= ";

class Token { // a very simple user-defined type
public:
    char kind;
    double value;
};

class Token_stream {
public:
    Token get();            // get a Token
    void putback(Token t);  // put a Token back
    void ignore(char c);    // discard characters up to and including a c
private:
    bool full {false};  // is there a Token in the buffer?
    Token buffer;       // here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t; // copy t to buffer
    full = true; // buffer is now full
}

// read characters from cin and compose a Token
Token Token_stream::get()
{
    if (full) { // check if we already have a Token ready
        full = false;
        return buffer;
    }
    char ch;
    cin >> ch; // note that >> skips whitespace (space, newline, tag, etc.)

    switch (ch) {
        case '%': 
        case '/':
        case '(': 
        case ')': 
        case '+': 
        case '-': 
        case '*':
        case c_print:
        case c_quit:
            return Token {ch}; // let each character represent itself
        case '.':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch); // put digit back into the input stream
            double val;
            cin >> val;
            return Token {c_number, val};
        }
        default:
            error("Bad token");
    }
}

/* @c represents the kind of token */
void Token_stream::ignore(char c) 
{
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch = 0;
    while (cin >> ch)
        if (ch == c) return;
}

//vector<Token> tok; // we'll put the tokens here
Token_stream ts; // provides get() and putback()
// functions to match the grammar rules:
double expression(); // deal with + and -
double term(); // deal with *, / and %
double primary(); // deal with numbers and parentheses


void clean_up_mess()
{
    ts.ignore(c_print);
}

void calculate()
{
    while(cin)
    {
        try {
            cout << prompt; // print prompt
            Token t = ts.get();
            while (t.kind == c_print) t=ts.get(); // eat ';'
            if (t.kind == c_quit) return;
            ts.putback(t);
            cout << result << expression() << '\n';
        } catch (exception& e) {
            cerr << e.what() << '\n';
            clean_up_mess();
        }
    }
}

int main()
{
    calculate();
    keep_window_open();

    return 0;
}

double expression()
{
    double left = term(); // read and evaluate an Term
    Token t = ts.get(); // get next Token from the Token stream

    while (true) {
        switch (t.kind) {
            case '+':
                left += term(); // evaluate Term and add
                t = ts.get();
                break;
            case '-':
                left -= term(); // evaluate Term and subtract
                t = ts.get();
                break;
            default:
                ts.putback(t); // put t back into the token stream
                return left; // finally: no more + or -; return the answer
        }
    }
}

double term()
{
    double left = primary();
    Token t = ts.get(); // get the next Token from the Token stream
    while (true) {
        switch(t.kind) {
            case '*':
                left *= primary();
                t = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
            case '%':
            {
                int v1 = narrow_cast<int>(left);
                int v2 = narrow_cast<int>(primary());
                if (v2 == 0) error("divide by zero");
                left = v1 % v2;
                t = ts.get();
            }
            default: 
                ts.putback(t); // put t back into the token stream
                return left;
        }
    }
}

double primary()
{
    Token t = ts.get();
    switch (t.kind) {
        case '(': // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
        case c_number:
            return t.value; // return the number's value
        case '+':
            return +primary();
        case '-':
            return -primary();
        default:
            error("primary expected");
    }
}