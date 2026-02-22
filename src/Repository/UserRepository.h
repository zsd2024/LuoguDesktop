#pragma once
#include "Models/User.h"
#include "Network/NetworkHelper.h"
#include "Network/NetworkManager.h"

class UserRepository
{
public:
    explicit UserRepository(NetworkManager *network);

    // 获取用户信息
    User fetchUser(int uid);

private:
    User analyzeUserResponse(const QByteArray &res);
    NetworkManager *m_network;
    NetworkHelper m_helper;
    const int RETRY_LIMIT = 3;
};
