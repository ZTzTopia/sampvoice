/*
    This is a SampVoice project file
    Developer: CyberMor <cyber.mor.2020@gmail.ru>

    See more here https://github.com/CyberMor/sampvoice

    Copyright (c) Daniel (CyberMor) 2020 All rights reserved
*/

#pragma once

#include <cstdint>
#include <functional>
#include <mutex>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "Memory.hpp"

class Render {

    Render() = delete;
    ~Render() = delete;
    Render(const Render&) = delete;
    Render(Render&&) = delete;
    Render& operator=(const Render&) = delete;
    Render& operator=(Render&&) = delete;

private:

    using DeviceInitCallback = std::function<void(IDirect3D9*, IDirect3DDevice9*, const D3DPRESENT_PARAMETERS&)>;
    using BeforeResetCallback = std::function<void()>;
    using BeginSceneCallback = std::function<void()>;
    using RenderCallback = std::function<void()>;
    using EndSceneCallback = std::function<void()>;
    using AfterResetCallback = std::function<void(IDirect3DDevice9*, const D3DPRESENT_PARAMETERS&)>;
    using DeviceFreeCallback = std::function<void()>;

public:

    static constexpr float kBaseWidth = 640.f;
    static constexpr float kBaseHeight = 480.f;

public:

    static bool Init() noexcept;
    static void Free() noexcept;

    static bool GetWindowHandle(HWND& windowHandle) noexcept;
    static bool GetScreenSize(float& screenWidth, float& screenHeight) noexcept;
    static bool ConvertBaseXValueToScreenXValue(float baseValue, float& screenValue) noexcept;
    static bool ConvertBaseYValueToScreenYValue(float baseValue, float& screenValue) noexcept;
    static bool ConvertScreenXValueToBaseXValue(float screenValue, float& baseValue) noexcept;
    static bool ConvertScreenYValueToBaseYValue(float screenValue, float& baseValue) noexcept;

public:

    static std::size_t AddDeviceInitCallback(DeviceInitCallback callback) noexcept;
    static std::size_t AddBeforeResetCallback(BeforeResetCallback callback) noexcept;
    static std::size_t AddBeginSceneCallback(BeginSceneCallback callback) noexcept;
    static std::size_t AddRenderCallback(RenderCallback callback) noexcept;
    static std::size_t AddEndSceneCallback(EndSceneCallback callback) noexcept;
    static std::size_t AddAfterResetCallback(AfterResetCallback callback) noexcept;
    static std::size_t AddDeviceFreeCallback(DeviceFreeCallback callback) noexcept;

    static void RemoveDeviceInitCallback(std::size_t callback) noexcept;
    static void RemoveBeforeResetCallback(std::size_t callback) noexcept;
    static void RemoveBeginSceneCallback(std::size_t callback) noexcept;
    static void RemoveRenderCallback(std::size_t callback) noexcept;
    static void RemoveEndSceneCallback(std::size_t callback) noexcept;
    static void RemoveAfterResetCallback(std::size_t callback) noexcept;
    static void RemoveDeviceFreeCallback(std::size_t callback) noexcept;

private:

    interface IDirect3DDevice9Hook : public IDirect3DDevice9 {

        IDirect3DDevice9Hook() = delete;
        IDirect3DDevice9Hook(const IDirect3DDevice9Hook&) = delete;
        IDirect3DDevice9Hook(IDirect3DDevice9Hook&&) = delete;
        IDirect3DDevice9Hook& operator=(const IDirect3DDevice9Hook&) = delete;
        IDirect3DDevice9Hook& operator=(IDirect3DDevice9Hook&&) = delete;

    public:

        explicit IDirect3DDevice9Hook(IDirect3DDevice9* pOrigInterface) noexcept;

        ~IDirect3DDevice9Hook() noexcept;

    public:

        HRESULT __stdcall Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) noexcept override;
        HRESULT __stdcall QueryInterface(REFIID riid, VOID** ppvObj) noexcept override;
        ULONG __stdcall AddRef() noexcept override;
        ULONG __stdcall Release() noexcept override;
        HRESULT __stdcall TestCooperativeLevel() noexcept override;
        UINT __stdcall GetAvailableTextureMem() noexcept override;
        HRESULT __stdcall EvictManagedResources() noexcept override;
        HRESULT __stdcall GetDirect3D(IDirect3D9** ppD3D9) noexcept override;
        HRESULT __stdcall GetDeviceCaps(D3DCAPS9* pCaps) noexcept override;
        HRESULT __stdcall Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, FLOAT Z, DWORD Stencil) noexcept override;
        HRESULT __stdcall SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries) noexcept override;

    private:

        IDirect3DDevice9* const pOrigInterface;

        bool resetStatus { false };
        bool sceneStatus { false };

    };

    interface IDirect3D9Hook : public IDirect3D9 {

        IDirect3D9Hook() = delete;
        IDirect3D9Hook(const IDirect3D9Hook&) = delete;
        IDirect3D9Hook(IDirect3D9Hook&&) = delete;
        IDirect3D9Hook& operator=(const IDirect3D9Hook&) = delete;
        IDirect3D9Hook& operator=(IDirect3D9Hook&&) = delete;

    public:

        explicit IDirect3D9Hook(IDirect3D9* pOrigInterface) noexcept;

        ~IDirect3D9Hook() noexcept;

    public:
        
        HRESULT __stdcall QueryInterface(REFIID riid, VOID** ppvObj) noexcept;
        ULONG __stdcall AddRef() noexcept;
        ULONG __stdcall Release() noexcept;
        HRESULT __stdcall RegisterSoftwareDevice(VOID* pInitializeFunction) noexcept;
        UINT __stdcall GetAdapterCount() noexcept;
        HRESULT __stdcall GetAdapterIdentifier(UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9* pIdentifier) noexcept;
        UINT __stdcall GetAdapterModeCount(UINT Adapter, D3DFORMAT Format) noexcept;
        HRESULT __stdcall EnumAdapterModes(UINT Adapter, D3DFORMAT Format, UINT Mode, D3DDISPLAYMODE* pMode) noexcept;
        HRESULT __stdcall GetAdapterDisplayMode(UINT Adapter, D3DDISPLAYMODE* pMode) noexcept;
        HRESULT __stdcall CheckDeviceType(UINT Adapter, D3DDEVTYPE DevType, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, BOOL bWindowed) noexcept;
        HRESULT __stdcall CheckDeviceFormat(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat) noexcept;
        HRESULT __stdcall CheckDeviceMultiSampleType(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SurfaceFormat, BOOL Windowed, D3DMULTISAMPLE_TYPE MultiSampleType, DWORD* pQualityLevels) noexcept;
        HRESULT __stdcall CheckDepthStencilMatch(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, D3DFORMAT RenderTargetFormat, D3DFORMAT DepthStencilFormat) noexcept;
        HRESULT __stdcall CheckDeviceFormatConversion(UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT SourceFormat, D3DFORMAT TargetFormat) noexcept;
        HRESULT __stdcall GetDeviceCaps(UINT Adapter, D3DDEVTYPE DeviceType, D3DCAPS9* pCaps) noexcept;
        HMONITOR __stdcall GetAdapterMonitor(UINT Adapter) noexcept;
        HRESULT __stdcall CreateDevice(UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDeviceInterface) noexcept;

    private:

        IDirect3D9* const pOrigInterface;

    };

private:

    static IDirect3D9* CALLBACK HookDirect3DCreate9(UINT SDKVersion) noexcept;

private:

    static bool initStatus;

    static std::mutex deviceMutex;
    static IDirect3D9* pDirectInterface;
    static IDirect3DDevice9* pDeviceInterface;
    static D3DPRESENT_PARAMETERS deviceParameters;

    static std::vector<DeviceInitCallback> deviceInitCallbacks;
    static std::vector<BeforeResetCallback> beforeResetCallbacks;
    static std::vector<BeginSceneCallback> beginSceneCallbacks;
    static std::vector<RenderCallback> renderCallbacks;
    static std::vector<EndSceneCallback> endSceneCallbacks;
    static std::vector<AfterResetCallback> afterResetCallbacks;
    static std::vector<DeviceFreeCallback> deviceFreeCallbacks;

    static Memory::JumpHookPtr hookDirect3DCreate9;

};