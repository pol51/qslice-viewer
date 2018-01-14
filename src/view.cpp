#include "view.h"

#include "data.h"

#include <QtWidgets>

#include <algorithm>

#define HEIGHT 40

View::View(const Data &data) : QMainWindow()
{
  QHash<int, QBrush> brushes;
  {
    QList<int> ids;
    {
      QSet<int> unique_ids;
      for (const Data::Slice &slice: data.slices())
        unique_ids.insert(slice.id);
      ids = unique_ids.values();
      std::sort(ids.begin(), ids.end());
    }
    for (int i = ids.size(); --i >= 0; )
      brushes[ids[i]] = QBrush(QColor::fromHsv(int(360/ids.size() * i), 245, 245, 255));
  }

  QGraphicsScene *scene = new QGraphicsScene();
  scene->setSceneRect(QRectF(0, 0, data.length(), HEIGHT));
  for (const Data::Slice &slice: data.slices())
  {
    QGraphicsRectItem *item = scene->addRect(QRectF(slice.start, 0, slice.length, HEIGHT));
    item->setBrush(brushes[slice.id]);
  }
  scene->addRect(QRectF(0, 0, data.length(), HEIGHT));

  QGraphicsView *view = new QGraphicsView(scene);

  setCentralWidget(view);
}
