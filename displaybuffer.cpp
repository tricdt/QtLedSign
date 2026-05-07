#include "displaybuffer.h"

DisplayBuffer::DisplayBuffer(QObject *parent) : QObject{parent} {}

DisplayBuffer::~DisplayBuffer() {
  _buffer = QPixmap(); // reset buffer
  _capacity = QSize();
}

const QPixmap &DisplayBuffer::buffer() const
{
    return _buffer;
}

QSize DisplayBuffer::capacity() const
{
    return _capacity;
}

QSize DisplayBuffer::size() const
{
    return _size;
}

void DisplayBuffer::setSize(const QSize &value)
{
    _size = value;

    if (value.width() <= _capacity.width() && value.width() >= _capacity.width() / 4
        && value.height() <= _capacity.height() && value.height() >= _capacity.height() / 4) {
        return;
    }
    _buffer = QPixmap();
    _capacity = QSize();
    _capacity = QSize(value.width() * 2, value.height() * 2);
    _buffer = QPixmap(_capacity);
    _buffer.fill(Qt::transparent);

    // // Lưu lại nội dung cũ
    // QPixmap oldBuffer = _buffer;

    // // Tạo buffer mới với capacity gấp đôi
    // _capacity = QSize(value.width() * 2, value.height() * 2);
    // _buffer = QPixmap(_capacity);
    // _buffer.fill(_lineColor);

    // // Nếu có buffer cũ thì crop và vẽ lại
    // if (!oldBuffer.isNull()) {
    //     int w = std::min(oldBuffer.width(), _size.width());
    //     int h = std::min(oldBuffer.height(), _size.height());
    //     QPixmap cropped = oldBuffer.copy(0, 0, w, h);

    //     QPainter p(&_buffer);
    //     p.drawPixmap(0, 0, cropped);
    // }
}
