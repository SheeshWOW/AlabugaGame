#pragma once

#include <string>
#include <SDL3/SDL.h>

typedef struct {
	SDL_FRect src_first_frame; // FRect �� ������ ���� ��������

	int frames_amount; // ���-�� ������ � �������� (�� X ���)
	int frame_index; // ������� ���� ��������
	double frame_duration; // ����� �� 1 ����
	double current_duration; // ������� ������ ������� � ���������� ����� (���������� � Update += delta_time)

	double sprite_sizeX; // ������ 1 ������� �������� �� X
} AnimationData;

