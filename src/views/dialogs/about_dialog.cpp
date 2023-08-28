#include "about_dialog.h"
#include "ui_about_dialog.h"

using namespace NetSim;

About_Dialog::About_Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::About_Dialog) {
  ui->setupUi(this);
  QTextCursor cursor = QTextCursor(ui->full_description_textBox->document());
  cursor.movePosition(QTextCursor::EndOfLine);
  ui->full_description_textBox->setTextCursor(cursor);
  cursor.insertText(QCoreApplication::applicationVersion());
}

About_Dialog::~About_Dialog() { delete ui; }
