#ifndef PARSE_H
#define PARSE_H

#include "util.h"

typedef enum Operator {
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
} Operator;

typedef struct expression {
	Frac a, b;
	Operator op;
} Expression;

Frac eval(Expression exp);

#endif // PARSE_H
