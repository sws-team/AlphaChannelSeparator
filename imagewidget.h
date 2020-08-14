#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = Q_NULLPTR);

    QString fileName() const;

public Q_SLOTS:
    void loadImage(const QString& fileName);
    bool convertImage() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;

private:
    QString m_fileName;
    QImage image;
};

#endif // IMAGEWIDGET_H
