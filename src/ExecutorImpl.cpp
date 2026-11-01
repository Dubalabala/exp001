#include "ExecutorImpl.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    // 核心简化：利用初始化列表，直接构建映射表，并加上 const 保证安全
    const std::unordered_map<char, std::function<void(PoseHandler&)>> cMderMap{
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'F', FastCommand()},
        {'B', ReverseCommand()} 
    };

    for (const auto cmd : commands) {
        const auto it = cMderMap.find(cmd);
        if (it != cMderMap.end()) {
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