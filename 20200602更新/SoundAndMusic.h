#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

extern bool soundCondition;
extern bool musicCondition;
//void init();
void playMusic(const char* music, bool loop, int command);
void playMusic(const char* music, bool loop);
void playSound(const char* sound, int command);
void playSound(const char* sound);

#endif // __SOUND_H__

//#define __SOUND_H__