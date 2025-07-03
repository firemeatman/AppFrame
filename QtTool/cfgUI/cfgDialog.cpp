#include "cfgDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

CfgDialog::CfgDialog(QWidget *parent)
    : QDialog(parent)
{
    //============整体UI================
    QVBoxLayout* vLayout = nullptr;
    QHBoxLayout* hLayout = nullptr;
    QWidget* box = nullptr;

    m_contentWidget = new QStackedWidget(this);
    m_contentWidget->resize(100,100);
    m_nextBtn = new QPushButton(this);
    m_nextBtn->setText("下一个");
    m_prvBtn = new QPushButton(this);
    m_prvBtn->setText("上一个");
    m_cancelBtn = new QPushButton(this);
    m_cancelBtn->setText("取消");
    m_okBtn = new QPushButton(this);
    m_okBtn->setText("完成配置");
    m_okBtn->hide();

    box = new QWidget(this);
    hLayout = new QHBoxLayout(box);
    hLayout->addWidget(m_cancelBtn);
    hLayout->addWidget(m_prvBtn);
    hLayout->addWidget(m_nextBtn);
    hLayout->addWidget(m_okBtn);


    vLayout = new QVBoxLayout(this);
    vLayout->addWidget(m_contentWidget, 5);
    vLayout->addWidget(box, 1);



    connect(m_cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_nextBtn, &QPushButton::clicked, this, &CfgDialog::_on_nextBtnClicked);
    connect(m_prvBtn, &QPushButton::clicked, this, &CfgDialog::_on_prevBtnClicked);
    connect(m_okBtn, &QPushButton::clicked, this, &CfgDialog::_on_okBtnClicked);

    connect(m_contentWidget, &QStackedWidget::currentChanged, this, &CfgDialog::_on_currentPageChanged);

}


void CfgDialog::clear_ContentWidgets()
{
    int num = m_contentWidget->count();
    // CfgContentWidget* widget = nullptr;

    for(int i=0;i < num;i++){
        QWidget* widget = m_contentWidget->widget(i);
        m_contentWidget->removeWidget(widget);
    }

    m_widgetList.clear();
}


void CfgDialog::set_ContentWidgets(std::vector<CfgContentWidget *> &list)
{

    clear_ContentWidgets();

    for(size_t i=0;i < list.size();i++){
        m_contentWidget->addWidget(list[i]);
        list[i]->read_cfg();
    }

    if(list.size() > 0){
        m_contentWidget->setCurrentIndex(0);
        //_on_currentPageChanged(0);
    }

    m_widgetList = list;
}


void CfgDialog:: _on_currentPageChanged(int index)
{
    int num = m_contentWidget->count();

    if(num == 1 || num == 0){
        m_nextBtn->hide();
        m_okBtn->show();
        m_prvBtn->setEnabled(false);
        return;
    }

    if( index == 0){
        m_prvBtn->setEnabled(false);
    }

    if(index > 0 && index < num - 1){
        m_nextBtn->show();
        m_okBtn->hide();
        m_nextBtn->setEnabled(true);
        m_prvBtn->setEnabled(true);
    }

    if(index == num - 1){
        m_nextBtn->hide();
        m_okBtn->show();
        m_prvBtn->setEnabled(true);
    }
}


void CfgDialog::_on_nextBtnClicked()
{
    int num = m_contentWidget->count();
    int index = m_contentWidget->currentIndex();


    if(index < num - 1){
        m_contentWidget->setCurrentIndex(index + 1);
    }


}


void CfgDialog::_on_prevBtnClicked()
{
    //int num = m_contentWidget->count();
    int index = m_contentWidget->currentIndex();

    if( index > 0){
        m_contentWidget->setCurrentIndex(index - 1);
    }
}


void CfgDialog::_on_okBtnClicked()
{

    for(size_t i=0;i<m_widgetList.size();i++){
        m_widgetList[i]->write_cfg();
    }

    accept();
}
