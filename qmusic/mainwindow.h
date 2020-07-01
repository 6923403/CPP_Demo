#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QString>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Mainit();
    QStringList getFilename(const QString &path);
    void additem(QString name);
    void PutMusic(const QStringList & mc);

public:
    void SlotShowCurrentMedia();
    void SlotButtonStart();
    void SlotButtonPrevious();
    void SlotButtonNext();

private:
    Ui::MainWindow * ui;
    QString musicpath;
    QStringList fileList;
    QMediaPlaylist * PlayerList;
    QMediaPlayer * Player;
    bool isPlay = false;
};
#endif // MAINWINDOW_H
