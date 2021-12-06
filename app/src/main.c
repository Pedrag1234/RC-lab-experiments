#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int i;
    printf("%d\n",argc);
    for(i=1;i<argc;i++)
    {
        printf("%s",argv[i]);
    }

    return 0;
}
