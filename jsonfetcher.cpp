#include "jsonfetcher.h"

JsonFetcher::JsonFetcher(QTableView *tableView, QObject *parent) : QObject(parent), tableView(tableView) {
    connect(&manager, &QNetworkAccessManager::finished, this, &JsonFetcher::onFinished);
}

void JsonFetcher::fetch(const QUrl &url) {
    QNetworkRequest request(url);
    manager.get(request);
}

void JsonFetcher::onFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        if (jsonDoc.isArray()) {
            QJsonArray jsonArray = jsonDoc.array();
            QStandardItemModel *model = new QStandardItemModel(jsonArray.size(), 3, this);
            model->setHorizontalHeaderLabels({ "Date", "Commit", "Description"});

            for (int i = 0; i < jsonArray.size(); ++i) {
                QJsonObject obj = jsonArray[i].toObject();
                QStandardItem *dateItem = new QStandardItem(obj["date"].toString());
                QStandardItem *commitItem = new QStandardItem(obj["commit"].toString().left(8));
                QStandardItem *descriptionItem = new QStandardItem(obj["description"].toString());

                // Ustawienie flag, aby elementy były tylko do odczytu
                dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
                commitItem->setFlags(commitItem->flags() & ~Qt::ItemIsEditable);
                descriptionItem->setFlags(descriptionItem->flags() & ~Qt::ItemIsEditable);

                model->setItem(i, 0, dateItem);
                model->setItem(i, 1, commitItem);
                model->setItem(i, 2, descriptionItem);
            }

            tableView->setModel(model);

            // Ustawienie rozmiaru kolumn
            tableView->setColumnWidth(0, 140); // Commit
            tableView->setColumnWidth(1, 90); // Date
            tableView->setColumnWidth(2, 400); // Description

            // Alternatywnie, można użyć resizeColumnsToContents() do automatycznego dopasowania rozmiaru kolumn
            // tableView->resizeColumnsToContents();
        }
    }
    reply->deleteLater();
}
