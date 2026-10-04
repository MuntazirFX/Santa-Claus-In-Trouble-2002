// Minimal D3D8 engine skeleton: window + device + game loop + package open.
#include <windows.h>
#include <d3d8.h>
#include "core/xpk.h"

static IDirect3D8*       g_d3d = nullptr;
static IDirect3DDevice8* g_dev = nullptr;
static bool              g_run = true;

static LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) { g_run = false; PostQuitMessage(0); return 0; }
    return DefWindowProcA(h, m, w, l);
}

static bool InitD3D(HWND hwnd) {
    g_d3d = Direct3DCreate8(D3D_SDK_VERSION);
    if (!g_d3d) return false;

    D3DPRESENT_PARAMETERS pp = {};
    pp.Windowed               = TRUE;
    pp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
    pp.BackBufferFormat       = D3DFMT_UNKNOWN;
    pp.EnableAutoDepthStencil = TRUE;
    pp.AutoDepthStencilFormat = D3DFMT_D16;

    return SUCCEEDED(g_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &g_dev));
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR, int show) {
    WNDCLASSA wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = inst;
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = "SantaEngine";
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowA("SantaEngine", "Santa Engine", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, inst, nullptr);
    ShowWindow(hwnd, show);

    if (!InitD3D(hwnd)) {
        MessageBoxA(hwnd, "Failed to create engine", "Error", MB_OK);
        return 1;
    }

    XpkPackage pkg;
    pkg.Open("xmas.xpk");   // TODO: format reverse hone ke baad assets yahan se load honge

    MSG msg;
    while (g_run) {
        while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
        g_dev->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                     D3DCOLOR_XRGB(10, 20, 60), 1.0f, 0);
        g_dev->BeginScene();
        // TODO: update(), level draw, meshes
        g_dev->EndScene();
        g_dev->Present(nullptr, nullptr, nullptr, nullptr);
    }

    g_dev->Release();
    g_d3d->Release();
    return 0;
}
