#include "pch.h"

static __declspec(noreturn) void ExitSDLError()
{
	LOG_ERROR("SDL Error: %s\n", SDL_GetError());
	exit(1);
}

static SDL_Window* window{};
static SDL_Renderer* renderer{};
static bool isRunning = true;

static bool RenderClear(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
{
	if (SDL_SetRenderDrawColor(renderer, r, g, b, a) != 0)
		return false;

	return SDL_RenderClear(renderer) == 0;
}

static bool RenderFillRect(const SDL_Rect& Rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
{
	if (SDL_SetRenderDrawColor(renderer, r, g, b, a) != 0)
		return false;

	return SDL_RenderFillRect(renderer, &Rect) == 0;
}

static void MainLoop(float timeStep)
{
	SDL_Event event{};
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
		}
	}

	if (!RenderClear(222, 222, 222))
		ExitSDLError();

	const int size = 50;
	SDL_Rect square{ 0, 0, size, size };
	Uint32 mouseState = SDL_GetMouseState(&square.x, &square.y);
	square.x -= size / 2;
	square.y -= size / 2;

	if (!RenderFillRect(square, 77, 77, 77))
		ExitSDLError();

	SDL_RenderPresent(renderer);

	LOG_INFO("Rendering took %.2f ms.\n", timeStep);
}

static int MainEntry(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ExitSDLError();

	window = SDL_CreateWindow("SDLSudoku", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	if (window == NULL)
		ExitSDLError();

	renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
		ExitSDLError();

	std::chrono::time_point start = std::chrono::steady_clock::now();
	while (isRunning)
	{
		const std::chrono::time_point now = std::chrono::steady_clock::now();
		const size_t Nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
		const float Milliseconds = static_cast<float>(Nanoseconds) / 1000000.0f;
		MainLoop(Milliseconds);
		start = now;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

#if NDEBUG
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return MainEntry(__argc, __argv);
}
#else
int main(int argc, char** argv)
{
	return MainEntry(argc, argv);
}
#endif // NDEBUG
