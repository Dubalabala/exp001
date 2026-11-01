
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
    // 1. 构建表驱动
    std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap;
    cmderMap.emplace('M', std::make_unique<MoveCommand>());
    cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
    cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
    cmderMap.emplace('F', std::make_unique<FastCommand>());
    cmderMap.emplace('B', std::make_unique<ReverseCommand>());  // 新增这一行

    // 2. 统一的遍历逻辑（对应 PPT Page 16 截图的下半部分）
    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            // 重点：这里传入的是解耦后的 poseHandler，不再是 *this
            it->second->DoOperate(poseHandler);
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