#include "PoseHandler.hpp"

namespace adas
{

PoseHandler::PoseHandler(const Pose& pose) noexcept : pose(pose)
{
}

void PoseHandler::Move() noexcept
{
    if (reverse) {
        // 倒车逻辑：方向全部反过来
        if (pose.heading == 'E') {
            --pose.x;
        } else if (pose.heading == 'W') {
            ++pose.x;
        } else if (pose.heading == 'N') {
            --pose.y;
        } else if (pose.heading == 'S') {
            ++pose.y;
        }
    } else {
        // 正常前进逻辑
        if (pose.heading == 'E') {
            ++pose.x;
        } else if (pose.heading == 'W') {
            --pose.x;
        } else if (pose.heading == 'N') {
            ++pose.y;
        } else if (pose.heading == 'S') {
            --pose.y;
        }
    }
}

void PoseHandler::TurnLeft() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    }
}

void PoseHandler::TurnRight() noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'E';
    }
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}
bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}
bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

Pose PoseHandler::Query() const noexcept
{
    return pose;
}

}  // namespace adas