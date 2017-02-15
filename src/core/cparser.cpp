#include "cparser.h"

/**
 * @brief Adds a character to the string value
 * @param c
 */
void CParser::PushString(char c)
{
    yylval.s += c;
}
//------------------------------------------------------------------------
/**
 * @brief Mapping token to the corresponding index
 * @param str
 * @param index
 */
void CParser::Load_tokenentry(string str,int index)
{
    IP_Token_table[str]=index;
    IP_revToken_table[index]=str;
}
/**
 * @brief Init token table
 */
void CParser::IP_init_token_table()
{
    Load_tokenentry("STRING1",3);
    Load_tokenentry("IDENTIFIER",4);
    Load_tokenentry("INTEGER1",5);
//    int ii=TOKENSTART;                //TOKENSTART = 300
//    Load_tokenentry("AND",ii++);      //301
//    Load_tokenentry("OR",ii++);       //302
//    Load_tokenentry("Begin",ii++);    //303
//    Load_tokenentry("End",ii++);      //304
}

//------------------------------------------------------------------------
/**
 * @brief CParser::pr_tokentable
 */
//void CParser::pr_tokentable()
//{
//    typedef map<string,int>::const_iterator CI;
//    const char* buf;
//    printf( "Symbol Table ---------------------------------------------\n");
//    for(CI p=IP_Token_table.begin(); p!=IP_Token_table.end(); ++p){
//        buf = p->first.c_str();
//        printf(" key:%s val:%d\n ", buf, p->second);
//    }
//}
//------------------------------------------------------------------------
/**
 * @brief Return the class of word and print the result
 *
 */
int CParser::yyparse()
{
    int tok;
    if(prflag)fprintf(IP_List,"%5d ",(int)IP_LineNumber);
    /*
    * Go parse things!
    */
    while ((tok=yylex())!=0){
        printf("%d ",tok);
        if(tok==STRING1){
            printf("%s %s ",IP_revToken_table[tok].c_str(),yylval.s.c_str());
            return STRING1;
        }
        else
            if(tok==INTEGER1){
                printf("%s %d ",IP_revToken_table[tok].c_str(),yylval.i);
                return INTEGER1;
            }
            else
                if(tok==IDENTIFIER){
                    printf("%s %s ",IP_revToken_table[tok].c_str(),yylval.s.c_str());
                    return IDENTIFIER;
                }
                else
                    if(tok>=TOKENSTART){
                        printf("%s ",IP_revToken_table[tok].c_str());
                        return TOKENSTART;
                    }
                    else
                        printf("%c ",tok);
                        return 1;               //Unbekanntes Zeichen
        if(!prflag)printf("\n");
    }
    return 0;
}

//------------------------------------------------------------------------
/*
* Parse File:
*
*/
/**
 * @brief Init parser
 * @param inp   File input
 * @param err   Error output
 * @param lst   output
 */
void CParser::InitParse(FILE *inp,FILE *err,FILE *lst)
{
    /*
    * Set up the file state to something useful.
    */
    IP_Input = inp;
    IP_Error = err;
    IP_List = lst;
    IP_LineNumber = 1;
    ugetflag=0;
    /*
    * Define both the enabled token and keyword strings.
    */
    IP_init_token_table();
}
//------------------------------------------------------------------------
/**
 * @brief Return the corresponding index for the token
 * @param tok
 * @return
 */
int CParser::IP_MatchToken(string &tok)
{
    int retval;
    if( IP_Token_table.find(tok) != IP_Token_table.end()){
        retval = (IP_Token_table[tok]);
    }else{
        retval = (0);
    }
    return retval;
}

//------------------------------------------------------------------------
/*
* yylex:
*
*/
/**
 * @brief Copy from script
 * @return
 */
int CParser::yylex()
{
    //Locals
    int c;
    lexstate s;
    /*
    * Keep on sucking up characters until we find something which
    * explicitly forces us out of this function.
    */
    for (s = L_START,yytext = ""; 1;){
        c = Getc(IP_Input);             //Hole Zeichen aus Datei
        yytext = yytext + (char)c;      //Zeichen an Text anfuegen
//        if(!ugetflag) {
//            if(c != EOF)if(prflag)fprintf(IP_List,"%c",c);
//        }else ugetflag = 0;

        switch (s){
        //Starting state, look for something resembling a token.
            case L_START:
                if (isdigit(c)){
                s = L_INT;
                }else if (isalpha(c) || c == '\\' ){
                    s = L_IDENT;
                }else if (isspace(c)){
                    if (c == '\n'){
                        IP_LineNumber += 1;
                        if(prflag)
                            fprintf(IP_List,"%5d ",(int)IP_LineNumber);
                    }
                    yytext = "";
                }else if (c == '/'){
                    yytext = "";
                    s = L_COMMENT;
                }else if (c == '"'){
                    s = L_STRING;
                }else if (c == EOF){
                    return ('\0');
                }else{                  //Nicht zugeordnet
                    return (c);
                }
            break;

            case L_COMMENT:
                if (c == '/')
                    s = L_LINE_COMMENT;
                else if(c == '*')
                    s = L_TEXT_COMMENT;
                else{
                    Ungetc(c);
                    return('/'); /* its the division operator not a comment */
                }
                break;

            case L_LINE_COMMENT:
                if ( c == '\n'){
                    s = L_START;
                    Ungetc(c);
                }
                yytext = "";
            break;

            case L_TEXT_COMMENT:
                if ( c == '\n'){
                    IP_LineNumber += 1;
                }else if (c == '*')
                    s = L_END_TEXT_COMMENT;
                    yytext = "";
            break;

            case L_END_TEXT_COMMENT:
                if (c == '/'){
                    s = L_START;
                }else{
                    s = L_TEXT_COMMENT;
                }
                yytext = "";
            break;

        /*
        * Suck up the integer digits.
        */
            case L_INT:
                if (isdigit(c)){
                    break;
                }else {
                    Ungetc(c);
                    yylval.s = yytext.substr(0,yytext.size()-1);
                    yylval.i = atoi(yylval.s.c_str());
                    return (INTEGER1);
                }
            break;

        /*
        * Grab an identifier, see if the current context enables
        * it with a specific token value.
        */
            case L_IDENT:
                if (isalpha(c) || isdigit(c) || c == '_')
                    break;
                Ungetc(c);
                yytext = yytext.substr(0,yytext.size()-1);
                yylval.s = yytext;
                if (c = IP_MatchToken(yytext)){                 //Abfrage ob yytext definiertes token ist
                    return (c);
                }else{
                    return (IDENTIFIER);
                }

        /*
        * Suck up string characters but once resolved they should
        * be deposited in the string bucket because they can be
        * arbitrarily long.
        */
            case L_STRING2:
                s = L_STRING;
                if(c == '"'){
                    PushString((char)c);
                }else{
                    if(c == '\\'){
                        PushString((char)c);
                    }else{
                        PushString((char)'\\');
                        PushString((char)c);
                    }
                }
             break;

            case L_STRING:
                if (c == '\n')
                    IP_LineNumber += 1;
                else if (c == '\r');
                else if (c == '"' || c == EOF){
                    return (STRING1);
                } else if(c=='\\'){
                    s = L_STRING2;
                }else
                    PushString((char)c);
            break;
            default: printf("***Fatal Error*** Wrong case label in yylex\n");
            }
        }
}


