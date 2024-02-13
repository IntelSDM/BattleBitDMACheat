#include "pch.h"
#include "Init.h"
#include "drawing.h"
#include "GUI.h"
#include "Globals.h"
ID2D1Factory* Factory;
IDWriteFactory* FontFactory;
ID2D1HwndRenderTarget* RenderTarget;
ID2D1SolidColorBrush* Brush;

void InitD2D(HWND hWnd)
{
	HRESULT result = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &Factory);
	RECT rect;
	GetClientRect(hWnd, &rect);
	result = Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED)), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom), D2D1_PRESENT_OPTIONS_IMMEDIATELY), &RenderTarget);
	if (!SUCCEEDED(result))
		return;

	result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&FontFactory));
	if (!SUCCEEDED(result))
		return;

	CreateFonts(LIT("Verdana"), LIT(L"Verdana"), 10, DWRITE_FONT_WEIGHT_NORMAL);
	CreateFonts("VerdanaBold", LIT(L"Verdana"), 10, DWRITE_FONT_WEIGHT_SEMI_BOLD);
	RenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &Brush); // create global brush
	RenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE); // set aa mode
}
std::shared_ptr<CheatFunction> UpdateViewMatrix = std::make_shared<CheatFunction>(5, []() {
	Camera->UpdateViewMatrix();
	});

void CleanD2D()
{
	// ensure pointer is valid
	// then release memory
	if (Factory)
		Factory->Release();
	if (RenderTarget)
		RenderTarget->Release();
	if (Brush)
		Brush->Release();
	for (std::pair dict : Fonts)
	{
		const FontInformation& fontInfo = dict.second;
		if (fontInfo.font)
			fontInfo.font->Release();
	}
	//Clean all cached text layours
	for (std::pair dict : TextLayouts)
	{
		IDWriteTextLayout* layout = dict.second;
		if (layout)
			layout->Release();
	}

	for (std::pair dict : TextCache)
	{
		IDWriteTextLayout* layout = dict.second;
		if (layout)
			layout->Release();
	}
}

int FrameRate()
{
	static int fps;
	static int lastfps;
	static float lasttime;
	static float time;

	time = clock() * 0.001f;
	fps++;
	float DeltaTime = time - lasttime;
	if ((DeltaTime) >= 1.0f)
	{
		lasttime = time;
		lastfps = fps;
		fps = 0;
	}
	return lastfps;
}

void RenderFrame()
{
	// begin a new backbuffer
	RenderTarget->BeginDraw();
	RenderTarget->Clear(Colour(0, 0, 0, 255)); // clear over the last buffer
	RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity()); // set new transform
	//Text("test123", 200, 10, 50, LIT("Verdana"), Colour(255, 0, 0, 255),FontAlignment::None);
	//TextClipped("test123", 200, 100,50,50, 50, LIT("Verdana"), Colour(255, 0, 0, 255), FontAlignment::None);
	//if (BaseLocalPlayer->PlayerList.size() != 0)
	//{
	
//	}
	Render();
	RenderTarget->EndDraw();
}
