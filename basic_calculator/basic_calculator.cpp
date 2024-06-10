#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <cmath>

using namespace std;

struct Token {
    enum class Type {
        NUMBER,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        END
    };

    Type type;
    unsigned value;
};

struct Result {
    int nominator;
    int denominator;
};

map<Token::Type, int> precedence = {
    {Token::Type::PLUS, 1},
    {Token::Type::MINUS, 1},
    {Token::Type::MULTIPLY, 2},
    {Token::Type::DIVIDE, 2}
};

vector<Token> tokenize(string str) {
    vector<Token> tokens;

    for(auto i = 0; i < str.length(); i++) {
        if (str[i] == '+') {
            tokens.push_back({Token::Type::PLUS, 0});
        } else if (str[i] == '-') {
            tokens.push_back({Token::Type::MINUS, 0});
        } else if (str[i] == '*') {
            tokens.push_back({Token::Type::MULTIPLY, 0});
        } else if (str[i] == '/') {
            tokens.push_back({Token::Type::DIVIDE, 0});
        } else if (str[i] == '(') {
            tokens.push_back({Token::Type::LPAREN, 0});
        } else if (str[i] == ')') {
            tokens.push_back({Token::Type::RPAREN, 0});
        } else if (isdigit(str[i])) {
            unsigned value = 0;
            while (i < str.length() && isdigit(str[i])) {
                value = value * 10 + (str[i] - '0');
                i++;
            }
            tokens.push_back({Token::Type::NUMBER, value});
            i--;
        }
    }

    tokens.push_back({Token::Type::END, 0});

    return tokens;
}

vector<Token> shunting_yard_algorithm(vector<Token> tokens) {
    vector<Token> output;
    stack<Token> operators;

    for(auto i = 0; i < tokens.size(); i++) {
        auto token = tokens[i];
        auto type = token.type;

        if (type == Token::Type::NUMBER) {
            output.push_back(token);
        } else if (type == Token::Type::PLUS || type == Token::Type::MINUS || type == Token::Type::MULTIPLY || type == Token::Type::DIVIDE) {
            while(!operators.empty()) {
                auto last_operator = operators.top();
                if (last_operator.type == Token::Type::LPAREN || precedence[last_operator.type] < precedence[type]) {
                    break;
                }
                output.push_back(last_operator);
                operators.pop();
            }
            operators.push(token);
        } else if (type == Token::Type::LPAREN) {
            operators.push(token);
        } else if (type == Token::Type::RPAREN) {
            while(!operators.empty()) {
                auto last_operator = operators.top();
                if (last_operator.type == Token::Type::LPAREN) {
                    break;
                }
                output.push_back(last_operator);
                operators.pop();
            }
            operators.pop();
        }
    }

    while(!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    if (a < b) {
        return gcd(b, a);
    }
    return gcd(b, a % b);
}

void display_token(Token token) {
    switch (token.type) {
        case Token::Type::NUMBER:
            cout << token.value << " ";
            break;
        case Token::Type::PLUS:
            cout << "+ ";
            break;
        case Token::Type::MINUS:
            cout << "- ";
            break;
        case Token::Type::MULTIPLY:
            cout << "* ";
            break;
        case Token::Type::DIVIDE:
            cout << "/ ";
            break;
        case Token::Type::LPAREN:
            cout << "( ";
            break;
        case Token::Type::RPAREN:
            cout << ") ";
            break;
        case Token::Type::END:
            cout << endl;
            break;
    }
}

Result eval(vector<Token> tokens) {
    stack<Result> stack;

    for(auto i = 0; i < tokens.size(); i++) {
        auto token = tokens[i];
        auto type = token.type;

        Result result;
        Result one, two;
        int common;

        switch(type) {
            case Token::Type::NUMBER:
                result.nominator = token.value;
                result.denominator = 1;
                stack.push(result);
                break;
            case Token::Type::PLUS:
                one = stack.top();
                stack.pop();
                two = stack.top();
                stack.pop();
                result.nominator = one.nominator * two.denominator + two.nominator * one.denominator;
                result.denominator = one.denominator * two.denominator;
                stack.push(result);
                break;
            case Token::Type::MINUS:
                one = stack.top();
                stack.pop();
                two = stack.top();
                stack.pop();
                result.nominator = two.nominator * one.denominator - one.nominator * two.denominator;
                result.denominator = one.denominator * two.denominator;
                stack.push(result);
                break;
            case Token::Type::MULTIPLY:
                one = stack.top();
                stack.pop();
                two = stack.top();
                stack.pop();
                result.nominator = one.nominator * two.nominator;
                result.denominator = one.denominator * two.denominator;
                common = gcd(abs(result.nominator), abs(result.denominator));
                result.nominator /= common;
                result.denominator /= common;
                stack.push(result);
                break;
            case Token::Type::DIVIDE:
                one = stack.top();
                stack.pop();
                two = stack.top();
                stack.pop();
                result.nominator = two.nominator * one.denominator;
                result.denominator = two.denominator * one.nominator;
                if (result.denominator == 0) {
                    cout << "ERROR" << endl;
                    exit(0);
                }
                common = gcd(abs(result.nominator), abs(result.denominator));
                result.nominator /= common;
                result.denominator /= common;
                stack.push(result);
                break;
            default:
                break;
        }
    }

    return stack.top();
}

int main() {
    string str;

    // str = "1 + 5 * 7 / 8";      // Result: 43/8
    // str = "1 * (3*4/(8-(7+0)))";    // Result: 12
    // str = "1 / (0 - 5)";    // Result: -1/5
    // str = "1 / 0";    // Result: ERROR
    getline(cin, str);

    auto tokens = tokenize(str);
    auto output = shunting_yard_algorithm(tokens);

    auto result = eval(output);

    auto sign = result.nominator * result.denominator < 0 ? -1 : 1;

    if (sign == -1) {
        cout << "-";
    }
    if (result.denominator == 1) {
        cout << abs(result.nominator) << endl;
    } else {
        cout << abs(result.nominator) << '/' << abs(result.denominator) << endl;
    }

    return 0;
}