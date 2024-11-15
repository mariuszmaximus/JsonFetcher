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
#include <QKeyEvent>
#include <QDesktopServices>


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


class CustomTableView : public QTableView {
    Q_OBJECT
public:
    CustomTableView(QWidget *parent = nullptr) : QTableView(parent) {}

protected:
    void keyPressEvent(QKeyEvent *event) override {
        if (event->key() == Qt::Key_F1) {
            if(isColumnHidden(3))
            {
                showColumn(3);
                showColumn(4); 
            }
            else {
                hideColumn(3);
                hideColumn(4);
            }

        }
        QTableView::keyPressEvent(event);
    }

    void mouseDoubleClickEvent(QMouseEvent *event) override {
        QModelIndex index = indexAt(event->pos());
        if (index.isValid()) {
            QString filename = model()->data(model()->index(index.row(), 4)).toString(); // Assuming 'Filename' is the 5th column (index 4)
            QUrl url(QString("http://update.draminski.com/iScan3/release/%1.7z").arg(filename));
            QDesktopServices::openUrl(url);
        }
        QTableView::mouseDoubleClickEvent(event);
    }    
};


#endif // JSONFETCHER_H
