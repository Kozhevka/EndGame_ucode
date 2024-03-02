

typedef struct
{
    int wight;
    int height;
    float scaleFactor;
    float aspectRatio;
} ScreenParameters;

float GetScreenScale();
ScreenParameters GetScreenParameters();

void ChangeGameResolution(int wight, int height);
