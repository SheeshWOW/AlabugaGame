#include "Actor.h"

Actor::Actor(SDL_Renderer* renderer, const char* texturePath) : Sprite(renderer, texturePath)
{
}

void Actor::Handle_Event(SDL_Event* event)
{
}

void Actor::Update(double delta_time)
{
	this->actor_state = ActorState::Idle;
	this->actor_direction = ActorDirection::Down;

	Animation* current_anim;
	switch (this->actor_state) {
		
	case ActorState::Idle:
	default:
		current_anim = &this->actor_anims.idle;
		break;
	}

	this->UpdateAnimation(delta_time, current_anim);
}

Animation* Actor::UpdateAnimation(double delta_time, Animation* animation)
{
	if (animation == nullptr) return nullptr;

	//SDL_Log("Animation: %s", animation->anim_name.c_str());
	//SDL_Log("AnimationDir: %d", animation->GetDirection());

	if (this->actor_direction == ActorDirection::Left) {
		this->flip = SDL_FLIP_HORIZONTAL;
	}
	else if (this->actor_direction == ActorDirection::Right) {
		this->flip = SDL_FLIP_NONE;
	}

	if (actor_anim && actor_anim->anim_name != animation->anim_name) {
		actor_anim->Stop();
		actor_anim = nullptr;
	}

	if (this->actor_anim == nullptr && animation != nullptr) {
		this->actor_anim = animation;
		this->actor_anim->Play(&this->srcRect);
	}
	
	this->actor_anim->SetDirection(this->actor_direction);
	this->actor_anim->Update(delta_time);
	return this->actor_anim;
}

ActorState Actor::UpdateMovement(double delta_time)
{
	return ActorState::Idle;
}

ActorDirection Actor::UpdateDirection(double delta_time)
{
	return ActorDirection::Down;
}

void Actor::SetMoveSpeed(double move_speed)
{
	this->move_speed = move_speed;
}
