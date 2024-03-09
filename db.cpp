#include "db.h"

DB::DB(QObject *parent) : QObject(parent) {};

DB::~DB() {};

void DB::connectToDB() {

    if(!QFile("/tmp/" DB_NAME).exists()) {
        this->restoreDB();
    } else {
        this->openDB();
    }

}

bool DB::restoreDB() {
    if(this->openDB()){
        if(!this->createDeviceTable()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных"; return false;
    }
    return false;
}

bool DB::openDB() {
    db = QSqlDatabase::addDatabase("QSQLITE"); db.setHostName(DB_HOSTNAME);
    db.setDatabaseName("/tmp/" DB_NAME); if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DB::closeDB() {
    db.close();
}

bool DB::createDeviceTable() {
    QSqlQuery query;
    if(!query.exec( "CREATE TABLE " DEVICE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    DEVICE_HOSTNAME  " VARCHAR(255)   NOT NULL,"
                    DEVICE_IP       " VARCHAR(16)    NOT NULL," DEVICE_MAC      " VARCHAR(18)    NOT NULL"
                    " )"
                    )) {
        qDebug() << "DataBase: error of create " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool DB::inserIntoDeviceTable(const QVariantList &data) {
    /* Запрос SQL формируется из QVariantList,
* в который передаются данные для вставки в таблицу. */
    QSqlQuery query;
    /* В начале SQL запрос формируется с ключами,
* которые потом связываются методом bindValue
* для подстановки данных из QVariantList
* */
    query.prepare("INSERT INTO " DEVICE " ( " DEVICE_HOSTNAME ", " DEVICE_IP ", " DEVICE_MAC " ) "
                  "VALUES (:Hostname, :IP, :MAC )"); query.bindValue(":Hostname",   data[0].toString());

    query.bindValue(":IP",         data[1].toString());
    query.bindValue(":MAC",        data[2].toString());
    // После чего выполняется запрос методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << DEVICE;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}




