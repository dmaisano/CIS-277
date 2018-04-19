/*
*  parser.h (modified parse.cpp)
*
*  Created on: Mar 8, 2018
*  Author: gerardryan
*/

#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include "./parsetree.h"
using namespace std;

// prototypes
ParseTree *Prog(istream *in, int *line);
ParseTree *Slist(istream *in, int *line);
ParseTree *Stmt(istream *in, int *line);
ParseTree *VarStmt(istream *in, int *line);
ParseTree *SetStmt(istream *in, int *line);
ParseTree *PrintStmt(istream *in, int *line);
ParseTree *RepeatStmt(istream *in, int *line);
ParseTree *Expr(istream *in, int *line);
ParseTree *Term(istream *in, int *line);
ParseTree *Factor(istream *in, int *line);
ParseTree *Primary(istream *in, int *line);

// parser wrapper
namespace Parser {
bool pushed_back = false;
Token	pushed_token;

static Token GetNextToken(istream *in, int *line) {
	if(pushed_back) {
		pushed_back = false;
		return pushed_token;
	}
	return getNextToken(in, line);
}

static void PushBackToken(Token& tok) {
	if(pushed_back) {
		abort();
	}
	pushed_back = true;
	pushed_token = tok;
}

static ParseTree *Parse(istream *in, bool trace) {
  int linenum = 0;

  ParseTree *prog = Prog(in, &linenum);

  if(!prog)
    return 0;

  return prog;
}

}

// global error counter
static int error_count = 0;

// error handler
void ParseError(int line, string msg) {
	++error_count;
	cout << line << ": " << msg << endl;
}

// parse tree that contains the entire program
ParseTree *Prog(istream *in, int *line) {
	ParseTree *sl = Slist(in, line);

	if(!sl)
		ParseError(*line, "No statements in program");

	if(error_count)
		return 0;

	return sl;
}

// Slist is a Statement followed by a Statement List
ParseTree *Slist(istream *in, int *line) {
	ParseTree *s = Stmt(in, line);
	if(!s)
		return 0;
 
	if(Parser::GetNextToken(in, line) != SC) {
		ParseError(*line, "Missing semicolon");
		delete s;
		return 0;
	}

	ParseTree *sl = Slist(in, line);
  if(!sl)
    return s;

	return new StmtList(s, sl);
}

// statement node
ParseTree *Stmt(istream *in, int *line) {
	ParseTree *s;

	Token tok = Parser::GetNextToken(in, line);
	switch(tok.GetTokenType()) {
	case VAR:
		s = VarStmt(in, line);
		break;

	case SET:
		s = SetStmt(in,line);
		break;

	case PRINT:
		s = PrintStmt(in, line);
		break;

	case REPEAT:
		s = RepeatStmt(in, line);
		break;

	case DONE:
		return 0;

	default:
		ParseError(*line, "Invalid statement");
		return 0;
	}

	return s;
}

// variable node
ParseTree *VarStmt(istream *in, int *line) {
	Token tok = Parser::GetNextToken(in, line);

	if(tok != IDENT) {
		ParseError(*line, "Missing identifier after var");
		return 0;
	}

	ParseTree *expr = Expr(in, line);
	if(!expr) {
		ParseError(*line, "Missing expression after identifier");
		return 0;
	}

	return new VarDecl(tok, expr);
}

// SET statement node
ParseTree *SetStmt(istream *in, int *line) {
	Token tok = Parser::GetNextToken(in, line);

	if(tok != IDENT) {
		ParseError(*line, "Missing identifier after set");
		return 0;
	}

	ParseTree *expr = Expr(in, line);
	if(!expr) {
		ParseError(*line, "Missing expression after identifier");
		return 0;
	}

	return new Assignment(tok, expr);
}

// PRINT statement node
ParseTree *PrintStmt(istream *in, int *line) {
	ParseTree *expr = Expr(in, line);

	if(!expr) {
		ParseError(*line, "Missing expression after print");
		return 0;
	}

	return new Print(*line, expr);
}

ParseTree *RepeatStmt(istream *in, int *line) {
 	ParseTree *expr = Expr(in, line);

	if(!expr) {
		ParseError(*line, "Missing expression after repeat");
		return 0;
	}

	ParseTree *stmt = Stmt(in, line);
	if(!stmt) {
		ParseError(*line, "Missing statement for repeat");
		return 0;
	}
	return new Repeat(*line, expr, stmt);
}

ParseTree *Expr(istream *in, int *line) {
	ParseTree *t1 = Term(in, line);

	if(!t1)
		return 0;

	while(true) {
		Token tok = Parser::GetNextToken(in, line);

		if(tok != PLUS && tok != MINUS) {
			Parser::PushBackToken(tok);
			return t1;
		}

		ParseTree *t2 = Term(in, line);
		if(!t2) {
			ParseError(*line, "Missing expression after operator");
			return 0;
		}

		if(tok == PLUS)
			t1 = new PlusExpr(tok.GetLinenum(), t1, t2);
		else if(tok == MINUS)
			t1 = new MinusExpr(tok.GetLinenum(), t1, t2);
	}
}

ParseTree *Term(istream *in, int *line) {
	ParseTree *t1 = Factor(in, line);

	if(!t1)
		return 0;

	while(true) {
		Token tok = Parser::GetNextToken(in, line);

		if(tok != STAR) {
			Parser::PushBackToken(tok);
			return t1;
		}

		ParseTree *t2 = Factor(in, line);
		if(!t2) {
			ParseError(*line, "Missing expression after operator");
			return 0;
		}

		t1 = new TimesExpr(tok.GetLinenum(), t1, t2);
	}
}

ParseTree *Factor(istream *in, int *line) {
	ParseTree *primary = Primary(in, line);

	while(true) {
		Token tok = Parser::GetNextToken(in, line);

		if(tok != LSQ) {
			Parser::PushBackToken(tok);
			return primary;
		}

		ParseTree *expr1 = Expr(in, line);
		if(!expr1) {
			ParseError(*line, "Missing expression after [");
			return 0;
		}

		if(Parser::GetNextToken(in,line) != COLON) {
			ParseError(*line, "Missing colon after expression");
			return 0;
		}

		ParseTree *expr2 = Expr(in, line);
		if(!expr2) {
			ParseError(*line, "Missing expression after :");
			return 0;
		}

		if(Parser::GetNextToken(in,line) != RSQ) {
			ParseError(*line, "Missing ] after expression");
			return 0;
		}

		primary = new SliceExpr(tok.GetLinenum(), primary, new SliceOperand(*line,expr1,expr2));
	}
}

ParseTree *Primary(istream *in, int *line) {
	Token tok = Parser::GetNextToken(in, line);

	if(tok == IDENT)
		return new Ident(tok);
	else if(tok == ICONST )
		return new IConst(tok);
	else if( tok == SCONST)
		return new SConst(tok);
	else if( tok == LPAREN ) {
		ParseTree *expr = Expr(in, line);
		if(!expr) {
			ParseError(*line, "Missing expression after repeat");
			return 0;
		}
		if(Parser::GetNextToken(in, line) == RPAREN)
			return expr;

		ParseError(*line, "Missing ) after expression");
		return 0;
	}

	ParseError(*line, "Primary expected");
	return 0;
}

#endif
