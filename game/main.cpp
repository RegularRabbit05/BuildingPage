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
    SetTargetFPS(24);

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
    cube[1].model = LoadModel("Graphics/cube.glb");
    cube[1].anim = LoadModelAnimations("Graphics/cube.glb", &cube[1].count);
    cube[1].frame = (cube[1].anim->frameCount / 2);

    while (!WindowShouldClose()) {
        base.frame++;
        if (base.frame >= base.anim->frameCount) base.frame = 0;
        UpdateModelAnimation(base.model, *base.anim, base.frame);
        cube[0].frame++;
        if (cube[0].frame >= cube[0].anim->frameCount) cube[0].frame = 0;
        UpdateModelAnimation(cube[0].model, *cube[0].anim, cube[0].frame);
        cube[1].frame++;
        if (cube[1].frame >= cube[1].anim->frameCount) cube[1].frame = 0;
        UpdateModelAnimation(cube[1].model, *cube[1].anim, cube[1].frame);

        BeginDrawing();
        ClearBackground(BLANK);

        BeginMode3D(camera);
        DrawModel(base.model, (Vector3){0, 0, 0}, 1.0f, WHITE);
        DrawModel(cube[0].model, (Vector3){0, 0, 0}, 1.0f, WHITE);
        DrawModel(cube[1].model, (Vector3){0, 0, 0}, 1.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }

    UnloadModel(base.model);
    UnloadModelAnimations(base.anim, base.count);

    for (int i = 0; i < 2; i++) {
        UnloadModel(cube[i].model);
        UnloadModelAnimations(cube[i].anim, cube[i].count);
    }

    CloseWindow();
    return 0;
}