/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* parser.h
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

static int error_count = 0;

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

// return the token that is not needed
// pretty much like in->putback()
static void PushBackToken(Token& tok) {
	if(pushed_back)
		abort();

	pushed_back = true;
	pushed_token = tok;
}

static void Parse(istream *in, bool traceMode) {
  int line = 0;

  ParseTree *prog = Prog(in, &line);

  // not a valid program
  if(prog == 0 || error_count != 0)
    exit(0);
}

}

// error handler
void ParseError(int line, string msg) {
  cout << line << ": " << msg << endl;
  ++error_count;
}


ParseTree *Prog(istream *in, int *line) {
  // the program is essentially a statement list
	ParseTree *sl = Slist(in, line);

	if(sl == 0)
		ParseError(*line, "No statements in program");

  // stop if we find any errors
	if(error_count)
		return 0;

  // if not return the statement list
	return sl;
}


// Slist is a Statement followed by a Statement List
ParseTree *Slist(istream *in, int *line) {
  // grab the statement
	ParseTree *s = Stmt(in, line);

	if(s == 0)
		return 0;
 
  Token nextToken = Parser::GetNextToken(in, line);

	if(nextToken != SC) {
		ParseError(*line, "Missing semicolon");
		delete s;
		return 0;
	}

  // now grab another statement list, if there is one
	ParseTree *sl = Slist(in, line);
  
  if(sl == 0)
    return s;

  // and return it
	return new StmtList(s, sl);
}


ParseTree *Stmt(istream *in, int *line) {
  Token stmt = Parser::GetNextToken(in, line);

  if(stmt == ERR) {
    ParseError(*line, "Invalid token");
    return 0;
  }

  if(stmt == DONE)
    return 0;

  if(stmt == VAR)
    return VarStmt(in, line);
    
  if(stmt == SET)
    return SetStmt(in, line);

  if(stmt == PRINT) {
    // process the expression inside the PRINT stmt
    ParseTree *exp = Expr(in, line);

    if(exp == 0) {
      ParseError(*line, "Expecting expression after print");
      return 0;
    }

    Token nextToken = Parser::GetNextToken(in, line);
    if(nextToken != SC) {
      ParseError(*line, "Missing semicolon");
      delete exp;
      return 0;
    }
  }

  if(stmt == REPEAT) {
    return 0;
  }

  return 0;
}


ParseTree *VarStmt(istream *in, int *line) {
  Token identToken = Parser::GetNextToken(in, line);

  if(identToken != IDENT) {
    ParseError(*line, "Expected identifier");
    return 0;
  }

  // get the expression
  ParseTree *exp = Expr(in, line);
  if(exp == 0)
    return 0;

  return new VarDecl(*line, new Ident(identToken), exp);
}


ParseTree *SetStmt(istream *in, int *line) {
  Token tok = Parser::GetNextToken(in, line);

  if(tok == IDENT) {
    ParseTree *exp = Expr(in, line);

    if(exp == 0)
      return 0;

    return new Assignment(*line, new Ident(tok), exp);
  }

  ParseError(*line, "Syntax error, expected IDENT");
  return 0;
}


ParseTree *PrintStmt(istream *in, int *line) {
	int l = *line;

	ParseTree *ex = Expr(in, line);
	if( ex == 0 ) {
		ParseError(*line, "Missing expression after print");
		return 0;
	}

	return new Print(l, ex);
}


ParseTree *RepeatStmt(istream *in, int *line) {
	return 0;
}

ParseTree *Expr(istream *in, int *line) {
  ParseTree *term = Term(in, line);
  
  if(term == 0)
    return 0;
  
  while(true) {
    Token tok = Parser::GetNextToken(in, line);
    
    if(tok != PLUS && tok != MINUS) {
      Parser::PushBackToken(tok);
      return term;
    }
    
    ParseTree *term2 = Term(in, line);

    if(term2 == 0) {
      ParseError(*line, "Missing expression after operator");
      return 0;
    }

    if(tok == PLUS)
      return new PlusExpr(*line, term, term2);
    
    if(tok == MINUS)
      return new MinusExpr(*line, term, term2);
  }
  
  return term;
}

ParseTree *Term(istream *in, int *line) {
  ParseTree *primary = Primary(in, line);
  
  if(primary == 0)
    return 0;
  
  while(true) {
    Token tok = Parser::GetNextToken(in, line);
    
    if(tok != STAR) {
      Parser::PushBackToken(tok);
      // break; or return 0; ??
      // assuming return 0;
      return 0;
    }
    
    ParseTree *primary2 = Primary(in, line);
    if(primary2 == 0) {
      ParseError(*line, "missing operand after *");
      return 0;
    }
    
    return new TimesExpr(*line, primary, primary2);
  }
  
  return 0;
}

ParseTree *Factor(istream *in, int *line) {
  ParseTree *prim = Primary(in, line);

  if(prim == 0) {
    ParseError(*line, "Expected primary");
    return 0;
  }

  while(true) {
    Token tok = Parser::GetNextToken(in, line);

    if(tok != LSQ) {
      Parser::PushBackToken(tok);
      return prim;
    }

    // a bracket was found, so continue
    ParseTree *prim2 = Expr(in, line);
    if(prim2 == 0) {
      ParseError(*line, "Expected primary after operator");
    }

    tok = Parser::GetNextToken(in, line);
    if(tok != COLON) {
      ParseError(*line, "Missing semicolon");
      return 0;
    }

    ParseTree *prim3 = Expr(in, line);
    if(prim3 == 0) {
      ParseError(*line, "Expected Primary after operator");
      return 0;
    }

    tok = Parser::GetNextToken(in, line);
    if(tok != RSQ) {
      ParseError(*line, "Expected closing bracket");
      return 0;
    }

    prim = new SliceExpr(*line, prim, new SliceOperand(*line, prim2, prim3));
  }
}

ParseTree *Primary(istream *in, int *line) {
  Token tok = Parser::GetNextToken(in, line);
  
  if(tok == IDENT)
      return new Ident(tok);

  else if(tok == ICONST)
      return new IConst(tok);

  else if(tok == SCONST) {
      Parser::PushBackToken(tok);
      return new SConst(tok); // ???
  }

  else if(tok == LPAREN) {
    ParseTree *exp = Expr(in, line);

    if(exp == 0)
      return 0;

    tok = Parser::GetNextToken(in, line);
    if(tok != RPAREN) {
      ParseError(*line, "Expected right parens");
      return 0;
    }
    
    return exp;
  }
  
  return 0;
}

#endif
