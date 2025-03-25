#pragma once
#include <SDL3/SDL.h>
#include <string>

class Sprite {
public:
    Sprite(SDL_Renderer* renderer, const char* texturePath);
    virtual ~Sprite();

    SDL_Texture* LoadTexture(const char* texturePath);

    virtual void Handle_Event(SDL_Event* event);
    virtual void Update(double deltaTime);
    virtual void Render();

    void SetPosition(double x, double y);
    void SetSourceRect(SDL_FRect srcRect);
    void SetScale(double scaleX, double scaleY);
    void SetScale(double scale);
    void SetColor(Uint8 r=255, Uint8 g=255, Uint8 b=255, Uint8 a = 255);
    void SetVisible(bool visible);
    void SetRotation(double rotation);
    void SetFlipMode(SDL_FlipMode flip_mode);

    SDL_FRect GetRect();
    bool IsVisible();

    //Debug
    void ShowPosition();

protected:
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_FRect destRect = { 0, 0, 0, 0 };
    SDL_FRect srcRect = { 0, 0, 0, 0 };
    SDL_Color color{ 255, 255, 255, 255 };
    double scaleX = 1.0, scaleY = 1.0;
    double angle = 0;
    SDL_FlipMode flip = SDL_FLIP_NONE;

    bool visible = true;
};
