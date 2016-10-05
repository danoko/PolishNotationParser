#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include "Lexer.h"
#include "ASTNode.h"


/*
Class Parser is used to create Abstract Syntax Tree from list of tokens
*/


class Parser{
private:
	//custom type see: ASTNode.h
	TSharedASTNode root;
	//custom type see: Lexer.h
	TTokenList tokenList;
	unsigned index;
	std::shared_ptr<Token> currToken;

	void getNextToken(){
		index++;
		currToken = tokenList[index];
	}

	TSharedASTNode numNode(){
		TSharedASTNode num(new ASTNode());
		if (currToken->type == UMINUS){
			num->token = currToken;
			getNextToken();
			num->leftNode = numNode();
		}
		else if (currToken->type == NUM){
			num->token = currToken;
			getNextToken();
		}
		else if (currToken->type == LPAREN){
			getNextToken();
			num = exprNode();
			getNextToken();
		}
		return num;
	}

	TSharedASTNode exponentNode(){
		TSharedASTNode base = numNode();
		if (currToken->type == POW){
			TSharedASTNode exp = TSharedASTNode(new ASTNode);
			exp->token = currToken;
			getNextToken();
			exp->leftNode = base;
			exp->rightNode = exprNode();
			return exp;
		}
		return base;
	}

	TSharedASTNode factorialNode(){
		TSharedASTNode factorial = exponentNode();
		while (currToken->type == MUL || currToken->type == DIV || currToken->type == MOD){
			TSharedASTNode newNode(new ASTNode());
			newNode->token = currToken;
			getNextToken();
			newNode->leftNode = factorial;
			newNode->rightNode = exponentNode();
			factorial = newNode;
		}
		return factorial;
	}

	TSharedASTNode termNode(){
		TSharedASTNode term = factorialNode();
		while (currToken->type == PLUS || currToken->type == MINUS){
			TSharedASTNode newNode(new ASTNode());
			newNode->token = currToken;
			getNextToken();
			newNode->leftNode = term;
			newNode->rightNode = factorialNode();
			term = newNode;
		}
		return term;
	}

	TSharedASTNode exprNode(){
		TSharedASTNode expr = termNode();
		return expr;
	}

public:

	void setTokenList(const TTokenList& list){
		tokenList = list;
		root = TSharedASTNode(new ASTNode());
		root->token = std::shared_ptr<Token>(new Token(EPS, ""));
		index = 0;
		currToken = tokenList[index];
	}

	void parse(){
		if (currToken->type == EPS) return;
		root = exprNode();
	}

	const TSharedASTNode& getRoot(){
		return root;
	}

	~Parser(){
		tokenList.clear();
	}
};

#endif