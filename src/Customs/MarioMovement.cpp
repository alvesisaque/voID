#include "Customs/MarioMovement.h"
#include "Components/Renderer.h"
#include "Engine/InputSystem.h"
#include "Log/log.h"
#include "Math/Vector.h"

MarioMovement::MarioMovement(GameObject *owner) : Script(owner) {
  // getting reference for the input system
  input = InputSystem::GetInstance();
}

void MarioMovement::Start() {
  // getting reference for the renderer component
  renderer = (Renderer *)GetOwner()->GetComponent("Renderer");
  // making an error raise if there no renderer component
  if (!renderer) {
    ERROR("NO RENDERER FOUND!");
    exit(1);
  }
}

void MarioMovement::ComponentUpdate() {
  // deactivate object
  bool deactivate = input->GetKeyUp(INPUT_Q);
  GetOwner()->active = !deactivate;

  // deactivate this script
  if (input->GetKeyDown(INPUT_E))
    isVisible = !isVisible;
  GetOwner()->GetComponent("Renderer")->active = isVisible;

  // checking input for movement
  right = input->GetKeyPressed(INPUT_D);
  left = input->GetKeyPressed(INPUT_A);

  // flip image
  if (left)
    renderer->GetImage()->Flip(true, false);
  else if (right)
    renderer->GetImage()->Flip(false, false);
}

void MarioMovement::FixedComponentUpdate() {
  // getting current position ans setting speed
  Vector position = renderer->GetPosition();

  // changing position values
  position.m_x += right * speed;
  position.m_x -= left * speed;
  position.m_y -= input->GetKeyPressed(INPUT_W) * speed;
  position.m_y += input->GetKeyPressed(INPUT_S) * speed;

  // updating position according to new position
  renderer->SetPosition(position);
}