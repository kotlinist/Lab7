#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowTitle("QDataWidgetMapper Example");

    db = new DB();
    db->connectToDB();

    this->setupModel(DEVICE,
                     QStringList() << "id"
                                   << "Имя хоста"
                                   << "IP адрес"
                                   << "MAC-адрес");
    this->createUI();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers) {
    // Производим инициализацию модели представления данных
    modelDevice = new QSqlTableModel(this);
    modelDevice->setTable(tableName);
    modelDevice->select();
    // Устанавливаем названия колонок в таблице с сортировкой данных
    for(int i = 0, j = 0; i < modelDevice->columnCount(); i++, j++) {
        modelDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void MainWindow::createUI() {
    ui->deviceTableView->setModel(modelDevice);    // Устанавливаем модель на TableView
    ui->deviceTableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->deviceTableView->setSelectionBehavior(QAbstractItemView::SelectRows); // Устанавливаем режим выделения лишь одной строки в таблице
    ui->deviceTableView->setSelectionMode(QAbstractItemView::SingleSelection); // Устанавливаем размер колонок по содержимому
    ui->deviceTableView->resizeColumnsToContents();
    ui->deviceTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); ui->deviceTableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->deviceTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotEditRecord(QModelIndex)));
}

// // Метод для активации диалога добавления записей
// void MainWindow::on_addDeviceButton_clicked() {
//     // Создаем диалог и подключаем его сигнал завершения работы к слоту обновления вида модели представления данных
//     Dialog *addDeviceDialog = new Dialog(); connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
//     // Выполняем запуск диалогового окна
//     addDeviceDialog->setWindowTitle("Добавить Устройство");
//     addDeviceDialog->exec();
// }

// Слот обновления модели представления данных
void MainWindow::slotUpdateModels()
{
    modelDevice->select();
}
// Метод для активации диалога добавления записей в режиме редактирования * с передачей индекса выбранной строки
void MainWindow::slotEditRecord(QModelIndex index)
{
    // Также создаем диалог и подключаем его сигнал завершения работы * к слоту обновления вида модели представления данных, но передаём * в качестве параметров строку записи
    Dialog *addDeviceDialog = new Dialog(index.row()); connect(addDeviceDialog, SIGNAL(signalReady()), this,
            SLOT(slotUpdateModel()));
    // Выполняем запуск диалогового окна
    addDeviceDialog->setWindowTitle("Редактировать Устройство"); addDeviceDialog->exec();
}

void MainWindow::on_addBtn_clicked() {
    // Создаем диалог и подключаем его сигнал завершения работы к слоту обновления вида модели представления данных
    Dialog *addDeviceDialog = new Dialog(); connect(addDeviceDialog, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));
    // Выполняем запуск диалогового окна
    addDeviceDialog->setWindowTitle("Добавить Устройство");
    addDeviceDialog->exec();
}

