#include "sound.h"

#include <QSound>

Sound::Sound(QString filename)
    :QObject()
{
    this->filename = filename;
    sound = new QSound(filename);
}

Sound::~Sound()
{
    delete sound;
}

void Sound::Play(bool infinite)
{
    Play("", infinite);
}

void Sound::Play(QString filename, bool infinite)
{
    if(infinite == true)
        sound->setLoops(QSound::Infinite);

    if(!filename.isEmpty())
        sound->play(filename);
    else
        sound->play();
}


void Sound::Stop()
{
    sound->stop();
}

bool Sound::IsPlaying()
{
    return !sound->isFinished();
}

void Sound::SetFilename(QString filename)
{
    this->filename = filename;
}

