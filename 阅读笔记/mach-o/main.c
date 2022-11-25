#include <stdio.h>

void lwPrint(char *str);

extern char *g_String;

int main()
{
    lwPrint(g_String);
  return 0;
}
