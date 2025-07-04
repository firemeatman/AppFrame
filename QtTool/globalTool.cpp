#include "globalTool.h"


#include <QFileInfo>


QStringList GlobalTool::open_fileSeleWin(QString& path, QString default_path)
{
    QString currentDir = path;
    QStringList fileNames;
    QFileDialog* fileDialog = new QFileDialog();

    // ����һ�� QFileInfo ����
    if (currentDir.isEmpty()) {
        currentDir = default_path;
    }
    QFileInfo fileInfo(currentDir);

    // ��ȡ�ļ���·��
    if (!fileInfo.isDir()) {
        currentDir = fileInfo.absolutePath();
    }


    fileDialog->setWindowTitle("ѡ���ļ�");
    if (!currentDir.isEmpty()) {
        fileDialog->setDirectory(currentDir);
    }
    //fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setViewMode(QFileDialog::Detail);

    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }
    fileDialog->deleteLater();

    return fileNames;
}


QStringList GlobalTool::open_dirSeleWin(QString& path, QString default_path)
{
    QString currentDir = path;
    QStringList fileNames;
    QFileDialog* fileDialog = new QFileDialog();

    // ����һ�� QFileInfo ����
    if (currentDir.isEmpty()) {
        currentDir = default_path;
    }
    QFileInfo fileInfo(currentDir);

    // ��ȡ�ļ���·��
    if (!fileInfo.isDir()) {
        currentDir = fileInfo.absolutePath();
    }

    fileDialog->setWindowTitle("ѡ���ļ���");
    if (!currentDir.isEmpty()) {
        fileDialog->setDirectory(currentDir);
    }
    //fileDialog->setOption(QFileDialog::DontUseNativeDialog);
    fileDialog->setFileMode(QFileDialog::Directory);
    fileDialog->setViewMode(QFileDialog::Detail);

    if (fileDialog->exec()) {
        fileNames = fileDialog->selectedFiles();
    }
    fileDialog->deleteLater();

    return fileNames;
}


void GlobalTool::safe_deleThread(QThread* thread)
{
    if (thread) {
        thread->quit();
        thread->requestInterruption();
        if (!thread->wait(500)) {
            thread->terminate();
        }
        thread->wait();
        delete thread;
        thread = nullptr;
    }
}