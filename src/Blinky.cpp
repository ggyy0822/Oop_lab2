#include "Object/Blinky.hpp"
#include "State/ChaseState.hpp"
#include "State/ScatterState.hpp"

namespace Object {

// 初始化 Blinky 的位置和狀態
Blinky::Blinky() {
    pos = {BLINKY_INITIAL_POS_X, BLINKY_INITIAL_POS_Y}; // 初始位置為 (0, 0)
    state = std::make_shared<State::ChaseState>();      // 初始狀態為追逐模式
}

// 獲取怪物名稱
std::string Blinky::GetName() const {
    return name; // 返回名稱 "Blinky"
}

// 獲取當前位置
Object::GamePosition Blinky::GetPosition() const {
    return pos;
}

// 設置怪物的狀態（追逐模式或散開模式）
void Blinky::SetState(Object::MonsterState s) {
    if (s == Object::MonsterState::Chase) {
        state = std::make_shared<State::ChaseState>();
    } else if (s == Object::MonsterState::Scatter) {
        state = std::make_shared<State::ScatterState>();
    }
}

// 根據玩家位置移動
void Blinky::Move(const Object::GamePosition& playerPos) {
    if (state) {
        // 根據當前狀態的行為決定新位置
        pos = state->Behavior(GhostType::BLINKY, pos, playerPos);
    }
}

} // namespace Object
