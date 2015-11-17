#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include <QObject>
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class DownloadThread : public QObject
{
    Q_OBJECT
public:
    enum State{Waiting,Downloading,Finished,Stoped};
    explicit DownloadThread(QObject *parent = 0);

    //开始下载
    void startDownload(int _index, const QString & _url, QFile * _file, qint64 _startPoint, qint64 _endPoint, qint64 _readySize = 0);

    State getState()const{return state;}

    //errorString

    int index;
    qint64 startPoint;
    qint64 endPoint;
    qint64 readySize;
signals:
    //结束信号
    void finished(int index);
    //进度改变信号
    void progressChange(int index, qint64 startPoint, qint64 endPoint, qint64 readySize);
    //错误信号
    //error
public slots:
    void stop();
    void restart();

private slots:
    void finishedSlot();
    void readyReadSlot();
    //error;
private:
    QString url;
    QFile * file;
    QNetworkAccessManager * manager;
    QNetworkReply * reply;
    State state;
    QString errorInfo;
};

#endif // DOWNLOADTHREAD_H
