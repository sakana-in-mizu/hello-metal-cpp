#include "app_delegate.h"

#include "view_delegate.h"

AppDelegate::~AppDelegate() {
    m_window->release();
    m_view->release();
    m_device->release();

    m_view_delegate.reset();
}

void AppDelegate::applicationWillFinishLaunching(NS::Notification *notification) {
    NS::Application *app = reinterpret_cast<NS::Application *>(notification->object());
    app->setActivationPolicy(NS::ActivationPolicy::ActivationPolicyRegular);
}

void AppDelegate::applicationDidFinishLaunching(NS::Notification *notification) {
    CGRect frame = (CGRect) {{100.0, 100.0}, {640.0, 480.0}};

    m_window = NS::Window::alloc()->init(
        frame, NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled, NS::BackingStoreBuffered, false
    );

    m_device = MTL::CreateSystemDefaultDevice();

    m_view = MTK::View::alloc()->init(frame, m_device);
    m_view->setColorPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);
    m_view->setClearColor(MTL::ClearColor::Make(1.0, 1.0, 0.6, 1.0));

    m_view_delegate = std::make_unique<ViewDelegate>(m_device);
    m_view->setDelegate(m_view_delegate.get());

    m_window->setContentView(m_view);
    m_window->setTitle(NS::String::string("Window", NS::StringEncoding::UTF8StringEncoding));
    m_window->makeKeyAndOrderFront(nullptr);

    NS::Application *app = reinterpret_cast<NS::Application *>(notification->object());
    app->activateIgnoringOtherApps(true);
}

bool AppDelegate::applicationShouldTerminateAfterLastWindowClosed(NS::Application *sender) { return true; }