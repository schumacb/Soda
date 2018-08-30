
#include <QApplication>
#include <QDialog>

#include "ui_aboutdialog.h"

int main(int argc, char **argv) {

  QApplication app(argc, argv);

  QDialog* about_dialog = new QDialog(0);
  Ui::AboutDialog ui_about_dialog = Ui::AboutDialog();
  ui_about_dialog.setupUi(about_dialog);

  about_dialog.show();

  app.exec();

  return 0;
}
