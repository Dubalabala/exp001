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

}  // namespace adas