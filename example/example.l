%{
    #include <iostream>
    int test = 0;
%}

%%

 ( )*      →  {}
\n         →  {}
;          →  { std::cout << "MATCH: ;" << std::endl; }
\\(        →  { std::cout << "MATCH: (" << std::endl; }   
\\)        →  { std::cout << "MATCH: )" << std::endl; }   
{          →  { std::cout << "MATCH: {" << std::endl; }   
}          →  { std::cout << "MATCH: }" << std::endl; }
[          →  { std::cout << "MATCH: [" << std::endl; }   
]          →  { std::cout << "MATCH: ]" << std::endl; }

main       →  { std::cout << "MATCH: main" << std::endl; }

auto       →  { std::cout << "MATCH: auto" << std::endl; }             
case       →  { std::cout << "MATCH: case" << std::endl; }             
const      →  { std::cout << "MATCH: const" << std::endl; }              
default    →  { std::cout << "MATCH: default" << std::endl; }                
double     →  { std::cout << "MATCH: double" << std::endl; }               
enum       →  { std::cout << "MATCH: enum" << std::endl; }             
float      →  { std::cout << "MATCH: float" << std::endl; }              
goto       →  { std::cout << "MATCH: goto" << std::endl; }             
int        →  { std::cout << "MATCH: int" << std::endl; }            
register   →  { std::cout << "MATCH: register" << std::endl; }                 
short      →  { std::cout << "MATCH: short" << std::endl; }              
sizeof     →  { std::cout << "MATCH: sizeof" << std::endl; }               
struct     →  { std::cout << "MATCH: struct" << std::endl; }               
typedef    →  { std::cout << "MATCH: typedef" << std::endl; }                
unsigned   →  { std::cout << "MATCH: unsigned" << std::endl; }                 
volatile   →  { std::cout << "MATCH: volatile" << std::endl; }                 
break      →  { std::cout << "MATCH: break" << std::endl; }              
char       →  { std::cout << "MATCH: char" << std::endl; }             
continue   →  { std::cout << "MATCH: continue" << std::endl; }                 
do         →  { std::cout << "MATCH: do" << std::endl; }           
else       →  { std::cout << "MATCH: else" << std::endl; }             
extern     →  { std::cout << "MATCH: extern" << std::endl; }               
for        →  { std::cout << "MATCH: for" << std::endl; }            
if         →  { std::cout << "MATCH: if" << std::endl; }           
long       →  { std::cout << "MATCH: long" << std::endl; }             
return     →  { std::cout << "MATCH: return" << std::endl; }               
signed     →  { std::cout << "MATCH: signed" << std::endl; }               
while      →  { std::cout << "MATCH: while" << std::endl; }              
switch     →  { std::cout << "MATCH: switch" << std::endl; }               
union      →  { std::cout << "MATCH: union" << std::endl; }              
void       →  { std::cout << "MATCH: void" << std::endl; }             
static     →  { std::cout << "MATCH: static" << std::endl; }

+          →  { std::cout << "MATCH: +" << std::endl; }                  
-          →  { std::cout << "MATCH: -" << std::endl; }                  
\\*        →  { std::cout << "MATCH: *" << std::endl; }                  
/          →  { std::cout << "MATCH: /" << std::endl; }                  
%          →  { std::cout << "MATCH: %" << std::endl; }                  
==         →  { std::cout << "MATCH: ==" << std::endl; }                   
!=         →  { std::cout << "MATCH: !=" << std::endl; }                   
>          →  { std::cout << "MATCH: >" << std::endl; }                  
<          →  { std::cout << "MATCH: <" << std::endl; }                  
>=         →  { std::cout << "MATCH: >=" << std::endl; }                   
<=         →  { std::cout << "MATCH: <=" << std::endl; }                   
&&         →  { std::cout << "MATCH: &&" << std::endl; }                   
\\|\\|     →  { std::cout << "MATCH: ||" << std::endl; }                   
!          →  { std::cout << "MATCH: !" << std::endl; }                  
&          →  { std::cout << "MATCH: &" << std::endl; }                  
\\|        →  { std::cout << "MATCH: |" << std::endl; }                  
^          →  { std::cout << "MATCH: ^" << std::endl; }                  
~          →  { std::cout << "MATCH: ~" << std::endl; }                  
<<         →  { std::cout << "MATCH: <<" << std::endl; }                   
>>         →  { std::cout << "MATCH: >>" << std::endl; }                   
=          →  { std::cout << "MATCH: =" << std::endl; }                  
+=         →  { std::cout << "MATCH: +=" << std::endl; }                   
-=         →  { std::cout << "MATCH: -=" << std::endl; }                   
\\*=       →  { std::cout << "MATCH: *=" << std::endl; }                   
/=         →  { std::cout << "MATCH: /=" << std::endl; }                   
%=         →  { std::cout << "MATCH: %=" << std::endl; }                   
<<=        →  { std::cout << "MATCH: <<=" << std::endl; }                    
>>=        →  { std::cout << "MATCH: >>=" << std::endl; }                    
&=         →  { std::cout << "MATCH: &=" << std::endl; }                   
^=         →  { std::cout << "MATCH: ^=" << std::endl; }                   
\\|=       →  { std::cout << "MATCH: |=" << std::endl; }                   
++         →  { std::cout << "MATCH: ++" << std::endl; }                   
--         →  { std::cout << "MATCH: --" << std::endl; }                   

(0-9)*                        →  { std::cout << "MATCH: integer" << std::endl; }
(0-9)*.(0-9)*                 →  { std::cout << "MATCH: float" << std::endl; }
(A-Z|a-z|_)(A-Z|a-z|0-9|_)*   →  { std::cout << "MATCH: identifier" << std::endl; }

%%

int main(int argc, char** argv) {
    yyin = argv[1];
    yylex();
    return 0;
}
