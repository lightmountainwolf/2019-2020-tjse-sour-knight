#include "Settings/SoundAndMusic.h"
using namespace CocosDenshion;

//when you want to adjust the music and the sound, please first #include "SoundAndMusic.h" 
//如果想要调整音乐和音效，请先#include "SoundAndMusic.h"

//string music输入音乐路径;如果要循环，则bool loop输入true
//command直接传入soundToggleMenuItem->getSelectedIndex()，on->off的时候等于1
bool soundCondition = true;
bool musicCondition = true;
bool doContinueGame = false;
float musicVolume = 1;
float soundVolumn = 1;

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
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);
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
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(musicVolume);
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
        SimpleAudioEngine::getInstance()->setEffectsVolume(soundVolumn);
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
        SimpleAudioEngine::getInstance()->setEffectsVolume(soundVolumn);
    }
}

void MusicVolumnIncrease()
{
    float OrigionVolumnMusic = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    float volumnMusic = OrigionVolumnMusic + 0.1;
    if (volumnMusic > 1)
    {
        volumnMusic = 1;
    }
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volumnMusic);
    musicVolume = volumnMusic;

}
void MusicVolumnDecrease()
{
    float OrigionVolumnMusic = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
    float volumnMusic  = OrigionVolumnMusic - 0.1;
    if (volumnMusic < 0)
    {
        volumnMusic = 0;
    }
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volumnMusic);
    musicVolume = volumnMusic;
}

void SoundVolumnIncrease()
{
    float OrigionVolumnSound = SimpleAudioEngine::getInstance()->getEffectsVolume();
    float volumnSound = OrigionVolumnSound +0.1;
    if (volumnSound > 1)
    {
        volumnSound = 1;
    }
    SimpleAudioEngine::getInstance()->setEffectsVolume(volumnSound);
    soundVolumn = volumnSound;
    //SimpleAudioEngine::getInstance()->setEffectsVolume(1);
}

void SoundVolumnDecrease()
{
    float OrigionVolumnSound = SimpleAudioEngine::getInstance()->getEffectsVolume();
    float volumnSound = OrigionVolumnSound-0.1;
    if (volumnSound < 0)
    {
        volumnSound = 0;
    }
    soundVolumn = volumnSound;
    SimpleAudioEngine::getInstance()->setEffectsVolume(volumnSound);
   // SimpleAudioEngine::getInstance()->setEffectsVolume(0);
}