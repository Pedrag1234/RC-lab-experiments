#pragma once

#include "../../middleware/auth/auth.h";
#include "../../middleware/connection/connection.h";

int active_connect(user_info *user_info);

int active_download();