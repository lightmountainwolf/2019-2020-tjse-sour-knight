#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

extern bool soundCondition;
extern bool musicCondition;
//void init();
void playMusic(const char* music, const char* sound, bool loop, int command);
void playSound(const char* sound, int command);
/*class Sound
{
private:
    bool soundCondition;
    bool musicCondition;
public:
    static Sound Sound::createSound();
    void Sound::init();
    void Sound::playMusic(const char *music, const char* sound, bool loop,int command);
    void Sound::playSound(const char* sound,int command);
}£»
*/
#endif // __SOUND_H__

//#define __SOUND_H__