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

    if(argsParser(argv[1],&Uinfo) != 0){
        exit(-1)
    }

    printUserInfo(&Uinfo);
    //  TODO:  login here

    

    return 0;
}
