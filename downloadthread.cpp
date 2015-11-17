#include "downloadthread.h"

DownloadThread::DownloadThread(QObject * parent) :
QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    state = Waiting;
    index = 0;
}


void DownloadThread::startDownload(int _index, const QString &_url, QFile *_file, qint64 _startPoint, qint64 _endPoint, qint64 _readySize)
{
    if(state == Downloading){
        errorInfo = " is downloading a file!";
        //错误处理
        return;
    }
    index = _index;
    url = _url;
    file = _file;
    startPoint = _startPoint;
    endPoint = _endPoint;
    readySize = _readySize;

    QNetworkRequest request;
    request.setUrl(_url);
    QString range = QString("bytes=%0-%1").arg(startPoint + readySize).arg(endPoint);
    request.setRawHeader("Range", range.toLatin1());

    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(finishedSlot()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
    // error connect(reply, SIGNAL(error()));

    state = Downloading;
    emit progressChange(index, startPoint, endPoint, readySize);
}

//QString errorString()
//{
//    return
//}

void DownloadThread::stop()
{
    if(state != Downloading){
        errorInfo = " is not download now! ";
        //emit error();
        return;
    }
    state = Stoped;

    reply->abort();
    file->flush();
    reply->deleteLater();
}


void DownloadThread::restart()
{
    if(state!=Stoped){
        errorInfo = " is not stop now! ";
        //emit error()
        return;
    }
    startDownload(index, url, file, startPoint, endPoint, readySize);
}

void DownloadThread::finishedSlot()
{
    if(state != Downloading)
        return;
    file->flush();
    reply->deleteLater();

    state = Finished;
    emit finished(index);
}

void DownloadThread::readyReadSlot()
{
    QByteArray buff = reply->readAll();
    file->seek(startPoint + readySize);
    file->write(buff);
    readySize == buff.size();

    emit progressChange(index, startPoint, endPoint, readySize);
}

//void errorSlot
