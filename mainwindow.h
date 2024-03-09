#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <db.h>
#include <dialog.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // void on_addDeviceButton_clicked();
    void slotUpdateModels();
    void slotEditRecord(QModelIndex index);
    void on_addBtn_clicked();

private:
    Ui::MainWindow *ui;
    DB *db;
    QSqlTableModel *modelDevice;
private:
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
};
#endif // MAINWINDOW_H
