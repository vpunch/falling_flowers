#include "mystyle.h"

#include <QDebug>

MyStyle::MyStyle()
{

}

void MyStyle::drawControl(ControlElement ce, const QStyleOption *popt, QPainter *pp, const QWidget *pwidget) const {
    switch(ce) {
    case CE_PushButton: {
        const QStyleOptionButton *poptb = qstyleoption_cast<const QStyleOptionButton*>(popt);
        if(poptb) {
            bool synken = poptb->state&State_Sunken;
            synken?pp->fillRect(poptb->rect, Qt::darkCyan):pp->fillRect(poptb->rect, Qt::cyan);
            pp->drawText(poptb->rect, Qt::AlignCenter, poptb->text);
        }
        break;
    }
//    case CE_ScrollBarSlider: {
    case CE_HeaderSection: {
        pp->fillRect(popt->rect/*.marginsAdded(QMargins(-2, -2, -2, -2))*/, Qt::cyan);
        const QStyleOptionHeader* popth = qstyleoption_cast<const QStyleOptionHeader*>(popt);
        pp->setPen(QPen(Qt::black, 2));
        if(popth->position!=QStyleOptionHeader::End && popth->position!=QStyleOptionHeader::OnlyOneSection) {
            pp->drawLine(popt->rect.topRight(), popt->rect.bottomRight());
        }
        break;
    }
    case CE_ItemViewItem: {
        const QStyleOptionViewItem* poptvi = qstyleoption_cast<const QStyleOptionViewItem*>(popt);
        if(poptvi->state & QStyle::State_Selected) {
            pp->fillRect(poptvi->rect, Qt::cyan);
        }
        //если здесь сделать собственную отцентровку текста, то editor будет появляться не на тексте, а на месте отцетровки item->setTextAlighment
        //поэтому используем заданную отцентровку из поля класса опции
        pp->drawText(poptvi->rect, poptvi->decorationAlignment, poptvi->text);

        break;
    }

//    case CE_ScrollBarAddPage: {
    default: {
        QCommonStyle::drawControl(ce, popt, pp, pwidget);
        break;
    }
    }
}

void MyStyle::drawPrimitive(PrimitiveElement pe, const QStyleOption *popt, QPainter *pp, const QWidget *pwidget) const {
    switch(pe) {
    case PE_Frame: {
        pp->fillRect(popt->rect, Qt::cyan);
        break;
    }

//    case PE_PanelScrollAreaCorner: {
    default: {
        QCommonStyle::drawPrimitive(pe, popt, pp, pwidget);
    }
    }
}
