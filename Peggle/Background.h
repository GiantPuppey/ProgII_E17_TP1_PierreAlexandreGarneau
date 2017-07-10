#pragma once
class Background
{
public:
	Background();
	Background(float gravity ,float startX, float startY);
	~Background();


	bool GetIsLaunched() const { return isLaunched; }

//protected:
	void Update();
	void Draw(ID3DXSprite* spriteBatch);

private:
	// Sprite
	IDirect3DTexture9* texture;
	D3DXIMAGE_INFO info;
	D3DXVECTOR3 position;
	D3DXVECTOR3 center;

	float gravityForce;
	float speed;
	bool isLaunched;
};

