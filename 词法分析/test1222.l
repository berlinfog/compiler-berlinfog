%{
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include<windows.h>
const char *r1="true";
const char *r2="false";
const char *r3="and";
const char *r4="not";
const char *r5="or";
%}

ida [0-9][0-9]*
idb [a-zA-z][a-zA-z0-9]*
end "#"
rop "=="|">="|"<="|"!="|">"|"<"
left "("
right ")"

%%

{idb} {
if(strcmp(r1,yytext)&&strcmp(r2,yytext)&&
strcmp(r3,yytext)&&strcmp(r4,yytext)&&strcmp(r5,yytext))
{FILE *fout0= fopen("E:\\data.txt","a+");fprintf(fout0,"id ");fclose(fout0);}
else if(!strcmp(r1,yytext)){FILE *fout2= fopen("E:\\data.txt","a+");fprintf(fout2,"true ");fclose(fout2);}
else if(!strcmp(r2,yytext)){FILE *fout3= fopen("E:\\data.txt","a+");fprintf(fout3,"false ");fclose(fout3);}
else if(!strcmp(r3,yytext)){FILE *fout5= fopen("E:\\data.txt","a+");fprintf(fout5,"and ");fclose(fout5);}
else if(!strcmp(r4,yytext)){FILE *fout4= fopen("E:\\data.txt","a+");fprintf(fout4,"not ");fclose(fout4);}
else if(!strcmp(r5,yytext)) {FILE *fout6= fopen("E:\\data.txt","a+");fprintf(fout6,"or ");fclose(fout6);}
}
{ida} {FILE *fout88;fout88= fopen("E:\\data.txt","a+");fprintf(fout88,"id ");fclose(fout88);}
{rop} {FILE *fout1= fopen("E:\\data.txt","a+");fprintf(fout1,"rop ");fclose(fout1);}
{end} {FILE *fout7= fopen("E:\\data.txt","a+");fprintf(fout7,"# ");fclose(fout7);}
{left} {FILE *fout8= fopen("E:\\data.txt","a+");fprintf(fout8,"( ");fclose(fout8);}
{right} {FILE *fout9= fopen("E:\\data.txt","a+");fprintf(fout9,") ");fclose(fout9);}




%%
main()
{
FILE *fout10= fopen("E:\\data.txt","w");fclose(fout10);
yyin=fopen("E:\\example.txt","r");
yylex();
fclose(yyin);
printf("词法分析已经处理完成，结果在E:\\data.txt\n");
system("pause");
}
