#include <stdio.h>
#include <string.h>
int main(void)
{
  char number[20];
  int length, i;
  printf("±Ý¾×À» ÀÔ·ÂÇÏ°í Enter>");
  scanf("%s", number);
  length=strlen(number);
  for(i=length;i>=0;i--)
     printf("%c\n", number[i]);
  return 0;
}