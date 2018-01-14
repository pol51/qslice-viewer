#include "data.h"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QVariant>

#include <cstdio>

bool Data::load(const QString &filename)
{
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    fprintf(stderr, "cannot read '%s'\n", qPrintable(filename));
    return false;
  }

  QJsonParseError error;
  QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
  if (error.error != QJsonParseError::NoError)
  {
    fprintf(stderr, "cannot read json document: %s\n", qPrintable(error.errorString()));
    return false;
  }

  QJsonObject obj = doc.object();
  if (obj.contains("length"))
  {
    bool ok = false;
    _length = obj.value("length").toVariant().toLongLong(&ok);
    if (!ok)
    {
      fprintf(stderr, "cannot read valid length from 'length' attribute\n");
      return false;
    }
  }
  else
  {
    fprintf(stderr, "cannot find 'length' attribute\n");
    return false;
  }

  if (obj.contains("slices"))
  {
    _slices.clear();
    QJsonArray slices_array = obj.value("slices").toArray();
    for (const QJsonValue &value: slices_array)
    {
      Slice slice;
      QJsonObject slice_obj = value.toObject();
      slice.start = slice_obj["start"].toVariant().toLongLong();
      slice.length = slice_obj["length"].toVariant().toLongLong();
      slice.id = slice_obj["id"].toInt();
      _slices.append(slice);
    }
  }
  else
  {
    fprintf(stderr, "cannot find 'slices' attribute\n");
    return false;
  }

  return true;
}
