#include <stdio.h>
#include <string.h>

#include "api/connection/connection.h"
#include "lib/utils/utils.h"
#include "lib/macros.h"
#include "lib/types.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        //fprintf(stderr,"")
        exit(1);
    }
    user_info Uinfo;

    argsParser(argv[1],&Uinfo);

    printUserInfo(&Uinfo);

    return 0;
}
