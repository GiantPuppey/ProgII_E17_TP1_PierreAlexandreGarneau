#include "stdafx.h"
#include "Catcher.h"
#include "D3DApp.h"
#include <math.h>

Catcher::Catcher()
	: center(8.0f, 8.0f, .0f)
	, position(.0f, 200.0f, .0f)
	, direction(.0f, .0f, .0f)
	, speed(300)
	, isLauched(false)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"Catcher.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));

	initPosition = position;
	lastPosition = position;
}

Catcher::~Catcher()
{
	ReleaseCOM(texture);
}

void Catcher::Update()
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

void Catcher::Draw(ID3DXSprite* spriteBatch)
{
	if (isLauched)
	{
		HR(spriteBatch->Draw(texture, 0, &center, &position, D3DCOLOR_XRGB(255, 255, 255)));
		HR(spriteBatch->Flush());
	}
}

void Catcher::Launch(float angle)
{
	direction.x = cos(angle);
	direction.y = sin(angle);
	isLauched = true;
}

void Catcher::Die()
{
	isLauched = false;
	position = initPosition;
}

bool Catcher::IsLauched()
{
	return isLauched;
}
float Catcher::GetDirection()
{
	return M_PI;
}
