#ifndef ASTNODE_H
#define ASTNODE_H
#include <memory>
#include "Token.h"


struct ASTNode;
//my custom type for smart pointer of ASTNode
typedef std::shared_ptr<ASTNode> TSharedASTNode;

struct ASTNode{
	TSharedASTNode  leftNode;
	TSharedASTNode  rightNode;
	std::shared_ptr<Token>token;
	ASTNode(){
		leftNode = nullptr;
		rightNode = nullptr;
		token = nullptr;
	}
};


#endif