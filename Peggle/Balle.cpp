#include "stdafx.h"
#include "Balle.h"
#include "D3DApp.h"

Balle::Balle()
	: center(.0f, .0f, .0f)
	, position(-1000.0f, -1000.0f, .0f)
	, direction(.0f, .0f, .0f)
	, speed(0)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"ball.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));
}

Balle::~Balle()
{
	ReleaseCOM(texture);
}

void Balle::Update()
{
	position += ((direction * speed) * gD3DApp->GetTimer()->GetDeltaTime());
	

	D3DVIEWPORT9 *v = new D3DVIEWPORT9();
	gD3DDevice->GetViewport(v);

	if (position.y > v->Height / 2)
	{
		//position.y = v->Height / 2 - 1;
		direction.y *= -1;
	}
	if (position.y < (int)v->Height / -2)
	{
		//position.y = (int)v->Height / -2 + 1;
		direction.y *= -1;
	}

	if (position.x > v->Width / 2)
	{
		//position.x = v->Width / 2 - 1;
		direction.x *= -1;
	}
	if (position.x < (int)v->Width / -2)
	{
		//position.x = (int)v->Width / -2 + 1;
		direction.x *= -1;
	}
}

void Balle::Draw(ID3DXSprite* spriteBatch)
{
	HR(spriteBatch->Draw(texture, 0, &center, &position, D3DCOLOR_XRGB(255, 255, 255)));
	HR(spriteBatch->Flush());
}

void Balle::Launch(float angle)
{
	position.x = 0;
	position.y = -300;
	speed = 200;
	direction.x = cos(angle);
	direction.y = sin(angle);
}
