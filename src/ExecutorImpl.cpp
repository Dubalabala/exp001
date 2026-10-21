
#include "ExecutorImpl.hpp"

namespace adas
{

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept
{
    // 空实现：暂未保存初始位置，后续将在功能实现阶段完善
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