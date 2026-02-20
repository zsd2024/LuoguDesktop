#pragma once
#include "Models/User.h"
#include "Network/NetworkManager.h"

class UserRepository
{
public:
    UserRepository(NetworkManager *network);

    // 获取用户信息
    User fetchUser(int uid);

private:
    User analyzeUserResponse(const QByteArray &res);
    NetworkManager *m_network;
    const int RETRY_LIMIT = 3;
};
