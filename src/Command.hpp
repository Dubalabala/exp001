#pragma once
#include "PoseHandler.hpp"

namespace adas
{

class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(PoseHandler& poseHandler) const noexcept = 0;
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
        }  // 叠加时先退1格
        // 倒车时左转，实际上是车头向右转
        if (poseHandler.IsReverse()) {
            poseHandler.TurnRight();
        } else {
            poseHandler.TurnLeft();
        }
    }
};

class TurnRightCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }  // 叠加时先退1格
        // 倒车时右转，实际上是车头向左转
        if (poseHandler.IsReverse()) {
            poseHandler.TurnLeft();
        } else {
            poseHandler.TurnRight();
        }
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

class ReverseCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        poseHandler.Reverse();
    }
};

}  // namespace adas