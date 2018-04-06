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
    ParseTree *exp = Expr(in, line);

    if(exp == 0) {
      ParseError(*line, "Expecting expression after print");
      return 0;
    }

    Token nextToken = Parser::GetNextToken(in, line);
    if(nextToken.GetTokenType() != SC) {
      ParseError(*line, "Missing semicolon");
      delete exp;
      return 0;
    }

    // return new PrintStmt();
  }

  if(stmt.GetTokenType() == REPEAT) {
    return 0;
  }
}


ParseTree *VarStmt(istream *in, int *line) {
  Token identToken = Parser::GetNextToken(in, line);

  // error handling
  if(identToken.GetTokenType() != IDENT) {
      ParseError(*line, "IDENT expected in var, got " + identToken.GetLexeme());
      return 0;
  }

  // get the expression
  // ParseTree *exp = Expr(in, *line);

  // if(exp == 0)
  //   return 0;

  // if it is a valid var statement
  // return a VarDecl with the IDENT and the expression
	// return new VarDecl(*line, new Ident(identToken), exp)
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


// ParseTree *Primary(istream *in, int *line) {
//   Token tok = Parser::GetNextToken(in, line);

//   if(tok.GetTokenType() == IDENT)
//     return new IDENT(tok, *line);

//   else if(tok.GetTokenType() == ICONST)
//     return new IConst(tok, *line);

//   else if(tok.GetTokenType() == SCONST)
//     return new SConst(tok, *line);

//   else if(tok.GetTokenType() == LPAREN) {
//     ParseTree *exp = Expr(in, *line);

//     if(exp == 0)
//       return 0;

//     Token nextTok = Parser::GetNextToken(in, line);
//     if(nextTok.GetTokenType() != RPAREN) {
//       ParseError("expected right parens");
//       return 0;
//     }
//   }

//   return 0;
// }

ParseTree *Expr(istream *in, int *line) {
  ParseTree *exp = Term(in, line);
  
  if(exp == 0)
    return 0;
  
  while(true) {
    Token tok = Parser::GetNextToken(in, line);
    auto tt = tok.GetTokenType();
    
    if(tt != PLUS && tt != MINUS) {
      Parser::PushBackToken(tok);
      return exp;
    }
    
    ParseTree *exp2 = Term(in, line);

    if(exp2 == 0) {
      ParseError(*line, "Missing expression after operator");
      return 0;
    }

    if(tt == PLUS)
      return new PlusExpr(*line, exp, exp2);
    
    if(tt == MINUS)
      return new MinusExpr(*line, exp, exp2);
  }
  
  return exp;
}

ParseTree *Term(istream *in, int *line) {
  ParseTree *primary = Primary(in, line);
  
  if(primary == 0)
    return 0;
  
  while(true) {
    Token tok = Parser::GetNextToken(in, line);
    auto tt = tok.GetTokenType();
    
    if(tt != STAR) {
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

ParseTree *Primary(istream *in, int *line) {
  Token tok = Parser::GetNextToken(in, line);
  auto tt = tok.GetTokenType();
  
  if(tt == IDENT)
      return new Ident(tok);

  else if(tt == ICONST)
      return new IConst(tok);

  else if(tt == SCONST) {
      Parser::PushBackToken(tok);
      // return SConst(in); ???
  }

  else if(tt == LPAREN) {
    ParseTree *exp = Expr(in, line);

    if(exp == 0)
      return 0;

    auto nextTok = Parser::GetNextToken(in, line);
    if(nextTok.GetTokenType() != RPAREN) {
      ParseError(*line, "expected right parens");
      return 0;
    }
    
    return exp;
  }
  
  return 0;
}

#endif
