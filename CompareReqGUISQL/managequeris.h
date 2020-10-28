#ifndef MANAGEQUERIS_H
#define MANAGEQUERIS_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDateTime>



namespace Ui {
class ManageQueris;
}

class ManageQueris : public QDialog
{
    Q_OBJECT

public:
    explicit ManageQueris(QWidget *parent = nullptr);
    ~ManageQueris();
    QSettings* currentSettings;
    QString asCurrentQuery;
    QString asQueryToLoad;
    QString asSelectedKey;

private slots:
    void on_btn_SaveQuery_clicked();
    void showEvent(QShowEvent* event);
    void on_listWidget_StoredQueries_itemClicked(QListWidgetItem *item);

    void on_btn_LoadQuery_clicked();

    void on_btn_RemoveQuery_clicked();

    void on_btn_Debug_clicked();

    void on_btn_Export_clicked();

    void on_btn_Close_clicked();

private:
    Ui::ManageQueris *ui;
    void refreshStoredQueries();
};

#endif // MANAGEQUERIS_H
