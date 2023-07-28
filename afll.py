import ply.lex as lex
import ply.yacc as yacc

tokens = ['if', 'else', 'variable', 'statements', 'next', 'normalopenbracket',
          'normalclosebracket', 'curlyopenbracket', 'curlyclosebracket', 'semicolon','and','or','condition']

t_ignore = ' \t';
t_next = ' \\n';
t_curlyopenbracket = r'\{';
t_curlyclosebracket = r'\}';
t_normalopenbracket = r'\(';
t_normalclosebracket = r'\)';
t_semicolon = r';';
t_if = r'if';
t_else = r'else';
t_variable = r'variable';
t_statements = r'statements';
t_and=r'&&';
t_or=r'\|\|';
t_condition=r'condition';


def p_if(p):
    """assign : if expr"""
    


def p_expr(p):
    '''expr : conditionsub next statementsub
            | conditionsub next statementsub elsesub
            | conditionsub statementsub
            | conditionsub statementsub elsesub
            | conditionsub next statementsub next elsesub
            | conditionsub next statementsub next elseifsub'''



# def p_expp(p):
#     '''expp : conditionsub next statementsub
#             | conditionsub next statementsub elsesub
#             | conditionsub statementsub
#             | conditionsub statementsub elsesub
#             | conditionsub next statementsub next elsesub
#             | conditionsub next statementsub next elseifsub'''

def p_elseifsub(p):
    """elseifsub : else if 
                 | next else if """

def p_conditionsub(p):
    '''conditionsub : normalopenbracket expressionsub normalclosebracket
                    | normalopenbracket condition normalclosebracket'''

def p_expressionsub(p):
    """expressionsub : variable and variable 
                     | variable or variable"""

def p_statementsub(p):
    """statementsub : curlyopenbracket next statements semicolon next curlyclosebracket
                    | curlyopenbracket next statements next curlyclosebracket
                    | curlyopenbracket next if expr next curlyclosebracket next elsesub
                    | curlyopenbracket next if expr next curlyclosebracket next elseifsub
                    | if expr"""

def p_elsesub(p):
    """elsesub  : else next statementsub
                | else statementsub"""


error=0
def p_error(p):
    if(p!=None):
        print("Syntax Error 2",p)
        global error
        error=1




lex.lex()
yacc.yacc()


#for this data
data='''()
{
    statements;
}
else if()
{
}
else{
    statements;
    }
'''



try:
    yacc.parse(data)
except:
    print("Syntax Error")
    error=1

if error==0:
    print("Syntax is correct")
else:
    print("Syntax Has error")

