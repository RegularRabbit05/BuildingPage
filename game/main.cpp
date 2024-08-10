#include <raylib.h>
#include "trace.h"

struct AnimatedModel {
    Model model;
    ModelAnimation *anim;
    int count;
    int frame;
};

int main() {
    SetTraceLogCallback(TraceLogFunction);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_TRANSPARENT);
    InitWindow(1000, 500, "Construction in progress... Come back later!");
    SetExitKey(2);

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

    while (!WindowShouldClose()) {
        base.frame++;
        if (base.frame >= base.anim->frameCount) base.frame = 0;
        UpdateModelAnimation(base.model, *base.anim, base.frame);

        BeginDrawing();
        ClearBackground(BLANK);

        BeginMode3D(camera);
        DrawModel(base.model, (Vector3){0, 0, 0}, 1.0f, WHITE);
        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadModel(base.model);
    UnloadModelAnimations(base.anim, base.count);

    CloseWindow();
    return 0;
}