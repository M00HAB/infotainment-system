#include "MusicPlayer.h"
#include <QDebug>
#include <QUrl>
#include <QFileInfo>

MusicPlayer::MusicPlayer(QObject *parent) : QObject(parent), currentTrackIndex(0) {
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    // Set your predefined song paths (Make sure they exist)
    playlist << "C:/Users/Youssef/Downloads/Music/MARWAN PABLO - ATARY - مروان بابلو - أتاري (192 kbps).mp3"
             << "C:/Users/Youssef/Downloads/Music/Ruback - Close Your Eyes.mp3"
             << "C:/Users/Youssef/Music/song3.mp3";

    if (!playlist.isEmpty()) {
        player->setSource(QUrl::fromLocalFile(playlist[currentTrackIndex]));
    }
    connect(player, &QMediaPlayer::positionChanged, this, [&](qint64 pos) {
        emit positionChanged(pos);
    });

    connect(player, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
        emit durationChanged(dur);
    });
}

void MusicPlayer::playPause() {
    if (player->playbackState() == QMediaPlayer::PlayingState) {
        player->pause();
        qDebug() << "Music paused.";
    } else {
        player->play();
        qDebug() << "Playing:" << playlist[currentTrackIndex];
    }
    QFileInfo fileInfo(playlist[currentTrackIndex]);
    QString extractedName = fileInfo.baseName();
    m_songName = extractedName;
}

void MusicPlayer::setVolume(int value) {
    audioOutput->setVolume(value / 100.0);  // Convert to 0.0-1.0 scale
}

void MusicPlayer::stopMusic() {
    player->stop();
    qDebug() << "Music stopped.";
}

void MusicPlayer::nextTrack() {
    if (playlist.isEmpty()) return;

    currentTrackIndex = (currentTrackIndex + 1) % playlist.size();
    player->setSource(QUrl::fromLocalFile(playlist[currentTrackIndex]));
    player->play();
    qDebug() << "Now playing:" << playlist[currentTrackIndex];
}

void MusicPlayer::previousTrack() {
    if (playlist.isEmpty()) return;

    currentTrackIndex = (currentTrackIndex - 1 + playlist.size()) % playlist.size();
    player->setSource(QUrl::fromLocalFile(playlist[currentTrackIndex]));
    player->play();
    qDebug() << "Now playing:" << playlist[currentTrackIndex];
}

qint64 MusicPlayer::position() const {
    return player->position();
}

qint64 MusicPlayer::duration() const {
    return player->duration();
}

void MusicPlayer::setPosition(qint64 newPosition) {
    player->setPosition(newPosition);
    emit positionChanged(newPosition);
}

void MusicPlayer::playSong(const QString &filePath) {
    if (filePath.isEmpty()){
        qDebug() << "playSong() called with an empty file path!";
        return;
    };

    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();

    // Extract file name from the full path
    QFileInfo fileInfo(filePath);
    QString extractedName = fileInfo.baseName();  // Extract song name

    qDebug() << "Extracted song name (before encoding check):" << extractedName;

    if (extractedName.isEmpty()) {
        qDebug() << "Warning: QFileInfo returned an empty song name! Trying fallback.";
        extractedName = filePath.split("/").last().split(".").first();  // Manual extraction
    }

    m_songName = extractedName;
    qDebug() << "Final extracted song name:" << m_songName;

    emit songNameChanged();  // Notify QML
}
