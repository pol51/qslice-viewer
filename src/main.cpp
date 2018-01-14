#include <QtWidgets/QApplication>

#include <cstdlib>
#include <cstdio>

#include "data.h"
#include "view.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  if (argc != 2)
  {
    fprintf(stderr, "missing json input\n");
    return EXIT_FAILURE;
  }

  Data data;
  if (!data.load(argv[1]))
  {
    fprintf(stderr, "bad json input\n");
    return EXIT_FAILURE;
  }

  View view(data);
  view.show();

  return app.exec();
}
