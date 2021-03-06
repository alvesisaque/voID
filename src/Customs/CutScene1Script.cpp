#include "Customs/CutScene1Script.hpp"
#include "Globals/EngineGlobals.hpp"

const int imageWidth = 1705;
const int imageHeight = 255;
const int frameWidth = 341;
const int frameHeight = 255;
const int framesPerSecond = 9;


/**
    @brief Constructor for the ThunderScript class.
    @param[in] owner
*/
CutScene1Script::CutScene1Script(GameObject *owner) : Script(owner) {}

/**
    @brief Start the animation for the cut scene 1.
*/
void CutScene1Script::Start() {
    INFO("CutScene1Script - initializing");
    /*
        Creates the animations defining position the place to insert
        and the scene that will be inserted.
    */
    CreateAnimations();
    m_position = GetOwner()->GetPosition();
    m_animator = (Animator *)GetOwner()->GetComponent("Animator");
    m_input = InputSystem::GetInstance();
    m_gamecontroller = m_input -> GetGameController(0);
    GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    // Checks for the map, and sets its properties.
    if(map) {
        GetOwner()->SetZoomProportion(Vector(map -> originalWidth / GetOwner()
                                             ->originalWidth, map
                                             -> originalHeight / GetOwner()
                                             -> originalHeight));
    } else {
        // Do nothing
    }
    
    INFO("CutScene1Script - initialized");
}

/**
    @brief Create the animations of the cut scene 1.
*/
void CutScene1Script::CreateAnimations() {
    INFO("CutScene1Script - Creating animations");
    // Image light sprite.
    auto centrallightSprite = new Image("assets/cut1.png", 0, 0, imageWidth, imageHeight);

    // Animation light.
    auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
    centrallightAnimation->AddFrame(new Frame(0, 0, frameWidth, frameHeight));

    // Animation.
    auto centrallightAnimator = new Animator(GetOwner());
    centrallightAnimation->SetFramesPerSecond(framesPerSecond);
    centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION",
                                       centrallightAnimation);

    INFO("CutScene1Script - Animations created");
}

/**
    @brief Update the animation of the cut scene 1.
*/
void CutScene1Script::ComponentUpdate() {
    // Compares the animator state.
    if(!m_animator->IsPlaying("CENTRAL LIGHT ANIMATION") && m_active) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    } else {
        // Do nothing
    }

    // Checks the animator state.
    if(m_animator->IsPlaying("CENTRAL LIGHT ANIMATION")) {
        m_animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    } else {
        // Do nothing
    }
}

/**
    @brief Do nothing.
*/
void CutScene1Script::FixedComponentUpdate() {}
