#ifndef DBTRENINGQUERY_H
#define DBTRENINGQUERY_H
#include "IDBManager.h"
#include <QSqlQuery>
#include <QVariantList>
#include <QString>
#include <QDateTime>
#include <QSqlError>
class DBTreningQuery : public IDBManager
{
public:
    DBTreningQuery(const QString& DBName, const QString& queryName) : IDBManager(DBName, queryName)
    {
        if(!_database.open()) qDebug()<<"database faild";
        setQuery(_queryName);
    }
    ~DBTreningQuery() override
    {
        _database.close();
    }
    void setQuery(const QString &queryName) override
    {
        if(!_database.isOpen() )qDebug()<<"database is not open insetQuery";
        QSqlQuery typingResultQuery;                                                 //" + queryName + "
        typingResultQuery.exec("CREATE TABLE IF NOT EXISTS " + queryName + " ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                               "exercise TEXT,"
                               "typing_speed INTEGER,"
                               "number_of_mistakes INTEGER,"
                               "datetime TEXT)");
        if (!typingResultQuery.isActive()) qDebug() << "Error: Could not create table " << queryName + ".";
    }
    void saveResult(const QVariantList& result) override
    {
        if(_database.open())
        {
            QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
            QSqlQuery query;
            query.prepare("INSERT INTO " + _queryName + " (exercise, typing_speed, number_of_mistakes, datetime) "
                          "VALUES (:exercise, :typingSpeed, :numberOfMistakes, :dateTime)");
            query.bindValue(":exercise", result[0].toString());
            query.bindValue(":typingSpeed", result[1].toInt());
            query.bindValue(":numberOfMistakes", result[2].toInt());
            query.bindValue(":dateTime", dateTime);

            if (query.exec())
            {
                qDebug() << "Data inserted successfully!";
            } else qDebug() << "Error inserting data:" << query.lastError().text();
        }else qDebug() << "Error: Could not open the database.";
    }
    QList<QVariantMap> getAllResults() const override
    {
        QList<QVariantMap> results;

        QSqlQuery query("SELECT * FROM " + _queryName);
        while (query.next()) {
            QVariantMap result;
            result["Exercise"] = query.value("exercise").toString();
            result["Typing speed"] = query.value("typing_speed").toInt();
            result["Number of mistakes"] = query.value("number_of_mistakes").toInt();
            result["Datetime"] = query.value("datetime").toDateTime();

            results.append(result);
        }
        return results;
    }

    QSqlQuery getQuery() const override
    {
        QSqlQuery query = QSqlQuery("SELECT * FROM " + _queryName);
        return query;
    }

};

#endif // DBTRENINGQUERY_H