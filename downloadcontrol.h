#ifndef DOWNLOADCONTROL_H
#define DOWNLOADCONTROL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <qglobal.h>

class DownloadControl : public QObject
{
    Q_OBJECT
public:
    enum State{Waiting, Downloading, Pause, Stop, Finished};

    explicit DownloadControl(QObject *parent = 0);

    //errorString

    qint64 getFileSize(const QString & url, int tryTimes = 3);

    bool downloadFile(const QString & _url, const QString & _loadFile, int _count);

    //ini file download

    //getSettingCount

    State getState()const{return state;}
    QString getUrl()const{return url;}
    QString getSaveFile()const{return saveFile;}
    int getCount()const{return count;}
    int getRunningCount()const{return runningCount;}
signals:
    void finished();
    void progressChange(int index, qint64 startPoint, qint64 endPoint, qint64 readySize);
    //error

public slots:
    void pause();
    void restart();
    void stop();

private slots:
    void finishedSlot(int index);
    void progressChangeSlot(int index, qint64 startPoint, qint64 endPoint, qint64 readySize);
    //error;

private:
    void downloadingFinished();

    QString errorInfo;
    State state;
    QVector<DownloadThread * > threads;
    QString url;
    QString saveFile;
    int count, runningCount;
    qint64 readySize, totalSize;
    QFile * file;

};

#endif // DOWNLOADCONTROL_H
