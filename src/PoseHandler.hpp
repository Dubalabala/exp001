#pragma once
#include "Executor.hpp"

namespace adas
{
class PoseHandler final
{
public:
    PoseHandler(const Pose& pose) noexcept;
    // 禁止拷贝构造和赋值，确保状态管理唯一性
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    Pose Query(void) const noexcept;

private:
    Pose pose;
    bool fast{false};
};
}  // namespace adas