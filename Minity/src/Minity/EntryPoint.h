#pragma once

extern Minity::Application* Minity::CreateApplication();

int main(int argc, char** argv)
{
    Minity::Application* app = Minity::CreateApplication();
    app->Run();
    delete app;
    return 0;
}
    


