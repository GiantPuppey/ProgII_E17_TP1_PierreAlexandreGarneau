#include "stdafx.h"
#include "Peggle.h"

Peggle::Peggle()
{
}

Peggle::Peggle(HINSTANCE hInstance, int nCmdShow)
	: D3DApp(hInstance, nCmdShow)
	, eyePos(.0f, .0f, -10.f)
	, target(0.f, 0.f, 0.f)
	, up(0.f, -1.0f, 0.f)
{
	HR(D3DXCreateSprite(gD3DDevice, &spriteBatch));

	D3DXMatrixLookAtRH(&view, &eyePos, &target, &up);
	D3DXMatrixOrthoRH(&ortho, d3dPP.BackBufferWidth, d3dPP.BackBufferHeight, 0.01f, 1000.0f);
	
	// Fixed pipeline
	HR(gD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
	HR(gD3DDevice->SetRenderState(D3DRS_LIGHTING, false));

	HR(gD3DDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gD3DDevice->SetTransform(D3DTS_PROJECTION, &ortho));
}

Peggle::~Peggle()
{
	ReleaseCOM(spriteBatch);
}

void Peggle::Update()
{
	Input* input = gD3DApp->GetInput();
	if (input->MouseButtonDown(0) == true)
	{
		if (canon.GetIsReady() == true)
		{
			canon.SetIsReady(false);
			balle.Launch(canon.GetAngle());
		}
	}

	balle.Update();
	canon.Update();
	background.Update();
}

void Peggle::Draw()
{
	HR(gD3DDevice->Clear(0, 0, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(128, 128, 128), 1.0, 0));

	HR(gD3DDevice->BeginScene());
	HR(spriteBatch->Begin(	D3DXSPRITE_ALPHABLEND | 
		D3DXSPRITE_OBJECTSPACE | D3DXSPRITE_DONOTMODIFY_RENDERSTATE));

	background.Draw(spriteBatch);
	balle.Draw(spriteBatch);
	canon.Draw(spriteBatch);

	HR(spriteBatch->End());
	HR(gD3DDevice->EndScene());

	HR(gD3DDevice->Present(0, 0, 0, 0));
}

