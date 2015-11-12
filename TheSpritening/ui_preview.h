/********************************************************************************
** Form generated from reading UI file 'preview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREVIEW_H
#define UI_PREVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_preview
{
public:
    QGraphicsView *graphicsView;

    void setupUi(QDialog *preview)
    {
        if (preview->objectName().isEmpty())
            preview->setObjectName(QStringLiteral("preview"));
        preview->resize(640, 440);
        graphicsView = new QGraphicsView(preview);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(100, 40, 256, 192));

        retranslateUi(preview);

        QMetaObject::connectSlotsByName(preview);
    } // setupUi

    void retranslateUi(QDialog *preview)
    {
        preview->setWindowTitle(QApplication::translate("preview", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class preview: public Ui_preview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEW_H
