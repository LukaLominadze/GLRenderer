#include <core/EntryPoint.h>

#include "tests/TestClearColor.h"

Application* CreateApplication() {
    Application* app = new Application("OpenGLRenderer", 960, 540, true, false);
    app->PushLayer(new Test::TestLayer());
    return app;
}