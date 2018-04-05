/*
* Domenico Maisano
* CS280
* Spring 2018
* 
* parser.h
*/

#include <iostream>
#include "./lexer.h"
#include "./parsetree.h"
using namespace std;

// prototypes
extern ParseTree *Prog(istream *in, int *line);
extern ParseTree *Slist(istream *in, int *line);
extern ParseTree *Stmt(istream *in, int *line);
extern ParseTree *VarStmt(istream *in, int *line);
extern ParseTree *SetStmt(istream *in, int *line);
extern ParseTree *PrintStmt(istream *in, int *line);
extern ParseTree *RepeatStmt(istream *in, int *line);
extern ParseTree *Expr(istream *in, int *line);
extern ParseTree *Term(istream *in, int *line);
extern ParseTree *Factor(istream *in, int *line);
extern ParseTree *Primary(istream *in, int *line);

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

static void PushBackToken(Token& t) {
	if(pushed_back)
		abort();

	pushed_back = true;
	pushed_token = t;
}

}


static int error_count = 0;

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
  // statement
	ParseTree *s = Stmt(in, line);

	if(s == 0)
		return 0;
 
  Token nextToken = Parser::GetNextToken(in, line);

	if(nextToken != SC) {
		ParseError(*line, "Missing semicolon");
		delete s;
		return 0;
	}

  // now grab the statement list
	ParseTree *sl = Slist(in, line);
  
  if(sl == 0)
    return s;

  // and return it
	return new StmtList(s, sl);
}


ParseTree *Stmt(istream *in, int *line) {
  Token stmt = Parser::GetNextToken(in, line);

  if(stmt.GetTokenType() == VAR) {
    return 0;
  }
    
  if(stmt.GetTokenType() == SET) {
    return 0;
  }

  if(stmt.GetTokenType() == PRINT) {
    // process the expression inside the PRINT stmt
    ParseTree *expr = Expr(in, line);

    if(expr == 0) {
      ParseError(*line, "Expecting expression after print");
      return 0;
    }

    Token nextToken = Parser::GetNextToken(in, line);
    if(nextToken.GetTokenType() != SC) {
      ParseError(*line, "Missing semicolon");
      delete expr;
      return 0;
    }

    // return new PrintStmt();
  }

  if(stmt.GetTokenType() == REPEAT) {
    return 0;
  }
}


ParseTree *VarStmt(istream *in, int *line) {
  Token tok = Parser::GetNextToken(in, line);

  if(tok.GetTokenType() == IDENT) {

  }

	return 0;
}


ParseTree *SetStmt(istream *in, int *line) {
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
	ParseTree *t1 = Term(in, line);
	if( t1 == 0 ) {
		return 0;
	}

	while ( true ) {
		Token t = Parser::GetNextToken(in, line);

		if( t != PLUS && t != MINUS ) {
			Parser::PushBackToken(t);
			return t1;
		}

		ParseTree *t2 = Term(in, line);
		if( t2 == 0 ) {
			ParseError(*line, "Missing expression after operator");
			return 0;
		}

		// if( t == PLUS )
		// 	t1 = new PlusExpr(t.GetLinenum(), t1, t2);
		// else
		// 	t1 = new MinusExpr(t.GetLinenum(), t1, t2);
	}
}


ParseTree *Term(istream *in, int *line) {
	return 0;
}


ParseTree *Factor(istream *in, int *line) {
	return 0;
}


ParseTree *Primary(istream *in, int *line) {
	return 0;
}

