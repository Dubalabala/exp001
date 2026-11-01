#pragma once
#include "PoseHandler.hpp"  // 依赖变成 PoseHandler

namespace adas
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(PoseHandler& poseHandler) const noexcept = 0;  // 参数变更
};

class MoveCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.Move();
    }
};

class TurnLeftCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnLeft();  // 纠错PPT的笔误
    }
};

class TurnRightCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }
        poseHandler.TurnRight();
    }
};

class FastCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        poseHandler.Fast();
    }
};

}  // namespace adas