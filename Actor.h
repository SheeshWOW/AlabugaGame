#pragma once

#include "Sprite.h"
#include "Animation.h"
#include "ActorTypes.h"

struct ActorAnimations {
    Animation idle = {"IdleAnimation"};
};

class Actor : public Sprite {
public:
    Actor(SDL_Renderer* renderer, const char* texturePath);

    virtual void Handle_Event(SDL_Event* event);
    virtual void Update(double delta_time);

    virtual Animation* UpdateAnimation(double delta_time, Animation* animation);
    virtual ActorState UpdateMovement(double delta_time);
    virtual ActorDirection UpdateDirection(double delta_time);

    //void Render() override;

    void SetMoveSpeed(double move_speed);

protected:

    double move_speed = 0.0;
    MoveDirection move_direction = { 0.0, 0.0 };

    ActorAnimations actor_anims;
    Animation* actor_anim = nullptr;
    ActorState actor_state = ActorState::Idle;
    ActorDirection actor_direction = ActorDirection::Down;
};

