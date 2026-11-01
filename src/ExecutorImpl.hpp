#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas
{

class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    void Execute(const std::string& commands) noexcept override;
    Pose Query(void) const noexcept override;

private:
    PoseHandler poseHandler;  // 只有这一个私有成员
};

}  // namespace adas