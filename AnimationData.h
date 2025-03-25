#pragma once

#include <string>
#include <SDL3/SDL.h>

typedef struct {
	SDL_FRect src_first_frame; // FRect на первый кадр анимации

	int frames_amount; // Кол-во кадров в анимации (по X оси)
	int frame_index; // Текущий кадр анимации
	double frame_duration; // Время на 1 кадр
	double current_duration; // Сколько прошло времени с последнего кадра (изменяется в Update += delta_time)

	double sprite_sizeX; // Размер 1 спрайта анимации по X
} AnimationData;

