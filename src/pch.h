#pragma once

#define SDL_MAIN_HANDLED

#if NDEBUG
#define LOG_INFO(...) ((void)0)
#define LOG_ERROR(...) ((void)0)
#else
#define LOG_INFO(...) printf(__VA_ARGS__)
#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#endif // NDEBUG

#include <iostream>
#include <chrono>

#include <Windows.h>

#include <SDL.h>
