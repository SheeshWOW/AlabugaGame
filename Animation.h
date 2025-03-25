#pragma once

#include <SDL3/SDL.h>
#include "AnimationData.h"
#include "ActorTypes.h"
#include <map>

class Animation
{
public:
    std::string anim_name;

    Animation(std::string anim_name="Animation");
    ~Animation();

    void LoadAnimation(ActorDirection direction, AnimationData anim_data);
	void Update(double delta_time);

    void SetDirection(ActorDirection direction);

    void Play(SDL_FRect* srcRect);
    void Pause();
    void Stop();
    void Reset();

    bool isPlaying() const;
    ActorDirection GetDirection() const;

private:
    AnimationData* GetCurrentAnimationData();

    SDL_FRect* sourceRect = { 0 };
    std::map<ActorDirection, AnimationData> anims_data;
	ActorDirection anim_direction = ActorDirection::Down;

    bool playing = false;
};

