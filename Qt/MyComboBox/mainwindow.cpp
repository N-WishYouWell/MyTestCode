#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "MyComboBox.h"

#include <QListWidget>
#include <QScrollBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //准备下拉选项串
    QStringList str_list;
    for(int i=0;i<5;i++)
    {
        str_list.push_back(QString("%1 item").arg(i));
    }
    //测试长文本显示
    str_list[0]="0 item: text long long long long long long";

    //【1】
    QListWidget *item_list=new QListWidget(this);
    ui->comboBoxA->setModel(item_list->model());
    ui->comboBoxA->setView(item_list);

    //添加选项
    for(int i=0;i<str_list.size();i++)
    {
        //组合一个带按钮的widget
        QWidget *item_widget=new QWidget();
        QHBoxLayout *layout=new QHBoxLayout(item_widget);
        layout->addStretch(); //弹簧
        QPushButton *btn=new QPushButton(str_list.at(i),item_widget);
        layout->addWidget(btn);
        layout->setMargin(0);
        layout->setSpacing(0);

        QListWidgetItem* item_wrap = new QListWidgetItem(item_list);
        //设置显示的data，这样combox才有文字
        item_wrap->setData(Qt::DisplayRole,str_list.at(i));
        //item_list->addItem(item_wrap);
        item_list->setItemWidget(item_wrap,item_widget);

        connect(btn,&QPushButton::clicked,this,[=](){
            ui->comboBoxA->hidePopup(); //没有刷新弹框大小
            item_list->takeItem(item_list->row(item_wrap));
            delete item_wrap;
        });
    }

    //【2】
    //QStringList str_list;
    ui->comboBoxB->setRemovableItems(str_list);
    //ui->comboBoxB->setMaxVisibleItems(20);

    connect(ui->comboBoxB,&MyComboBox::itemRemoved,this,[=](const QString &text){
        qDebug()<<"item remove"<<text;
        //ui->comboBox_2->clear();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
