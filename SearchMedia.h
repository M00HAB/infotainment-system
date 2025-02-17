#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "MusicController.h"

class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(MusicController* musicController READ musicController CONSTANT)
public:
    explicit Backend(QObject *parent = nullptr)
        : QObject(parent), m_musicController(new MusicController(this))
    {
        // Here you can initialize other controllers (e.g. SearchManager, LocationManager)
    }

    MusicController* musicController() const { return m_musicController; }

private:
    MusicController* m_musicController;
};

#endif // BACKEND_H
