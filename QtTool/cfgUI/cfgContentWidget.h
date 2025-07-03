#ifndef CFGCONTENTWIDGET_H
#define CFGCONTENTWIDGET_H

#include <QWidget>

class CfgContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CfgContentWidget(QWidget *parent = nullptr);

    virtual void read_cfg() = 0; // 读取配置结构体，设置UI
    virtual void write_cfg() = 0; // 从UI的输入写入配置结构体
};

#endif // CFGCONTENTWIDGET_H
