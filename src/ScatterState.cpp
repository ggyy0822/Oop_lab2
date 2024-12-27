#include "State/ScatterState.hpp"
#include "Object/GameObject.hpp"

namespace State {
Object::GamePosition ScatterState::Behavior(
    GhostType            type,
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
    switch (type) {
    case GhostType::BLINKY:
        return Blinky(pos, playerPos);
    case GhostType::INKY:
        return Inky(pos, playerPos);
    case GhostType::PINKY:
        return Pinky(pos, playerPos);
    case GhostType::CLYDE:
        return Clyde(pos, playerPos);
    default:
        return pos; // 如果類型未知，位置保持不變
    }
};

Object::GamePosition ScatterState::Blinky(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
  return {0,0};
}

Object::GamePosition ScatterState::Clyde(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
  return {11,0};
}

Object::GamePosition ScatterState::Inky(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
  return {11,11};
}

Object::GamePosition ScatterState::Pinky(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
  return {0,11};
}
}  // namespace State
