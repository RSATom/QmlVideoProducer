#include "DesktopVideoProducer.h"

#include <QtQml/qqml.h>

#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>

void DesktopVideoProducer::registerQmlType()
{
    // @uri DesktopVideoProducer
    qmlRegisterType<DesktopVideoProducer>(
        "DesktopVideoProducer", 0, 1,
        "DesktopVideoProducer" );
}

DesktopVideoProducer::DesktopVideoProducer( QObject *parent )
    : QObject( parent ), _surface( 0 )
{
    startTimer( 1000 / 15 ); //15 fps
}

DesktopVideoProducer::~DesktopVideoProducer()
{
    closeSurface();
}

QAbstractVideoSurface* DesktopVideoProducer::videoSurface() const
{
    return _surface;
}

void DesktopVideoProducer::setVideoSurface( QAbstractVideoSurface* s )
{
    closeSurface();
    _surface = s;
}

void DesktopVideoProducer::closeSurface()
{
    if( _surface && _surface->isActive() )
        _surface->stop();
}

void DesktopVideoProducer::timerEvent( QTimerEvent* )
{
    if( !_surface )
        return;

    QScreen* screen = QGuiApplication::primaryScreen();
    QDesktopWidget* desktop = QApplication::desktop();

    if( !screen || !desktop )
        return;

    //Получим screenshot и преобразуем в формат подходящий для QVideoFrame
    QPixmap screenPixmap = screen->grabWindow( desktop->screen()->winId() );
    QImage screenImage = screenPixmap.toImage();
    QVideoFrame::PixelFormat pixelFormat =
        QVideoFrame::pixelFormatFromImageFormat( screenImage.format() );

    //если формат кадра по какой-то причине поменялся (или это первый кадр)-
    //выполним повторную (первичную) инициализацию surface
    if( screenPixmap.size() != _format.frameSize() ||
        pixelFormat != _format.pixelFormat() )
    {
        closeSurface();
        _format =
            QVideoSurfaceFormat( screenPixmap.size(),
                                 pixelFormat );
        _surface->start( _format );
    }

    //передадим полученный кадр на отрисовку
    _surface->present( QVideoFrame( screenImage ) );
}
