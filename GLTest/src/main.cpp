#include <core/EntryPoint.h>

#include "tests/TestClearColor.h"

Application* CreateApplication() {
    Application* app = new Application("OpenGLRenderer", 960, 540, true, true);
    app->PushLayer(new Test::TestLayer());
    return app;
}