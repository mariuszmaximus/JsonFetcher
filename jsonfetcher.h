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
#include <QStyledItemDelegate>
#include <QPainter>

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

class HighlightDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    HighlightDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        if (index.model()->data(index.model()->index(index.row(), 3)).toBool())
        { // Assuming 'current' is the 4th column
            painter->fillRect(option.rect, Qt::green);
        }
        QStyledItemDelegate::paint(painter, option, index);
    }
};

#endif // JSONFETCHER_H
