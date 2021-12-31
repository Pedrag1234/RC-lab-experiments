#include <stdio.h>
#include <string.h>

#include "lib/macros.h"
#include "lib/types.h"
#include "lib/utils/utils.h"
#include "api/connection/connection.h"
#include "middleware/auth/auth.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        // fprintf(stderr,"")
        exit(1);
    }

    user_info user_info;

    if(argsParser(argv[1],&user_info) != 0){
        exit(-1);
    }

    printUserInfo(&user_info);

    int fd = init_connection(&user_info);
    auth_login(fd, &user_info);

    return 0;
}
