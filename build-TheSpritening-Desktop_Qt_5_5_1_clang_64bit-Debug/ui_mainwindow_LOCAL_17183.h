/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionSave_2;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QPushButton *clearButton;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QPushButton *addFrameButton;
    QPushButton *colorButton;
    QFrame *line_4;
    QPushButton *pencil;
    QPushButton *eraser;
    QPushButton *flip;
    QPushButton *pushButton_7;
    QSlider *horizontalSlider;
    QPushButton *preview;
    QPushButton *backward;
    QPushButton *playPause;
    QPushButton *forward;
    QGraphicsView *graphicsView_2;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *clearButton_2;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1105, 566);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_2 = new QAction(MainWindow);
        actionSave_2->setObjectName(QStringLiteral("actionSave_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(350, 10, 380, 380));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setGeometry(QRect(220, 250, 61, 61));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(330, 20, 20, 371));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 230, 331, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 10, 20, 381));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        addFrameButton = new QPushButton(centralWidget);
        addFrameButton->setObjectName(QStringLiteral("addFrameButton"));
        addFrameButton->setGeometry(QRect(20, 431, 41, 41));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/imageassets/plus_math.png"), QSize(), QIcon::Normal, QIcon::Off);
        addFrameButton->setIcon(icon);
        colorButton = new QPushButton(centralWidget);
        colorButton->setObjectName(QStringLiteral("colorButton"));
        colorButton->setGeometry(QRect(20, 280, 71, 71));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(10, 380, 331, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        pencil = new QPushButton(centralWidget);
        pencil->setObjectName(QStringLiteral("pencil"));
        pencil->setGeometry(QRect(160, 250, 61, 61));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/imageassets/pencil.png"), QSize(), QIcon::Normal, QIcon::Off);
        pencil->setIcon(icon1);
        eraser = new QPushButton(centralWidget);
        eraser->setObjectName(QStringLiteral("eraser"));
        eraser->setGeometry(QRect(100, 250, 61, 61));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/imageassets/erase.png"), QSize(), QIcon::Normal, QIcon::Off);
        eraser->setIcon(icon2);
        flip = new QPushButton(centralWidget);
        flip->setObjectName(QStringLiteral("flip"));
        flip->setGeometry(QRect(100, 310, 61, 61));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/imageassets/last_quarter.png"), QSize(), QIcon::Normal, QIcon::Off);
        flip->setIcon(icon3);
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(160, 310, 61, 61));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/imageassets/rotate_right.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_7->setIcon(icon4);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(100, 170, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        preview = new QPushButton(centralWidget);
        preview->setObjectName(QStringLiteral("preview"));
        preview->setGeometry(QRect(90, 0, 181, 32));
        backward = new QPushButton(centralWidget);
        backward->setObjectName(QStringLiteral("backward"));
        backward->setGeometry(QRect(90, 200, 31, 32));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/imageassets/rewind.png"), QSize(), QIcon::Normal, QIcon::Off);
        backward->setIcon(icon5);
        playPause = new QPushButton(centralWidget);
        playPause->setObjectName(QStringLiteral("playPause"));
        playPause->setGeometry(QRect(150, 200, 31, 32));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/imageassets/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        playPause->setIcon(icon6);
        forward = new QPushButton(centralWidget);
        forward->setObjectName(QStringLiteral("forward"));
        forward->setGeometry(QRect(210, 200, 31, 32));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/imageassets/fast_forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        forward->setIcon(icon7);
        graphicsView_2 = new QGraphicsView(centralWidget);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(110, 30, 140, 140));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(70, 420, 1021, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        clearButton_2 = new QPushButton(centralWidget);
        clearButton_2->setObjectName(QStringLiteral("clearButton_2"));
        clearButton_2->setGeometry(QRect(220, 310, 61, 61));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/imageassets/delete_sign.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton_2->setIcon(icon8);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(780, 50, 271, 111));
        QFont font;
        font.setFamily(QStringLiteral("Futura"));
        font.setPointSize(64);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(780, 140, 291, 111));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1105, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSave_2->setText(QApplication::translate("MainWindow", "Load", 0));
#ifndef QT_NO_TOOLTIP
        clearButton->setToolTip(QApplication::translate("MainWindow", "Clear the canvas", 0));
#endif // QT_NO_TOOLTIP
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0));
#ifndef QT_NO_TOOLTIP
        addFrameButton->setToolTip(QApplication::translate("MainWindow", "Add a frame", 0));
#endif // QT_NO_TOOLTIP
        addFrameButton->setText(QString());
        colorButton->setText(QApplication::translate("MainWindow", "Color", 0));
        pencil->setText(QString());
        eraser->setText(QString());
        flip->setText(QString());
        pushButton_7->setText(QString());
        preview->setText(QApplication::translate("MainWindow", "View Full Preview", 0));
        backward->setText(QString());
        playPause->setText(QString());
        forward->setText(QString());
#ifndef QT_NO_TOOLTIP
        clearButton_2->setToolTip(QApplication::translate("MainWindow", "Clear the canvas", 0));
#endif // QT_NO_TOOLTIP
        clearButton_2->setText(QString());
        label->setText(QApplication::translate("MainWindow", "The", 0));
        label_2->setText(QApplication::translate("MainWindow", "Spritening", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
