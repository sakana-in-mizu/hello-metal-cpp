#include "view_delegate.h"

#include "view/renderer.h"

ViewDelegate::ViewDelegate(MTL::Device *device) { m_renderer = std::make_unique<Renderer>(device); }

ViewDelegate::~ViewDelegate() { m_renderer.reset(); }

void ViewDelegate::drawInMTKView(MTK::View *view) { m_renderer->draw(view); }