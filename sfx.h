#include<iostream>
#include<conio.h>
#include<string>
#include <random>
#include<windows.h>
#include <chrono>
#include <thread>
#pragma comment (lib, "winmm.lib")

using namespace std;


void music() {
	waveOutSetVolume(0, 0x1000);
	PlaySound(TEXT("./sfx/ost.wav"), NULL, SND_ASYNC | SND_LOOP);
}

