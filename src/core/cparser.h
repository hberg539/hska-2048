#ifndef CPARSER_H
#define CPARSER_H

#pragma warning(disable:4786)
#include <string>
#include <map>
using namespace std;
#define Getc(s) getc(s)
#define Ungetc(c) {ungetc(c,IP_Input); ugetflag=1;}
/*
* Lexical analyzer states.
*/
enum lexstate{L_START,L_INT,L_IDENT,L_STRING,L_STRING2,
L_COMMENT,L_TEXT_COMMENT,L_LINE_COMMENT,L_END_TEXT_COMMENT};
const int STRING1=3;
const int IDENTIFIER=4;
const int INTEGER1=5;
const int TOKENSTART=300;

class CParser
{
public:
    string yytext; //input buffer
    struct tyylval{ //value return structure
    string s; //string
    int i; //integer
    }yylval;
    FILE *IP_Input; //Input File
    FILE *IP_Error; //Error Output
    FILE *IP_List; //List Output
    int IP_LineNumber; //Line counter
    int ugetflag; //checks ungets
    int prflag; //controls printing
    map<string,int> IP_Token_table; //Tokendefinitions
    map<int,string> IP_revToken_table; //reverse Tokendefinitions
    int yylex(); //lexical analyser
    void yyerror(char *ers); //error reporter
    int IP_MatchToken(string &tok); //checks the token
    void InitParse(FILE *inp,FILE *err,FILE *lst); //Sets the File pointers
    int yyparse(); //parser
    //void pr_tokentable(); //test output for tokens
    void IP_init_token_table(); //loads the tokens
    void Load_tokenentry(string str,int index); //load one token
    void PushString(char c); //Used for dtring assembly
    CParser(){IP_LineNumber = 1;ugetflag=0;prflag=0;}; //Constructor
};

#endif // CPARSER_H
