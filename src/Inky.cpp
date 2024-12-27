#include "Object/Inky.hpp"

namespace Object {

Inky::Inky() {
    pos = {INKY_INITIAL_POS_X, INKY_INITIAL_POS_Y};
    state = std::make_shared<State::ChaseState>();
};

std::string Inky::GetName() const {
  return name;
};

Object::GamePosition Inky::GetPosition() const {
  return pos;
};

void Inky::SetState(Object::MonsterState s) {
  if (s == Object::MonsterState::Chase){
      state = std::make_shared<State::ChaseState>();
  }
  if (s == Object::MonsterState::Scatter){
      state = std::make_shared<State::ScatterState>();
  }
}

void Inky::Move(const Object::GamePosition& playerPos) {
  if (state) {
      // 使用當前狀態的行為邏輯計算下一步位置
      pos = state->Behavior(GhostType::INKY, pos, playerPos);
  }
}

}  // namespace Object
