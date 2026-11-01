#include "PoseHandler.hpp"

namespace adas
{

PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

// 辅助函数：字符转数字 (对应 PPT 27 页的 E=0, S=1, W=2, N=3)
int ToInt(char heading)
{
    if (heading == 'E')
        return 0;
    if (heading == 'S')
        return 1;
    if (heading == 'W')
        return 2;
    return 3;  // 'N'
}

// 辅助函数：数字转字符
char ToChar(int dir)
{
    const char map[] = {'E', 'S', 'W', 'N'};
    return map[dir];
}

void PoseHandler::Move() noexcept
{
    // 建立坐标偏移量表 (对应 E, S, W, N)
    // E(0): x+1, S(1): y-1, W(2): x-1, N(3): y+1
    static const int dx[] = {1, 0, -1, 0};
    static const int dy[] = {0, -1, 0, 1};

    int dir = ToInt(pose.heading);

    // 如果是倒车，所有的坐标偏移量乘以 -1
    int step = reverse ? -1 : 1;

    pose.x += dx[dir] * step;
    pose.y += dy[dir] * step;
}

void PoseHandler::TurnLeft() noexcept
{
    int dir = ToInt(pose.heading);

    // 正常左转：-1。倒车左转：+1（相当于右转）
    int delta = reverse ? 1 : -1;

    // +4 是为了防止负数取模，例如 (-1 + 4) % 4 = 3
    dir = (dir + delta + 4) % 4;
    pose.heading = ToChar(dir);
}

void PoseHandler::TurnRight() noexcept
{
    int dir = ToInt(pose.heading);

    // 正常右转：+1。倒车右转：-1（相当于左转）
    int delta = reverse ? -1 : 1;

    dir = (dir + delta + 4) % 4;
    pose.heading = ToChar(dir);
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}
bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}
bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}

}  // namespace adas