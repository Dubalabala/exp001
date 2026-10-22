
#include "ExecutorImpl.hpp"

namespace adas
{

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
    // 这里使用初始化列表直接保存传入的 pose
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto cmd : commands) {
        if (cmd == 'M') {
            if (pose.heading == 'E') {
                ++pose.x;
            } else if (pose.heading == 'W') {
                --pose.x;
            } else if (pose.heading == 'N') {
                ++pose.y;
            } else if (pose.heading == 'S') {
                --pose.y;
            }
        } else if (cmd == 'L') {
            switch (pose.heading) {
            case 'E':
                pose.heading = 'N';
                break;
            case 'N':
                pose.heading = 'W';
                break;
            case 'W':
                pose.heading = 'S';
                break;
            case 'S':
                pose.heading = 'E';
                break;
            default:
                break;
            }
        } else if (cmd == 'R') {
            switch (pose.heading) {
            case 'E':
                pose.heading = 'S';
                break;
            case 'S':
                pose.heading = 'W';
                break;
            case 'W':
                pose.heading = 'N';
                break;
            case 'N':
                pose.heading = 'E';
                break;
            default:
                break;
            }
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;  // 返回当前（未初始化的）pose
}

}  // namespace adas