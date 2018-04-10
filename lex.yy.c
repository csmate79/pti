%{
#include<stdio.h>
int sorok=0, szavak=0,betuk=0, szam=0,total=0;
%}
%%


 
\n { sorok++; szavak++;}
[\t ' '] szavak++;
[A-Z] betuk++;
[a-z] betuk++;
[0-9] szam++;
%%





main(void)
{
yyin= fopen("myfile.txt","r");
yylex();
total=betuk+szam;
printf(" A fajl tartalmaz ...");
printf("\n\t%d sort.", sorok);
printf("\n\t%d szot.",szavak);
printf("\n\t%d betut.", betuk);
printf("\n\t%d szamot.", szam);
printf("\n\taz osszes %d karakterben.\n",total);
}
 
int yywrap()
{
return(1);
}
