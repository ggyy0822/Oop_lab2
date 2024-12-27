#include "Object/Dot.hpp"

namespace Object {
Dot::Dot(Object::GamePosition pos) : position(pos){};

uint8_t Dot::GetPoint() {
  return 1;
}

std::string Dot::GetName() const {
  return "d";
}

Object::GamePosition Dot::GetPosition() const {
  return position;
}
}  // namespace Object
