#pragma once
#include "ExecutorImpl.hpp"

namespace adas{

// 2. 定义抽象基类 ICommand
class ICommand
{
public:
    virtual ~ICommand() = default;
    virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
};

// 3. 定义具体的命令类，继承自 ICommand
class MoveCommand final : public ICommand
{
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();  // 加速状态下多走一格
        }
        executor.Move();
    }
};

class TurnLeftCommand final : public ICommand
{
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();  // 加速状态下先走一格
        }
        executor.TurnLeft();
    }
};

class TurnRightCommand final : public ICommand
{
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override
    {
        if (executor.IsFast()) {
            executor.Move();  // 加速状态下先走一格
        }
        executor.TurnRight();
    }
};

class FastCommand final : public ICommand
{
public:
    void DoOperate(ExecutorImpl& executor) const noexcept override
    {
        executor.Fast();
    }
};
}