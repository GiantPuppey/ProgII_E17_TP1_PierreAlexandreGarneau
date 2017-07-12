#pragma once
#include "Bloc.h"
#define M_PI           3.14159265358979323846
class Catcher
{
public:
	Catcher();
	~Catcher();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);
	bool IsLauched();
	void Launch(float angle);
	void Die();
	float GetDirection();
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

