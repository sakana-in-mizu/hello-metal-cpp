#pragma once

#include <memory>

#include <MetalKit/MetalKit.hpp>

class Renderer;

class ViewDelegate : public MTK::ViewDelegate {
public:
    ViewDelegate(MTL::Device *device);
    virtual ~ViewDelegate() override;

    virtual void drawInMTKView(MTK::View *view) override;

private:
    std::unique_ptr<Renderer> m_renderer {};
};