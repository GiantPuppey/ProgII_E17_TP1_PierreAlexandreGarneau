#include "stdafx.h"
#include "Balle.h"
#include "D3DApp.h"

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

		position += ((direction * speed) * gD3DApp->GetTimer()->GetDeltaTime());

		if (position.y > height)
		{
			Die();
		}
		if (position.y < -height)
		{
			position.y = -height + 1;
			direction.y *= -1;
		}
		if (position.x > width)
		{
			position.x = width - 1;
			direction.x *= -1;
		}
		if (position.x < -width)
		{
			position.x = -width + 1;
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