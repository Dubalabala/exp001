
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
    // 空实现：暂不处理指令
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;  // 返回当前（未初始化的）pose
}

}  // namespace adas