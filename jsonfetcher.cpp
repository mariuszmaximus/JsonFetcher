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
            QStandardItemModel *model = new QStandardItemModel(jsonArray.size(), 4, this); // 4 columns including 'current'
            model->setHorizontalHeaderLabels({"Commit", "Date", "Description", "Current", "Filename"});

            for (int i = 0; i < jsonArray.size(); ++i) {
                QJsonObject obj = jsonArray[i].toObject();

                QString commit = obj["commit"].toString().left(8); // Przycięcie do 8 znaków
                QStandardItem *commitItem = new QStandardItem(commit);
                //
                QStandardItem *dateItem = new QStandardItem(obj["date"].toString());
                //
                QStandardItem *descriptionItem = new QStandardItem(obj["description"].toString());
                //
                QStandardItem *currentItem = new QStandardItem();
                currentItem->setData(obj["current"].toBool(), Qt::DisplayRole);
                //
                QStandardItem *filename = new QStandardItem(obj["filename"].toString());


                // Ustawienie flag, aby elementy były tylko do odczytu
                commitItem->setFlags(commitItem->flags() & ~Qt::ItemIsEditable);
                dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);
                descriptionItem->setFlags(descriptionItem->flags() & ~Qt::ItemIsEditable);
                currentItem->setFlags(currentItem->flags() & ~Qt::ItemIsEditable);
                filename->setFlags(currentItem->flags() & ~Qt::ItemIsEditable);

                model->setItem(i, 0, commitItem);
                model->setItem(i, 1, dateItem);
                model->setItem(i, 2, descriptionItem);
                model->setItem(i, 3, currentItem);
                model->setItem(i, 4, filename);
            }

            tableView->setModel(model);

            // Ustawienie rozmiaru kolumn
            tableView->setColumnWidth(0, 100); // Commit
            tableView->setColumnWidth(1, 150); // Date
            tableView->setColumnWidth(2, 400); // Description
            tableView->setColumnWidth(3, 50);  // Current (hidden)
            tableView->setColumnWidth(4, 250); // Filename (hidden)

            // Ustawienie delegata do wyróżniania wierszy
            tableView->setItemDelegate(new HighlightDelegate(tableView));

            // Ukrycie kolumny 'Current'
            tableView->setColumnHidden(3, true);
            tableView->setColumnHidden(4, true);

            // Alternatywnie, można użyć resizeColumnsToContents() do automatycznego dopasowania rozmiaru kolumn
            // tableView->resizeColumnsToContents();
        }
    }
    reply->deleteLater();
}
