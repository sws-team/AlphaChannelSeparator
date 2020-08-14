#include "imagewidget.h"

#include <QDropEvent>
#include <QMimeData>
#include <QDebug>
#include <QFileInfo>
#include <QPainter>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent)
{
    setAcceptDrops(true);
}

void ImageWidget::loadImage(const QString &fileName)
{
    const QFileInfo fileInfo(fileName);
    if (!fileInfo.exists())
        return;
    if (fileInfo.suffix() != "png")
        return;
    if (!image.load(fileName))
        return;
    m_fileName = fileName;
    update();
}

bool ImageWidget::convertImage() const
{
    const QFileInfo fileInfo(m_fileName);
    Q_DECL_CONSTEXPR int quality = 80;
    const QString basePath = fileInfo.path() + "/" +fileInfo.baseName();
    const QString destinationFileName = basePath + ".jpg";
    const QString alphaChannelDestinationFileName = basePath + "_alpha.jpg";

    QImage destinationImage = image;
    QImage alphaChannelImage = image;
    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            const QRgb rgb = image.pixel(x, y);
            const int alpha = qAlpha(rgb);
            if (alpha == 0)
                destinationImage.setPixel(x, y, rgb);
            else
            {
                destinationImage.setPixel(x, y, rgb);
            }

            const int alphaValue = alpha == 0 ? 0 : 255;
            alphaChannelImage.setPixel(x, y, qRgb(alphaValue, alphaValue, alphaValue));
        }
    }
    const bool alphaChannelResult = alphaChannelImage.save(alphaChannelDestinationFileName, Q_NULLPTR, quality);
    const bool result = destinationImage.save(destinationFileName, Q_NULLPTR, quality);
    return result && alphaChannelResult;
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const QRect drawRect = event->rect();
    painter.fillRect(drawRect, Qt::cyan);
    if (!image.isNull())
        painter.drawImage(drawRect, image.scaled(drawRect.size()), drawRect);
}

void ImageWidget::dropEvent(QDropEvent *event)
{
    if (!event->mimeData()->hasUrls())
        return;

    const QList<QUrl> urlList = event->mimeData()->urls();
    if (urlList.isEmpty())
        return;

    loadImage(urlList.first().toLocalFile());
}

void ImageWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

QString ImageWidget::fileName() const
{
    return m_fileName;
}
