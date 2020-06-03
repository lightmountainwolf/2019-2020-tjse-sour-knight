#include "SoundAndMusic.h"
using namespace CocosDenshion;

//when you want to adjust the music and the sound, please first #include "SoundAndMusic.h" 
//如果想要调整音乐和音效，请先#include "SoundAndMusic.h"

//string music输入音乐路径;如果要循环，则bool loop输入true
//command直接传入soundToggleMenuItem->getSelectedIndex()，on->off的时候等于1
bool soundCondition = true;
bool musicCondition = true;

void playMusic(const char *music, bool loop, int command)
{
    if (command == 1)
    {
        musicCondition = false;
    }
    else {
        musicCondition = true;
    }

    if(musicCondition == true)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(music, loop);
    }
    else
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(music);
    }
}

void playMusic(const char* music, bool loop)
{
    if (musicCondition == true)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(music, loop);
    }
    else
    {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(music);
    }
}

//sound写文件路径;command直接传入soundToggleMenuItem->getSelectedIndex()，on->off的时候等于1
void playSound(const char* sound,int command)
{
    if (soundCondition == true)
    {
        SimpleAudioEngine::getInstance()->playEffect(sound);
    }

    if (command == 1)
    {
        soundCondition = false;
    }
    else
    {
        soundCondition = true;
    }
}

void playSound(const char* sound)
{
    if (soundCondition == true)
    {
        SimpleAudioEngine::getInstance()->playEffect(sound);
    }
}