#include <iostream>
#include <memory>
#include <vector>
#include "Interface/MonsterMovable.hpp"
#include "Object/GameObject.hpp"
#include "Util/Map.hpp"
#include "Util/RuntimeFramework.hpp"

namespace Util {

void RuntimeFramework::Initial() {
    player = std::make_shared<Object::Player>();
    blinky = std::make_shared<Object::Blinky>();
    inky = std::make_shared<Object::Inky>();
    pinky = std::make_shared<Object::Pinky>();
    clyde = std::make_shared<Object::Clyde>();

    blinky->pos={0, 0};
    inky->pos = {0, 11};
    pinky->pos = {11, 0};
    clyde->pos = {11, 11};
    player->pos = {7, 7}; // 示例初始位置
    // 初始化點數
    std::vector<Object::GamePosition> dotPositions = {
      {2, 8}, {9, 9}, {8, 3}, {5, 7} // Example positions
    };
    point_manager = std::make_shared<Util::DotManager>(player, dotPositions);

    state = RuntimeState::RUNNING;
    std::cout << "Game Initialized.\n";
}

void RuntimeFramework::Running() {
    // 避免在非 RUNNING 狀態下執行
    if (state != RuntimeState::RUNNING) {
        return;
    }
    char input;
    std::cout << "Enter move direction (w/a/s/d): ";
    std::cin >> input;
    switch (input) {
    case 'w':
    case 'a':
    case 's':
    case 'd':
        // 玩家移動
        player->Move(input);
        break;
    case 'c':
        // 怪物切換到追逐模式
        blinky->SetState(Object::MonsterState::Chase);
        inky->SetState(Object::MonsterState::Chase);
        pinky->SetState(Object::MonsterState::Chase);
        clyde->SetState(Object::MonsterState::Chase);
        std::cout << "Monsters switched to CHASE mode.\n";
        break;
    case 'x':
        // 怪物切換到散開模式
        blinky->SetState(Object::MonsterState::Scatter);
        inky->SetState(Object::MonsterState::Scatter);
        pinky->SetState(Object::MonsterState::Scatter);
        clyde->SetState(Object::MonsterState::Scatter);
        std::cout << "Monsters switched to SCATTER mode.\n";
        break;
    default:
        // 其他無效輸入可視需求做處理
        std::cout << "Invalid input! Try again.\n";
        break;
    }
    blinky->Move(player->GetPosition());
    inky->Move(player->GetPosition());
    pinky->Move(player->GetPosition());
    clyde->Move(player->GetPosition());

    if (point_manager->IsOverlapping()) {
        std::cout << "A dot is eaten!\n";

        // 如果所有點數都被吃光，遊戲勝利，狀態切到 END
        if (point_manager->GetPointListSize() == 0) {
            std::cout << "All dots eaten! You win!\n";
            state = RuntimeState::END;
            return;
        }
    }
    if (blinky->GetPosition() == player->GetPosition()) {
        std::cout << "Player eaten by Blinky! Game Over.\n";
        state = RuntimeState::END;
        return;
    }
    if (inky->GetPosition() == player->GetPosition()) {
        std::cout << "Player eaten by Blinky! Game Over.\n";
        state = RuntimeState::END;
        return;
    }
    if (pinky->GetPosition() == player->GetPosition()) {
        std::cout << "Player eaten by Blinky! Game Over.\n";
        state = RuntimeState::END;
        return;
    }
    if (clyde->GetPosition() == player->GetPosition()) {
        std::cout << "Player eaten by Blinky! Game Over.\n";
        state = RuntimeState::END;
        return;
    }


}


void RuntimeFramework::Render() {
    std::vector<std::shared_ptr<Object::GameObject>> gameObjects;

    // 添加角色到渲染列表
    if (blinky) gameObjects.push_back(blinky);
    if (inky) gameObjects.push_back(inky);
    if (pinky) gameObjects.push_back(pinky);
    if (clyde) gameObjects.push_back(clyde);
    if (player) gameObjects.push_back(player);

    // 添加點數到渲染列表
    for (const auto& dot : point_manager->GetPointList()) {
        gameObjects.push_back(dot);
    }
    for (const auto& obj : gameObjects) {
        std::cout << obj->GetName() << " at (" << obj->GetPosition().x
                  << ", " << obj->GetPosition().y << ")\n";
    }

    // 繪製地圖
    Map::Draw(gameObjects);
}

void RuntimeFramework::End() {
    std::cout << "Game Over! Thanks for playing.\n";
}
};  // namespace Util
