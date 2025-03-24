// #include "layerlayout.h"

// class LayerLayoutPrivate: public QLayoutPrivate
// {
//     Q_DECLARE_PUBLIC(LayerLayout)
// public:
//     LayerLayoutPrivate() : index(-1), stackingMode(QStackedLayout::StackAll) {}
//     QLayoutItem* replaceAt(int index, QLayoutItem *newitem) override;
//     QList<QLayoutItem*> list;
//     int index;
//     QStackedLayout::StackingMode stackingMode;
// };

// QLayoutItem* LayerLayoutPrivate::replaceAt(int index, QLayoutItem *newitem)
// {
//     Q_Q(LayerLayout);
//     if (idx < 0 || idx >= list.size() || !newitem)
//         return nullptr;
//     QWidget *wdg = newitem->widget();
//     if (Q_UNLIKELY(!wdg))
//     {
//         qWarning("LayerLayout::replaceAt: Only widgets can be added");
//         return nullptr;
//     }
//     QLayoutItem *orgitem = list.at(idx);
//     list.replace(idx, newitem);
//     if (idx == index)
//         q->setCurrentIndex(index);
//     return orgitem;
// }

// LayerLayout::LayerLayout()
//     : QLayout(*new LayerLayoutPrivate, nullptr, nullptr)
// {

// }

// LayerLayout::LayerLayout(QWidget *parent)
//     : QLayout(*new LayerLayoutPrivate, nullptr, parent)
// {

// }

// LayerLayout::LayerLayout(QLayout *parentLayout)
//     : QLayout(*new LayerLayoutPrivate, parentLayout, nullptr)
// {

// }

// LayerLayout::~LayerLayout()
// {
//     Q_D(LayerLayout);
//     qDeleteAll(d->list);
// }

// void LayerLayout::setCurrentIndex(int index)
// {
//     Q_D(LayerLayout);
//     QWidget *prev = currentWidget();
//     QWidget *next = widget(index);
//     if (!next || next == prev)
//         return;

//     bool reenableUpdates = false;
//     QWidget *parent = parentWidget();

//     if (parent && parent->updatesEnabled()) {
//         reenableUpdates = true;
//         parent->setUpdatesEnabled(false);
//     }

//     QPointer<QWidget> fw = parent ? parent->window()->focusWidget() : nullptr;
//     const bool focusWasOnOldPage = fw && (prev && prev->isAncestorOf(fw));

//     if (prev) {
//         prev->clearFocus();
//         if (d->stackingMode == StackOne)
//             prev->hide();
//     }

//     d->index = index;
//     //next->raise();
//     next->show();

//     // try to move focus onto the incoming widget if focus
//     // was somewhere on the outgoing widget.

//     if (parent) {
//         if (focusWasOnOldPage) {
//             // look for the best focus widget we can find
//             if (QWidget *nfw = next->focusWidget())
//                 nfw->setFocus();
//             else {
//                 // second best: first child widget in the focus chain
//                 if (QWidget *i = fw) {
//                     while ((i = i->nextInFocusChain()) != fw) {
//                         if (((i->focusPolicy() & Qt::TabFocus) == Qt::TabFocus)
//                             && !i->focusProxy() && i->isVisibleTo(next) && i->isEnabled()
//                             && next->isAncestorOf(i)) {
//                             i->setFocus();
//                             break;
//                         }
//                     }
//                     // third best: incoming widget
//                     if (i == fw )
//                         next->setFocus();
//                 }
//             }
//         }
//     }
//     if (reenableUpdates)
//         parent->setUpdatesEnabled(true);
//     emit currentChanged(index);
// }
