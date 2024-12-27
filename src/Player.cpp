#include "Object/Player.hpp"
#include "Object/GameObject.hpp"
#include "iostream"
#include <algorithm>

namespace Object {

std::string Player::GetName() const {
    return name;
}

Object::GamePosition Player::GetPosition() const {
    return pos;
}

void Player::Move(char direction) {
    switch (direction) {
    case 'w': // 向上移動
        ++pos.y;
        break;
    case 's': // 向下移動
        --pos.y;
        break;
    case 'a': // 向左移動
        --pos.x;
        break;
    case 'd': // 向右移動
        ++pos.x;
        break;
    }
    // 邊界檢查，防止超出 [0, 11] 範圍
    pos.x = std::max(0, std::min(pos.x, 11));
    pos.y = std::max(0, std::min(pos.y, 11));
}

bool Player::IsOutRange() {
    // 檢查玩家位置是否在範圍外 (範圍 [0, 11])
    return pos.x < 0 || pos.x > 11 || pos.y < 0 || pos.y > 11;
}

}  // namespace Object
