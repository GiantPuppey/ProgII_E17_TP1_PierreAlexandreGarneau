#include "stdafx.h"
#include "Peggle.h"

// Main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
	gD3DApp = new Peggle(hInstance, nCmdShow);

	return gD3DApp->Run();
}