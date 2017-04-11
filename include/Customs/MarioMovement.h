#ifndef __MARIO_MOVEMENT__
#define __MARIO_MOVEMENT__

#include "Components/Script.h"

class Renderer;
class InputSystem;

class MarioMovement : public Script {
public:
  MarioMovement(GameObject *owner);
  // Start method override
  void Start() override;

protected:
  void ComponentUpdate() override;
  void FixedComponentUpdate() override;
  std::string GetComponentName() override { return "MarioMovement"; };

private:
  bool right, left;
  float speed = 5;
  bool isVisible = true;
  Renderer *renderer;
  InputSystem *input;
};

#endif // __MARIO_MOVEMENT__