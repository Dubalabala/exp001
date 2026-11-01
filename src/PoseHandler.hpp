#pragma once
#include "Executor.hpp"

namespace adas
{
class PoseHandler final
{
public:
    PoseHandler(const Pose& pose) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

public:
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    void Reverse(void) noexcept;          // 新增倒车状态切换
    bool IsReverse(void) const noexcept;  // 新增倒车状态查询
    Pose Query(void) const noexcept;

private:
    Pose pose;
    bool fast{false};
    bool reverse{false};  // 倒车状态
};
}  // namespace adas