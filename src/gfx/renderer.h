#pragma once
// Backend interface: Metal on iOS, Direct3D 8 on Windows.
class IRenderer {
public:
    virtual ~IRenderer() {}
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    // TODO: UploadMesh, UploadTexture, DrawMesh, DrawText
};
