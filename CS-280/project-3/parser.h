/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* parser.h
* (modified parse.cpp)
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

// traversals
ParseTree *postTraversalStats(ParseTree *tree, bool trace);

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

// 'pushback' the token that will be needed
// pretty much like in->putback()
static void PushBackToken(Token& tok) {
	if(pushed_back)
		abort();

	pushed_back = true;
	pushed_token = tok;
}

static void Parse(istream *in, bool traceMode) {
  int line = 1;

  ParseTree *prog = Prog(in, &line);

  postTraversal(prog, traceMode);
}

}

ParseTree *postTraversalStats(ParseTree *node, bool trace) {
  auto left = node->GetLeftChild();
  auto right = node->GetRightChild();

  // node that has left && right child
  if(&left != NULL && &right != NULL && trace)
    cout << "N";

  // node that has a left child
  else if(&left != NULL) {
    cout << "l";

    auto new_left  = left.GetLeftChild();
    auto new_right = left.GetRightChild();

    node = new StmtList(&new_left, &new_right);

    cout << "L";
    postTraversal(node, trace);
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

	if(error_count)
		return 0;

	return sl;
}


// Slist is a Statement followed by a Statement List
ParseTree *Slist(istream *in, int *line) {
  // grab the statement
	ParseTree *s = Stmt(in, line);

	if(s == 0)
    return 0;
 
  Token tok = Parser::GetNextToken(in, line);

	if(tok != SC) {
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

  if(stmt == IDENT) {
    ParseError(*line, "Cannot use a variable, before declaring it");
    return 0;
  }

  if(stmt == DONE)
    return 0;

  if(stmt == VAR)
    return VarStmt(in, line);
    
  if(stmt == SET)
    return SetStmt(in, line);

  if(stmt == PRINT)
    return PrintStmt(in, line);

  if(stmt == REPEAT)
    return RepeatStmt(in, line);

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
  if(exp == 0) {
    ParseError(*line, "Expected expression after identifier");
    return 0;
  }

  return new VarDecl(*line, new Ident(identToken), exp);
}


ParseTree *SetStmt(istream *in, int *line) {
  Token tok = Parser::GetNextToken(in, line);

  if(tok != IDENT) {
    ParseError(*line, "Expected identifier in set statement");
    return 0;
  }

  // found an IDENT, continue
  ParseTree *exp = Expr(in, line);
  if(exp == 0) {
    ParseError(*line, "Expected expression after identifier");
    return 0;
  }

  return new Assignment(*line, new Ident(tok), exp);
}


ParseTree *PrintStmt(istream *in, int *line) {
	ParseTree *exp = Expr(in, line);

	if(exp == 0) {
		ParseError(*line, "Missing expression after print");
		return 0;
	}

	return new Print(*line, exp);
}


ParseTree *RepeatStmt(istream *in, int *line) {
  ParseTree *exp = Expr(in, line);

  if(exp == 0)
    return 0;

  ParseTree *s = Stmt(in, line);

  if(s == 0) {
    ParseError(*line, "Expected statement");
    return 0;
  }

  return new Repeat(*line, exp, s);
}

ParseTree *Expr(istream *in, int *line) {
  ParseTree *term = Term(in, line);
  
  if(term == 0)
    return 0;
  
  while(true) {
    Token tok = Parser::GetNextToken(in, line);
    
    if(tok != PLUS && tok != MINUS) {
      Parser::PushBackToken(tok);
      // cout << "Returning EXPR" << endl;
      return term;
    }
    
    // we found a PLUS or MINUS token
    ParseTree *term2 = Term(in, line);

    if(term2 == 0) {
      ParseError(*line, "Missing expression after operator");
      return 0;
    }

    if(tok == PLUS) {
      // cout << "Returning PLUS EXPR" << endl;
      return new PlusExpr(*line, term, term2);
    }
    
    if(tok == MINUS) {
      // cout << "Returning MINUS EXPR" << endl;
      return new MinusExpr(*line, term, term2);
    }
  }
  
  return term;
}

ParseTree *Term(istream *in, int *line) {
  ParseTree *factor = Factor(in, line);
  
  if(factor == 0)
    return 0;
  
  while(true) {
    Token tok = Parser::GetNextToken(in, line);
    
    if(tok != STAR) {
      Parser::PushBackToken(tok);
      // cout << "Returning TERM" << endl;
      return factor;
    }
    
    ParseTree *factor2 = Factor(in, line);
    if(factor2 == 0) {
      ParseError(*line, "missing factor after times");
      return 0;
    }
    
    // cout << "Returning TIMES EXPR" << endl;
    return new TimesExpr(*line, factor, factor2);
  }
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
      // cout << "Returning FACTOR" << endl;
      return prim;
    }

    // a bracket was found, so continue
    ParseTree *expr1 = Expr(in, line);
    if(expr1 == 0) {
      ParseError(*line, "Expected expression after bracket");
      return 0;
    }

    tok = Parser::GetNextToken(in, line);
    if(tok != COLON) {
      ParseError(*line, "Expected colon in slice");
      return 0;
    }

    ParseTree *expr2 = Expr(in, line);
    if(expr2 == 0) {
      ParseError(*line, "Expected expression after colon in 'slice'");
      return 0;
    }

    tok = Parser::GetNextToken(in, line);
    if(tok != RSQ) {
      ParseError(*line, "Expected closing bracket");
      return 0;
    }

    // left node is the original primary
    // rigt node is the 'slice expr'
    // cout << "Returning SLICE EXPR" << endl;
    return new SliceExpr(*line, prim, new SliceOperand(*line, expr1, expr2));
  }
}

ParseTree *Primary(istream *in, int *line) {
  Token tok = Parser::GetNextToken(in, line);
  
  if(tok == IDENT) {
    tok = Parser::GetNextToken(in, line);

    // cout << "Returning IDENT" << endl;
    return new Ident(tok);
  }

  else if(tok == ICONST) {
    // cout << "Returning ICONST" << endl;
    return new IConst(tok);
  }

  else if(tok == SCONST) {
    // cout << "Returning SCONST" << endl;
    return new SConst(tok);
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
    
    // cout << "Returning PARENS EXPR" << endl;
    return exp;
  }

  return 0;
}

#endif
