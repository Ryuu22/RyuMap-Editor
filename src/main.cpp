#include "raylib.h"
#include "rmapfs.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

int main(int argc, char const *argv[])
{
	// Initialization
    //--------------------------------------------------------------------------------------
      
    const int screenWidth = 1440;
    const int screenHeight = 900;

    bool dropDown001EditMode = false;
    int dropdownBox001Active = 0;

    rmapfs::MapVector mapIndex[9];

    mapIndex[0] = rmapfs::MapVector(0,0,0);
    mapIndex[5] = rmapfs::MapVector(1,1,0);

    InitWindow(screenWidth, screenHeight, "rmap editor");

    rmapfs::Map currentMap;
    currentMap.loadMap();

    Texture2D tilemap = LoadTexture("../resources/tilemap.png");        // Texture loading


    Camera2D camera = { 0 };
    camera.target = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    bool zoomLock = false;



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        // Camera zoom controls

        if(!zoomLock)
        {
            camera.target = GetMousePosition();
            camera.zoom += ((float)GetMouseWheelMove()*0.05f);
        }

        if (IsKeyPressed(KEY_Z))zoomLock = !zoomLock;

        if (IsKeyPressed(KEY_F)) ToggleFullscreen();




        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        // Camera reset (zoom and rotation)
        if (IsKeyPressed(KEY_R))
        {
            camera.zoom = 1.0f;
            camera.rotation = 0.0f;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Ryu Map Editor", 190, 200, 20, LIGHTGRAY);

        BeginMode2D(camera);

            currentMap.draw(mapIndex, tilemap);

        EndMode2D();

        GuiStatusBar((Rectangle){ 0, screenHeight - 20, screenWidth, 20 }, "This is a status bar");
        GuiStatusBar((Rectangle){ 0, 0, screenWidth, 20 }, "This is a status bar");

        int dactive = 0;
        int *active = &dactive;

        //GuiDropdownBox((Rectangle){ 0, 0, 200, 20 }, "Dropdown", active, true);
        // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding  
        GuiSetStyle(DROPDOWNBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
        if (GuiDropdownBox((Rectangle){ 0, 0, 100, 20 }, "#01#save;#02#load;#03#quit", &dropdownBox001Active, dropDown001EditMode)) dropDown001EditMode = !dropDown001EditMode;
        GuiButton((Rectangle){ 0, 0, 100, 20 }, GuiIconText(RICON_FILE_SAVE, "File"));        

        DrawTexture(tilemap, 20, screenHeight / 2  - tilemap.height, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
	return 0;
}