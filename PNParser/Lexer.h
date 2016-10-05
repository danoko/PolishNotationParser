#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <memory>
#include <string>
#include <cctype>
#include "Token.h"

//my custom name for vector containing smart pointers of tokens
typedef std::vector<std::shared_ptr<Token>> TTokenList;


/*
Class Lexer is used for braking strings into list of tokens(lexems)
*/

class Lexer{
private:
	//as it's named
	std::string expressionToParse;
	//current char to be scanned 
	char currChar;
	//current index of char to be scanned
	unsigned pos;
	//flag of state used to distinguish unary minus from binary minus
	bool canBeUMinus;
	//it's custom name for vector of Tokens
	TTokenList tokenList;

	//method to reset current char to next in string
	void advance(){
		pos++;
		currChar = expressionToParse[pos];
	}

	//method to test if a char is any of arithmetic operators
	bool isOper(char c){
		switch (c){
		case '+':
			return true;
		case '-':
			return true;
		case '*':
			return true;
		case '/':
			return true;
		case '%':
			return true;
		case '^':
			return true;
		case '(':
			return true;
		case ')':
			return true;
		default:
			return false;
		}
	}

	//method to tokenize operators
	void scanOper(){

		switch (currChar){
		case '+':
			tokenList.push_back(std::shared_ptr<Token>(new Token(PLUS, "+")));
			advance();
			break;
		case '-':
			Type t;
			if (canBeUMinus == true)
				t = UMINUS;
			else
				t = MINUS;
			tokenList.push_back(std::shared_ptr<Token>(new Token(t, "-")));
			advance();
			break;
		case '*':
			tokenList.push_back(std::shared_ptr<Token>(new Token(MUL, "*")));
			advance();
			break;
		case '%':
			tokenList.push_back(std::shared_ptr<Token>(new Token(MOD, "%")));
			advance();
			break;
		case '/':
			tokenList.push_back(std::shared_ptr<Token>(new Token(DIV, "/")));
			advance();
			break;
		case '^':
			tokenList.push_back(std::shared_ptr<Token>(new Token(POW, "^")));
			advance();
			break;
		case '(':
			tokenList.push_back(std::shared_ptr<Token>(new Token(LPAREN, "(")));
			advance();
			break;
		case ')':
			tokenList.push_back(std::shared_ptr<Token>(new Token(RPAREN, ")")));
			advance();
			break;
		}
		canBeUMinus = true;
	}

	//method to scan string of numerical characters
	std::string getNum(){
		std::string num;
		while (isdigit(currChar)){
			num += currChar;
			advance();
		}
		return num;
	}

	//method to scan integers or reals
	void scanDigit(){

		std::string num;
		num = getNum();

		if (currChar == '.') {
			num += currChar;
			advance();
			num += getNum();
		}

		canBeUMinus = false;
		tokenList.push_back(std::shared_ptr<Token>(new Token(NUM, num)));
	}

public:
	Lexer(){
		pos = 0;
		currChar = '\0';
		canBeUMinus = true;
	}

	void setExpressionToScan(const std::string& expr){
		expressionToParse = expr;
		pos = 0;
		currChar = expressionToParse[pos];
		canBeUMinus = true;
	}

	void scanTokens(){

		while (pos < expressionToParse.length()){
			if (isdigit(currChar)) scanDigit();
			else if (isOper(currChar)) scanOper();
			else if (isspace(currChar))advance();
			else
				throw "error at lexer\n";
		}
		tokenList.push_back(std::shared_ptr<Token>(new Token(EPS, "")));
	}

	const TTokenList& getTokenList(){
		return tokenList;
	}

	~Lexer(){
		tokenList.clear();
	}
};
#endif