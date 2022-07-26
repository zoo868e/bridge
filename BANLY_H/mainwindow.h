#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QFileDialog>
#include <QDateTime>
#include <QScrollBar>
#include <QTextStream>
#include <QElapsedTimer>
#include <QBitArray>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPen>
#include "anlys.h"
#include "config.h"
#include "dealer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//private slots:
    void on_tab_dealer_sethand_currentChanged(int index);
    void on_bdt_cellClicked(int row, int column);
    void on_nt1_clicked();
    void on_s1_clicked();
    void on_h1_clicked();
    void on_d1_clicked();
    void on_c1_clicked();
    void on_nt2_clicked();
    void on_s2_clicked();
    void on_h2_clicked();
    void on_d2_clicked();
    void on_c2_clicked();
    void on_nt3_clicked();
    void on_s3_clicked();
    void on_h3_clicked();
    void on_d3_clicked();
    void on_c3_clicked();
    void on_nt4_clicked();
    void on_s4_clicked();
    void on_h4_clicked();
    void on_d4_clicked();
    void on_c4_clicked();
    void on_nt5_clicked();
    void on_s5_clicked();
    void on_h5_clicked();
    void on_d5_clicked();
    void on_c5_clicked();
    void on_nt6_clicked();
    void on_s6_clicked();
    void on_h6_clicked();
    void on_d6_clicked();
    void on_c6_clicked();
    void on_nt7_clicked();
    void on_s7_clicked();
    void on_h7_clicked();
    void on_d7_clicked();
    void on_c7_clicked();
    void on_pass_clicked();
    void on_xx_clicked();
    void on_x_clicked();
    void on_ns_vul_clicked();
    void on_ew_vul_clicked();
    void on_pb_bal_clicked();
    void on_pb_del_clicked();
    void on_pb_clear_clicked();
    void on_pb_undo_clicked();
    void on_pb_reset_clicked();
    void on_ckb_n_stateChanged(int arg1);
    void on_ckb_e_stateChanged(int arg1);
    void on_ckb_s_stateChanged(int arg1);
    void on_ckb_w_stateChanged(int arg1);
    void on_pb_sub_clicked(std::string pos, int s_lo = 0, int s_hi = 13, int h_lo = 0, int h_hi = 13, int d_lo = 0, int d_hi = 13, int c_lo = 0, int c_hi = 13, int M_lo = 0, int M_hi = 13, int m_lo = 0, int m_hi = 13, int hcp_lo = 0, int hcp_hi = 37, std::string edit_distr = std::string());
    void on_edit_deal_max_textChanged(const QString &arg1);
    void on_edit_deal_tar_textChanged(const QString &arg1);
    void on_btn_deal_click_clicked(std::string edit_n = std::string(), std::string edit_e = std::string(), std::string edit_s = std::string(), std::string edit_w = std::string());

    void on_pb_anlys_file_open_clicked();

private:
    Ui::MainWindow *ui;
    void init_();
    void set_config();
    void checkbd(int level, int suit);
    void checkbds();
    void resetpb();
    void init_anlys_bdahmsg(int pos);
};

#endif // MAINWINDOW_H
