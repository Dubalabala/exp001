
#include "ExecutorImpl.hpp"

#include <memory>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 映射表的 Value 变成了 std::function<void(PoseHandler&)>
    std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap;

    MoveCommand moveCommand;
    cmderMap.emplace('M', moveCommand.operate);
    TurnLeftCommand turnLeftCommand;
    cmderMap.emplace('L', turnLeftCommand.operate);
    TurnRightCommand turnRightCommand;
    cmderMap.emplace('R', turnRightCommand.operate);
    FastCommand fastCommand;
    cmderMap.emplace('F', fastCommand.operate);
    ReverseCommand reverseCommand;
    cmderMap.emplace('B', reverseCommand.operate);

    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            it->second(poseHandler);  // 直接像调用函数一样调用 operate
        }
    }
}

void ExecutorImpl::Move() noexcept
{
    if (pose.heading == 'E')
        ++pose.x;
    else if (pose.heading == 'W')
        --pose.x;
    else if (pose.heading == 'N')
        ++pose.y;
    else if (pose.heading == 'S')
        --pose.y;
}

void ExecutorImpl::TurnLeft() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    }
}

void ExecutorImpl::TurnRight() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'E';
    }
}

void ExecutorImpl::Fast() noexcept
{
    fast = !fast;  // 取反：未加速变加速，加速变普通
}

bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();  // 委托查询
}

}  // namespace adas