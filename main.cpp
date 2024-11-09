#include <QApplication>
#include <QTableView>
#include "jsonfetcher.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QTableView tableView;
    tableView.setWindowTitle("JSON Data Table");
    tableView.resize(800, 600);
    tableView.show();

    // Ustawienie, aby zaznaczał się cały wiersz
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);

    // Wyłączenie multiselect
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);

    JsonFetcher fetcher(&tableView);
    fetcher.fetch(QUrl("http://update.draminski.com/iScan3/"));

    return app.exec();
}
