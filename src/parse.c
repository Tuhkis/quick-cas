#include "parse.h"

Frac eval(Expression exp) {
	if (exp.op == OP_ADD) return fracAdd(exp.a, exp.b);
	else if (exp.op == OP_SUB) return fracSub(exp.a, exp.b);
	else if (exp.op == OP_MUL) return fracMul(exp.a, exp.b);
	else if (exp.op == OP_DIV) return fracDiv(exp.a, exp.b);
	ASSERT(exp.op == OP_ADD);
	return (Frac) {0, 0};
}

