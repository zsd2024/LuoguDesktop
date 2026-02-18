#pragma once
#include <QDate>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <optional>

using namespace Qt::StringLiterals;

struct UserPrize
{
    int year;                     // 获奖年份
    QString contest;              // 比赛名称
    std::optional<QString> event; // 子事件（可能为空）
    QString prize;                // 奖项名称
    int score;                    // 奖项分数
    int rank;                     // 奖项排名
    // ===== 解析函数 =====
    static UserPrize fromJson(const QJsonObject &json);
};

struct Gu
{
    int rating;     // 总咕值
    QDateTime time; // 达成时间
    int social;     // 社区贡献
    int basic;      // 基础信用
    int contest;    // 比赛情况
    int practice;   // 练习情况
    int prize;      // 获得成就
    // ===== 解析函数 =====
    static Gu fromJson(const QJsonObject &json);
};

struct EloRecord
{
    int rating;                  // 当时的 Elo 值
    QDateTime time;              // 达成时间
    int contestId;               // 比赛 ID
    QDateTime contestStart;      // 开始时间
    QDateTime contestEnd;        // 结束时间
    QString contestName;         // 比赛名称
    int userCount;               // 参赛人数
    std::optional<int> prevDiff; // Elo 变化（可能为空）
    // ===== 解析函数 =====
    static EloRecord fromJson(const QJsonObject &json);
};

struct DailyCount
{
    int count;         // 通过的题目数量
    int maxDifficulty; // 最高难度
    // ===== 解析函数 =====
    static DailyCount fromJson(const QJsonArray &json);
};

enum class UserColor
{
    Gray,    // 灰名
    Blue,    // 蓝名
    Green,   // 绿名
    Orange,  // 橙名
    Red,     // 红名
    Cheater, // 棕名（作弊者）
    Purple,  // 紫名（管理员）
    Unknown  // 未知颜色
};

struct UserProfile
{
    // ===== 基础信息 =====
    int uid;                      // 用户 ID
    QString name;                 // 用户名
    QString avatar;               // 用户头像 URL
    QString slogan;               // 个性签名
    QString introduction;         // 个人介绍
    std::optional<QString> badge; // 用户徽章（可能为空）
    QDateTime registerTime;       // 注册时间

    // ===== 权限信息 =====
    bool isAdmin;  // 是否为管理员
    bool isBanned; // 是否被封禁

    // ===== 用户颜色 =====
    UserColor color;  // 用户颜色
    QString rawColor; // 用户颜色（原始字符串）

    // ===== 等级信息 =====
    int ccfLevel;  // CCF 等级
    int xcpcLevel; // XCPC 等级

    // ===== 主页背景 =====
    QString background; // 主页背景图 URL

    // ===== Elo 信息 =====
    std::optional<int> eloValue; // 当前 Elo 值（可能为空）

    // ===== 社交信息 =====
    int followingCount; // 关注的人数
    int followerCount;  // 粉丝的人数
    int ranking;        // 全站排名

    // ===== 刷题信息 =====
    int passedProblemCount;    // 通过的题目数量
    int submittedProblemCount; // 提交的题目数量

    // ===== 解析函数 =====
    static UserProfile fromJson(const QJsonObject &json);

    // ===== 颜色转换 =====
    static UserColor parseUserColor(const QString &str);
};

class User
{
public:
    // ===== 基础信息 =====
    UserProfile profile;

    // ===== 奖项列表 =====
    QVector<UserPrize> prizes;

    // ===== 估值信息 =====
    Gu gu;

    // ===== Elo 历史信息 =====
    QVector<EloRecord> eloHistory;

    // ===== 每日题目信息 =====
    QMap<QDate, DailyCount> dailyCounts;

    // ===== 解析函数 =====
    //
    // 本函数输入 json 对象应为用户主页源代码中 json 数据中的 `data` 字段
    static User fromJson(const QJsonObject &json);
};
