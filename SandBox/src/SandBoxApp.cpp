
#include <iostream>
#include "Minity.h"


class SandBoxApp :public Minity::Application
{
private:
    /* data */
public:
    SandBoxApp();
    ~SandBoxApp();
};

SandBoxApp::SandBoxApp()
{
}

SandBoxApp::~SandBoxApp()
{
}


Minity::Application* Minity::CreateApplication()
{
    return new SandBoxApp();
}