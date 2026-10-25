#pragma once

#include "Executor.hpp"

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

private:
    // 1. 先声明具体的动作方法
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;

    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;

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

    // 4. 成员变量放在最后
    Pose pose;
    bool fast{false};  // 默认未处于加速状态
};

}  // namespace adas