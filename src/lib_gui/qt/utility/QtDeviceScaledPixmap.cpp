#include "QtDeviceScaledPixmap.h"

#include <QApplication>

#include "utilityQt.h"

static QImage mirrorImage(QImage image)
{
	#if QT_VERSION > QT_VERSION_CHECK(6, 9, 0)
		image.flip();
	#else
		image.mirror();
	#endif

	#if QT_VERSION >= QT_VERSION_CHECK(6, 13, 0)
		#warning "QImage::mirror call can be removed"
	#endif

	return image;
}

qreal QtDeviceScaledPixmap::devicePixelRatio()
{
	QApplication* app = dynamic_cast<QApplication*>(QCoreApplication::instance());
	return app->devicePixelRatio();
}

QtDeviceScaledPixmap::QtDeviceScaledPixmap() = default;

QtDeviceScaledPixmap::QtDeviceScaledPixmap(const QString& filePath): m_pixmap(filePath)
{
	m_pixmap.setDevicePixelRatio(devicePixelRatio());
}

QtDeviceScaledPixmap::~QtDeviceScaledPixmap() = default;

const QPixmap& QtDeviceScaledPixmap::pixmap() const
{
	return m_pixmap;
}

qreal QtDeviceScaledPixmap::width() const
{
	return m_pixmap.width() / devicePixelRatio();
}

qreal QtDeviceScaledPixmap::height() const
{
	return m_pixmap.height() / devicePixelRatio();
}

void QtDeviceScaledPixmap::scaleToWidth(int width)
{
	m_pixmap = m_pixmap.scaledToWidth(
		static_cast<int>(width * devicePixelRatio()), Qt::SmoothTransformation);
	m_pixmap.setDevicePixelRatio(devicePixelRatio());
}

void QtDeviceScaledPixmap::scaleToHeight(int height)
{
	m_pixmap = m_pixmap.scaledToHeight(
		static_cast<int>(height * devicePixelRatio()), Qt::SmoothTransformation);
	m_pixmap.setDevicePixelRatio(devicePixelRatio());
}

void QtDeviceScaledPixmap::mirror()
{
	m_pixmap = QPixmap::fromImage(mirrorImage(m_pixmap.toImage()));
	m_pixmap.setDevicePixelRatio(devicePixelRatio());
}

void QtDeviceScaledPixmap::colorize(QColor color)
{
	m_pixmap = utility::colorizePixmap(m_pixmap, color);
}
