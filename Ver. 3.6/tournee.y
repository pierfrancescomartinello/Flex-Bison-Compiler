%{
#include <stdio.h>
#include "symb_table.h"
int yylex();
void yyerror(char const *);
%}
%union {
    int int_t;
    char* string_t;
}
%define parse.error verbose

%token <string_t>   NOMEC NOMEL NOMET
%token <int_t>      NUM
%token              SEP SEP1 SEP2 DIV OP OPEN CLOSED PERC VALUE ARR DATEDIV 
                    NOMEC_PREF NOMEL_PREF DATE_PREF BIGL_PREF PREZ_PREF

%start Input
%%
Input           :   First SEP1 Second SEP2 Third 
                ;
First           :   /*epsilon*/ 
                |   Tappa SEP First
                ;

Tappa           :   City Date Dettagli
                ;
City            :   NOMEC_PREF NOMEC DIV NOMEL_PREF NOMEL DIV    {setTappa($2, $5);}
                ;
Date            :   DATE_PREF NUM DATEDIV NUM DATEDIV NUM DIV
                ;
Dettagli        :   /*epsilon*/                                  {detBind();} 
                |   DetLeft DetRight Dettagli
                ;
DetLeft         :   BIGL_PREF NOMET OP                           {detInit($2);}
                ;
DetRight        :   OPEN ElencoCateg CLOSED DIV
                ;
ElencoCateg     :   Categoria CicleCateg
                ;
CicleCateg      :   /*epsilon*/                                  {catBind();} 
                |   DIV ElencoCateg 
                ;
Categoria       :   NOMET OP NUM                                 {catInit($1, $3);} 
                ;
Second          :   /*epsilon*/
                |   Prezzo Second
                ;
Prezzo          :   PREZ_PREF NOMET ARR NUM VALUE                {setPrezzo($2, $4);} 
                ;
                
Third           :   /*epsilon*/
                |   NOMEL OP NUM PERC Third                      {setSconto($1, $3);}
                ;


%%
int main(){
    freeAll();
    if(yyparse()==0){
        priceCalc();
        price_output();
        freeAll();
    }
    return 0;
}

void yyerror(char const *s) {
    fprintf(stderr, "%s\n", s);
}