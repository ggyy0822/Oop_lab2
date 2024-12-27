#include "State/ChaseState.hpp"
#include "iostream"
namespace State {
Object::GamePosition ChaseState::Behavior(
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
        return pos; // 若類型未知，保持當前位置
    }
}

bool ChaseState::IsOutRange(Object::GamePosition pos) {
    // 初始化標記，表示位置是否需要修正
    bool adjusted = false;
    // 檢查 X 軸範圍
    if (pos.x < 0) {
        pos.x = 0;
        adjusted = true;
    } else if (pos.x > 11) {
        pos.x = 11;
        adjusted = true;
    }
    // 檢查 Y 軸範圍
    if (pos.y < 0) {
        pos.y = 0;
        adjusted = true;
    } else if (pos.y > 11) {
        pos.y = 11;
        adjusted = true;
    }
    // 返回是否有調整
    return adjusted;
}
// Blinky：直接向玩家最短距離移動
Object::GamePosition ChaseState::Blinky(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
    int dx = playerPos.x - pos.x;
    int dy = playerPos.y - pos.y;

    // 決定移動方向
    if (abs(dx) > abs(dy)) {
        // 優先縮小 X 軸距離
        pos.x += (dx > 0) ? 1 : -1;
    } else {
        // 優先縮小 Y 軸距離
        pos.y += (dy > 0) ? 1 : -1;
    }
    IsOutRange(pos); // 確保移動後位置合法
    // 返回新位置
    return pos;
}
// Clyde：在玩家周圍 4 格內才追逐，否則隨機移動
Object::GamePosition ChaseState::Clyde(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
    int distance = std::max(abs(playerPos.x - pos.x), abs(playerPos.y - pos.y));

    if (distance <= 4) {
        // 距離玩家 4 格內，執行追逐邏輯
        return Blinky(pos, playerPos);
    } else {
        // 隨機移動
        pos.x += (rand() % 3 - 1); // -1, 0, or 1
        pos.y += (rand() % 3 - 1); // -1, 0, or 1
        IsOutRange(pos); // 確保移動後位置合法
        return pos;
    }
}
// Inky：目標為玩家位置 + (玩家位置 - Inky 位置)
Object::GamePosition ChaseState::Inky(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
    Object::GamePosition target = {
      playerPos.x + (playerPos.x - pos.x),
      playerPos.y + (playerPos.y - pos.y)
    };

    int dx = target.x - pos.x;
    int dy = target.y - pos.y;

    // 決定移動方向
    if (abs(dx) > abs(dy)) {
        pos.x += (dx > 0) ? 1 : -1;
    } else {
        pos.y += (dy > 0) ? 1 : -1;
    }
    IsOutRange(pos); // 確保移動後位置合法
    return pos;
}
// Pinky：目標為玩家位置的 X 軸 +4
Object::GamePosition ChaseState::Pinky(
    Object::GamePosition pos,
    Object::GamePosition playerPos
) {
    Object::GamePosition target = {
      playerPos.x + 4,
      playerPos.y
    };

    int dx = target.x - pos.x;
    int dy = target.y - pos.y;

    // 決定移動方向
    if (abs(dx) > abs(dy)) {
        pos.x += (dx > 0) ? 1 : -1;
    } else {
        pos.y += (dy > 0) ? 1 : -1;
    }
    IsOutRange(pos); // 確保移動後位置合法
    return pos;
}
}  // namespace State
