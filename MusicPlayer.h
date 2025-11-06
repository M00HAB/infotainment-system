#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QStringList>

class MusicPlayer : public QObject {
    Q_OBJECT
    Q_PROPERTY(qint64 position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(QString songName READ songName NOTIFY songNameChanged)

public:
    explicit MusicPlayer(QObject *parent = nullptr);

    Q_INVOKABLE void setVolume(int value);
    Q_INVOKABLE void playPause();
    Q_INVOKABLE void stopMusic();
    Q_INVOKABLE void nextTrack();
    Q_INVOKABLE void previousTrack();
    Q_INVOKABLE void setPosition(qint64 newPosition);


    QString currentSongTitle() const;
    QString currentArtist() const;

    qint64 position() const;
    qint64 duration() const;

    Q_INVOKABLE void playSong(const QString &filePath);
    QString songName() const { return m_songName; }


signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);

    void songNameChanged();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QStringList playlist;

    QString m_songName;

    int currentTrackIndex;
    void updateSongInfo();
};

#endif // MUSICPLAYER_H
