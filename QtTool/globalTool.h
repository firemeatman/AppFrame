#ifndef GLOBALTOOL_H
#define GLOBALTOOL_H

#include <QString>
#include <QStringList>
#include <QThread>
#include <QFileDialog>


/*
    ������Qt�г��õ�ȫ�ֹ��ߺ���

*/
class GlobalTool
{
public:
    explicit GlobalTool() {}
    ~GlobalTool() {}
public:
    static QStringList open_fileSeleWin(QString& path, QString default_path = "");
    static QStringList open_dirSeleWin(QString& path, QString default_path = "");
public:
    static void safe_deleThread(QThread* thread);
};


#endif
