#ifndef DB_H
#define DB_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DB_HOSTNAME "ExampleDataBase"
#define DB_NAME "Lab7.db"
#define DEVICE "DeviceTable"
#define DEVICE_HOSTNAME "Hostname"
#define DEVICE_IP "IP"
#define DEVICE_MAC "MAC"

class DB : public QObject {
    Q_OBJECT
public:
    explicit DB(QObject *parent = 0);
    ~DB();
    void connectToDataBase();
    bool inserIntoDeviceTable(const QVariantList &data);
    void connectToDB();
private:
    QSqlDatabase   db;
private:
    bool openDB();
    bool restoreDB();
    void closeDB();
    bool createDeviceTable();
};

#endif // DB_H
