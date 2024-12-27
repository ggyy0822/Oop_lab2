#include "Object/Pinky.hpp"

namespace Object {

Pinky::Pinky() {
    pos = {PINKY_INITIAL_POS_X,PINKY_INITIAL_POS_Y};
    state = std::make_shared<State::ChaseState>();
};

std::string Pinky::GetName() const {
  return name;
};

Object::GamePosition Pinky::GetPosition() const {
  return pos;
};

void Pinky::SetState(Object::MonsterState s) {
  if( s == Object::MonsterState::Chase){
      state = std::make_shared<State::ChaseState>();
  } else if ( s == Object::MonsterState::Scatter){
      state = std::make_shared<State::ScatterState>();
  }
}

void Pinky::Move(const Object::GamePosition& playerPos) {
      if (state) {
          // 使用當前狀態的行為邏輯計算下一步位置
          pos = state->Behavior(GhostType::PINKY, pos, playerPos);
      }
}

}  // namespace Object
