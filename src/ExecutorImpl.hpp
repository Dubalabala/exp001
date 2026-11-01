#pragma once
#include "Executor.hpp"
#include "PoseHandler.hpp"

namespace adas
{

class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() noexcept = default;

    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

public:
    // 1. 先声明具体的动作方法
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;

    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;

    // 4. 成员变量放在最后
    Pose pose;
    bool fast{false};  // 默认未处于加速状态

private:
    PoseHandler poseHandler;
};

}  // namespace adas