/**
    @file QuitButtonScript.cpp
    @brief Manages the Quit button functions.
    @copyright LGPL. MIT License.
*/

#include "Customs/QuitButtonScript.hpp"

const int grayTone = 160;
const int whiteTone = 255;

/**
    @brief Constructor of the class QuitButtonScript.
    @param[in] GameObject *owner - Owns the component.
*/
QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {

}

/**
    @brief Starts the Quit button.
*/
void QuitButtonScript::Start() {
    INFO("QuitButtonScript - initializing");
    m_interactiveButton = (UIButton *)GetOwner()->GetComponent("UIButton");
    INFO("QuitButtonScript - completed");
}

/**
    @brief Updates the text and sound of the Quit button.
*/
void QuitButtonScript::ComponentUpdate() {
    // Sound component to play the sound of the Play Button
    auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");

    // Change sound and running status when mouse is clicked
    if (m_interactiveButton->IsClicked()) {
        soundButton->Play(0, -1);
        SDLSystem::GetInstance()->SetRunning(false);
    }

    // Text component to set the colors of the Quit Button
    auto textButton = (UIText *)GetOwner()->GetComponent("UIText");

    // Set QuitButton color depending if mouse is over the button or not
    if (m_interactiveButton->IsOver()) {
        textButton->SetColor(grayTone, grayTone, grayTone, whiteTone);
    } else {
        textButton->SetColor(whiteTone, whiteTone, whiteTone, whiteTone);
    }
}
