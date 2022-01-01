#pragma once

#include "../../middleware/auth/auth.h";
#include "../../middleware/connection/connection.h";

int pasv_connect(user_info *user_info);

int pasv_download();