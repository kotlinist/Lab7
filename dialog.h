#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
// #include <QRegExp>
#include <QRegularExpression>
// #include <QRegExpValidator>
#include <QRegularExpressionValidator>
#include <db.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(int row = -1, QWidget *parent = nullptr);
    ~Dialog();

signals:
    void signalReady();

private slots:
    void updateButtons(int row);
    void on_btnCancel_clicked();
    void on_btnOk_clicked();

private:
    Ui::Dialog *ui;
    QSqlTableModel *model;
    QDataWidgetMapper *mapper;

    void setupModel();
    void createUI();
    void accept();
};

#endif // DIALOG_H
