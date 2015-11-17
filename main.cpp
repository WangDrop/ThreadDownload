#include "widget.h"
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>
#include "config.h"
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget * w;

    int btn= QMessageBox::information(0, title, "请选择", "新建下载", "继续下载", "取消");
    qDebug() << btn;
    if(btn == 0){//新建下载
        QString url = QInputDialog.getText(0, title, "请输入下载链接");
        if(url.isEmpty())
            return -1;
        QString file = QFileDialog.getSaveFileName(0, title);
        if(file.isEmpty())
            return -1;
//        w = new Widget;

    }
    return a.exec();
}
