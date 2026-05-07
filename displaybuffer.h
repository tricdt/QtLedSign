#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#include <QObject>
#include <QImage>
#include <QPixmap>



class DisplayBuffer : public QObject
{
    Q_OBJECT
public:
    explicit DisplayBuffer(QObject *parent = nullptr);
    ~DisplayBuffer();
    const QPixmap& buffer()const;
    QSize capacity() const;
    QSize size() const;
    void setSize(const QSize &value);
Q_SIGNALS:
private:
    QPixmap _buffer;
    QSize _capacity;
    QSize _size; 
};

#endif // DISPLAYBUFFER_H

/*
class DisplayBuffer {
private:
    QImage _buffer;
    QSize _capacity;
    QSize _size;

public:
    DisplayBuffer()
        : _buffer(0, 0, QImage::Format_ARGB32_Premultiplied),
          _capacity(0, 0),
          _size(0, 0) {}

    const QImage& buffer() const { return _buffer; }
    QSize capacity() const { return _capacity; }
    QSize size() const { return _size; }

    void setSize(const QSize& value) {
        _size = value;
        if (value.width() <= _capacity.width() &&
            value.width() >= _capacity.width() / 4 &&
            value.height() <= _capacity.height() &&
            value.height() >= _capacity.height() / 4) {
            return;
        }

        dispose();

        _capacity = QSize(value.width() * 2, value.height() * 2);
        _buffer = QImage(_capacity.width(), _capacity.height(),
                         QImage::Format_ARGB32_Premultiplied);
        _buffer.fill(Qt::transparent);
    }

    void clear(const QColor& color) {
        QPainter p(&_buffer);
        p.fillRect(QRect(QPoint(0,0), _size), color);
    }

    void clearColumn(int offset, int width, const QColor& color) {
        QPainter p(&_buffer);
        p.fillRect(QRect(offset, 0, width, _size.height()), color);
    }

    void dispose() {
        _buffer = QImage();
        _capacity = QSize(0,0);
        _size = QSize(0,0);
    }
};

*/

/*
class DisplayBuffer {
private:
    QImage _buffer;
    QSize _capacity;
    QSize _size;
    QBrush _lineColor;

public:
    DisplayBuffer()
        : _buffer(0, 0, QImage::Format_ARGB32_Premultiplied),
          _capacity(0, 0),
          _size(0, 0),
          _lineColor(QColor(Qt::darkSlateGray)) {}

    const QImage& buffer() const { return _buffer; }
    QSize capacity() const { return _capacity; }
    QSize size() const { return _size; }

    void setSize(const QSize& value) {
        _size = value;
        if (value.width() <= _capacity.width() &&
            value.width() >= _capacity.width() / 4 &&
            value.height() <= _capacity.height() &&
            value.height() >= _capacity.height() / 4) {
            return;
        }

        _capacity = QSize(value.width() * 2, value.height() * 2);

        // tạo buffer mới
        QImage newBuffer(_capacity.width(), _capacity.height(),
                         QImage::Format_ARGB32_Premultiplied);
        newBuffer.fill(_lineColor.color());

        // copy nội dung cũ nếu có
        if (!_buffer.isNull()) {
            QPainter p(&newBuffer);
            int copyW = qMin(_buffer.width(), _size.width());
            int copyH = qMin(_buffer.height(), _size.height());
            p.drawImage(QRect(0, 0, copyW, copyH), _buffer,
                        QRect(0, 0, copyW, copyH));
        }

        _buffer = newBuffer;
    }

    void clear(const QBrush& color) {
        QPainter p(&_buffer);
        p.fillRect(QRect(QPoint(0,0), _size), color);
    }

    void draw(const std::function<void(QPainter&)>& drawAction) {
        QPainter p(&_buffer);
        drawAction(p);
    }

    void dispose() {
        _buffer = QImage();
        _capacity = QSize(0,0);
        _size = QSize(0,0);
    }
};

*/
