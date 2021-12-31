#include <stdio.h>
#include <string.h>

#include "lib/macros.h"
#include "lib/types.h"
#include "lib/utils/utils.h"
#include "middleware/connection/connection.h"
#include "middleware/auth/auth.h"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        perror("app.error.args_missing");
        exit(1);
    }

    user_info user_info;
    ftp_mode_t selected_mode;

    if(argsParser(argv[1], &user_info) != 0){
        perror("app.error.args_parsing");
        exit(-1);
    }

    printUserInfo(&user_info);

    char *token;
    token = strtok(argv[2], "-");

    bool is_active = strcmp(token, "A") == 0;
    bool is_pasv = strcmp(token, "P") == 0; 

    if (!is_pasv && !is_active) {
        perror("app.error.args_mode");
        exit(-1);
    }

    selected_mode = is_active ? ACTIVE : PASV;

    int fd = init_connection(&user_info);
    auth_login(fd, &user_info);

    return 0;
}
