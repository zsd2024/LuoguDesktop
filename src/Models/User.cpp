#include "User.h"

UserPrize UserPrize::fromJson(const QJsonObject &json)
{
    UserPrize prize;
    QJsonObject prizeJson = json[u"prize"_s].toObject();
    prize.year = prizeJson[u"year"_s].toInt();
    prize.contest = prizeJson[u"contest"_s].toString();
    QJsonValue eventValue = prizeJson[u"event"_s];
    if (eventValue.isString())
        prize.event = eventValue.toString();
    else
        prize.event.reset();
    prize.prize = prizeJson[u"prize"_s].toString();
    prize.score = prizeJson[u"score"_s].toInt();
    prize.rank = prizeJson[u"rank"_s].toInt();
    return prize;
}

Gu Gu::fromJson(const QJsonObject &json)
{
    Gu gu;
    gu.time = QDateTime::fromSecsSinceEpoch(json[u"time"_s].toInteger());
    gu.rating = json[u"rating"_s].toInt();
    QJsonObject guScores = json[u"scores"_s].toObject();
    gu.social = guScores[u"social"_s].toInt();
    gu.basic = guScores[u"basic"_s].toInt();
    gu.contest = guScores[u"contest"_s].toInt();
    gu.practice = guScores[u"practice"_s].toInt();
    gu.prize = guScores[u"prize"_s].toInt();
    return gu;
}

EloRecord EloRecord::fromJson(const QJsonObject &json)
{
    EloRecord record;
    record.rating = json[u"rating"_s].toInt();
    record.time = QDateTime::fromSecsSinceEpoch(json[u"time"_s].toInteger());
    record.userCount = json[u"userCount"_s].toInt();
    QJsonValue prevDiffValue = json[u"prevDiff"_s];
    if (prevDiffValue.isDouble())
        record.prevDiff = prevDiffValue.toInt();
    else
        record.prevDiff.reset();
    QJsonObject contestJson = json[u"contest"_s].toObject();
    record.contestId = contestJson[u"id"_s].toInt();
    record.contestStart = QDateTime::fromSecsSinceEpoch(contestJson[u"startTime"_s].toInteger());
    record.contestEnd = QDateTime::fromSecsSinceEpoch(contestJson[u"endTime"_s].toInteger());
    record.contestName = contestJson[u"name"_s].toString();
    return record;
}

DailyCount DailyCount::fromJson(const QJsonArray &json)
{
    DailyCount count;
    count.count = json[0].toInt();
    count.maxDifficulty = json[1].toInt();
    return count;
}

UserProfile UserProfile::fromJson(const QJsonObject &json)
{
    UserProfile profile;
    profile.uid = json[u"uid"_s].toInt();
    profile.name = json[u"name"_s].toString();
    profile.avatar = json[u"avatar"_s].toString();
    profile.slogan = json[u"slogan"_s].toString();
    profile.introduction = json[u"introduction"_s].toString();
    QJsonValue badgeValue = json[u"badge"_s];
    if (badgeValue.isString())
        profile.badge = badgeValue.toString();
    else
        profile.badge.reset();
    profile.registerTime = QDateTime::fromSecsSinceEpoch(json[u"registerTime"_s].toInteger());
    profile.isAdmin = json[u"isAdmin"_s].toBool();
    profile.isBanned = json[u"isBanned"_s].toBool();
    profile.rawColor = json[u"color"_s].toString();
    profile.color = parseUserColor(profile.rawColor);
    profile.ccfLevel = json[u"ccfLevel"_s].toInt();
    profile.xcpcLevel = json[u"xcpcLevel"_s].toInt();
    profile.background = json[u"background"_s].toString();
    QJsonValue eloValue = json[u"elo"_s];
    if (eloValue.isDouble())
        profile.eloValue = eloValue.toInt();
    else
        profile.eloValue.reset();
    profile.followingCount = json[u"followingCount"_s].toInt();
    profile.followerCount = json[u"followerCount"_s].toInt();
    profile.ranking = json[u"ranking"_s].toInt();

    // userRelationship 和 reverseUserRelationship 两个字段暂未发现其作用

    profile.passedProblemCount = json[u"passedProblemCount"_s].toInt();
    profile.submittedProblemCount = json[u"submittedProblemCount"_s].toInt();
    return profile;
}

User User::fromJson(const QJsonObject &json)
{
    User user;
    user.profile = UserProfile::fromJson(json[u"user"_s].toObject());
    QJsonArray prizesJson = json[u"prizes"_s].toArray();
    for (const QJsonValue &prizeValue : prizesJson)
        user.prizes.push_back(UserPrize::fromJson(prizeValue.toObject()));
    user.gu = Gu::fromJson(json[u"gu"_s].toObject());
    QJsonArray eloHistoryJson = json[u"elo"_s].toArray();
    for (const QJsonValue &eloValue : eloHistoryJson)
        user.eloHistory.push_back(EloRecord::fromJson(eloValue.toObject()));
    QJsonObject dailyCountJson = json[u"dailyCounts"_s].toObject();
    for (auto it = dailyCountJson.begin(); it != dailyCountJson.end(); ++it)
        user.dailyCounts[QDate::fromString(it.key(), Qt::ISODate)] = DailyCount::fromJson(it.value().toArray());
    return user;
}

UserColor UserProfile::parseUserColor(const QString &str)
{
    if (str == u"Gray"_s)
        return UserColor::Gray;
    else if (str == u"Blue"_s)
        return UserColor::Blue;
    else if (str == u"Green"_s)
        return UserColor::Green;
    else if (str == u"Orange"_s)
        return UserColor::Orange;
    else if (str == u"Red"_s)
        return UserColor::Red;
    else if (str == u"Cheater"_s)
        return UserColor::Cheater;
    else if (str == u"Purple"_s)
        return UserColor::Purple;
    else
        return UserColor::Unknown;
}

bool UserPrize::operator==(const UserPrize &other) const
{
    return std::tie(year, contest, event, prize, score, rank) == std::tie(other.year, other.contest, other.event, other.prize, other.score, other.rank);
}

bool Gu::operator==(const Gu &other) const
{
    return std::tie(rating, time, social, basic, contest, practice, prize) == std::tie(other.rating, other.time, other.social, other.basic, other.contest, other.practice, other.prize);
}

bool EloRecord::operator==(const EloRecord &other) const
{
    return std::tie(rating, time, contestId, contestStart, contestEnd, contestName, userCount, prevDiff) == std::tie(other.rating, other.time, other.contestId, other.contestStart, other.contestEnd, other.contestName, other.userCount, other.prevDiff);
}

bool DailyCount::operator==(const DailyCount &other) const
{
    return std::tie(count, maxDifficulty) == std::tie(other.count, other.maxDifficulty);
}

bool UserProfile::operator==(const UserProfile &other) const
{
    return std::tie(uid, name, avatar, slogan, introduction, badge, registerTime, isAdmin, isBanned, color, rawColor, ccfLevel, xcpcLevel, background, eloValue, followingCount, followerCount, ranking, passedProblemCount, submittedProblemCount) == std::tie(other.uid, other.name, other.avatar, other.slogan, other.introduction, other.badge, other.registerTime, other.isAdmin, other.isBanned, other.color, other.rawColor, other.ccfLevel, other.xcpcLevel, other.background, other.eloValue, other.followingCount, other.followerCount, other.ranking, other.passedProblemCount, other.submittedProblemCount);
}

bool User::operator==(const User &other) const
{
    return std::tie(profile, prizes, gu, eloHistory, dailyCounts) == std::tie(other.profile, other.prizes, other.gu, other.eloHistory, other.dailyCounts);
}

bool User::operator!=(const User &other) const
{
    return !(*this == other);
}
