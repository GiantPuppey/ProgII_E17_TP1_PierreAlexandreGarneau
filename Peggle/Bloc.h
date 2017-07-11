#pragma once
class Bloc
{
public:
	Bloc(float x, float y);
	~Bloc();

	void Update();
	void Draw(ID3DXSprite* spriteBatch);
	float GetX();
	float GetY();
	float GetH();
	float GetW();

private:
	// Sprite
	IDirect3DTexture9* texture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 position;
	D3DXVECTOR3 center;
};

