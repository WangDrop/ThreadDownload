#include "downloadcontrol.h"

DownloadControl::DownloadControl(QObject *parent) : QObject(parent),
state(Waiting), file(NULL)
{
}

//errorString

qint64 DownloadControl::getFileSize(const QString & url, int tryTimes)
{
    qint64 size = -1;
    while(tryTimes--){
        QNetworkAccessManager manager;
        QEventLoop loop;

        QNetworkReply * reply = manager.head(QNetworkRequest(url));
        if(!reply) continue;//最多请求tryTimes次

        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();//计入事件循环，在下载完成之前都不会去做其他的事
        if(reply->error() != QNetworkReply::NoError){
            errorInfo = reply->errorString();
            continue;
        }
        QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
        reply->deleteLater();
        size = var.toLongLong();
        break;
    }
    return size;
}

bool DownloadControl::downloadFile(const QString &_url, const QString &_loadFile, int _count)
{
    if(state == Downloading){
        errorInfo = " is downloading a file! ";
        //emit error();
        return false;
    }
    if(file != NULL){

    }
}
