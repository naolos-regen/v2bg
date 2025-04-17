#include "raylib.h"

int	main(void)
{
	// This is a test for Borderless fullscreen that is put before main Window Manager by manipulating order
	InitWindow(GetScreenWidth(), GetScreenHeight(), "fcbh");
	Vector2 ballposition = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Vector2 bollspeed    = { 5.0, 4.0f };
	
	float ballradio = 20;
	int   frejmctx  = 0;
	SetTargetFPS(69);

	SetWindowState(FLAG_WINDOW_UNFOCUSED);
	ToggleBorderlessWindowed();

	while (!WindowShouldClose())
	{
		ballposition.x += bollspeed.x;
		ballposition.y += bollspeed.y;
		if ((ballposition.x >= (GetScreenWidth() - ballradio)) || (ballposition.x <= ballradio)) bollspeed.x *= -1.0f;
		if ((ballposition.y >= (GetScreenHeight() - ballradio)) || (ballposition.y <= ballradio)) bollspeed.y *= -1.0f;

		BeginDrawing();
		if (IsWindowState(FLAG_WINDOW_TRANSPARENT)) ClearBackground(BLANK);
		else ClearBackground(BLACK);
		DrawCircleV(ballposition, ballradio, MAROON);
		DrawRectangleLinesEx((Rectangle) { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, 4, BLACK);
		DrawCircleV(GetMousePosition(), 10, DARKBLUE);
		DrawFPS(10,10);
 	        DrawText(TextFormat("Screen Size: [%i, %i]", GetScreenWidth(), GetScreenHeight()), 10, 40, 10, GREEN);
		
		EndDrawing();
	}

	CloseWindow();

	return (0);
}
