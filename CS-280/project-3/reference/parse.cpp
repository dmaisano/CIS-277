/*
 * parse.cpp
 */

#include "../parse.h"
#include "./parsetree.h"

namespace Parser {
bool pushed_back = false;
Token	pushed_token;

static Token GetNextToken(istream *in, int *line) {
	if( pushed_back ) {
		pushed_back = false;
		return pushed_token;
	}
	return getNextToken(in, line);
}

static void PushBackToken(Token& t) {
	if( pushed_back ) {
		abort();
	}
	pushed_back = true;
	pushed_token = t;
}

}

static int error_count = 0;

void
ParseError(int line, string msg)
{
	cout << line << ": "<< msg<<endl;
}

ParseTree *Prog(istream *in, int *line)
{
	ParseTree *sl = Slist(in, line);//because line is defined as a pointer already you don't pass it with &

	if( sl == 0 )
	{
		ParseError(*line, "No statements in program");
		return 0;
	}
	

	if( error_count )
		return 0;

	return sl;
}

// Slist is a Statement followed by a Statement List
ParseTree *Slist(istream *in, int *line) {
	ParseTree *s = Stmt(in, line);
	if( s == 0 )
		return 0;
 
        Token sc = Parser::GetNextToken(in, line);
	if( sc != SC ) {
		ParseError(*line, "Missing semicolon");
		delete s;
		return 0;
	}

	ParseTree *sl = Slist(in, line);
        if( sl == 0 )
            return s;
	return new StmtList(s, sl);
}

ParseTree *Stmt(istream *in, int *line) {
	Token my_verify_command = Parser::GetNextToken(in, line);
	ParseTree *my_command_selection;
	
	if(my_verify_command == VAR)
		my_command_selection = VarStmt(in, line);
	
	else if(my_verify_command == SET)
		my_command_selection = SetStmt(in, line);
	
	else if(my_verify_command == PRINT)
		my_command_selection = PrintStmt(in, line);
	
	else if(my_verify_command == REPEAT)
		my_command_selection = RepeatStmt(in, line);
	
	else
	{
		ParseError(*line, "Could not find a command");
		return 0;
	}
	if(my_command_selection == 0)
		return 0;
	
	return 0;
}

ParseTree *VarStmt(istream *in, int *line) {
	Token my_we_need_ident = Parser::GetNextToken(in, line);//This is a local my_we_need_ident
	if(my_we_need_ident == IDENT)
	{
		//Token get_next_expected = Parser::GetNextToken(in, line);//Don't need to get the next token because expression will take care of it, even validate if it is an expression
		ParseTree *my_get_next_expected = Expr(in, line);
		if(my_get_next_expected == 0)
			return 0;
		else
			return new VarDecl(line, my_get_next_expected);
		
	}
	else
	{
		ParseError(*line, "syntax error, expected IDENT");
		return 0;
	}
	return 0;
}

ParseTree *SetStmt(istream *in, int *line) {
	Token my_we_need_ident = Parser::GetNextToken(in, line);//This is a local my_we_need_ident
	if(my_we_need_ident == IDENT)
	{
		//Token get_next_expected = Parser::GetNextToken(in, line);//Don't need to get the next token because expression will take care of it, even validate if it is an expression
		ParseTree *my_get_next_expected = Expr(in, line);
		if(my_get_next_expected == 0)
			return 0;
		else
			return new Assignment(line, my_get_next_expected);
	}
	else
	{
		ParseError(*line, "Syntax error, expected IDENT");
		return 0;
	}
	
	return 0;
}
ParseTree *PrintStmt(istream *in, int *line) {
	int l = *line;

	ParseTree *ex = Expr(in, line);
	if( ex == 0 ) {
		ParseError(*line, "Missing expression after print");
		return 0;
	}

	return new Print(l, ex);//Do I need return 0 here or should I delete the return 0s from the other ones
}

ParseTree *RepeatStmt(istream *in, int *line) {
	ParseTree *my_get_next_expected_1st = Expr(in, line);
	if(my_get_next_expected == 0)
	{
		ParseError(*line, "Missing expression after repeat")
		return 0;
	}
	else
	{
		ParseTree *my_get_next_expected_2nd = Stmt(in, line);
		if(my_get_next_expected_2nd ==0)
		{
			ParseError(*line, "Missing statement ");
			return 0;
		}
		else
		return new (line, get_next_expected);
	}
	return 0;//should I keep this return 0? is it needed
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

		if( t == PLUS )
			t1 = new PlusExpr(t.GetLinenum(), t1, t2);
		else
			t1 = new MinusExpr(t.GetLinenum(), t1, t2);
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
