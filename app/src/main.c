#include "api/active/active.h"
#include "api/passive/pasv.h"

int main(int argc, char const *argv[])
{
    if (argc < 2)
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

    if (!is_pasv && !is_active)
        selected_mode = PASV;
    else
        selected_mode = is_active ? ACTIVE : PASV;

    switch (selected_mode) {
        case ACTIVE:
            // active_download(&user_info);
            break;
        default:
            pasv_download(&user_info);
            break;
    }

    return 0;
}
