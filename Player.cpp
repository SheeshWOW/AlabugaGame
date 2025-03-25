#include "Player.h"
#include "AnimationData.h"
#include <cmath>

const int SPRITE_SIZE = 32;

//AnimationData CreateAnimationData(const char* anim_name, int frames_amount=6, double frames_duration=0.1,) {

//}

Player::Player(SDL_Renderer* renderer, const char* texturePath) : Actor(renderer, texturePath)
{

	AnimationData idle_data_down;
	idle_data_down.frames_amount = 6;
	idle_data_down.frame_index = 0;
	idle_data_down.frame_duration = 0.1;
	idle_data_down.current_duration = 0;
	idle_data_down.sprite_sizeX = SPRITE_SIZE;
	idle_data_down.src_first_frame = { 0, 0, SPRITE_SIZE, SPRITE_SIZE };
				  
	AnimationData walk_data_right_n_left;
	walk_data_right_n_left.frames_amount = 6;
	walk_data_right_n_left.frame_index = 0;
	walk_data_right_n_left.frame_duration = 0.1;
	walk_data_right_n_left.current_duration = 0;
	walk_data_right_n_left.sprite_sizeX = SPRITE_SIZE;
	walk_data_right_n_left.src_first_frame = { 0, 128, SPRITE_SIZE, SPRITE_SIZE };

	AnimationData walk_data_down;
	walk_data_down.frames_amount = 6;
	walk_data_down.frame_index = 0;
	walk_data_down.frame_duration = 0.1;
	walk_data_down.current_duration = 0;
	walk_data_down.sprite_sizeX = SPRITE_SIZE;
	walk_data_down.src_first_frame = { 0, 96, SPRITE_SIZE, SPRITE_SIZE };

	AnimationData walk_data_up;
	walk_data_up.frames_amount = 6;
	walk_data_up.frame_index = 0;
	walk_data_up.frame_duration = 0.1;
	walk_data_up.current_duration = 0;
	walk_data_up.sprite_sizeX = SPRITE_SIZE;
	walk_data_up.src_first_frame = { 0, 160, SPRITE_SIZE, SPRITE_SIZE };
	
	// Idle
	this->actor_anims.idle.LoadAnimation(ActorDirection::Down, idle_data_down);

	// Walk
	this->actor_anims.walk.LoadAnimation(ActorDirection::Right, walk_data_right_n_left);
	this->actor_anims.walk.LoadAnimation(ActorDirection::Left, walk_data_right_n_left);
	this->actor_anims.walk.LoadAnimation(ActorDirection::Down, walk_data_down);
	this->actor_anims.walk.LoadAnimation(ActorDirection::Up, walk_data_up);
}

void Player::Handle_Event(SDL_Event* event)
{
	switch (event->type) {
	case SDL_EVENT_KEY_DOWN:

		switch (event->key.scancode) {
		case SDL_SCANCODE_SPACE:
			SDL_Log("Player: Jump!");
			break;
		default: break;

		}
	default: break;
	}
}

void Player::Update(double delta_time)
{
	
	ActorState movementState = this->UpdateMovement(delta_time);
	ActorDirection movementDirection = this->UpdateDirection(delta_time);

	Animation* current_anim;
	switch (movementState) {
	case ActorState::Walk:
		current_anim = &this->actor_anims.walk;
		break;
	case ActorState::Idle:
	default: 
		current_anim = &this->actor_anims.idle;
		break;
	}

	this->UpdateAnimation(delta_time, current_anim);
}

ActorState Player::UpdateMovement(double delta_time)
{
	const bool* keys = SDL_GetKeyboardState(NULL);

	double speed = this->move_speed * delta_time;
	ActorState state = ActorState::Idle;
	this->move_direction = { 0, 0 };

	// Movement
	if (keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S]) {
		state = ActorState::Walk;
		this->move_direction.y = -1;
	}
	if (keys[SDL_SCANCODE_S] && !keys[SDL_SCANCODE_W]) {
		state = ActorState::Walk;
		this->move_direction.y = 1;
	}

	if (keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_D]) {
		state = ActorState::Walk;
		this->move_direction.x = -1;
	}
	if (keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A]) {
		state = ActorState::Walk;
		this->move_direction.x = 1;
	}

	/*// Jump
	if (keys[SDL_SCANCODE_SPACE]) {
		state = ActorState::Jump;
	} */

	double move_rad = atan2(this->move_direction.y, this->move_direction.x);
	MoveDirection normalized_move_direction = { move_direction.x * abs(cos(move_rad)), move_direction.y * abs(sin(move_rad)) };

	this->destRect.x += normalized_move_direction.x * speed;
	this->destRect.y += normalized_move_direction.y * speed;

	return state;
}

ActorDirection Player::UpdateDirection(double delta_time)
{
	ActorDirection direction = ActorDirection::Down;
	if (this->move_direction.y == 1) {
		direction = ActorDirection::Down;
	}
	else if (this->move_direction.y == -1) {
		direction = ActorDirection::Up;
	}

	// Overrdrive Up&Down movement (Don't have sprites for this).
	if (this->move_direction.x == 1) {
		direction = ActorDirection::Right;
	}
	else if (this->move_direction.x == -1) {
		direction = ActorDirection::Left;
	}

	this->actor_direction = direction;
	return direction;
}

/*
void Player::Render()
{
}
*/

void Player::SetMoveSpeed(double move_speed)
{
	this->move_speed = move_speed;
}
