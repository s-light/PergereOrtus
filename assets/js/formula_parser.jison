// http://zaa.ch/jison/try/
// based on
// https://github.com/zaach/jison/blob/master/examples/calculator.jison
// https://github.com/xsanisty/jquery-calx/blob/master/library/parser-2.0.0-rev-4.jison
// https://stackoverflow.com/questions/26661565/adding-functions-to-bison-jison-calculator-language#26662228
// ---------------------------------------------------------------------------
// Describe Your Language
// ---------------------------------------------------------------------------

/*
    description:
    Parses end executes mathematical expressions.
    And tries to get a value from 'variable_names' with a call to 'getValue'
*/

/* lexical grammar */
%lex
%%

\s+                             /* skip whitespace */
[0-9]+("."[0-9]+)?\b            return 'NUMBER'
"*"                             return '*'
"/"                             return '/'
"-"                             return '-'
"+"                             return '+'
"^"                             return '^'
"!"                             return '!'
"%"                             return '%'
"("                             return '('
")"                             return ')'
";"                             return ';'
"PI"|"π"                        return 'PI'
"E"                             return 'E'
"toFixed("                      return 'TOFIXED'
^[a-zA-z]+([a-zA-z_0-9]+)?\b    return 'ELEMENTVALUE'
<<EOF>>                         return 'EOF'
.                               return 'INVALID'

/lex

/* operator associations and precedence */

%left '+' '-'
%left '*' '/'
%left '^'
%right '!'
%right '%'
%left UMINUS

%start expressions

%%/* language grammar */

expressions
    : e EOF
        { typeof console !== 'undefined' ? console.log($1) : print($1);
          return $1; }
    ;

e
    : e '+' e
        {$$ = $1+$3;}
    | e '-' e
        {$$ = $1-$3;}
    | e '*' e
        {$$ = $1*$3;}
    | e '/' e
        {$$ = $1/$3;}
    | e '^' e
        {$$ = Math.pow($1, $3);}
    | e '!'
        {{
          $$ = (function fact (n) { return n==0 ? 1 : fact(n-1) * n })($1);
        }}
    | e '%'
        {$$ = $1/100;}
    | '-' e %prec UMINUS
        {$$ = -$2;}
    | '(' e ')'
        {$$ = $2;}
    | NUMBER
        {$$ = Number(yytext);}
    | ELEMENTVALUE
        {
            typeof yy.getValue !== 'undefined' ? $$ = yy.getValue(yytext) : $$ = NaN;
        }
    | TOFIXED expseq ')'
        {
            // console.log('$1', $1);
            // console.log('$2', $2);
            // console.log('$3', $3);
            // console.log('$4', $4);
            $$ = $2[0].toFixed(
                $2[1] !== 'undefined' ? $2[1] : 0
            );
        }
    | E
        {$$ = Math.E;}
    | PI
        {$$ = Math.PI;}
    ;

expseq :
    e
        {
            $$ = [$1];
        }
    | expseq ';' e
        {
            $1.push($3);
            $$ = $1;
        }
;
