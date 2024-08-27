#pragma once

#include <memory>

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

class AppDelegate : public NS::ApplicationDelegate {
public:
    virtual ~AppDelegate() override;

    virtual void applicationWillFinishLaunching(NS::Notification *notification) override;
    virtual void applicationDidFinishLaunching(NS::Notification *notification) override;
    virtual bool applicationShouldTerminateAfterLastWindowClosed(NS::Application *sender) override;

private:
    NS::Window  *m_window {};
    MTK::View   *m_view {};
    MTL::Device *m_device {};

    std::unique_ptr<MTK::ViewDelegate> m_view_delegate {};
};