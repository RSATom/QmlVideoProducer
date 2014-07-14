#pragma once

#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>

class DesktopVideoProducer : public QObject
{
    Q_OBJECT
public:
    static void registerQmlType();

    explicit DesktopVideoProducer( QObject *parent = 0 );
    ~DesktopVideoProducer();

    Q_PROPERTY( QAbstractVideoSurface* videoSurface READ videoSurface WRITE setVideoSurface )

    QAbstractVideoSurface* videoSurface() const;
    void setVideoSurface( QAbstractVideoSurface* s );

protected:
    void timerEvent( QTimerEvent* );

private:
    void closeSurface();

private:
    QAbstractVideoSurface* _surface;
    QVideoSurfaceFormat _format;
};
