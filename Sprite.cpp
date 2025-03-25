#include "Sprite.h"
#include <SDL3_image/SDL_image.h>

Sprite::Sprite(SDL_Renderer* renderer, const char* texturePath)
{
	this->renderer = renderer;
	this->texture = this->LoadTexture(texturePath);

	SDL_GetTextureSize(this->texture, &this->destRect.w, &this->destRect.h);

	this->ShowPosition();
}

Sprite::~Sprite()
{
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}
}

SDL_Texture* Sprite::LoadTexture(const char* texturePath)
{
	SDL_Texture* new_texture = IMG_LoadTexture(renderer, texturePath);
	if (new_texture == NULL) {
		SDL_Log("(Sprite.Constructor) IMG_LoadTexture error: %s", SDL_GetError());
		return NULL;
	}
	else {
		if (this->texture != NULL) {
			SDL_DestroyTexture(this->texture);
		}

		this->texture = new_texture;
		SDL_SetTextureScaleMode(new_texture, SDL_SCALEMODE_NEAREST);

		return new_texture;
	}

	return NULL;
}

void Sprite::Handle_Event(SDL_Event* event)
{
}

void Sprite::Update(double deltaTime)
{
}

void Sprite::Render()
{
	if (!visible || !texture) return;
	SDL_FRect scaledDestRect = { this->destRect.x, this->destRect.y, this->destRect.w * scaleX, this->destRect.h * scaleY };

	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture, color.a);
	SDL_RenderTextureRotated(
		this->renderer,
		this->texture,
		&this->srcRect,
		&scaledDestRect,
		this->angle,
		nullptr,
		this->flip
		);
	//SDL_RenderTexture(this->renderer, this->texture, &this->srcRect, &scaledDestRect);
	//SDL_RenderTexture(this->renderer, this->texture, NULL, NULL);
}

void Sprite::SetPosition(double x, double y)
{
	this->destRect.x = x;
	this->destRect.y = y;
}

void Sprite::SetSourceRect(SDL_FRect srcRect)
{
	this->srcRect = srcRect;
}

void Sprite::SetScale(double scaleX, double scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

void Sprite::SetScale(double scale)
{
	this->scaleX = scale;
	this->scaleY = scale;
}

void Sprite::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

void Sprite::SetVisible(bool visible)
{
	this->visible = visible;
}

void Sprite::SetRotation(double rotation)
{
	this->angle = rotation;
}

void Sprite::SetFlipMode(SDL_FlipMode flip_mode)
{
	this->flip = flip_mode;
}

SDL_FRect Sprite::GetRect()
{
	return this->destRect;
}

bool Sprite::IsVisible()
{
	return this->visible;
}

void Sprite::ShowPosition()
{
	SDL_Log("PosX: %lf\nPosY: %lf\n\n", this->destRect.x, this->destRect.y);
}
