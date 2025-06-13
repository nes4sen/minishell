#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



int main()
{
 char *str = getenv("HOMEf");
 if (str)
    printf("%s\n", str);
else 
printf("tt");


}