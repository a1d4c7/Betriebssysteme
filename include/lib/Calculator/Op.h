#ifndef Op_h
#define Op_h

#include "lib/Chain.h"

class Op: public Chain {
public:
    enum Type {
        OPERATOR,
        OPERAND
    };

    Op(int i) : operand(i), cOp(' '), type(OPERAND)
    {}

    /**
	 *  '+' fuer Plus '-' fuer Minus '*' fuer Mal '/' fuer Geteilt
	 */
    Op(char c) : operand(0), cOp(c), type(OPERAND)
    {}
    
    int getOperand() { return operand; }

    char getOperato() { return cOp; }	

    Type getType() { return type; }

private:
	int operand;    //operand
    char cOp;         //operator
    Type type;
};

#endif
