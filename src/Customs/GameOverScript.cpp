/**
    @file GameOverScript.cpp
    @brief Methods that manages the game over script of the game.
    @copyright LGPL. MIT License.
*/

#include "Customs/GameOverScript.hpp"

const int quantityFrameLine = 22;
const int quantityFrameColumn = 12;

GameOverScript::GameOverScript(GameObject *owner) : Script(owner) {

}

/**
    @brief that function starts the game over script. Create the animation,
    position, the animator and the input.
*/
void GameOverScript::Start() {
    // Starts game-over animations by setting its positions and animator.Sets gameobject's vector zoom proportion.
    position = GetOwner()->GetPosition();
    animator = (Animator *)GetOwner()->GetComponent("Animator");
    input = InputSystem::GetInstance();
    GetOwner()->SetZoomProportion(Vector(0, 0));
}

/**
    @brief that function creates the animations. Create the snow image, the game
    over animation and animator.
*/
void GameOverScript::CreateAnimations() {
    /*
        Creates game-over animation by setting a image and a animation with
        defined frames positions over it.
    */
    auto snowImage = new Image("assets/Ending_PARTE_FINAL.png",0,0,4096, 2048);

    auto gameOverAnimation= new Animation(GetOwner(),snowImage );
    for (int  line = 0; line < quantityFrameLine; line++) {
        for (int column = 0 ; column < quantityFrameColumn ; column++) {
            gameOverAnimation->AddFrame(new Frame(column * 341,line* 256, 341, 256));
            gameOverAnimation->AddFrame(new Frame(column * 341,line* 256, 341, 256));
        }
    }

    // animator.
    auto gameOverAnimator = new Animator(GetOwner());
    gameOverAnimator->AddAnimation("snowAnimation", gameOverAnimation);
}

/**
    @brief that function updates the components of the game over.
*/
void GameOverScript::ComponentUpdate() {
    /*
        Updates the game-over component and sets the state of played audios.
    */
    animator->PlayAnimation("snowAnimation");
    // Check for the player and its animator and input state.
    if (play==1) {
        animator->PlayAnimation("snowAnimation");
    }

    if (input->GetKeyDown(INPUT_T) && play==0) {
        // animator->StopAllAnimations();
        AudioController::GetInstance()->PlayAudio("snowSound", -1);
        play=1;
    }
    else if (input->GetKeyDown(INPUT_T) && play==1) {
        play=0;
        AudioController::GetInstance()->StopAudio("snowSound");
        animator->StopAllAnimations();
    }
}

/**
    @brief that function fixs the component upddate of the game over Script.
    They set the position x and y to zero.
*/
void GameOverScript::FixedComponentUpdate() {
    // Check the components positions, and end them by setting it to zero.
    position->m_x = 0;
    position->m_y = 0;

}
