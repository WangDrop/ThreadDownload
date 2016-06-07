#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(int type, const QString url, const QString saveFile = "", QWidget *parent = 0);
    ~Widget();
private:
    DownloadControl * control;
    int type;
    QString url, saveFile;
    QLabel * fileName, *errorLabel;
    QLabel * title;
};

#endif // WIDGET_H
