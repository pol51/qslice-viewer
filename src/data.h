#pragma once

#include <QtCore/QList>
#include <QtCore/QString>

class Data
{
  public:
    typedef struct {
      qint64 start = 0;
      qint64 length = 0;
      int id = 0;
    } Slice;

  public:
    bool load(const QString &filename);

    qint64 length() const { return _length; }
    const QList<Slice> slices() const { return _slices; }

  protected:
    qint64 _length = 0;
    QList<Slice> _slices;
};
