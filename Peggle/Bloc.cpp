#include "stdafx.h"
#include "Bloc.h"
#include "D3DApp.h"


Bloc::Bloc(float x, float y)
	: center(16.0f, 16.0f, .0f)
	, position(x, y, .0f)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"blueBrick12a.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));
}

Bloc::~Bloc()
{
	ReleaseCOM(texture);
}

void Bloc::Update()
{
}

void Bloc::Draw(ID3DXSprite* spriteBatch)
{
	D3DXMATRIX r;
	D3DXMATRIX t;
	D3DXMatrixRotationZ(&r, D3DX_PI / 2);
	D3DXMatrixTranslation(&t, position.x, position.y, 0);

	HR(spriteBatch->SetTransform(&(r * t)));
	HR(spriteBatch->Draw(texture, 0, &center, 0, D3DCOLOR_XRGB(255, 255, 255)));

	D3DXMatrixIdentity(&r);
	HR(spriteBatch->SetTransform(&r));

	HR(spriteBatch->Flush());
}