#ifndef JSONFETCHER_H
#define JSONFETCHER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTableView>
#include <QStandardItemModel>

class JsonFetcher : public QObject {
    Q_OBJECT
public:
    JsonFetcher(QTableView *tableView, QObject *parent = nullptr);
    void fetch(const QUrl &url);

private slots:
    void onFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager manager;
    QTableView *tableView;
};

#endif // JSONFETCHER_H
