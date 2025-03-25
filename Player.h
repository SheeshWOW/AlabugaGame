#pragma once

#include "Actor.h"
#include "Animation.h"

struct PlayerAnimations : public ActorAnimations {
    Animation walk = {"WalkAnimation"};
};

class Player : public Actor {
public:
    Player(SDL_Renderer* renderer, const char* texturePath);

    void Handle_Event(SDL_Event* event) override;

    void Update(double deltaTime) override;
    ActorState UpdateMovement(double delta_time) override;
    ActorDirection UpdateDirection(double delta_time) override;

    void SetMoveSpeed(double move_speed);

private:
    PlayerAnimations actor_anims;
};
