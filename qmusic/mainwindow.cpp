#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->ButtonStillMc,&QPushButton::clicked,this,&MainWindow::SlotButtonStart);
    connect(ui->ButtonDownMc,&QPushButton::clicked,this,&MainWindow::SlotButtonNext);
    connect(ui->ButtonUpMc,&QPushButton::clicked,this,&MainWindow::SlotButtonPrevious);
    Mainit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Mainit()
{
    PlayerList = new QMediaPlaylist;		//实例化播放器和播放列表
    Player = new QMediaPlayer;

    //musicpath = "C:\\Users\\Then\\Desktop\\3mc\\";
    musicpath = "C:\\Users\\puxiaofei\Desktop\\新建文件夹\\";
    fileList = getFilename(musicpath);

    //* qDebug() << "All Music File: \n" << filelist;

    PutMusic(fileList);
    SlotButtonNext();
    SlotButtonPrevious();

    Player->setPlaylist(PlayerList);//将播放列表加载到播放器
    connect(Player,&QMediaPlayer::currentMediaChanged,this,&MainWindow::SlotShowCurrentMedia);
}

void MainWindow::SlotShowCurrentMedia()
{
    int index = PlayerList->currentIndex();
    QString songName = fileList.at(index);
    ui->label->setText(songName);

}

void MainWindow::PutMusic(const QStringList &filelist)
{
    for(int i = 0; i < filelist.size(); i++)
    {
        QString fileName = filelist.at(i);
        additem(fileName);
        PlayerList->addMedia(QUrl::fromLocalFile(musicpath + "\\" + fileName));
    }

}

void MainWindow::SlotButtonPrevious()
{
    PlayerList->previous();
    PlayerList->previousIndex();
}

QStringList MainWindow::getFilename(const QString &path)
{
        QDir dir(path);
        QStringList nameFilters;
        nameFilters << "*.mp3";
        QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
        return files;
}

void MainWindow::additem(QString name)
{
    int count = ui->tableWidget->rowCount();
        ui->tableWidget->setRowCount(count+1);

        QTableWidgetItem *itemName = new QTableWidgetItem(name);
        ui->tableWidget->setItem(count, 0 , itemName);

        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);  //设置为可以选中单个
}

void MainWindow::SlotButtonStart()
{
    if(!isPlay)
    {
        isPlay = true;
        //ui->ButtonStillMc->setIcon(QIcon(":/pause.ico"));
        ui->ButtonStillMc->setText("停止");
        Player->play();
    }
    else
    {
        isPlay = false;
       // ui->ButtonStillMc->setIcon(QIcon(":/play.ico"));
        ui->ButtonStillMc->setText("开始");
        Player->pause();
    }
}

void MainWindow::SlotButtonNext()
{
    PlayerList->next();
    PlayerList->nextIndex();
}
