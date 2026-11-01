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
        }                        // 叠加时先退/进1格
        poseHandler.TurnLeft();  // 直接调用，倒车逻辑底层已处理
    }
};

class TurnRightCommand final : public ICommand
{
public:
    void DoOperate(PoseHandler& poseHandler) const noexcept override
    {
        if (poseHandler.IsFast()) {
            poseHandler.Move();
        }                         // 叠加时先退/进1格
        poseHandler.TurnRight();  // 直接调用，倒车逻辑底层已处理
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