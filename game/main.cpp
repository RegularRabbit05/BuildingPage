#include <raylib.h>
#include "trace.hpp"

struct AnimatedModel {
    Model model;
    ModelAnimation *anim;
    int count;
    int frame;
};

int main() {
    SetTraceLogCallback(TraceLogFunction);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_TRANSPARENT | FLAG_MSAA_4X_HINT | FLAG_INTERLACED_HINT);
    InitWindow(1000, 500, "Construction in progress... Come back later!");
    SetExitKey(2);
    SetTargetFPS(24);

    Font font = LoadFont("Graphics/JetBrainsMono-ExtraBold.ttf");
    SetTextureFilter(font.texture, TEXTURE_FILTER_ANISOTROPIC_16X);

    Camera camera = { 
        {4.4, 5, 10},
        {0, 0, 0},
        {0, 1, 0},
        45,
        CAMERA_PERSPECTIVE
    };

    AnimatedModel base;
    base.model = LoadModel("Graphics/base.glb");
    base.anim = LoadModelAnimations("Graphics/base.glb", &base.count);

    AnimatedModel cube[2];
    cube[0].model = LoadModel("Graphics/cube.glb");
    cube[0].anim = LoadModelAnimations("Graphics/cube.glb", &cube[0].count);

    cube[1].model = cube[0].model;
    cube[1].anim = cube[0].anim;
    cube[1].frame = (cube[1].anim->frameCount / 2);

    const char *txt[] = {
        "Hello World",
        "We're working on this page, come back later!",
    };

    while (!WindowShouldClose()) {
        const float scrX = (float) GetScreenWidth(), scrY = (float) GetScreenHeight();

        base.frame++;
        if (base.frame >= base.anim->frameCount) base.frame = 0;
        UpdateModelAnimation(base.model, *base.anim, base.frame);

        BeginDrawing();
        ClearBackground(BLANK);

        BeginMode3D(camera);
        DrawModel(base.model, (Vector3){0, 0, 0}, 1.0f, WHITE);
        for (int i = 0; i < 2; i++) {
            cube[i].frame++;
            if (cube[i].frame >= cube[i].anim->frameCount) cube[i].frame = 0;
            UpdateModelAnimation(cube[i].model, *cube[i].anim, cube[i].frame);
            DrawModel(cube[i].model, (Vector3){0, 0, 0}, 1.0f, WHITE);
        }
        EndMode3D();

        for (float fontSize = 50, m = 0.f; fontSize > 0; fontSize--) {
            m = MeasureTextEx(font, txt[1], fontSize, 0).x;
            if (m > scrX-scrX/10*2 && fontSize > 4) continue;
            DrawTextEx(font, txt[1], (Vector2){scrX-scrX/10-m, scrY-scrY/10-fontSize/2}, (int) fontSize, 0, BLACK);
            m = MeasureTextEx(font, txt[0], fontSize, 0).x;
            DrawTextEx(font, txt[0], (Vector2){scrX-scrX/10-m, scrY-scrY/10-fontSize/2-fontSize}, (int) fontSize, 0, BLACK);
            break;
        }

        EndDrawing();
    }

    UnloadModel(base.model);
    UnloadModelAnimations(base.anim, base.count);

    UnloadModel(cube[0].model);
    UnloadModelAnimations(cube[0].anim, cube[0].count);

    UnloadFont(font);

    CloseWindow();
    return 0;
}