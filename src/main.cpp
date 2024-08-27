#include "control/app_delegate.h"

int main(int argc, char **argv) {
    NS::AutoreleasePool *pool = NS::AutoreleasePool::alloc()->init();
        
    AppDelegate controller;

    NS::Application *app = NS::Application::sharedApplication();
    app->setDelegate(&controller);
    app->run();

    pool->release();

    return 0;
}
