#include "Object/Clyde.hpp"
#include "State/ChaseState.hpp"
#include "State/ScatterState.hpp"


namespace Object {
//Clyde::Clyde() = default;
Clyde::Clyde() {
  pos = {CLYDE_INITIAL_POS_X, CLYDE_INITIAL_POS_Y};
  state = std::make_shared<State::ChaseState>();
};

std::string Clyde::GetName() const {
  return name;
};

Object::GamePosition Clyde::GetPosition() const {
  return pos;
};

void Clyde::SetState(Object::MonsterState s) {
  if (s == Object::MonsterState::Chase) {
      state = std::make_shared<State::ChaseState>();
  } else if (s == Object::MonsterState::Scatter) {
      state = std::make_shared<State::ScatterState>();
  }
}

void Clyde::Move(const Object::GamePosition& playerPos) {
  if (state) {
      // 使用當前狀態的行為邏輯計算下一步位置
      pos = state->Behavior(GhostType::CLYDE, pos, playerPos);
  }
}
}  // namespace Object
