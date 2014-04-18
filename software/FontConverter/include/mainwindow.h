#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include  "fontconfig.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:

private:
    Ui::MainWindow *ui;
    FontConfig *font_config;
    void MainWindow_init();
    void mainToolBar_init();
    void saveConfig(QSettings& settings,
                    const QString& name,
                    const QObject* object);
    void readConfig(QSettings& settings,
                    const QString& name,
                    QObject* object);
};

#endif // MAINWINDOW_H
