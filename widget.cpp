#include "widget.h"

#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      sett("rot", "forMom", this),
      pscene(new QGraphicsScene()),
      pview(new QGraphicsView(pscene, this))

{

    qApp->setStyle(new MyStyle);

    //-------

    pview->setBackgroundBrush(QColor("#e2faff"));
    pview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //-------

    QFont font = this->font();
    font.setPointSize(13);

    QDate date(1975, 07, 11);
    QDate nDate = QDate::currentDate();
    bool birthday = date.month()==nDate.month() && date.day()==nDate.day();

    pcongrats = createText("title", "<center><h3>ПОЗДРАВЛЯЮ</h3></center>", font);

    pcongText = createText("",
                           QString("<center>C%1 <b>Днем рождения</b>.<br>"
                                            "Согласно часам, %2 тебе исполнилось %3!<br>"
                                            "Желаю тебе много <b>цветов</b>, отличного <b>настроения</b> и остутствия <b>двоек</b> у Маши.<br>"
                                            "Все это ты можешь реализовать в моей <b>игре</b>, которую я написал специально для тебя.</center>")
                                            .arg(birthday?"":" прошедшим")
                                            .arg(birthday?"сегодня":QString("11.07.")+QString::number(
                                                                (
                                                                (date.month()==nDate.month() && date.day()>nDate.day()) ||
                                                                (date.month()>nDate.month())
                                                                )?
                                                                     nDate.year()-1:
                                                                     nDate.year()
                                                                                                     )
                                                )
                                            .arg((
                                                 (date.month()==nDate.month() && date.day()>nDate.day()) ||
                                                 (date.month()>nDate.month())
                                                 )?
                                                     nDate.year()-date.year()-1:
                                                     nDate.year()-date.year()
                                                ),
                           font);

    connect(qobject_cast<QPushButton*>(createGraphBtn(&pbtnplay, "Играть", font)), &QPushButton::clicked, [this]{
        if(pbtnplay->opacity()!=1) return;
        hideAnim(pcongrats);
        hideAnim(pcongText);
        hideAnim(pbtnplay);

        hideAnim(table);
        hideAnim(btnHint);
        hideAnim(btnStart);
        hideAnim(phTable);
        hideAnim(pttimer);
        hideAnim(ptflower);
    });

    hideAnim(pcongrats);
    hideAnim(pcongText);
    hideAnim(pbtnplay);

    //-----

    model = new QStandardItemModel(10, 3);


    //создаем элементы(items)
    for(short int i = 0; i<10; ++i) {
        for(short int j=0; j<3; ++j) {
            model->setData(model->index(i,j), sett.value(QString("/settings/table/")+QString::number(i)+QString::number(j), ""));
            model->item(i, j)->setTextAlignment(Qt::AlignCenter);
            model->item(i, j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        }
    }

    model->setHeaderData(0, Qt::Horizontal, "Имя", Qt::DisplayRole);
    model->setHeaderData(1, Qt::Horizontal, "Цветы", Qt::DisplayRole);
    model->setHeaderData(2, Qt::Horizontal, "Разрешение", Qt::DisplayRole);

    view = new QTreeView;
    view->setModel(model);
    view->setFont(font);

    view->setTreePosition(10);

    view->setColumnWidth(0, 95); //5 пикселей на то, чтобы не реагировал скролл бар даже в неотображаемом виде
    view->setColumnWidth(1, 70);

    view->resize(100*3, 232);
    view->setEditTriggers(QAbstractItemView::DoubleClicked);
//    view->edit();
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->header()->setMaximumSectionSize(100-5);
    view->header()->setDefaultAlignment(Qt::AlignCenter);

    connect(view, &QTreeView::doubleClicked, [this](QModelIndex idx){
        if(idx.column()>0){
            for(short int i=idx.row(); i<10; ++i){
                if(model->item(i, 1)->text()==""){break;}
                if(i!=9){
                    for(short int j =0; j<3; ++j) {
                        model->item(i, j)->setText(model->item(i+1,j)->text());
                        if(j==0 && model->item(i+1,j)->flags() & Qt::ItemIsEditable){
                            model->item(i,j)->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                            model->item(i+1, j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        }
                        else if (j==0){
                            model->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                        }
                    }
                }
                else {
                    for(short int j =0; j<3; ++j) {
                        model->item(i, j)->setText("");
                        model->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    }
                }
            }
        }
    });

    table = pscene->addWidget(view);
    table->setOpacity(0);
    table->hide();

    connect(qobject_cast<QPushButton*>(createGraphBtn( &btnHint, "Правила", font)), &QPushButton::clicked, [this]{
       if(btnHint->opacity()!=1) return;
       hideAnim(table);
       hideAnim(btnStart);
       hideAnim(btnHint);
       hideAnim(phTable);
       hideAnim(pttimer);
       hideAnim(ptflower);

       hideAnim(pReg);
       hideAnim(phReg);
       hideAnim(btnUnder);
    });

    pglobalTimer=new QTimer(this);
    pglobalTimer->setInterval(1000);

    connect(pglobalTimer, &QTimer::timeout, [this]{
        sec[0]++;
        if(sec[0]==10){sec[0]=0; ++sec[1];}
        if(sec[1]==6){sec[1]=0; ++min[0];}
        if(min[0]==10){min[0]=0; ++min[1];}
        if(min[1]==9 && min[0]==9 && sec[0]==5 && sec[1]==9){pglobalTimer->stop();}
        pttimer->setPlainText(QString("%1%2:%3%4").arg(min[1]).arg(min[0]).arg(sec[1]).arg(sec[0]));
    });

    connect(qobject_cast<QPushButton*>(createGraphBtn( &btnStart, "Начать", font)), &QPushButton::clicked, [this]{
       if(btnStart->opacity()!=1) return;
       hideAnim(table);
       hideAnim(btnStart);
       hideAnim(btnHint);
       hideAnim(phTable);

       windSize = this->size();

       pttimer->setPlainText("00:00");
       ptflower->setPlainText("0");

       for(short int i=0; i<2; ++i) {
           sec[i]=0;min[i]=0;
       }
       pglobalTimer->start();

       SmileItem *psmileItem = new SmileItem(2, pscene->width(), pscene->height());
       connect(psmileItem, &SmileItem::destroyed, [this, psmileItem]{
           elements.removeOne(psmileItem);
           endGame();
       });
       pscene->addItem(psmileItem);
       elements<<psmileItem;

       flowerCount=0;
       twoCount=0;
       flowerInterval=2000;

       pflowerTimer= new QTimer(this);
       pflowerTimer->setInterval(flowerInterval);
       pflowerTimer->start();
       connect(pflowerTimer, &QTimer::timeout, [this]{

           FlowerItem *pitem = new FlowerItem(4, pscene->width(), pscene->height());
           pscene->addItem(pitem);
           elements<<pitem;
           connect(pitem, &FlowerItem::clicked, [this] {
               flowerInterval-=20; if(flowerInterval<0) flowerInterval=0;
               ++flowerCount;
               ptflower->setPlainText(QString::number(flowerCount));
           });
           connect(pitem, &FlowerItem::destroyed, [this, pitem]{
              elements.removeOne(pitem);
           });

           pflowerTimer->setInterval(flowerInterval);
           qDebug() << flowerInterval;
       });

       ptwoTimer= new QTimer(this);
       ptwoTimer->setInterval(flowerInterval*1.5);
       ptwoTimer->start();
       connect(ptwoTimer, &QTimer::timeout, [this] {
           TwoItem *pti = new TwoItem(4, pscene->width(), pscene->height());
           pscene->addItem(pti);
           elements<<pti;
           ++twoCount;
           connect(pti, &TwoItem::destroyed, [this, pti]{
                --twoCount;
               elements.removeOne(pti);
           });
           if(twoCount>5){endGame();}


           ptwoTimer->setInterval(flowerInterval*1.5);
       });
    });

    phTable = createText("title", "<h3>ТАБЛИЦА РЕЗУЛЬТАТОВ</h3>", font);

    pReg = createText("",
                      "<center>Управление осуществляется одной кнопкой мышки - левой.<br>"
                                        "Игра закончится, если смайлик опустится ниже экрана, или на экране появится больше 5 двоек.<br>"
                                        "Чтобы перетащить смайлик вверх, нужно зажать на нем кнопку<br>"
                                        "Чтобы выбрасывать двойки за экран, нужно зажать кнопку и после резкого движения отпусить ее<br>"
                                        "Цветки- игровые баллы. Чтобы собрать цветок, следует нажать на нем кнопку<br>"
                                        "После каждой игры результаты сохраняются в таблицу, если в ней есть свободное место (максимум 10)<br>"
                                        "Чтобы удалить результат из таблицы, следует кликнуть по нему 2 раза<br>"
                                        "Чтобы изменить \"имя\" поставленного результата, нужно кликнуть по нему 2 раза<br>"
                                        "Результат не будет сохранен, если во время игры разрешение окна изменилось</center>",
                      font);


    phReg = createText("title", "<h3>ПРАВИЛА</h3>", font);

    connect(qobject_cast<QPushButton*>(createGraphBtn(&btnUnder, "Понятно", font)), &QPushButton::clicked, [this]{
       if(btnUnder->opacity()!=1) return;
       hideAnim(table);
       hideAnim(btnStart);
       hideAnim(btnHint);
       hideAnim(phTable);
       hideAnim(pttimer);
       hideAnim(ptflower);

       hideAnim(pReg);
       hideAnim(phReg);
       hideAnim(btnUnder);
    });

    pttimer = createText("", "00:00", font);
    pttimer->setTextWidth(50);
    ptflower = createText("", "0", font);
    ptflower->setTextWidth(50);

}

void Widget::endGame() {

    pglobalTimer->stop();
    pflowerTimer->deleteLater();
    ptwoTimer->deleteLater();

    for(auto it = elements.begin(); it!=elements.end(); ++it)
        (*it)->disconnect();
    elements.clear();

    hideAnim(table);
    hideAnim(btnStart);
    hideAnim(btnHint);
    hideAnim(phTable);

    if(windSize!=this->size()) {return;}

    for(int i=0; i<10; ++i){
//        QStandardItem *item = model->item(i);
        QModelIndex index = model->index(i,1);
        if(index.data()==""){
            for(int j = 0; j<3; ++j){
                QModelIndex rowIndex = model->index(i, j);
                if(j==0){
                    if(i!=0){
                        model->item(i-1,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                    }
//                    qDebug() << rowIndex.flags();
                    view->setCurrentIndex(rowIndex);
                    model->setData(rowIndex, "-");
                    model->item(i,j)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
//                    view->openPersistentEditor(rowIndex);
//                    view->setState();
//                    model->item()->flags()
                }
                else {
                    if(model->headerData(j, Qt::Horizontal)=="Разрешение") {
                        model->setData(rowIndex, QString::number(pscene->width())+"x"+QString::number(pscene->height()));
                    }
                    else { model->setData(rowIndex, QString::number(flowerCount)); }
                }
//                model->setData(rowIndex, "here");
            }
            break;
        }
    }
}

QGraphicsTextItem* Widget::createText(const QString &type, const QString &txt, const QFont &font) {
    QGraphicsTextItem* ptitem = new QGraphicsTextItem;
    ptitem->setFont(font);
    ptitem->setHtml(txt);
    if(type=="title") {
        setTitleAnim(ptitem);
    }
    ptitem->setOpacity(0);
    ptitem->hide();
    ptitem->setTextWidth(ptitem->document()->size().width());
    pscene->addItem(ptitem);
    return ptitem;
}

QWidget* Widget::createGraphBtn(QGraphicsProxyWidget **pproxWgt, const QString &txt, const QFont &font) {
    QWidget *pwgt;
        pwgt = new QPushButton(txt);
        pwgt->resize(200,40);
    (*pproxWgt) = pscene->addWidget(pwgt);
    (*pproxWgt)->setFont(font);
    (*pproxWgt)->hide();
    (*pproxWgt)->setOpacity(0);

    return pwgt;
}

void Widget::hideAnim(QGraphicsObject *pitem) {
    QPropertyAnimation *panim = new QPropertyAnimation(pitem, "opacity");
    panim->setDuration(1000);
    panim->setEasingCurve(QEasingCurve::OutQuad);
    panim->setEndValue((pitem->opacity())?0:1);
    panim->start(QPropertyAnimation::DeleteWhenStopped);
    if(pitem->opacity())
        connect(panim, &QPropertyAnimation::finished, [pitem]{pitem->hide();});
    else   pitem->show();
}

void Widget::setTitleAnim(QGraphicsObject *pitem) {
    QGraphicsTextItem *ptitem = qgraphicsitem_cast<QGraphicsTextItem*>(pitem);
    if(ptitem) {
        ptitem->setTransformOriginPoint(ptitem->document()->size().width()/2, ptitem->document()->size().height()/2);
        QPropertyAnimation *panim = new QPropertyAnimation(pitem, "scale");
        panim->setDuration(1300);
        panim->setEasingCurve(QEasingCurve::OutQuad);
        panim->setKeyValueAt(0.5, 1.2);
        panim->setKeyValueAt(1, 1);
        panim->setLoopCount(-1);
        panim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

Widget::~Widget()
{
    for(short int i = 0; i < 10; ++i)
        for(short int j = 0; j<3; ++j)
            sett.setValue(QString("/settings/table/")+QString::number(i)+QString::number(j), model->item(i,j)->text());

}

void Widget::resizeEvent(QResizeEvent *pe) {

    QPoint pnt(width()/2, height()/2);

    pview->resize(size());
    pscene->setSceneRect(QRect(0, 0, pview->width()-5, pview->height()-5)); //5px на исчезновение скролл бара

    pcongText->setPos(pnt.x()-pcongText->textWidth()/2, pnt.y() - pcongText->document()->size().height()/2);
    pcongrats->setPos(pnt.x()-pcongrats->textWidth()/2, pcongText->pos().y()-70);
    pbtnplay->setPos(width()/2-pbtnplay->widget()->width()/2, pcongText->pos().y()+pcongText->document()->size().height()+20);

    table->setPos(pnt-QPoint(view->width()/2, view->height()/2)-QPoint(0, 15));
    btnHint->setPos(pnt.x()-btnHint->widget()->width()/2 ,table->pos().y()+table->widget()->height()+20);
    btnStart->setPos(btnHint->pos()+QPoint(0, 20+btnHint->widget()->height()));
    phTable->setPos(pnt.x()-phTable->textWidth()/2, table->pos().y()-70);

    pReg->setPos(pnt.x()-pReg->textWidth()/2, pnt.y()-pReg->document()->size().height()/2-15);
    phReg->setPos(pnt.x()-phReg->textWidth()/2, pReg->pos().y()-70);
    btnUnder->setPos(pnt.x()-btnUnder->widget()->width()/2, pReg->y()+pReg->document()->size().height()+20);

    ptflower->setPos(x(), pscene->height()-ptflower->document()->size().height());
    pttimer->setPos(pscene->width()-pttimer->textWidth(), pscene->height()-pttimer->document()->size().height());

}
