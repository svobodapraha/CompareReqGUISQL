#include "managequeris.h"
#include "ui_managequeris.h"

ManageQueris::ManageQueris(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageQueris)
{
    ui->setupUi(this);
    asSelectedKey.clear();
}

ManageQueris::~ManageQueris()
{
    delete ui;
}

void ManageQueris::on_btn_SaveQuery_clicked()
{
    if (this->currentSettings != nullptr && !ui->lineEdit_QueryName->text().isEmpty())
    {
       currentSettings->setValue("queries/" + ui->lineEdit_QueryName->text(), asCurrentQuery.trimmed());
    }
    this->refreshStoredQueries();
}

void ManageQueris::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    //qDebug() << "manage queries shown";

    this->setWindowTitle("MANAGE QUERIES");
    this->refreshStoredQueries();
    ui->plainTextEdit_ShowQuery->clear();
    asSelectedKey.clear();
    asQueryToLoad.clear();
    ui->lineEdit_QueryName->clear();
}

void ManageQueris::refreshStoredQueries(void)
{


    if (this->currentSettings != nullptr)
    {
        currentSettings->beginGroup("queries");
        QStringList keys = currentSettings->childKeys();
        ui->listWidget_StoredQueries->clear();
        foreach (QString asKey, keys)
        {
           ui->listWidget_StoredQueries->addItem(asKey);
        }
        currentSettings->endGroup();
     }
     ui->plainTextEdit_ShowQuery->clear();

}

void ManageQueris::on_listWidget_StoredQueries_itemClicked(QListWidgetItem *item)
{
    //qDebug() << item->text();
    QVariant VarTemp;
    asSelectedKey = item->text().trimmed();
    if (this->currentSettings != nullptr)
    {
        currentSettings->beginGroup("queries");
        VarTemp = currentSettings->value(asSelectedKey);
        currentSettings->endGroup();
    }

    if (VarTemp.isValid())
    {
        ui->plainTextEdit_ShowQuery->setPlainText(VarTemp.toString());
    }
    else
    {
        ui->plainTextEdit_ShowQuery->clear();
    }

}

void ManageQueris::on_btn_LoadQuery_clicked()
{
   asQueryToLoad = ui->plainTextEdit_ShowQuery->toPlainText();
   asQueryToLoad = asQueryToLoad.trimmed();
   this->close();
}

void ManageQueris::on_btn_RemoveQuery_clicked()
{
  if(!asSelectedKey.isEmpty() && this->currentSettings != nullptr)
  {
      currentSettings->beginGroup("queries");
      currentSettings->remove(asSelectedKey);
      currentSettings->endGroup();
      this->refreshStoredQueries();
  }
}

void ManageQueris::on_btn_Debug_clicked()
{

}

void ManageQueris::on_btn_Export_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, "File to export queries", "", "Text Files (*.txt)");
    QFile exportFile(fileName);
    if (exportFile.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&exportFile);
//copy section "queries" from ini
        if (this->currentSettings != nullptr)
        {
            currentSettings->beginGroup("queries");
            QStringList keys = currentSettings->childKeys();
            stream << "generated on: " << QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss") << Qt::endl << Qt::endl;

            foreach (QString asKey, keys)
            {
                stream << QString("").rightJustified(asKey.length() + 4, '*') << Qt::endl;
                stream << "*" << asKey << ": *" << Qt::endl;
                stream << QString("").rightJustified(asKey.length() + 4, '*') << Qt::endl;
                stream << currentSettings->value(asKey).toString() << Qt::endl << Qt::endl;
            }
            currentSettings->endGroup();
        }
        else
        {
           stream << "Error to read queries";
        }

    }
}

void ManageQueris::on_btn_Close_clicked()
{
      this->close();
}
