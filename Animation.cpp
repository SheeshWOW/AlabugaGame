#include "Animation.h"


Animation::Animation(std::string anim_name)
{
	this->anims_data = {};

	this->anim_name = anim_name;
	this->playing = false;
}

Animation::~Animation()
{
}

void Animation::LoadAnimation(ActorDirection direction, AnimationData anim_data)
{
	this->anims_data[direction] = anim_data;
}

void Animation::Update(double delta_time)
{
	if (!playing) return;

	AnimationData* current_anim_data = GetCurrentAnimationData();
	if (current_anim_data == nullptr) {
		SDL_Log("current_anim_data is nullptr!");
		return;
	};

	current_anim_data->current_duration += delta_time;

	if (current_anim_data->frame_duration < current_anim_data->current_duration) {
		current_anim_data->current_duration = 0;
		current_anim_data->frame_index = (current_anim_data->frame_index + 1) % current_anim_data->frames_amount;
	}

	double next_frame_offsetX = (current_anim_data->sprite_sizeX * double(current_anim_data->frame_index));
	this->sourceRect->x = current_anim_data->src_first_frame.x + next_frame_offsetX;
	this->sourceRect->y = current_anim_data->src_first_frame.y;

	//SDL_Log("PosX: %lf", current_anim_data->src_first_frame.x + next_frame_offsetX);
	//SDL_Log("PosY: %lf", current_anim_data->src_first_frame.y);
}

void Animation::SetDirection(ActorDirection direction)
{
	this->anim_direction = direction;
}

void Animation::Play(SDL_FRect* srcRect)
{
	this->playing = true;
	this->sourceRect = srcRect;
}

void Animation::Pause()
{
	this->playing = false;
	this->Update(0);
}

void Animation::Stop()
{
	this->Pause();
	this->Reset();
}

void Animation::Reset()
{
	AnimationData* current_anim = this->GetCurrentAnimationData();
	current_anim->current_duration = 0;
	current_anim->frame_index = 0;
	this->Update(0);
}

bool Animation::isPlaying() const
{
	return this->playing;
}

ActorDirection Animation::GetDirection() const
{
	return this->anim_direction;
}

AnimationData* Animation::GetCurrentAnimationData()
{
	return &this->anims_data[this->anim_direction];
}
