#include "ExecutorImpl.hpp"

#include <functional>
#include <memory>  // 必须有
#include <unordered_map>

#include "Command.hpp"

namespace adas
{

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap;

    cmderMap.emplace('M', MoveCommand());
    cmderMap.emplace('L', TurnLeftCommand());
    cmderMap.emplace('R', TurnRightCommand());
    cmderMap.emplace('F', FastCommand());
    cmderMap.emplace('B', ReverseCommand());

    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);
        if (it != cmderMap.end()) {
            it->second(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new ExecutorImpl(pose);
}
}  // namespace adas