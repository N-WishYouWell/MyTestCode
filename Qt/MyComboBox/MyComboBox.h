#pragma once
#include <QComboBox>
#include <QListView>
#include <QListWidget>
#include <QPushButton>
#include <QLayout>
#include <QStyledItemDelegate>

class ComboView : public QListWidget
{
    Q_OBJECT
public:
    explicit ComboView(QWidget * parent=nullptr);

    QRect visualRect(const QModelIndex &index) const override;
};

class ComboItem : public QWidget
{
    Q_OBJECT
public:
    explicit ComboItem(const QString &text,QWidget *parent = nullptr);
    ~ComboItem();
    QString text() const;

signals:
    void itemClicked(const QString &text);

private:
    QString textValue;
    QPushButton *btn;
};

class ComboDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboDelegate(QObject *parent=nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

class MyComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit MyComboBox(QWidget *parent = nullptr);

    //设置下拉选项
    void setRemovableItems(const QStringList &items);
    //显示弹框
    void showPopup() override;
    void hidePopup() override;

signals:
    void itemRemoved(const QString &text);

private:
    QListWidget *itemList;
};
