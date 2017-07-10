#include "stdafx.h"
#include "Background.h"
#include "D3DApp.h"

Background::Background() : Background(0, 0, 0)
{
}

Background::Background(float gravity, float startX, float startY)
	: center(.0f, .0f, .0f)
	, position(-300.0f, -300.0f, .0f)
	,isLaunched(false)
	,gravityForce(gravity)
	,speed(300.0f)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"background.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));
}

Background::~Background()
{
	ReleaseCOM(texture);
}

void Background::Update()
{
}

void Background::Draw(ID3DXSprite* spriteBatch)
{
	HR(spriteBatch->Draw(texture, 0, &center, &position, D3DCOLOR_XRGB(255, 255, 255)));
	HR(spriteBatch->Flush());
}
