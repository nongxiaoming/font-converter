#ifndef CHARMAPDIALOG_H
#define CHARMAPDIALOG_H

#include <QDialog>
#include <QSet>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>

namespace Ui {
    class CharMapDialog;
}

class CharMapDialog : public QDialog {
    Q_OBJECT
public:
    CharMapDialog(QWidget *parent = 0);
    ~CharMapDialog();

    void setText(const QString& string);
    QString getText() const;
protected:
    void changeEvent(QEvent *e);


private:
    Ui::CharMapDialog *ui;
    QSet<uint>  m_codes;
    QMenu *popMenu;
private slots:
    void on_listWidget_itemChanged(QListWidgetItem* item);
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void onTextChanged(uint code,bool add);
    void on_listWidget_customContextMenuRequested(QPoint pos);
    void selectmarked_click();
    void unselectmarked_click();
    void selectall_click();
    void unselectall_click();
};

#endif // CHARMAPDIALOG_H
