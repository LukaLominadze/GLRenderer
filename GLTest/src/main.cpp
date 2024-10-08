#include "core/Application.h"

#include "tests/TestClearColor.h"

int main()
{
    Application app = Application("OpenGLRenderer", 960, 540, true);
    app.PushLayer(new Test::TestLayer());
    app.Run();
}