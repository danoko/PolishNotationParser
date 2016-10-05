#ifndef TOKEN_H
#define TOKEN_H
/*
struct Token is used by Lexer to tokenize strings
struct Token contains information about :
type : Type->data describing whether token is digit or operator of a given kind
value : String->data with the actual content of a scanned token
*/
enum Type{
	EPS,
	UMINUS,
	NUM,
	MINUS,
	PLUS,
	DIV,
	MOD,
	MUL,
	LPAREN,
	RPAREN,
	POW
};

struct Token{
	Type type;
	std::string value;
	Token(){
		type = EPS;
		value = "";
	}
	Token(Type t, const std::string& v){
		type = t;
		value = v;
	}

};
#endif