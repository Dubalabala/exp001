#include <gtest/gtest.h>

#include <memory>
#include <tuple>

#include "Executor.hpp"

namespace adas
{

// 为 Pose 定义 == 运算符重载，使得在测试中比较 Pose 对象变得简单明了
bool operator==(const Pose& lhs, const Pose& rhs)
{
    return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
}

// 测试用例1：初始化车的位置和朝向
TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when (无指令执行)

    // then
    const Pose target({0, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试用例2：未初始化车的位置和朝向，查询接口默认返回(0,0,N)
TEST(ExecutorTest, should_return_default_pose_when_without_init_and_command)
{
    // given (没有传入初始化位置，使用默认参数)
    std::unique_ptr<Executor> executor(Executor::NewExecutor());

    // when (无指令执行)

    // then (期望默认返回 0, 0, 'N')
    const Pose target({0, 0, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// 测试用例3：移动指令支持，向东移动1步
TEST(ExecutorTest, should_return_x_plus_1_given_command_is_M_and_facing_is_E)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when
    executor->Execute("M");

    // then
    const Pose target({1, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试用例4：移动指令支持，向西移动1步
TEST(ExecutorTest, should_return_x_minus_1_given_command_is_M_and_facing_is_W)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'W'}));

    // when
    executor->Execute("M");

    // then
    const Pose target({-1, 0, 'W'});
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas