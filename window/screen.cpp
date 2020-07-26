void MainWindow::catchScreen()
{
    isPixmapClear=false;
    QClipboard *clipbord=QApplication::clipboard();
#if(QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    Pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
#else if(QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QScreen *screen = QGuiApplication::primaryScreen();
    Pixmap = screen->grabWindow(QApplication::desktop()->winId());
#endif

    int height=QApplication::desktop()->height();
    int width=QApplication::desktop()->width();
    float dx=260.0f/(float)height;
    this->setMinimumSize(width,height);
    ui->SreeenLabel->setMaximumSize(width-width*dx,height-260);
    ui->SreeenLabel->setPixmap(Pixmap.scaled(QSize(ui->SreeenLabel->width(),ui->SreeenLabel->height())));
    disconnect(timer,SIGNAL(timeout()),this,SLOT(catchScreen()));
    clipbord->setPixmap(Pixmap);
    delete timer;
    this->setVisible(true);
}
