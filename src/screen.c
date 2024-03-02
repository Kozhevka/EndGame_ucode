#include "screen.h"

const int referenceHeight = 1080;
const int referenceWight = 1920;

ScreenParameters currentScreenParemeters;

float GetScreenScale()
{
   return currentScreenParemeters.scaleFactor;
}

ScreenParameters GetScreenParameters()
{
    return currentScreenParemeters;
}

void ChangeGameResolution(int wight, int height)
{
    currentScreenParemeters.wight = wight;
    currentScreenParemeters.height = height;
    currentScreenParemeters.aspectRatio = wight / height;
    currentScreenParemeters.scaleFactor = wight / referenceWight;
}