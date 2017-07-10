#include "stdafx.h"
#include "Canon.h"
#include "D3DApp.h"
#include <iostream>

Canon::Canon()
	: center( 9.0f, 9.0f, .0f)
	, position(.0f, .0f, .0f)
	, direction(.0f, .0f, .0f)
	, speed(0)
	, isReady(true)
{
	HR(D3DXCreateTextureFromFileEx(gD3DDevice, L"bannerSmallBlue.png", 0, 0, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 255, 255), &info, NULL, &texture));
}

Canon::~Canon()
{
	ReleaseCOM(texture);
}

void Canon::Update()
{
	Input* i = gD3DApp->GetInput();
	POINT mousePos = i->GetMousePos();
	D3DVIEWPORT9 v;
	gD3DDevice->GetViewport(&v);
	D3DXVECTOR3 vMousePos(mousePos.x - (float)v.Width / 2, mousePos.y - (float)v.Height / 2, 0.f);
	D3DXVECTOR3 centre(0, -300, 0);
	D3DXVECTOR3 dir = vMousePos - centre;
	D3DXVec3Normalize(&dir, &dir);
	angle = atan2(dir.y, dir.x);
}

void Canon::Draw(ID3DXSprite* spriteBatch)
{
	D3DXMATRIX transfomMatrix;
	D3DXVECTOR2 translation(0, -300);
	D3DXMatrixAffineTransformation2D(&transfomMatrix, 1, 0, angle, &translation);
	HR(spriteBatch->SetTransform(&transfomMatrix));
	HR(spriteBatch->Draw(texture, 0, &center, &position, D3DCOLOR_XRGB(255, 255, 255)));

	//restore transformation
	D3DXMatrixIdentity(&transfomMatrix);
	HR(spriteBatch->SetTransform(&transfomMatrix));

	HR(spriteBatch->Flush());
}

bool Canon::GetIsReady()
{
	return isReady;
}

void Canon::SetIsReady(bool pIsReady)
{
	isReady = pIsReady;
}

float Canon::GetAngle()
{
	return angle;
}