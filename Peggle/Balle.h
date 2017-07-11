#pragma once
#include "Bloc.h"

class Balle
{
public:
	Balle();
	~Balle();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);
	bool IsLauched();
	void Launch(float angle);
	void Die();
	bool Collide(Bloc* bloc);

private:
	// Sprite
	IDirect3DTexture9* texture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 position;
	D3DXVECTOR3 initPosition;
	D3DXVECTOR3 lastPosition;
	D3DXVECTOR3 center;
	D3DXVECTOR3 direction;
	float speed;
	bool isLauched;
};

