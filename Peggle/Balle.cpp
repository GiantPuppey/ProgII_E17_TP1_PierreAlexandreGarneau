#include "stdafx.h"
#include "Balle.h"
#include "D3DApp.h"
#include <math.h>

Balle::Balle()
	: center(8.0f, 8.0f, .0f)
	, position(.0f, -300.0f, .0f)
	, direction(.0f, .0f, .0f)
	, speed(200)
	, isLauched(false)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"ball.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));

	initPosition = position;
	lastPosition = position;
}

Balle::~Balle()
{
	ReleaseCOM(texture);
}

void Balle::Update()
{
	if (isLauched)
	{		
		D3DVIEWPORT9 v;
		gD3DDevice->GetViewport(&v);

		int height = (int)v.Height / 2;
		int width = (int)v.Width / 2;

		lastPosition = position;
		position += ((direction * speed) * gD3DApp->GetTimer()->GetDeltaTime());
		
		float ballRadius = center.x;

		if (position.y + ballRadius > height)
		{
			Die();
		}
		if (position.y - ballRadius < -height)
		{
			position.y = -height + 1 + ballRadius;
			direction.y *= -1;
		}
		if (position.x + ballRadius  > width)
		{
			position.x = width - 1 - ballRadius;;
			direction.x *= -1;
		}
		if (position.x - ballRadius  < -width)
		{
			position.x = -width + 1 + ballRadius;;
			direction.x *= -1;
		}
	}
}

void Balle::Draw(ID3DXSprite* spriteBatch)
{
	if (isLauched)
	{
		HR(spriteBatch->Draw(texture, 0, &center, &position, D3DCOLOR_XRGB(255, 255, 255)));
		HR(spriteBatch->Flush());
	}
}

void Balle::Launch(float angle)
{
	direction.x = cos(angle);
	direction.y = sin(angle);
	isLauched = true;
}

void Balle::Die()
{
	isLauched = false;
	position = initPosition;
}

bool Balle::IsLauched()
{
	return isLauched;
}

bool Balle::Collide(Bloc* bloc)
{
	float ballradius = center.x;
	D3DXVECTOR2 circleDistance;

	circleDistance.x = abs(position.x - bloc->GetX());
	circleDistance.y = abs(position.y - bloc->GetY());

	if (circleDistance.x > (bloc->GetW() / 2 + ballradius)) { return false; }
	if (circleDistance.y > (bloc->GetH() / 2 + ballradius)) { return false; }

	if (circleDistance.x <= (bloc->GetW()/ 2)) { return true; }
	if (circleDistance.y <= (bloc->GetH() / 2)) { return true; }

	float cornerDistance_sq = std::powf((circleDistance.x - bloc->GetW() / 2), 2.0f) + std::powf((circleDistance.y - bloc->GetH() / 2), 2.0f);

	return cornerDistance_sq <= std::powf(ballradius, 2.0f);
}