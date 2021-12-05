#pragma once

void ToggleDirection(int& direction, int T)
{
	direction = direction == T ? 0 : T;
}

void OffDirection(int& direction, int T)
{
	direction = direction == T ? 0 : direction;
}

void ToggleSpeed(float& speed, int T)
{
	speed = speed == T ? 0 : T;
}

void OffSpeed(float& speed, int T)
{
	speed = speed == T ? 0 : speed;
}
