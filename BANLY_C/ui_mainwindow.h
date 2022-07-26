/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionUpdate_config;
    QWidget *centralWidget;
    QTabWidget *tab_main;
    QWidget *wid_main;
    QTabWidget *tab_dealer_sethand;
    QWidget *tab_normal;
    QLineEdit *edit_e;
    QLabel *n;
    QLineEdit *edit_w;
    QLabel *w;
    QLineEdit *edit_s;
    QLineEdit *edit_n;
    QLabel *e;
    QLabel *s;
    QLabel *deal_tar;
    QLineEdit *edit_deal_tar;
    QPushButton *btn_deal_click;
    QLineEdit *edit_deal_max;
    QLabel *deal_max;
    QListWidget *list_nor_setting;
    QWidget *tab_bdbox;
    QGroupBox *bidding_box;
    QWidget *biddings;
    QGridLayout *gridLayout;
    QPushButton *h6;
    QPushButton *d5;
    QPushButton *x;
    QPushButton *c4;
    QPushButton *d1;
    QPushButton *d3;
    QPushButton *h4;
    QPushButton *nt1;
    QPushButton *pass;
    QPushButton *s3;
    QPushButton *s6;
    QPushButton *h1;
    QPushButton *c6;
    QPushButton *h7;
    QPushButton *d7;
    QPushButton *c5;
    QPushButton *nt5;
    QPushButton *nt6;
    QPushButton *h5;
    QPushButton *nt4;
    QPushButton *s2;
    QPushButton *c2;
    QPushButton *c7;
    QPushButton *s7;
    QPushButton *nt2;
    QPushButton *s4;
    QPushButton *s5;
    QPushButton *h2;
    QPushButton *xx;
    QPushButton *nt3;
    QPushButton *d2;
    QPushButton *d6;
    QPushButton *c1;
    QPushButton *s1;
    QPushButton *h3;
    QPushButton *c3;
    QPushButton *d4;
    QPushButton *nt7;
    QTabWidget *biddingwidget;
    QWidget *wid_bdt;
    QTableWidget *bdt;
    QListWidget *paper;
    QPushButton *ns_vul;
    QPushButton *ew_vul;
    QLabel *vul;
    QGroupBox *adv_set_box;
    QComboBox *cb_c_hi;
    QComboBox *cb_c_lo;
    QComboBox *cb_h_hi;
    QLabel *hcp;
    QLabel *spade;
    QComboBox *cb_m_hi;
    QComboBox *cb_s_hi;
    QComboBox *cb_M_hi;
    QComboBox *cb_M_lo;
    QComboBox *cb_d_lo;
    QComboBox *cb_d_hi;
    QComboBox *cb_s_lo;
    QLabel *heart;
    QComboBox *cb_m_lo;
    QLabel *label;
    QComboBox *cb_h_lo;
    QComboBox *cb_hcp_hi;
    QLabel *major;
    QLabel *diamond;
    QLabel *minor;
    QComboBox *cb_hcp_lo;
    QCheckBox *ckb_w;
    QCheckBox *ckb_s;
    QCheckBox *ckb_e;
    QCheckBox *ckb_n;
    QLabel *distr;
    QPushButton *pb_bal;
    QLineEdit *edit_distr;
    QPushButton *pb_reset;
    QPushButton *pb_clear;
    QPushButton *pb_undo;
    QPushButton *pb_del;
    QPushButton *pb_sub;
    QGroupBox *gb_tips;
    QTextBrowser *brow_tips;
    QTextBrowser *brow_dealer_msg;
    QWidget *wid_anlys;
    QGroupBox *gb_anlys_setting;
    QLineEdit *edit_anlys_filename;
    QPushButton *pb_anlys_file_open;
    QGroupBox *gb_anlys_bidding_and_hand;
    QTextEdit *edit_anlys_bdah;
    QTabWidget *anlymsg_tab_set;
    QWidget *anlys_tab;
    QTextBrowser *brow_anlys_infomsg;
    QWidget *anlys_tab_2;
    QTextBrowser *brow_anlys_sugmsg;
    QTabWidget *wid_anlys_dds;
    QWidget *tab_anlys_dds;
    QTableWidget *ddsresult;
    QWidget *tab_anlys_dds_n;
    QTableWidget *ddsresult_n;
    QWidget *tab_anlys_dds_e;
    QTableWidget *ddsresult_e;
    QWidget *tab_anlys_dds_s;
    QTableWidget *ddsresult_s;
    QWidget *tab_anlys_dds_w;
    QTableWidget *ddsresult_w;
    QTextBrowser *brow_anlys_msg;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 622);
        QFont font;
        font.setFamily(QString::fromUtf8("Helvetica"));
        font.setPointSize(10);
        MainWindow->setFont(font);
        actionUpdate_config = new QAction(MainWindow);
        actionUpdate_config->setObjectName(QString::fromUtf8("actionUpdate_config"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Helvetica"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        actionUpdate_config->setFont(font1);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tab_main = new QTabWidget(centralWidget);
        tab_main->setObjectName(QString::fromUtf8("tab_main"));
        tab_main->setGeometry(QRect(5, 5, 1014, 570));
        wid_main = new QWidget();
        wid_main->setObjectName(QString::fromUtf8("wid_main"));
        tab_dealer_sethand = new QTabWidget(wid_main);
        tab_dealer_sethand->setObjectName(QString::fromUtf8("tab_dealer_sethand"));
        tab_dealer_sethand->setGeometry(QRect(10, 5, 270, 530));
        QFont font2;
        font2.setPointSize(9);
        tab_dealer_sethand->setFont(font2);
        tab_dealer_sethand->setIconSize(QSize(16, 16));
        tab_normal = new QWidget();
        tab_normal->setObjectName(QString::fromUtf8("tab_normal"));
        edit_e = new QLineEdit(tab_normal);
        edit_e->setObjectName(QString::fromUtf8("edit_e"));
        edit_e->setGeometry(QRect(25, 30, 235, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setPointSize(12);
        edit_e->setFont(font3);
        edit_e->setMaxLength(16);
        edit_e->setReadOnly(false);
        n = new QLabel(tab_normal);
        n->setObjectName(QString::fromUtf8("n"));
        n->setGeometry(QRect(5, 10, 12, 12));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Times New Roman"));
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        n->setFont(font4);
        edit_w = new QLineEdit(tab_normal);
        edit_w->setObjectName(QString::fromUtf8("edit_w"));
        edit_w->setGeometry(QRect(25, 80, 235, 20));
        edit_w->setFont(font3);
        edit_w->setMaxLength(16);
        edit_w->setReadOnly(false);
        w = new QLabel(tab_normal);
        w->setObjectName(QString::fromUtf8("w"));
        w->setGeometry(QRect(5, 85, 15, 15));
        w->setFont(font4);
        edit_s = new QLineEdit(tab_normal);
        edit_s->setObjectName(QString::fromUtf8("edit_s"));
        edit_s->setGeometry(QRect(25, 55, 235, 20));
        edit_s->setFont(font3);
        edit_s->setMaxLength(16);
        edit_s->setReadOnly(false);
        edit_n = new QLineEdit(tab_normal);
        edit_n->setObjectName(QString::fromUtf8("edit_n"));
        edit_n->setGeometry(QRect(25, 5, 235, 20));
        edit_n->setFont(font3);
        edit_n->setMaxLength(16);
        edit_n->setReadOnly(false);
        e = new QLabel(tab_normal);
        e->setObjectName(QString::fromUtf8("e"));
        e->setGeometry(QRect(5, 35, 12, 12));
        e->setFont(font4);
        s = new QLabel(tab_normal);
        s->setObjectName(QString::fromUtf8("s"));
        s->setGeometry(QRect(5, 60, 12, 12));
        s->setFont(font4);
        deal_tar = new QLabel(tab_normal);
        deal_tar->setObjectName(QString::fromUtf8("deal_tar"));
        deal_tar->setGeometry(QRect(5, 415, 131, 20));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Helvetica"));
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setWeight(75);
        deal_tar->setFont(font5);
        edit_deal_tar = new QLineEdit(tab_normal);
        edit_deal_tar->setObjectName(QString::fromUtf8("edit_deal_tar"));
        edit_deal_tar->setGeometry(QRect(30, 440, 230, 20));
        edit_deal_tar->setFont(font3);
        edit_deal_tar->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edit_deal_tar->setReadOnly(false);
        btn_deal_click = new QPushButton(tab_normal);
        btn_deal_click->setObjectName(QString::fromUtf8("btn_deal_click"));
        btn_deal_click->setGeometry(QRect(5, 465, 255, 25));
        btn_deal_click->setFont(font5);
        btn_deal_click->setAutoDefault(false);
        edit_deal_max = new QLineEdit(tab_normal);
        edit_deal_max->setObjectName(QString::fromUtf8("edit_deal_max"));
        edit_deal_max->setGeometry(QRect(30, 390, 230, 20));
        edit_deal_max->setFont(font3);
        edit_deal_max->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        edit_deal_max->setReadOnly(false);
        deal_max = new QLabel(tab_normal);
        deal_max->setObjectName(QString::fromUtf8("deal_max"));
        deal_max->setGeometry(QRect(5, 365, 141, 20));
        deal_max->setFont(font5);
        list_nor_setting = new QListWidget(tab_normal);
        QFont font6;
        font6.setFamily(QString::fromUtf8("Times New Roman"));
        font6.setPointSize(12);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setWeight(75);
        font6.setStyleStrategy(QFont::PreferDefault);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(list_nor_setting);
        __qlistwidgetitem->setTextAlignment(Qt::AlignCenter);
        __qlistwidgetitem->setFont(font6);
        list_nor_setting->setObjectName(QString::fromUtf8("list_nor_setting"));
        list_nor_setting->setGeometry(QRect(5, 110, 255, 130));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Times New Roman"));
        font7.setPointSize(12);
        font7.setBold(false);
        font7.setUnderline(false);
        font7.setWeight(50);
        font7.setStrikeOut(false);
        list_nor_setting->setFont(font7);
        list_nor_setting->setAcceptDrops(false);
        list_nor_setting->setAutoFillBackground(false);
        list_nor_setting->setLineWidth(1);
        tab_dealer_sethand->addTab(tab_normal, QString());
        tab_bdbox = new QWidget();
        tab_bdbox->setObjectName(QString::fromUtf8("tab_bdbox"));
        bidding_box = new QGroupBox(tab_bdbox);
        bidding_box->setObjectName(QString::fromUtf8("bidding_box"));
        bidding_box->setGeometry(QRect(5, 230, 250, 265));
        biddings = new QWidget(bidding_box);
        biddings->setObjectName(QString::fromUtf8("biddings"));
        biddings->setGeometry(QRect(0, 10, 250, 255));
        gridLayout = new QGridLayout(biddings);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(5);
        gridLayout->setVerticalSpacing(8);
        h6 = new QPushButton(biddings);
        h6->setObjectName(QString::fromUtf8("h6"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Arial Black"));
        font8.setPointSize(12);
        font8.setBold(false);
        font8.setWeight(50);
        font8.setKerning(true);
        h6->setFont(font8);

        gridLayout->addWidget(h6, 5, 3, 1, 1);

        d5 = new QPushButton(biddings);
        d5->setObjectName(QString::fromUtf8("d5"));
        d5->setFont(font8);

        gridLayout->addWidget(d5, 4, 2, 1, 1);

        x = new QPushButton(biddings);
        x->setObjectName(QString::fromUtf8("x"));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Arial Black"));
        font9.setPointSize(10);
        font9.setBold(false);
        font9.setWeight(50);
        font9.setKerning(true);
        x->setFont(font9);

        gridLayout->addWidget(x, 8, 2, 1, 1);

        c4 = new QPushButton(biddings);
        c4->setObjectName(QString::fromUtf8("c4"));
        c4->setFont(font8);

        gridLayout->addWidget(c4, 3, 1, 1, 1);

        d1 = new QPushButton(biddings);
        d1->setObjectName(QString::fromUtf8("d1"));
        d1->setFont(font8);

        gridLayout->addWidget(d1, 0, 2, 1, 1);

        d3 = new QPushButton(biddings);
        d3->setObjectName(QString::fromUtf8("d3"));
        d3->setFont(font8);

        gridLayout->addWidget(d3, 2, 2, 1, 1);

        h4 = new QPushButton(biddings);
        h4->setObjectName(QString::fromUtf8("h4"));
        h4->setFont(font8);

        gridLayout->addWidget(h4, 3, 3, 1, 1);

        nt1 = new QPushButton(biddings);
        nt1->setObjectName(QString::fromUtf8("nt1"));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Arial Black"));
        font10.setPointSize(10);
        font10.setBold(true);
        font10.setWeight(75);
        font10.setKerning(true);
        nt1->setFont(font10);

        gridLayout->addWidget(nt1, 0, 6, 1, 1);

        pass = new QPushButton(biddings);
        pass->setObjectName(QString::fromUtf8("pass"));
        pass->setFont(font9);

        gridLayout->addWidget(pass, 8, 5, 1, 3);

        s3 = new QPushButton(biddings);
        s3->setObjectName(QString::fromUtf8("s3"));
        s3->setFont(font8);

        gridLayout->addWidget(s3, 2, 5, 1, 1);

        s6 = new QPushButton(biddings);
        s6->setObjectName(QString::fromUtf8("s6"));
        s6->setFont(font8);

        gridLayout->addWidget(s6, 5, 5, 1, 1);

        h1 = new QPushButton(biddings);
        h1->setObjectName(QString::fromUtf8("h1"));
        h1->setFont(font8);

        gridLayout->addWidget(h1, 0, 3, 1, 1);

        c6 = new QPushButton(biddings);
        c6->setObjectName(QString::fromUtf8("c6"));
        c6->setFont(font8);

        gridLayout->addWidget(c6, 5, 1, 1, 1);

        h7 = new QPushButton(biddings);
        h7->setObjectName(QString::fromUtf8("h7"));
        h7->setFont(font8);

        gridLayout->addWidget(h7, 7, 3, 1, 1);

        d7 = new QPushButton(biddings);
        d7->setObjectName(QString::fromUtf8("d7"));
        d7->setFont(font8);

        gridLayout->addWidget(d7, 7, 2, 1, 1);

        c5 = new QPushButton(biddings);
        c5->setObjectName(QString::fromUtf8("c5"));
        c5->setFont(font8);

        gridLayout->addWidget(c5, 4, 1, 1, 1);

        nt5 = new QPushButton(biddings);
        nt5->setObjectName(QString::fromUtf8("nt5"));
        nt5->setFont(font9);

        gridLayout->addWidget(nt5, 4, 6, 1, 1);

        nt6 = new QPushButton(biddings);
        nt6->setObjectName(QString::fromUtf8("nt6"));
        nt6->setFont(font9);

        gridLayout->addWidget(nt6, 5, 6, 1, 1);

        h5 = new QPushButton(biddings);
        h5->setObjectName(QString::fromUtf8("h5"));
        h5->setFont(font8);

        gridLayout->addWidget(h5, 4, 3, 1, 1);

        nt4 = new QPushButton(biddings);
        nt4->setObjectName(QString::fromUtf8("nt4"));
        nt4->setFont(font9);

        gridLayout->addWidget(nt4, 3, 6, 1, 1);

        s2 = new QPushButton(biddings);
        s2->setObjectName(QString::fromUtf8("s2"));
        s2->setFont(font8);

        gridLayout->addWidget(s2, 1, 5, 1, 1);

        c2 = new QPushButton(biddings);
        c2->setObjectName(QString::fromUtf8("c2"));
        c2->setFont(font8);

        gridLayout->addWidget(c2, 1, 1, 1, 1);

        c7 = new QPushButton(biddings);
        c7->setObjectName(QString::fromUtf8("c7"));
        c7->setFont(font8);

        gridLayout->addWidget(c7, 7, 1, 1, 1);

        s7 = new QPushButton(biddings);
        s7->setObjectName(QString::fromUtf8("s7"));
        s7->setFont(font8);

        gridLayout->addWidget(s7, 7, 5, 1, 1);

        nt2 = new QPushButton(biddings);
        nt2->setObjectName(QString::fromUtf8("nt2"));
        nt2->setFont(font9);

        gridLayout->addWidget(nt2, 1, 6, 1, 1);

        s4 = new QPushButton(biddings);
        s4->setObjectName(QString::fromUtf8("s4"));
        s4->setFont(font8);

        gridLayout->addWidget(s4, 3, 5, 1, 1);

        s5 = new QPushButton(biddings);
        s5->setObjectName(QString::fromUtf8("s5"));
        s5->setFont(font8);

        gridLayout->addWidget(s5, 4, 5, 1, 1);

        h2 = new QPushButton(biddings);
        h2->setObjectName(QString::fromUtf8("h2"));
        h2->setFont(font8);

        gridLayout->addWidget(h2, 1, 3, 1, 1);

        xx = new QPushButton(biddings);
        xx->setObjectName(QString::fromUtf8("xx"));
        xx->setFont(font9);

        gridLayout->addWidget(xx, 8, 3, 1, 1);

        nt3 = new QPushButton(biddings);
        nt3->setObjectName(QString::fromUtf8("nt3"));
        nt3->setFont(font9);

        gridLayout->addWidget(nt3, 2, 6, 1, 1);

        d2 = new QPushButton(biddings);
        d2->setObjectName(QString::fromUtf8("d2"));
        d2->setFont(font8);

        gridLayout->addWidget(d2, 1, 2, 1, 1);

        d6 = new QPushButton(biddings);
        d6->setObjectName(QString::fromUtf8("d6"));
        d6->setFont(font8);

        gridLayout->addWidget(d6, 5, 2, 1, 1);

        c1 = new QPushButton(biddings);
        c1->setObjectName(QString::fromUtf8("c1"));
        c1->setFont(font8);

        gridLayout->addWidget(c1, 0, 1, 1, 1);

        s1 = new QPushButton(biddings);
        s1->setObjectName(QString::fromUtf8("s1"));
        s1->setFont(font8);

        gridLayout->addWidget(s1, 0, 5, 1, 1);

        h3 = new QPushButton(biddings);
        h3->setObjectName(QString::fromUtf8("h3"));
        h3->setFont(font8);

        gridLayout->addWidget(h3, 2, 3, 1, 1);

        c3 = new QPushButton(biddings);
        c3->setObjectName(QString::fromUtf8("c3"));
        c3->setFont(font8);

        gridLayout->addWidget(c3, 2, 1, 1, 1);

        d4 = new QPushButton(biddings);
        d4->setObjectName(QString::fromUtf8("d4"));
        d4->setFont(font8);

        gridLayout->addWidget(d4, 3, 2, 1, 1);

        nt7 = new QPushButton(biddings);
        nt7->setObjectName(QString::fromUtf8("nt7"));
        nt7->setFont(font9);

        gridLayout->addWidget(nt7, 7, 6, 1, 1);

        biddingwidget = new QTabWidget(tab_bdbox);
        biddingwidget->setObjectName(QString::fromUtf8("biddingwidget"));
        biddingwidget->setGeometry(QRect(22, 5, 211, 130));
        wid_bdt = new QWidget();
        wid_bdt->setObjectName(QString::fromUtf8("wid_bdt"));
        bdt = new QTableWidget(wid_bdt);
        bdt->setObjectName(QString::fromUtf8("bdt"));
        bdt->setGeometry(QRect(0, 0, 205, 105));
        bdt->setContextMenuPolicy(Qt::NoContextMenu);
        bdt->setShowGrid(false);
        biddingwidget->addTab(wid_bdt, QString());
        paper = new QListWidget(tab_bdbox);
        paper->setObjectName(QString::fromUtf8("paper"));
        paper->setEnabled(true);
        paper->setGeometry(QRect(22, 140, 210, 65));
        ns_vul = new QPushButton(tab_bdbox);
        ns_vul->setObjectName(QString::fromUtf8("ns_vul"));
        ns_vul->setGeometry(QRect(122, 210, 50, 20));
        ns_vul->setCheckable(true);
        ew_vul = new QPushButton(tab_bdbox);
        ew_vul->setObjectName(QString::fromUtf8("ew_vul"));
        ew_vul->setGeometry(QRect(182, 210, 50, 20));
        ew_vul->setCheckable(true);
        vul = new QLabel(tab_bdbox);
        vul->setObjectName(QString::fromUtf8("vul"));
        vul->setGeometry(QRect(22, 210, 80, 20));
        vul->setFont(font4);
        vul->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tab_dealer_sethand->addTab(tab_bdbox, QString());
        adv_set_box = new QGroupBox(wid_main);
        adv_set_box->setObjectName(QString::fromUtf8("adv_set_box"));
        adv_set_box->setGeometry(QRect(290, 10, 240, 525));
        adv_set_box->setFlat(true);
        cb_c_hi = new QComboBox(adv_set_box);
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->addItem(QString());
        cb_c_hi->setObjectName(QString::fromUtf8("cb_c_hi"));
        cb_c_hi->setGeometry(QRect(165, 120, 55, 20));
        cb_c_hi->setFont(font4);
        cb_c_lo = new QComboBox(adv_set_box);
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->addItem(QString());
        cb_c_lo->setObjectName(QString::fromUtf8("cb_c_lo"));
        cb_c_lo->setGeometry(QRect(100, 120, 55, 20));
        cb_c_lo->setFont(font4);
        cb_h_hi = new QComboBox(adv_set_box);
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->addItem(QString());
        cb_h_hi->setObjectName(QString::fromUtf8("cb_h_hi"));
        cb_h_hi->setGeometry(QRect(165, 70, 55, 20));
        cb_h_hi->setFont(font4);
        hcp = new QLabel(adv_set_box);
        hcp->setObjectName(QString::fromUtf8("hcp"));
        hcp->setGeometry(QRect(10, 195, 40, 20));
        hcp->setFont(font4);
        hcp->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spade = new QLabel(adv_set_box);
        spade->setObjectName(QString::fromUtf8("spade"));
        spade->setGeometry(QRect(10, 45, 60, 20));
        spade->setFont(font4);
        spade->setTextFormat(Qt::RichText);
        spade->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cb_m_hi = new QComboBox(adv_set_box);
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->addItem(QString());
        cb_m_hi->setObjectName(QString::fromUtf8("cb_m_hi"));
        cb_m_hi->setGeometry(QRect(165, 170, 55, 20));
        cb_m_hi->setFont(font4);
        cb_s_hi = new QComboBox(adv_set_box);
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->addItem(QString());
        cb_s_hi->setObjectName(QString::fromUtf8("cb_s_hi"));
        cb_s_hi->setGeometry(QRect(165, 45, 55, 20));
        cb_s_hi->setFont(font4);
        cb_M_hi = new QComboBox(adv_set_box);
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->addItem(QString());
        cb_M_hi->setObjectName(QString::fromUtf8("cb_M_hi"));
        cb_M_hi->setGeometry(QRect(165, 145, 55, 20));
        cb_M_hi->setFont(font4);
        cb_M_lo = new QComboBox(adv_set_box);
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->addItem(QString());
        cb_M_lo->setObjectName(QString::fromUtf8("cb_M_lo"));
        cb_M_lo->setGeometry(QRect(100, 145, 55, 20));
        cb_M_lo->setFont(font4);
        cb_d_lo = new QComboBox(adv_set_box);
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->addItem(QString());
        cb_d_lo->setObjectName(QString::fromUtf8("cb_d_lo"));
        cb_d_lo->setGeometry(QRect(100, 95, 55, 20));
        cb_d_lo->setFont(font4);
        cb_d_hi = new QComboBox(adv_set_box);
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->addItem(QString());
        cb_d_hi->setObjectName(QString::fromUtf8("cb_d_hi"));
        cb_d_hi->setGeometry(QRect(165, 95, 55, 20));
        cb_d_hi->setFont(font4);
        cb_s_lo = new QComboBox(adv_set_box);
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->addItem(QString());
        cb_s_lo->setObjectName(QString::fromUtf8("cb_s_lo"));
        cb_s_lo->setGeometry(QRect(100, 45, 55, 20));
        cb_s_lo->setFont(font4);
        heart = new QLabel(adv_set_box);
        heart->setObjectName(QString::fromUtf8("heart"));
        heart->setGeometry(QRect(10, 70, 60, 20));
        heart->setFont(font4);
        heart->setTextFormat(Qt::RichText);
        heart->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cb_m_lo = new QComboBox(adv_set_box);
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->addItem(QString());
        cb_m_lo->setObjectName(QString::fromUtf8("cb_m_lo"));
        cb_m_lo->setGeometry(QRect(100, 170, 55, 20));
        cb_m_lo->setFont(font4);
        label = new QLabel(adv_set_box);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 120, 60, 20));
        label->setFont(font4);
        label->setTextFormat(Qt::RichText);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cb_h_lo = new QComboBox(adv_set_box);
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->addItem(QString());
        cb_h_lo->setObjectName(QString::fromUtf8("cb_h_lo"));
        cb_h_lo->setGeometry(QRect(100, 70, 55, 20));
        cb_h_lo->setFont(font4);
        cb_hcp_hi = new QComboBox(adv_set_box);
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->addItem(QString());
        cb_hcp_hi->setObjectName(QString::fromUtf8("cb_hcp_hi"));
        cb_hcp_hi->setGeometry(QRect(165, 195, 55, 20));
        cb_hcp_hi->setFont(font4);
        cb_hcp_hi->setMaxVisibleItems(10);
        cb_hcp_hi->setMaxCount(40);
        cb_hcp_hi->setMinimumContentsLength(0);
        major = new QLabel(adv_set_box);
        major->setObjectName(QString::fromUtf8("major"));
        major->setGeometry(QRect(10, 145, 60, 20));
        major->setFont(font4);
        major->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        diamond = new QLabel(adv_set_box);
        diamond->setObjectName(QString::fromUtf8("diamond"));
        diamond->setGeometry(QRect(10, 95, 81, 20));
        diamond->setFont(font4);
        diamond->setTextFormat(Qt::RichText);
        diamond->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        minor = new QLabel(adv_set_box);
        minor->setObjectName(QString::fromUtf8("minor"));
        minor->setGeometry(QRect(10, 170, 60, 20));
        minor->setFont(font4);
        minor->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        cb_hcp_lo = new QComboBox(adv_set_box);
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->addItem(QString());
        cb_hcp_lo->setObjectName(QString::fromUtf8("cb_hcp_lo"));
        cb_hcp_lo->setGeometry(QRect(100, 195, 55, 20));
        cb_hcp_lo->setMinimumSize(QSize(40, 20));
        cb_hcp_lo->setBaseSize(QSize(0, 0));
        cb_hcp_lo->setFont(font4);
        cb_hcp_lo->setMaxVisibleItems(10);
        cb_hcp_lo->setMaxCount(40);
        cb_hcp_lo->setMinimumContentsLength(0);
        cb_hcp_lo->setDuplicatesEnabled(false);
        ckb_w = new QCheckBox(adv_set_box);
        ckb_w->setObjectName(QString::fromUtf8("ckb_w"));
        ckb_w->setGeometry(QRect(145, 20, 40, 20));
        ckb_w->setFont(font4);
        ckb_w->setCheckable(true);
        ckb_w->setAutoExclusive(true);
        ckb_s = new QCheckBox(adv_set_box);
        ckb_s->setObjectName(QString::fromUtf8("ckb_s"));
        ckb_s->setGeometry(QRect(100, 20, 40, 20));
        ckb_s->setFont(font4);
        ckb_s->setAutoExclusive(true);
        ckb_e = new QCheckBox(adv_set_box);
        ckb_e->setObjectName(QString::fromUtf8("ckb_e"));
        ckb_e->setGeometry(QRect(55, 20, 40, 20));
        ckb_e->setFont(font4);
        ckb_e->setAutoExclusive(true);
        ckb_n = new QCheckBox(adv_set_box);
        ckb_n->setObjectName(QString::fromUtf8("ckb_n"));
        ckb_n->setGeometry(QRect(10, 20, 40, 20));
        ckb_n->setFont(font4);
        ckb_n->setCheckable(true);
        ckb_n->setChecked(true);
        ckb_n->setAutoExclusive(true);
        distr = new QLabel(adv_set_box);
        distr->setObjectName(QString::fromUtf8("distr"));
        distr->setGeometry(QRect(10, 230, 80, 20));
        distr->setFont(font4);
        distr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        pb_bal = new QPushButton(adv_set_box);
        pb_bal->setObjectName(QString::fromUtf8("pb_bal"));
        pb_bal->setGeometry(QRect(100, 230, 40, 20));
        pb_bal->setFont(font4);
        edit_distr = new QLineEdit(adv_set_box);
        edit_distr->setObjectName(QString::fromUtf8("edit_distr"));
        edit_distr->setGeometry(QRect(10, 255, 220, 20));
        edit_distr->setFont(font3);
        edit_distr->setReadOnly(false);
        pb_reset = new QPushButton(adv_set_box);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));
        pb_reset->setGeometry(QRect(170, 490, 60, 20));
        pb_clear = new QPushButton(adv_set_box);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(100, 280, 60, 20));
        pb_undo = new QPushButton(adv_set_box);
        pb_undo->setObjectName(QString::fromUtf8("pb_undo"));
        pb_undo->setGeometry(QRect(80, 305, 60, 20));
        pb_del = new QPushButton(adv_set_box);
        pb_del->setObjectName(QString::fromUtf8("pb_del"));
        pb_del->setGeometry(QRect(10, 305, 60, 20));
        pb_sub = new QPushButton(adv_set_box);
        pb_sub->setObjectName(QString::fromUtf8("pb_sub"));
        pb_sub->setGeometry(QRect(170, 280, 60, 20));
        gb_tips = new QGroupBox(adv_set_box);
        gb_tips->setObjectName(QString::fromUtf8("gb_tips"));
        gb_tips->setGeometry(QRect(10, 330, 220, 155));
        gb_tips->setFlat(true);
        gb_tips->setCheckable(false);
        brow_tips = new QTextBrowser(gb_tips);
        brow_tips->setObjectName(QString::fromUtf8("brow_tips"));
        brow_tips->setGeometry(QRect(0, 20, 220, 135));
        brow_tips->setAutoFillBackground(false);
        brow_tips->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0);"));
        brow_dealer_msg = new QTextBrowser(wid_main);
        brow_dealer_msg->setObjectName(QString::fromUtf8("brow_dealer_msg"));
        brow_dealer_msg->setGeometry(QRect(540, 18, 460, 515));
        brow_dealer_msg->setFont(font2);
        tab_main->addTab(wid_main, QString());
        wid_anlys = new QWidget();
        wid_anlys->setObjectName(QString::fromUtf8("wid_anlys"));
        gb_anlys_setting = new QGroupBox(wid_anlys);
        gb_anlys_setting->setObjectName(QString::fromUtf8("gb_anlys_setting"));
        gb_anlys_setting->setGeometry(QRect(10, 10, 440, 280));
        edit_anlys_filename = new QLineEdit(gb_anlys_setting);
        edit_anlys_filename->setObjectName(QString::fromUtf8("edit_anlys_filename"));
        edit_anlys_filename->setGeometry(QRect(10, 20, 340, 20));
        edit_anlys_filename->setFont(font2);
        edit_anlys_filename->setReadOnly(true);
        pb_anlys_file_open = new QPushButton(gb_anlys_setting);
        pb_anlys_file_open->setObjectName(QString::fromUtf8("pb_anlys_file_open"));
        pb_anlys_file_open->setGeometry(QRect(360, 20, 70, 20));
        gb_anlys_bidding_and_hand = new QGroupBox(gb_anlys_setting);
        gb_anlys_bidding_and_hand->setObjectName(QString::fromUtf8("gb_anlys_bidding_and_hand"));
        gb_anlys_bidding_and_hand->setGeometry(QRect(10, 50, 420, 221));
        edit_anlys_bdah = new QTextEdit(gb_anlys_bidding_and_hand);
        edit_anlys_bdah->setObjectName(QString::fromUtf8("edit_anlys_bdah"));
        edit_anlys_bdah->setGeometry(QRect(5, 20, 410, 195));
        anlymsg_tab_set = new QTabWidget(wid_anlys);
        anlymsg_tab_set->setObjectName(QString::fromUtf8("anlymsg_tab_set"));
        anlymsg_tab_set->setGeometry(QRect(460, 260, 540, 275));
        anlymsg_tab_set->setTabPosition(QTabWidget::North);
        anlys_tab = new QWidget();
        anlys_tab->setObjectName(QString::fromUtf8("anlys_tab"));
        brow_anlys_infomsg = new QTextBrowser(anlys_tab);
        brow_anlys_infomsg->setObjectName(QString::fromUtf8("brow_anlys_infomsg"));
        brow_anlys_infomsg->setGeometry(QRect(0, 0, 533, 246));
        anlymsg_tab_set->addTab(anlys_tab, QString());
        anlys_tab_2 = new QWidget();
        anlys_tab_2->setObjectName(QString::fromUtf8("anlys_tab_2"));
        brow_anlys_sugmsg = new QTextBrowser(anlys_tab_2);
        brow_anlys_sugmsg->setObjectName(QString::fromUtf8("brow_anlys_sugmsg"));
        brow_anlys_sugmsg->setGeometry(QRect(0, 0, 533, 246));
        anlymsg_tab_set->addTab(anlys_tab_2, QString());
        wid_anlys_dds = new QTabWidget(wid_anlys);
        wid_anlys_dds->setObjectName(QString::fromUtf8("wid_anlys_dds"));
        wid_anlys_dds->setGeometry(QRect(460, 18, 540, 149));
        wid_anlys_dds->setTabPosition(QTabWidget::North);
        tab_anlys_dds = new QWidget();
        tab_anlys_dds->setObjectName(QString::fromUtf8("tab_anlys_dds"));
        ddsresult = new QTableWidget(tab_anlys_dds);
        if (ddsresult->columnCount() < 6)
            ddsresult->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        ddsresult->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        ddsresult->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font);
        ddsresult->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font);
        ddsresult->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setFont(font);
        ddsresult->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setFont(font);
        ddsresult->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (ddsresult->rowCount() < 4)
            ddsresult->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setFont(font);
        ddsresult->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setFont(font);
        ddsresult->setVerticalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setFont(font);
        ddsresult->setVerticalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setFont(font);
        ddsresult->setVerticalHeaderItem(3, __qtablewidgetitem9);
        QFont font11;
        font11.setFamily(QString::fromUtf8("Helvetica"));
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setFont(font11);
        ddsresult->setItem(0, 0, __qtablewidgetitem10);
        ddsresult->setObjectName(QString::fromUtf8("ddsresult"));
        ddsresult->setEnabled(true);
        ddsresult->setGeometry(QRect(0, 0, 533, 120));
        ddsresult->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ddsresult->setShowGrid(true);
        wid_anlys_dds->addTab(tab_anlys_dds, QString());
        tab_anlys_dds_n = new QWidget();
        tab_anlys_dds_n->setObjectName(QString::fromUtf8("tab_anlys_dds_n"));
        ddsresult_n = new QTableWidget(tab_anlys_dds_n);
        if (ddsresult_n->columnCount() < 6)
            ddsresult_n->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setFont(font);
        ddsresult_n->setHorizontalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setFont(font);
        ddsresult_n->setHorizontalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setFont(font);
        ddsresult_n->setHorizontalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setFont(font);
        ddsresult_n->setHorizontalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setFont(font);
        ddsresult_n->setHorizontalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setFont(font);
        ddsresult_n->setHorizontalHeaderItem(5, __qtablewidgetitem16);
        if (ddsresult_n->rowCount() < 4)
            ddsresult_n->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setFont(font);
        ddsresult_n->setVerticalHeaderItem(0, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setFont(font);
        ddsresult_n->setVerticalHeaderItem(1, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setFont(font);
        ddsresult_n->setVerticalHeaderItem(2, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setFont(font);
        ddsresult_n->setVerticalHeaderItem(3, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setFont(font11);
        ddsresult_n->setItem(0, 0, __qtablewidgetitem21);
        ddsresult_n->setObjectName(QString::fromUtf8("ddsresult_n"));
        ddsresult_n->setEnabled(true);
        ddsresult_n->setGeometry(QRect(0, 0, 533, 120));
        ddsresult_n->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ddsresult_n->setShowGrid(true);
        wid_anlys_dds->addTab(tab_anlys_dds_n, QString());
        tab_anlys_dds_e = new QWidget();
        tab_anlys_dds_e->setObjectName(QString::fromUtf8("tab_anlys_dds_e"));
        ddsresult_e = new QTableWidget(tab_anlys_dds_e);
        if (ddsresult_e->columnCount() < 6)
            ddsresult_e->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setFont(font);
        ddsresult_e->setHorizontalHeaderItem(0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setFont(font);
        ddsresult_e->setHorizontalHeaderItem(1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setFont(font);
        ddsresult_e->setHorizontalHeaderItem(2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setFont(font);
        ddsresult_e->setHorizontalHeaderItem(3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setFont(font);
        ddsresult_e->setHorizontalHeaderItem(4, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setFont(font);
        ddsresult_e->setHorizontalHeaderItem(5, __qtablewidgetitem27);
        if (ddsresult_e->rowCount() < 4)
            ddsresult_e->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setFont(font);
        ddsresult_e->setVerticalHeaderItem(0, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setFont(font);
        ddsresult_e->setVerticalHeaderItem(1, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setFont(font);
        ddsresult_e->setVerticalHeaderItem(2, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        __qtablewidgetitem31->setFont(font);
        ddsresult_e->setVerticalHeaderItem(3, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setFont(font11);
        ddsresult_e->setItem(0, 0, __qtablewidgetitem32);
        ddsresult_e->setObjectName(QString::fromUtf8("ddsresult_e"));
        ddsresult_e->setEnabled(true);
        ddsresult_e->setGeometry(QRect(0, 0, 533, 120));
        ddsresult_e->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ddsresult_e->setShowGrid(true);
        wid_anlys_dds->addTab(tab_anlys_dds_e, QString());
        tab_anlys_dds_s = new QWidget();
        tab_anlys_dds_s->setObjectName(QString::fromUtf8("tab_anlys_dds_s"));
        ddsresult_s = new QTableWidget(tab_anlys_dds_s);
        if (ddsresult_s->columnCount() < 6)
            ddsresult_s->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        __qtablewidgetitem33->setFont(font);
        ddsresult_s->setHorizontalHeaderItem(0, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        __qtablewidgetitem34->setFont(font);
        ddsresult_s->setHorizontalHeaderItem(1, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        __qtablewidgetitem35->setFont(font);
        ddsresult_s->setHorizontalHeaderItem(2, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        __qtablewidgetitem36->setFont(font);
        ddsresult_s->setHorizontalHeaderItem(3, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        __qtablewidgetitem37->setFont(font);
        ddsresult_s->setHorizontalHeaderItem(4, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        __qtablewidgetitem38->setFont(font);
        ddsresult_s->setHorizontalHeaderItem(5, __qtablewidgetitem38);
        if (ddsresult_s->rowCount() < 4)
            ddsresult_s->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        __qtablewidgetitem39->setFont(font);
        ddsresult_s->setVerticalHeaderItem(0, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        __qtablewidgetitem40->setFont(font);
        ddsresult_s->setVerticalHeaderItem(1, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        __qtablewidgetitem41->setFont(font);
        ddsresult_s->setVerticalHeaderItem(2, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        __qtablewidgetitem42->setFont(font);
        ddsresult_s->setVerticalHeaderItem(3, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        __qtablewidgetitem43->setFont(font11);
        ddsresult_s->setItem(0, 0, __qtablewidgetitem43);
        ddsresult_s->setObjectName(QString::fromUtf8("ddsresult_s"));
        ddsresult_s->setEnabled(true);
        ddsresult_s->setGeometry(QRect(0, 0, 533, 120));
        ddsresult_s->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ddsresult_s->setShowGrid(true);
        wid_anlys_dds->addTab(tab_anlys_dds_s, QString());
        tab_anlys_dds_w = new QWidget();
        tab_anlys_dds_w->setObjectName(QString::fromUtf8("tab_anlys_dds_w"));
        ddsresult_w = new QTableWidget(tab_anlys_dds_w);
        if (ddsresult_w->columnCount() < 6)
            ddsresult_w->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        __qtablewidgetitem44->setFont(font);
        ddsresult_w->setHorizontalHeaderItem(0, __qtablewidgetitem44);
        QTableWidgetItem *__qtablewidgetitem45 = new QTableWidgetItem();
        __qtablewidgetitem45->setFont(font);
        ddsresult_w->setHorizontalHeaderItem(1, __qtablewidgetitem45);
        QTableWidgetItem *__qtablewidgetitem46 = new QTableWidgetItem();
        __qtablewidgetitem46->setFont(font);
        ddsresult_w->setHorizontalHeaderItem(2, __qtablewidgetitem46);
        QTableWidgetItem *__qtablewidgetitem47 = new QTableWidgetItem();
        __qtablewidgetitem47->setFont(font);
        ddsresult_w->setHorizontalHeaderItem(3, __qtablewidgetitem47);
        QTableWidgetItem *__qtablewidgetitem48 = new QTableWidgetItem();
        __qtablewidgetitem48->setFont(font);
        ddsresult_w->setHorizontalHeaderItem(4, __qtablewidgetitem48);
        QTableWidgetItem *__qtablewidgetitem49 = new QTableWidgetItem();
        __qtablewidgetitem49->setFont(font);
        ddsresult_w->setHorizontalHeaderItem(5, __qtablewidgetitem49);
        if (ddsresult_w->rowCount() < 4)
            ddsresult_w->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem50 = new QTableWidgetItem();
        __qtablewidgetitem50->setFont(font);
        ddsresult_w->setVerticalHeaderItem(0, __qtablewidgetitem50);
        QTableWidgetItem *__qtablewidgetitem51 = new QTableWidgetItem();
        __qtablewidgetitem51->setFont(font);
        ddsresult_w->setVerticalHeaderItem(1, __qtablewidgetitem51);
        QTableWidgetItem *__qtablewidgetitem52 = new QTableWidgetItem();
        __qtablewidgetitem52->setFont(font);
        ddsresult_w->setVerticalHeaderItem(2, __qtablewidgetitem52);
        QTableWidgetItem *__qtablewidgetitem53 = new QTableWidgetItem();
        __qtablewidgetitem53->setFont(font);
        ddsresult_w->setVerticalHeaderItem(3, __qtablewidgetitem53);
        QTableWidgetItem *__qtablewidgetitem54 = new QTableWidgetItem();
        __qtablewidgetitem54->setFont(font11);
        ddsresult_w->setItem(0, 0, __qtablewidgetitem54);
        ddsresult_w->setObjectName(QString::fromUtf8("ddsresult_w"));
        ddsresult_w->setEnabled(true);
        ddsresult_w->setGeometry(QRect(0, 0, 533, 120));
        ddsresult_w->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ddsresult_w->setShowGrid(true);
        wid_anlys_dds->addTab(tab_anlys_dds_w, QString());
        brow_anlys_msg = new QTextBrowser(wid_anlys);
        brow_anlys_msg->setObjectName(QString::fromUtf8("brow_anlys_msg"));
        brow_anlys_msg->setGeometry(QRect(10, 295, 440, 240));
        QFont font12;
        font12.setPointSize(8);
        brow_anlys_msg->setFont(font12);
        tab_main->addTab(wid_anlys, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 22));
        QFont font13;
        font13.setFamily(QString::fromUtf8("Helvetica"));
        font13.setPointSize(10);
        font13.setBold(false);
        font13.setWeight(50);
        menuBar->setFont(font13);
        menuBar->setLayoutDirection(Qt::LeftToRight);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        QFont font14;
        font14.setFamily(QString::fromUtf8("Helvetica"));
        font14.setPointSize(10);
        font14.setBold(false);
        font14.setWeight(50);
        font14.setKerning(true);
        menuFile->setFont(font14);
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionUpdate_config);

        retranslateUi(MainWindow);

        tab_main->setCurrentIndex(0);
        tab_dealer_sethand->setCurrentIndex(0);
        biddingwidget->setCurrentIndex(0);
        cb_c_hi->setCurrentIndex(13);
        cb_h_hi->setCurrentIndex(13);
        cb_m_hi->setCurrentIndex(13);
        cb_s_hi->setCurrentIndex(13);
        cb_M_hi->setCurrentIndex(13);
        cb_d_hi->setCurrentIndex(13);
        cb_hcp_hi->setCurrentIndex(37);
        cb_hcp_lo->setCurrentIndex(0);
        anlymsg_tab_set->setCurrentIndex(0);
        wid_anlys_dds->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionUpdate_config->setText(QApplication::translate("MainWindow", "Update Config", nullptr));
        actionUpdate_config->setIconText(QApplication::translate("MainWindow", "Update Config", nullptr));
        edit_e->setText(QString());
        edit_e->setPlaceholderText(QApplication::translate("MainWindow", "HCP Min = 0, Max = 37", nullptr));
        n->setText(QApplication::translate("MainWindow", "N", nullptr));
        edit_w->setText(QString());
        w->setText(QApplication::translate("MainWindow", "W", nullptr));
        edit_s->setText(QString());
        edit_n->setInputMask(QString());
        edit_n->setText(QString());
        edit_n->setPlaceholderText(QApplication::translate("MainWindow", "e.g. AK.Q432.T9862.54", nullptr));
        e->setText(QApplication::translate("MainWindow", "E", nullptr));
        s->setText(QApplication::translate("MainWindow", "S", nullptr));
        deal_tar->setText(QApplication::translate("MainWindow", "Produced Deals", nullptr));
        edit_deal_tar->setText(QApplication::translate("MainWindow", "1000", nullptr));
        btn_deal_click->setText(QApplication::translate("MainWindow", "Deal", nullptr));
        edit_deal_max->setText(QApplication::translate("MainWindow", "1000", nullptr));
        deal_max->setText(QApplication::translate("MainWindow", "Produced Maxed", nullptr));

        const bool __sortingEnabled = list_nor_setting->isSortingEnabled();
        list_nor_setting->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = list_nor_setting->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "New", nullptr));
        list_nor_setting->setSortingEnabled(__sortingEnabled);

#ifndef QT_NO_STATUSTIP
        list_nor_setting->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        tab_dealer_sethand->setTabText(tab_dealer_sethand->indexOf(tab_normal), QApplication::translate("MainWindow", "Normal", nullptr));
        bidding_box->setTitle(QApplication::translate("MainWindow", "BiddingBox", nullptr));
        h6->setText(QApplication::translate("MainWindow", "6\342\231\245", nullptr));
        d5->setText(QApplication::translate("MainWindow", "5\342\231\246", nullptr));
        x->setText(QApplication::translate("MainWindow", "X", nullptr));
        c4->setText(QApplication::translate("MainWindow", "4\342\231\243", nullptr));
        d1->setText(QApplication::translate("MainWindow", "1\342\231\246", nullptr));
        d3->setText(QApplication::translate("MainWindow", "3\342\231\246", nullptr));
        h4->setText(QApplication::translate("MainWindow", "4\342\231\245", nullptr));
        nt1->setText(QApplication::translate("MainWindow", "1NT", nullptr));
        pass->setText(QApplication::translate("MainWindow", "PASS", nullptr));
        s3->setText(QApplication::translate("MainWindow", "3\342\231\240", nullptr));
        s6->setText(QApplication::translate("MainWindow", "6\342\231\240", nullptr));
        h1->setText(QApplication::translate("MainWindow", "1\342\231\245", nullptr));
        c6->setText(QApplication::translate("MainWindow", "6\342\231\243", nullptr));
        h7->setText(QApplication::translate("MainWindow", "7\342\231\245", nullptr));
        d7->setText(QApplication::translate("MainWindow", "7\342\231\246", nullptr));
        c5->setText(QApplication::translate("MainWindow", "5\342\231\243", nullptr));
        nt5->setText(QApplication::translate("MainWindow", "5NT", nullptr));
        nt6->setText(QApplication::translate("MainWindow", "6NT", nullptr));
        h5->setText(QApplication::translate("MainWindow", "5\342\231\245", nullptr));
        nt4->setText(QApplication::translate("MainWindow", "4NT", nullptr));
        s2->setText(QApplication::translate("MainWindow", "2\342\231\240", nullptr));
        c2->setText(QApplication::translate("MainWindow", "2\342\231\243", nullptr));
        c7->setText(QApplication::translate("MainWindow", "7\342\231\243", nullptr));
        s7->setText(QApplication::translate("MainWindow", "7\342\231\240", nullptr));
        nt2->setText(QApplication::translate("MainWindow", "2NT", nullptr));
        s4->setText(QApplication::translate("MainWindow", "4\342\231\240", nullptr));
        s5->setText(QApplication::translate("MainWindow", "5\342\231\240", nullptr));
        h2->setText(QApplication::translate("MainWindow", "2\342\231\245", nullptr));
        xx->setText(QApplication::translate("MainWindow", "XX", nullptr));
        nt3->setText(QApplication::translate("MainWindow", "3NT", nullptr));
        d2->setText(QApplication::translate("MainWindow", "2\342\231\246", nullptr));
        d6->setText(QApplication::translate("MainWindow", "6\342\231\246", nullptr));
        c1->setText(QApplication::translate("MainWindow", "1\342\231\243", nullptr));
        s1->setText(QApplication::translate("MainWindow", "1\342\231\240", nullptr));
        h3->setText(QApplication::translate("MainWindow", "3\342\231\245", nullptr));
        c3->setText(QApplication::translate("MainWindow", "3\342\231\243", nullptr));
        d4->setText(QApplication::translate("MainWindow", "4\342\231\246", nullptr));
        nt7->setText(QApplication::translate("MainWindow", "7NT", nullptr));
        biddingwidget->setTabText(biddingwidget->indexOf(wid_bdt), QApplication::translate("MainWindow", "Bidding", nullptr));
        ns_vul->setText(QApplication::translate("MainWindow", "NS", nullptr));
        ew_vul->setText(QApplication::translate("MainWindow", "EW", nullptr));
        vul->setText(QApplication::translate("MainWindow", "Vulnerable", nullptr));
        tab_dealer_sethand->setTabText(tab_dealer_sethand->indexOf(tab_bdbox), QApplication::translate("MainWindow", "Biddings", nullptr));
        adv_set_box->setTitle(QApplication::translate("MainWindow", "Advanced", nullptr));
        cb_c_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_c_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_c_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_c_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_c_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_c_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_c_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_c_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_c_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_c_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_c_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_c_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_c_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_c_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_c_hi->setCurrentText(QApplication::translate("MainWindow", "13", nullptr));
        cb_c_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_c_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_c_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_c_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_c_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_c_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_c_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_c_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_c_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_c_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_c_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_c_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_c_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_c_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_h_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_h_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_h_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_h_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_h_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_h_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_h_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_h_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_h_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_h_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_h_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_h_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_h_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_h_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_h_hi->setCurrentText(QApplication::translate("MainWindow", "13", nullptr));
        hcp->setText(QApplication::translate("MainWindow", "HCP", nullptr));
        spade->setText(QApplication::translate("MainWindow", "\342\231\240Spades", nullptr));
        cb_m_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_m_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_m_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_m_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_m_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_m_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_m_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_m_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_m_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_m_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_m_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_m_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_m_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_m_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_m_hi->setCurrentText(QApplication::translate("MainWindow", "13", nullptr));
        cb_s_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_s_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_s_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_s_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_s_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_s_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_s_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_s_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_s_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_s_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_s_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_s_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_s_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_s_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_s_hi->setCurrentText(QApplication::translate("MainWindow", "13", nullptr));
        cb_M_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_M_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_M_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_M_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_M_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_M_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_M_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_M_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_M_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_M_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_M_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_M_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_M_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_M_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_M_hi->setCurrentText(QApplication::translate("MainWindow", "13", nullptr));
        cb_M_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_M_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_M_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_M_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_M_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_M_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_M_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_M_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_M_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_M_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_M_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_M_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_M_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_M_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_d_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_d_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_d_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_d_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_d_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_d_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_d_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_d_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_d_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_d_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_d_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_d_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_d_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_d_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_d_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_d_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_d_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_d_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_d_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_d_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_d_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_d_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_d_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_d_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_d_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_d_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_d_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_d_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_d_hi->setCurrentText(QApplication::translate("MainWindow", "13", nullptr));
        cb_s_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_s_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_s_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_s_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_s_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_s_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_s_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_s_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_s_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_s_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_s_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_s_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_s_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_s_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        heart->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0000;\">\342\231\245</span>Hearts</p></body></html>", nullptr));
        cb_m_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_m_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_m_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_m_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_m_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_m_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_m_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_m_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_m_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_m_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_m_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_m_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_m_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_m_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#404040;\">\342\231\243</span>Clubs</p></body></html>", nullptr));
        cb_h_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_h_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_h_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_h_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_h_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_h_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_h_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_h_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_h_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_h_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_h_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_h_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_h_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_h_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));

        cb_hcp_hi->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_hcp_hi->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_hcp_hi->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_hcp_hi->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_hcp_hi->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_hcp_hi->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_hcp_hi->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_hcp_hi->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_hcp_hi->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_hcp_hi->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_hcp_hi->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_hcp_hi->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_hcp_hi->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_hcp_hi->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));
        cb_hcp_hi->setItemText(14, QApplication::translate("MainWindow", "14", nullptr));
        cb_hcp_hi->setItemText(15, QApplication::translate("MainWindow", "15", nullptr));
        cb_hcp_hi->setItemText(16, QApplication::translate("MainWindow", "16", nullptr));
        cb_hcp_hi->setItemText(17, QApplication::translate("MainWindow", "17", nullptr));
        cb_hcp_hi->setItemText(18, QApplication::translate("MainWindow", "18", nullptr));
        cb_hcp_hi->setItemText(19, QApplication::translate("MainWindow", "19", nullptr));
        cb_hcp_hi->setItemText(20, QApplication::translate("MainWindow", "20", nullptr));
        cb_hcp_hi->setItemText(21, QApplication::translate("MainWindow", "21", nullptr));
        cb_hcp_hi->setItemText(22, QApplication::translate("MainWindow", "22", nullptr));
        cb_hcp_hi->setItemText(23, QApplication::translate("MainWindow", "23", nullptr));
        cb_hcp_hi->setItemText(24, QApplication::translate("MainWindow", "24", nullptr));
        cb_hcp_hi->setItemText(25, QApplication::translate("MainWindow", "25", nullptr));
        cb_hcp_hi->setItemText(26, QApplication::translate("MainWindow", "26", nullptr));
        cb_hcp_hi->setItemText(27, QApplication::translate("MainWindow", "27", nullptr));
        cb_hcp_hi->setItemText(28, QApplication::translate("MainWindow", "28", nullptr));
        cb_hcp_hi->setItemText(29, QApplication::translate("MainWindow", "29", nullptr));
        cb_hcp_hi->setItemText(30, QApplication::translate("MainWindow", "30", nullptr));
        cb_hcp_hi->setItemText(31, QApplication::translate("MainWindow", "31", nullptr));
        cb_hcp_hi->setItemText(32, QApplication::translate("MainWindow", "32", nullptr));
        cb_hcp_hi->setItemText(33, QApplication::translate("MainWindow", "33", nullptr));
        cb_hcp_hi->setItemText(34, QApplication::translate("MainWindow", "34", nullptr));
        cb_hcp_hi->setItemText(35, QApplication::translate("MainWindow", "35", nullptr));
        cb_hcp_hi->setItemText(36, QApplication::translate("MainWindow", "36", nullptr));
        cb_hcp_hi->setItemText(37, QApplication::translate("MainWindow", "37", nullptr));

        cb_hcp_hi->setCurrentText(QApplication::translate("MainWindow", "37", nullptr));
        major->setText(QApplication::translate("MainWindow", "Majors", nullptr));
        diamond->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff3600;\">\342\231\246</span>Diamonds</p></body></html>", nullptr));
        minor->setText(QApplication::translate("MainWindow", "Minors", nullptr));
        cb_hcp_lo->setItemText(0, QApplication::translate("MainWindow", "0", nullptr));
        cb_hcp_lo->setItemText(1, QApplication::translate("MainWindow", "1", nullptr));
        cb_hcp_lo->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));
        cb_hcp_lo->setItemText(3, QApplication::translate("MainWindow", "3", nullptr));
        cb_hcp_lo->setItemText(4, QApplication::translate("MainWindow", "4", nullptr));
        cb_hcp_lo->setItemText(5, QApplication::translate("MainWindow", "5", nullptr));
        cb_hcp_lo->setItemText(6, QApplication::translate("MainWindow", "6", nullptr));
        cb_hcp_lo->setItemText(7, QApplication::translate("MainWindow", "7", nullptr));
        cb_hcp_lo->setItemText(8, QApplication::translate("MainWindow", "8", nullptr));
        cb_hcp_lo->setItemText(9, QApplication::translate("MainWindow", "9", nullptr));
        cb_hcp_lo->setItemText(10, QApplication::translate("MainWindow", "10", nullptr));
        cb_hcp_lo->setItemText(11, QApplication::translate("MainWindow", "11", nullptr));
        cb_hcp_lo->setItemText(12, QApplication::translate("MainWindow", "12", nullptr));
        cb_hcp_lo->setItemText(13, QApplication::translate("MainWindow", "13", nullptr));
        cb_hcp_lo->setItemText(14, QApplication::translate("MainWindow", "14", nullptr));
        cb_hcp_lo->setItemText(15, QApplication::translate("MainWindow", "15", nullptr));
        cb_hcp_lo->setItemText(16, QApplication::translate("MainWindow", "16", nullptr));
        cb_hcp_lo->setItemText(17, QApplication::translate("MainWindow", "17", nullptr));
        cb_hcp_lo->setItemText(18, QApplication::translate("MainWindow", "18", nullptr));
        cb_hcp_lo->setItemText(19, QApplication::translate("MainWindow", "19", nullptr));
        cb_hcp_lo->setItemText(20, QApplication::translate("MainWindow", "20", nullptr));
        cb_hcp_lo->setItemText(21, QApplication::translate("MainWindow", "21", nullptr));
        cb_hcp_lo->setItemText(22, QApplication::translate("MainWindow", "22", nullptr));
        cb_hcp_lo->setItemText(23, QApplication::translate("MainWindow", "23", nullptr));
        cb_hcp_lo->setItemText(24, QApplication::translate("MainWindow", "24", nullptr));
        cb_hcp_lo->setItemText(25, QApplication::translate("MainWindow", "25", nullptr));
        cb_hcp_lo->setItemText(26, QApplication::translate("MainWindow", "26", nullptr));
        cb_hcp_lo->setItemText(27, QApplication::translate("MainWindow", "27", nullptr));
        cb_hcp_lo->setItemText(28, QApplication::translate("MainWindow", "28", nullptr));
        cb_hcp_lo->setItemText(29, QApplication::translate("MainWindow", "29", nullptr));
        cb_hcp_lo->setItemText(30, QApplication::translate("MainWindow", "30", nullptr));
        cb_hcp_lo->setItemText(31, QApplication::translate("MainWindow", "31", nullptr));
        cb_hcp_lo->setItemText(32, QApplication::translate("MainWindow", "32", nullptr));
        cb_hcp_lo->setItemText(33, QApplication::translate("MainWindow", "33", nullptr));
        cb_hcp_lo->setItemText(34, QApplication::translate("MainWindow", "34", nullptr));
        cb_hcp_lo->setItemText(35, QApplication::translate("MainWindow", "35", nullptr));
        cb_hcp_lo->setItemText(36, QApplication::translate("MainWindow", "36", nullptr));
        cb_hcp_lo->setItemText(37, QApplication::translate("MainWindow", "37", nullptr));

#ifndef QT_NO_STATUSTIP
        cb_hcp_lo->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        ckb_w->setText(QApplication::translate("MainWindow", "W", nullptr));
        ckb_s->setText(QApplication::translate("MainWindow", "S", nullptr));
        ckb_e->setText(QApplication::translate("MainWindow", "E", nullptr));
        ckb_n->setText(QApplication::translate("MainWindow", "N", nullptr));
        distr->setText(QApplication::translate("MainWindow", "Distribution", nullptr));
        pb_bal->setText(QApplication::translate("MainWindow", "BAL", nullptr));
        edit_distr->setPlaceholderText(QApplication::translate("MainWindow", "(4333)+4432+4441", nullptr));
        pb_reset->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        pb_clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        pb_undo->setText(QApplication::translate("MainWindow", "Undo", nullptr));
        pb_del->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        pb_sub->setText(QApplication::translate("MainWindow", "Submit", nullptr));
        gb_tips->setTitle(QApplication::translate("MainWindow", "Tips", nullptr));
        brow_tips->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Helvetica'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">You can write advanced settings</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">         in the Distribution section</span><span style=\" font-family:'Helvetica'; color:#ffff00;\">.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">The f"
                        "ormat : </span><span style=\" font-family:'Helvetica'; color:#ff0000;\">dist./adv./adv./...</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">    </span><span style=\" font-family:'Helvetica'; font-size:9pt;\">e.g. (5332)/ltc 6-8</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">    </span><span style=\" font-family:'Helvetica'; font-size:9pt;\">e.g. 4432+4333/sh 7-8</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">    </span><span style=\" font-family:'Helvetica'; font-size:9pt;\">e.g. /ltc 6-8</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><sp"
                        "an style=\" font-family:'Helvetica';\">        </span><span style=\" font-family:'Helvetica'; font-size:8pt;\">note. a &quot;/&quot; before adv.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#ff0000;\">Key words :</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">   </span><span style=\" font-family:'Helvetica'; color:#0000ff;\"> /[suit][suit](space)[range]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">        suit = s, h, d, c, M or m</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">        ran"
                        "ge = (number)-(number)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">            </span><span style=\" font-family:'Helvetica'; font-size:9pt;\">e.g. /sh 5-10</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">        </span><span style=\" font-family:'Helvetica'; font-size:8pt;\">note. always high-low(sh not hs)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">    </span><span style=\" font-family:'Helvetica'; color:#0000ff;\">/ltc(space)[range]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">    (ltc"
                        ": Losing-Trick Count)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">        range = (number)-(number)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">            </span><span style=\" font-family:'Helvetica'; font-size:9pt;\">e.g. /ltc 6-8</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:8pt;\">            note. /ltc (num) means ltc &lt; num</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">    </span><span style=\" font-family:'Helvetica'; color:#0000ff;\">/shc(space)[suit][range]</span></p>\n"
""
                        "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#0000ff;\">    </span><span style=\" font-family:'Helvetica'; color:#000000;\">(shc: Suit-Honor Count)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">        suit = s, h, d, c</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">        range = (number)-(number)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">                        or (solid)-(solid)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left"
                        ":0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">            solid = S, s, p</span><span style=\" font-family:'Helvetica'; font-size:8pt; color:#000000;\"> </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">            </span><span style=\" font-family:'Helvetica'; font-size:9pt; color:#000000;\">e.g. /shc s 0-3</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">            </span><span style=\" font-family:'Helvetica'; font-size:9pt; color:#000000;\">e.g. /shc s s-S</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">    "
                        "    </span><span style=\" font-family:'Helvetica'; font-size:8pt; color:#000000;\">note. 'S' solid, 's' semi-solid</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:8pt; color:#000000;\">                        ,  'p' others</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">   </span><span style=\" font-family:'Helvetica'; color:#0000ff;\"> /law(space)[level]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">    (law: rule of 2, 3)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Hel"
                        "vetica'; color:#000000;\">        level = (number)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">            </span><span style=\" font-family:'Helvetica'; font-size:9pt; color:#000000;\">e.g. /law 2</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:8pt; color:#000000;\">           note. rule of 4 is not included</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; color:#000000;\">   </span><span style=\" font-family:'Helvetica'; color:#0000ff;\"> /hwp(space)[range]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style"
                        "=\" font-family:'Helvetica'; color:#0000ff;\">    </span><span style=\" font-family:'Helvetica'; color:#000000;\">(hwp: this player's hcp plus its partner's)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica';\">        </span><span style=\" font-family:'Helvetica'; font-size:9pt;\">e.g. /hwp 20-21</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">    /wph(space)[a_suit][b_suit](space)[range]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">    (wph: with partner hand)</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><spa"
                        "n style=\" font-family:'Helvetica'; font-size:9pt;\">           e.g. /wph ss 5-9</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">                   note. a_suit = o means w/o b_suit, other suits must fit the condition.</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">    </span><span style=\" font-family:'Helvetica'; font-size:9pt; color:#0000ff;\">/skc(space)[suit/cards](space)[num](space)[keycard](space)[option]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">        e.g /skc s 2 K 0 or /skc 2 1 J 1</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margi"
                        "n-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">            &quot;/skc s 2 K 0&quot; means s has at least two cards bigger than K</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Helvetica'; font-size:9pt;\">            &quot;/skc 2 1 J 1&quot; means every suits which have 2 cards have Jx</span></p></body></html>", nullptr));
        tab_main->setTabText(tab_main->indexOf(wid_main), QApplication::translate("MainWindow", "Dealer", nullptr));
        gb_anlys_setting->setTitle(QApplication::translate("MainWindow", "General Setup", nullptr));
        pb_anlys_file_open->setText(QApplication::translate("MainWindow", "...", nullptr));
        gb_anlys_bidding_and_hand->setTitle(QApplication::translate("MainWindow", "Bidding and Hands", nullptr));
        anlymsg_tab_set->setTabText(anlymsg_tab_set->indexOf(anlys_tab), QApplication::translate("MainWindow", "Information", nullptr));
        anlymsg_tab_set->setTabText(anlymsg_tab_set->indexOf(anlys_tab_2), QApplication::translate("MainWindow", "Suggestion", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ddsresult->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "NT", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ddsresult->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Spade", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = ddsresult->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Heart", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = ddsresult->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "Diamond", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = ddsresult->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "Club", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = ddsresult->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "HCP", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = ddsresult->verticalHeaderItem(0);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "  N  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = ddsresult->verticalHeaderItem(1);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "  E  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = ddsresult->verticalHeaderItem(2);
        ___qtablewidgetitem8->setText(QApplication::translate("MainWindow", "  S  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = ddsresult->verticalHeaderItem(3);
        ___qtablewidgetitem9->setText(QApplication::translate("MainWindow", "  W  ", nullptr));

        const bool __sortingEnabled1 = ddsresult->isSortingEnabled();
        ddsresult->setSortingEnabled(false);
        ddsresult->setSortingEnabled(__sortingEnabled1);

        wid_anlys_dds->setTabText(wid_anlys_dds->indexOf(tab_anlys_dds), QApplication::translate("MainWindow", "Double Dummy Solver", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = ddsresult_n->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("MainWindow", "NT", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = ddsresult_n->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QApplication::translate("MainWindow", "Spade", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = ddsresult_n->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QApplication::translate("MainWindow", "Heart", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = ddsresult_n->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QApplication::translate("MainWindow", "Diamond", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = ddsresult_n->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QApplication::translate("MainWindow", "Club", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = ddsresult_n->horizontalHeaderItem(5);
        ___qtablewidgetitem15->setText(QApplication::translate("MainWindow", "HCP", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = ddsresult_n->verticalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("MainWindow", "  N  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = ddsresult_n->verticalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("MainWindow", "  E  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = ddsresult_n->verticalHeaderItem(2);
        ___qtablewidgetitem18->setText(QApplication::translate("MainWindow", "  S  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = ddsresult_n->verticalHeaderItem(3);
        ___qtablewidgetitem19->setText(QApplication::translate("MainWindow", "  W  ", nullptr));

        const bool __sortingEnabled2 = ddsresult_n->isSortingEnabled();
        ddsresult_n->setSortingEnabled(false);
        ddsresult_n->setSortingEnabled(__sortingEnabled2);

        wid_anlys_dds->setTabText(wid_anlys_dds->indexOf(tab_anlys_dds_n), QApplication::translate("MainWindow", "North", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = ddsresult_e->horizontalHeaderItem(0);
        ___qtablewidgetitem20->setText(QApplication::translate("MainWindow", "NT", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = ddsresult_e->horizontalHeaderItem(1);
        ___qtablewidgetitem21->setText(QApplication::translate("MainWindow", "Spade", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = ddsresult_e->horizontalHeaderItem(2);
        ___qtablewidgetitem22->setText(QApplication::translate("MainWindow", "Heart", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = ddsresult_e->horizontalHeaderItem(3);
        ___qtablewidgetitem23->setText(QApplication::translate("MainWindow", "Diamond", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = ddsresult_e->horizontalHeaderItem(4);
        ___qtablewidgetitem24->setText(QApplication::translate("MainWindow", "Club", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = ddsresult_e->horizontalHeaderItem(5);
        ___qtablewidgetitem25->setText(QApplication::translate("MainWindow", "HCP", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = ddsresult_e->verticalHeaderItem(0);
        ___qtablewidgetitem26->setText(QApplication::translate("MainWindow", "  N  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = ddsresult_e->verticalHeaderItem(1);
        ___qtablewidgetitem27->setText(QApplication::translate("MainWindow", "  E  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = ddsresult_e->verticalHeaderItem(2);
        ___qtablewidgetitem28->setText(QApplication::translate("MainWindow", "  S  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = ddsresult_e->verticalHeaderItem(3);
        ___qtablewidgetitem29->setText(QApplication::translate("MainWindow", "  W  ", nullptr));

        const bool __sortingEnabled3 = ddsresult_e->isSortingEnabled();
        ddsresult_e->setSortingEnabled(false);
        ddsresult_e->setSortingEnabled(__sortingEnabled3);

        wid_anlys_dds->setTabText(wid_anlys_dds->indexOf(tab_anlys_dds_e), QApplication::translate("MainWindow", "East", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = ddsresult_s->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QApplication::translate("MainWindow", "NT", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = ddsresult_s->horizontalHeaderItem(1);
        ___qtablewidgetitem31->setText(QApplication::translate("MainWindow", "Spade", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = ddsresult_s->horizontalHeaderItem(2);
        ___qtablewidgetitem32->setText(QApplication::translate("MainWindow", "Heart", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = ddsresult_s->horizontalHeaderItem(3);
        ___qtablewidgetitem33->setText(QApplication::translate("MainWindow", "Diamond", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = ddsresult_s->horizontalHeaderItem(4);
        ___qtablewidgetitem34->setText(QApplication::translate("MainWindow", "Club", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = ddsresult_s->horizontalHeaderItem(5);
        ___qtablewidgetitem35->setText(QApplication::translate("MainWindow", "HCP", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = ddsresult_s->verticalHeaderItem(0);
        ___qtablewidgetitem36->setText(QApplication::translate("MainWindow", "  N  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = ddsresult_s->verticalHeaderItem(1);
        ___qtablewidgetitem37->setText(QApplication::translate("MainWindow", "  E  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = ddsresult_s->verticalHeaderItem(2);
        ___qtablewidgetitem38->setText(QApplication::translate("MainWindow", "  S  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = ddsresult_s->verticalHeaderItem(3);
        ___qtablewidgetitem39->setText(QApplication::translate("MainWindow", "  W  ", nullptr));

        const bool __sortingEnabled4 = ddsresult_s->isSortingEnabled();
        ddsresult_s->setSortingEnabled(false);
        ddsresult_s->setSortingEnabled(__sortingEnabled4);

        wid_anlys_dds->setTabText(wid_anlys_dds->indexOf(tab_anlys_dds_s), QApplication::translate("MainWindow", "South", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = ddsresult_w->horizontalHeaderItem(0);
        ___qtablewidgetitem40->setText(QApplication::translate("MainWindow", "NT", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = ddsresult_w->horizontalHeaderItem(1);
        ___qtablewidgetitem41->setText(QApplication::translate("MainWindow", "Spade", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = ddsresult_w->horizontalHeaderItem(2);
        ___qtablewidgetitem42->setText(QApplication::translate("MainWindow", "Heart", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = ddsresult_w->horizontalHeaderItem(3);
        ___qtablewidgetitem43->setText(QApplication::translate("MainWindow", "Diamond", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = ddsresult_w->horizontalHeaderItem(4);
        ___qtablewidgetitem44->setText(QApplication::translate("MainWindow", "Club", nullptr));
        QTableWidgetItem *___qtablewidgetitem45 = ddsresult_w->horizontalHeaderItem(5);
        ___qtablewidgetitem45->setText(QApplication::translate("MainWindow", "HCP", nullptr));
        QTableWidgetItem *___qtablewidgetitem46 = ddsresult_w->verticalHeaderItem(0);
        ___qtablewidgetitem46->setText(QApplication::translate("MainWindow", "  N  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem47 = ddsresult_w->verticalHeaderItem(1);
        ___qtablewidgetitem47->setText(QApplication::translate("MainWindow", "  E  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem48 = ddsresult_w->verticalHeaderItem(2);
        ___qtablewidgetitem48->setText(QApplication::translate("MainWindow", "  S  ", nullptr));
        QTableWidgetItem *___qtablewidgetitem49 = ddsresult_w->verticalHeaderItem(3);
        ___qtablewidgetitem49->setText(QApplication::translate("MainWindow", "  W  ", nullptr));

        const bool __sortingEnabled5 = ddsresult_w->isSortingEnabled();
        ddsresult_w->setSortingEnabled(false);
        ddsresult_w->setSortingEnabled(__sortingEnabled5);

        wid_anlys_dds->setTabText(wid_anlys_dds->indexOf(tab_anlys_dds_w), QApplication::translate("MainWindow", "West", nullptr));
        tab_main->setTabText(tab_main->indexOf(wid_anlys), QApplication::translate("MainWindow", "Analyst", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "  File  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
