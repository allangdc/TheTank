#ifndef SOUND_H
#define SOUND_H

#include <QString>
#include <QObject>

class QSound;

class Sound: public QObject
{
    Q_OBJECT
public:
    explicit Sound(QString filename = "");
    ~Sound();
    void Play(bool infinite);
    void Play(QString filename, bool infinite);
    void Stop();
    bool IsPlaying();
    void SetFilename(QString filename);
private:
    QString filename;
    QSound *sound;
};

#endif // SOUND_H
