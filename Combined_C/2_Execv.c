#include<stdio.h>
#include<unistd.h>
int main()
{
char *temp[3];
temp[0]="ls";
temp[1]="-l";
temp[2]=(char *)0;
execv("/bin/ls",temp);
printf("This will not print\n");
}