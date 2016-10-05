#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <stack>
#include <sstream>
#include "Parser.h"

/*
Class Evaluator evaluates nodes of AST to arithmetic value of double precossion
it also implements simple shell
*/


class Evaluator{
private:
	Lexer*			lexer;
	Parser*			parser;

	TSharedASTNode	root;

	double empty(){
		std::cout << "nothing to do\n";
		return 0;
	}

	double evalNum(TSharedASTNode node){
		std::stringstream ss;

		ss << node->token->value;
		double x;
		ss >> x;

		return x;
	}

	double evalNegativeNum(TSharedASTNode node){
		return -privateEvaluate(node->leftNode);
	}

	double evalPlus(TSharedASTNode node){
		double left, right;
		left = privateEvaluate(node->leftNode);
		right = privateEvaluate(node->rightNode);
		return left + right;
	}

	double evalMinus(TSharedASTNode node){
		double left, right;
		left = privateEvaluate(node->leftNode);
		right = privateEvaluate(node->rightNode);
		return left - right;
	}

	double evalMul(TSharedASTNode node){
		double left, right, res;
		left = privateEvaluate(node->leftNode);
		right = privateEvaluate(node->rightNode);
		res = left * right;

		return left * right;
	}

	double evalDiv(TSharedASTNode node){
		double left, right;
		left = privateEvaluate(node->leftNode);
		right = privateEvaluate(node->rightNode);
		if (right == 0){
			throw "ARG 0!!!\n";
			return 0;
		}
		return left / right;
	}

	double evalMod(TSharedASTNode node){
		double left, right;
		left = privateEvaluate(node->leftNode);
		right = privateEvaluate(node->rightNode);
		if (right == 0){
			throw "ARG 0!!!\n";
			return 0;
		}
		return fmod(left, right);
	}

	double evalPow(TSharedASTNode node){
		double left, right;
		left = privateEvaluate(node->leftNode);
		right = privateEvaluate(node->rightNode);
		return pow(left, right);
	}

	double privateEvaluate(TSharedASTNode node){

		if (node->token == nullptr)
			throw "error at Evaluator\n";
		double x;
		switch (node->token->type){
		case EPS:
			x = empty();
			return x;
			break;
		case NUM:
			x = evalNum(node);
			break;
		case UMINUS:
			x = evalNegativeNum(node);
			break;
		case PLUS:
			x = evalPlus(node);
			break;
		case MINUS:
			x = evalMinus(node);
			break;
		case MUL:
			x = evalMul(node);
			break;
		case DIV:
			x = evalDiv(node);
			break;
		case MOD:
			x = evalMod(node);
			break;
		case POW:
			x = evalPow(node);
			break;
		default:
			throw "unknown symbol";
		}

		return x;
	}

public:
	Evaluator(){
		lexer = nullptr;
		parser = nullptr;

	}

	void setRoot(TSharedASTNode node){
		root = node;
	}
	void evaluate(){

		if (root == nullptr)return;
		double x = privateEvaluate(root);
		std::cout << x << std::endl;
	}

	void startParser(){

		std::string expression = "";
		try
		{
			for (;;){
				std::cout << "enter expression\n>>> ";
				std::cin >> expression;
				if (isalpha(expression[0]))
					if (expression == "quit")
						return;
					else if (expression == "clear"){
						system("cls");
						continue;
					}
					else
						std::cout << "unknown symbol\n";
					lexer = new Lexer();
					parser = new Parser();
					lexer->setExpressionToScan(expression);
					lexer->scanTokens();
					parser->setTokenList(lexer->getTokenList());
					parser->parse();
					setRoot(parser->getRoot());
					evaluate();
					delete parser;
					parser = nullptr;
					delete lexer;
					lexer = nullptr;
			}

		}
		catch (const char* ex)
		{
			std::cout << ex << std::endl;
		}

	}

	~Evaluator(){

	}
};

#endif