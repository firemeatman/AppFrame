#ifndef CFGDIALOG_H
#define CFGDIALOG_H

/*
 * CfgDialog.h
 *
 *实现了多步配置流程的一个对话框。通过CfgContentWidget类的两个虚函数自动进行UI输入和配置信息的同步；
 *
 *
 *
*/


#include <QDialog>
#include <QDialog>
#include <QStackedWidget>
#include <QPushButton>

#include "cfgContentWidget.h"


class CfgDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CfgDialog(QWidget *parent = nullptr);

    void set_ContentWidgets(std::vector<CfgContentWidget*>& list);
private:
    void clear_ContentWidgets();
private:
    QStackedWidget* m_contentWidget = nullptr;
    QPushButton* m_nextBtn = nullptr;
    QPushButton* m_prvBtn = nullptr;
    QPushButton* m_cancelBtn = nullptr;
    QPushButton* m_okBtn = nullptr;

    std::vector<CfgContentWidget*> m_widgetList;

public slots:
    void _on_currentPageChanged(int index);
    void _on_nextBtnClicked();
    void _on_prevBtnClicked();
    void _on_okBtnClicked();
};

#endif // CFGDIALOG_H
