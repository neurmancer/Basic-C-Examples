

/*
                                Lol this project is **ABANDONED**


        Sup? this file gonna be something but not today... but you know what they say, Starting means you're half way there to finish

        What retro fuckery is this? 
            This program applies a CRT-style filter to your current display. That's the sole purpose of this app
            So I dunno what to include what to do or not...Only thing I know is that I know nothing...nah just fucking with ya, only think I know is I need raylib to start
        I won't go over why this include,define etc. banners exists you know if you've seen my other raylib projects etc



        Lol I made a blue-blocker for now...now it also has scanlines, noise, flicker,
        a rolling brightness bar, and a vignette. In the future I'll add

            -Vignette 
            - RBG mask 
            - Flickers/Hickups
            - Slight curved distortion (since yk... old monitors weren't flat)

        but current version is good to work at night so I made a tool for myself (which prbably KDE already has(good thing I use dwm))



        This project is on stand-by currently due to the shader thingies which I don't know (I guess I gotta smash keys for a .fs with OpenGL thingies(Still...I have no idea what I'm doing))


        First things first: this file requires fuck ton of flags so here are they 

        cc crtFilter.c -o crtFilter -lraylib -lX11 -lm -ldl -lpthread (crtFilter is the old name change it before compiling)

        second this is a copy-paste from a version that I've tried to build barrel distortion
        which ended up bending all the fucking screen till singularity and it was petrifying at 2AM now I wanna keep it.
        Hence, this is a broken attempt with a side of summoning Cthulhu


 
        Let me tell you the story...at 3AM me and my friend obssesed over making this work he wrote the all fragment shadders I handled the C 
        and just tried to make this little piece of shit work for hours that felt like days... then decided to buy an actual CRT monitor...

        This didn't work because of a restiction caused by the idea's core: capture the screen below the overlay 

        1- We tried momentarely disable the overlay to capture screen and then add the shaders - Flickered like on crack
        2- Tried to use with overlay and this abomination happens...

        To sum up: This program is now property of Cthulhu himself and I leave this as it is

*/





/* =============== INCLUDES ===============  */

#define Font X11Font
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#undef Font

#include <raylib.h>
#include <stdlib.h>




/* ================= DEFINES ====================  */

#define WIDTH 1200
#define HEIGHT 900

#define FPS 120     //Does that fuck with the layer beneath? the actual screen yk...I gotta match this with monitor's refresh rate probably



/* =============== EFFECTS =============== */

static const char *CRT_FRAGMENT_SHADER =
    "#version 330\n"
    "in vec2 fragTexCoord;\n"
    "uniform sampler2D texture0;\n"
    "uniform float uTime;\n"
    "uniform vec2 uResolution;\n"
    "out vec4 finalColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec2 uv = fragTexCoord * 2.0 - 1.0;\n"
    "    vec2 bentUv = uv * (1.0 + 0.16 * vec2(uv.y * uv.y, uv.x * uv.x));\n"
    "    vec2 sourceUv = bentUv * 0.5 + 0.5;\n"
    "    float inScreen = step(0.0, sourceUv.x) * step(sourceUv.x, 1.0)\n"
    "                   * step(0.0, sourceUv.y) * step(sourceUv.y, 1.0);\n"
    "    float vignette = smoothstep(0.40, 1.15, length(bentUv));\n"
    "\n"
    "    float scanline = 0.5 + 0.5 * sin(fragTexCoord.y * uResolution.y * 3.14159265);\n"
    "    float rollingBar = smoothstep(0.03, 0.0, abs(fragTexCoord.y - fract(uTime * 0.16)));\n"
    "    float flicker = 0.985 + 0.015 * sin(uTime * 55.0);\n"
    "\n"
    "    vec3 color = texture(texture0, sourceUv).rgb;\n"
    "    color *= mix(0.92, 1.0, scanline) * flicker;\n"
    "    color += rollingBar * 0.012;\n"
    "    color *= 1.0 - vignette * 0.18;\n"
    "\n"
    "    finalColor = vec4(color * inScreen, 1.0);\n"
    "}\n";

static unsigned char ChannelFromMask(unsigned long pixel, unsigned long mask)
{
    unsigned long lowestBit;
    unsigned long value;
    unsigned long maximum;

    if (mask == 0) return 0;

    lowestBit = mask & (~mask + 1);
    value = (pixel & mask) / lowestBit;
    maximum = mask / lowestBit;
    return (unsigned char)((value * 255) / maximum);
}

static bool CaptureDesktop(Display *display, int width, int height, Color *pixels)
{
    XImage *image = XGetImage(display, DefaultRootWindow(display), 0, 0,
                              (unsigned int)width, (unsigned int)height,
                              AllPlanes, ZPixmap);

    if (image == NULL) return false;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned long pixel = XGetPixel(image, x, y);
            Color *color = &pixels[y * width + x];

            color->r = ChannelFromMask(pixel, image->red_mask);
            color->g = ChannelFromMask(pixel, image->green_mask);
            color->b = ChannelFromMask(pixel, image->blue_mask);
            color->a = 255;
        }
    }

    XDestroyImage(image);
    return true;
}



int main(void)
{
    bool crtEnabled = true;
    Shader crtShader;
    Texture2D desktopTexture;
    Display *display;
    Color *desktopPixels;
    int timeLocation;
    int resolutionLocation;
    int captureWidth;
    int captureHeight;
    int lastCaptureFrame = -1;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MOUSE_PASSTHROUGH);
    InitWindow(WIDTH, HEIGHT, "CRT THINGY");
    ToggleBorderlessWindowed();
    SetTargetFPS(FPS);

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        CloseWindow();
        return 1;
    }

    captureWidth = DisplayWidth(display, DefaultScreen(display));
    captureHeight = DisplayHeight(display, DefaultScreen(display));
    desktopPixels = calloc((size_t)captureWidth * (size_t)captureHeight, sizeof(*desktopPixels));
    if (desktopPixels == NULL) {
        XCloseDisplay(display);
        CloseWindow();
        return 1;
    }

    desktopTexture = LoadTextureFromImage((Image){desktopPixels, captureWidth, captureHeight,
                                                  1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8});
    SetTextureFilter(desktopTexture, TEXTURE_FILTER_BILINEAR);

    crtShader = LoadShaderFromMemory(NULL, CRT_FRAGMENT_SHADER);
    timeLocation = GetShaderLocation(crtShader, "uTime");
    resolutionLocation = GetShaderLocation(crtShader, "uResolution");

    while (!WindowShouldClose()) {
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        float time = (float)GetTime();
        float resolution[2] = {(float)screenWidth, (float)screenHeight};
        int captureFrame = (int)(time * 30.0f);

        if (IsKeyPressed(KEY_ESCAPE)) break;
        if (IsKeyPressed(KEY_C)) crtEnabled = !crtEnabled;

        if (captureFrame != lastCaptureFrame) {
            SetWindowOpacity(0.0f);
            XSync(display, False);
            if (CaptureDesktop(display, captureWidth, captureHeight, desktopPixels)) {
                UpdateTexture(desktopTexture, desktopPixels);
            }
            SetWindowOpacity(1.0f);
            lastCaptureFrame = captureFrame;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (crtEnabled) {
            SetShaderValue(crtShader, timeLocation, &time, SHADER_UNIFORM_FLOAT);
            SetShaderValue(crtShader, resolutionLocation, resolution, SHADER_UNIFORM_VEC2);

            BeginShaderMode(crtShader);
            DrawTexturePro(desktopTexture,
                           (Rectangle){0, 0, (float)desktopTexture.width, (float)desktopTexture.height},
                           (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
                           (Vector2){0, 0}, 0.0f, WHITE);
            EndShaderMode();
        } else {
            DrawTexturePro(desktopTexture,
                           (Rectangle){0, 0, (float)desktopTexture.width, (float)desktopTexture.height},
                           (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
                           (Vector2){0, 0}, 0.0f, WHITE);
        }

        EndDrawing();
    }

    UnloadShader(crtShader);
    UnloadTexture(desktopTexture);
    free(desktopPixels);
    XCloseDisplay(display);
    CloseWindow();

    return(0);
}
