#ifndef OOPLAB_RUNTIMEFRAMEWORK_HPP
#define OOPLAB_RUNTIMEFRAMEWORK_HPP
#include <memory>
#include "Object/Blinky.hpp"
#include "Object/Clyde.hpp"
#include "Object/Inky.hpp"
#include "Object/Pinky.hpp"
#include "Object/Player.hpp"
#include "Util/DotManager.hpp"
namespace Util {
enum RuntimeState {
    INITIAL,
    RUNNING,
    END,
};

class RuntimeFramework {
    RuntimeState state = RuntimeState::INITIAL;

    std::shared_ptr<Object::Blinky> blinky = std::make_shared<Object::Blinky>();
    std::shared_ptr<Object::Clyde>  clyde = std::make_shared<Object::Clyde>();
    std::shared_ptr<Object::Inky>   inky = std::make_shared<Object::Inky>();
    std::shared_ptr<Object::Pinky>  pinky = std::make_shared<Object::Pinky>();
    std::shared_ptr<Object::Player> player = std::make_shared<Object::Player>();

    std::shared_ptr<Util::DotManager> point_manager;
public:
    RuntimeFramework() = default;
    ~RuntimeFramework() = default;

    void Initial();

    void Running();

    void Render();

    void End();

    RuntimeState GetState() const { return state; }
};
}  // namespace Util
#endif  // OOPLAB_RUNTIMEFRAMEWORK_HPP
