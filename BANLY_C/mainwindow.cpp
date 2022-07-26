#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_dealer_sethand->setCurrentIndex(0);
    on_pb_reset_clicked();
    ui->edit_anlys_bdah->setReadOnly(1);
    init_();
    set_config();
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::init_(){
    ui->ddsresult->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_n->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_n->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_e->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_e->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_s->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_s->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_w->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ddsresult_w->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
void MainWindow::set_config(){
    QFile cfg("baconfig");
    if(QFile::exists("baconfig")){
        if(cfg.open(QIODevice::ReadOnly)){
            QTextStream ts(&cfg);
            QString line;
            QStringList cfgset;
            int size;
            while(!ts.atEnd()){
                line = ts.readLine();
                cfgset = line.split(" ", QString::SkipEmptyParts);
                size = cfgset.size();
                if(cfgset[0] == "<hcp>"){
                    for(int i = 1; i < size; ++i)
                       config::hcp[i-1] = cfgset.at(i).toFloat();
                }else if(cfgset[0] == "<card>"){
                    for(int i = 1; i < size; ++i)
                       config::card[i-1] = cfgset.at(i).toFloat();
                }else if(cfgset[0] == "<usr_deal>"){
                    config::pos_deal = cfgset[1].toInt();
                }else if(cfgset[0] == "<deal_setting>"){
                    config::limit_deal = cfgset[1].toInt();
                    config::deal = cfgset[2].toInt();
                    ui->edit_deal_max->setText(cfgset[1]);
                    ui->edit_deal_tar->setText(cfgset[2]);
                }else if(cfgset[0] == "<pos_deal>"){
                    config::pos_deal = cfgset[1].toInt();
                }else break;
            }
        }
    }
}
// For config setting
void MainWindow::on_edit_deal_max_textChanged(const QString &arg1){
    config::limit_deal = arg1.toInt();
}
void MainWindow::on_edit_deal_tar_textChanged(const QString &arg1){
    config::deal = arg1.toInt();
}
// For normal setting
void MainWindow::on_tab_dealer_sethand_currentChanged(int index){
    int cur = index;
    bool status;

    if(cur == 0) status = true;
    else status = false;
    ui->pb_undo->setVisible(!status);
    if(status) ui->list_nor_setting->setCurrentRow(0);
    if(config::bds.size() > 0){
        ui->list_nor_setting->setVisible(0);
        ui->ckb_n->setVisible(0);
        ui->ckb_e->setVisible(0);
        ui->ckb_s->setVisible(0);
        ui->ckb_w->setVisible(0);
    }
    else{
        ui->list_nor_setting->setVisible(1);
        ui->ckb_n->setVisible(status);
        ui->ckb_e->setVisible(status);
        ui->ckb_s->setVisible(status);
        ui->ckb_w->setVisible(status);
    }

}
void MainWindow::on_ckb_n_stateChanged(int arg1){
    if(arg1 == 2){  config::check_pos = "N/";}
}
void MainWindow::on_ckb_e_stateChanged(int arg1){
    if(arg1 == 2){  config::check_pos = "E/";}
}
void MainWindow::on_ckb_s_stateChanged(int arg1){
    if(arg1 == 2){  config::check_pos = "S/";}
}
void MainWindow::on_ckb_w_stateChanged(int arg1){
    if(arg1 == 2){  config::check_pos = "W/";}
}
// For bidding table
void MainWindow::resetpb(){
    ui->pass->setEnabled(true);
    ui->x->setEnabled(false);
    ui->xx->setEnabled(false);
    ui->nt7->setEnabled(true);
    ui->s7->setEnabled(true);
    ui->h7->setEnabled(true);
    ui->d7->setEnabled(true);
    ui->c7->setEnabled(true);
    ui->nt6->setEnabled(true);
    ui->s6->setEnabled(true);
    ui->h6->setEnabled(true);
    ui->d6->setEnabled(true);
    ui->c6->setEnabled(true);
    ui->nt5->setEnabled(true);
    ui->s5->setEnabled(true);
    ui->h5->setEnabled(true);
    ui->d5->setEnabled(true);
    ui->c5->setEnabled(true);
    ui->nt4->setEnabled(true);
    ui->s4->setEnabled(true);
    ui->h4->setEnabled(true);
    ui->d4->setEnabled(true);
    ui->c4->setEnabled(true);
    ui->nt3->setEnabled(true);
    ui->s3->setEnabled(true);
    ui->h3->setEnabled(true);
    ui->d3->setEnabled(true);
    ui->c3->setEnabled(true);
    ui->nt2->setEnabled(true);
    ui->s2->setEnabled(true);
    ui->h2->setEnabled(true);
    ui->d2->setEnabled(true);
    ui->c2->setEnabled(true);
    ui->nt1->setEnabled(true);
    ui->s1->setEnabled(true);
    ui->h1->setEnabled(true);
    ui->d1->setEnabled(true);
    ui->c1->setEnabled(true);
}
void MainWindow::checkbd(int level, int suit){
    switch(level){
        case 7:
            switch(suit){
                case 4: ui->nt7->setEnabled(false);
                case 0: ui->s7->setEnabled(false);
                case 1: ui->h7->setEnabled(false);
                case 2: ui->d7->setEnabled(false);
                case 3: ui->c7->setEnabled(false);
                suit = 4;
            }
        case 6:
            switch(suit){
                case 4: ui->nt6->setEnabled(false);
                case 0: ui->s6->setEnabled(false);
                case 1: ui->h6->setEnabled(false);
                case 2: ui->d6->setEnabled(false);
                case 3: ui->c6->setEnabled(false);
                suit = 4;
            }
        case 5:
            switch(suit){
                case 4: ui->nt5->setEnabled(false);
                case 0: ui->s5->setEnabled(false);
                case 1: ui->h5->setEnabled(false);
                case 2: ui->d5->setEnabled(false);
                case 3: ui->c5->setEnabled(false);
                suit = 4;
            }
        case 4:
            switch(suit){
                case 4: ui->nt4->setEnabled(false);
                case 0: ui->s4->setEnabled(false);
                case 1: ui->h4->setEnabled(false);
                case 2: ui->d4->setEnabled(false);
                case 3: ui->c4->setEnabled(false);
                suit = 4;
            }
        case 3:
            switch(suit){
                case 4: ui->nt3->setEnabled(false);
                case 0: ui->s3->setEnabled(false);
                case 1: ui->h3->setEnabled(false);
                case 2: ui->d3->setEnabled(false);
                case 3: ui->c3->setEnabled(false);
                suit = 4;
            }
        case 2:
            switch(suit){
                case 4: ui->nt2->setEnabled(false);
                case 0: ui->s2->setEnabled(false);
                case 1: ui->h2->setEnabled(false);
                case 2: ui->d2->setEnabled(false);
                case 3: ui->c2->setEnabled(false);
                suit = 4;
            }
        case 1:
            switch(suit){
                case 4: ui->nt1->setEnabled(false);
                case 0: ui->s1->setEnabled(false);
                case 1: ui->h1->setEnabled(false);
                case 2: ui->d1->setEnabled(false);
                case 3: ui->c1->setEnabled(false);
            }
    }
}
void MainWindow::checkbds(){
    QStringList header;
    QTableWidgetItem newitem;
    int row = ((config::bds.size()+1)/4)+1;
    QString contract;
    // basic setting
    ui->bdt->clear();
        ui->bdt->setColumnCount(4);
        ui->bdt->setRowCount(row);
        ui->bdt->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->bdt->setSelectionBehavior(QAbstractItemView::SelectItems);
        ui->bdt->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->bdt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->bdt->verticalHeader()->setVisible(false);
        ui->bdt->setFont(QFont("Helvetica", 10, QFont::Bold));
        ui->bdt->horizontalHeader()->setFont(QFont("Helvetica", 10, QFont::Bold));
        ui->bdt->resizeRowsToContents();
        ui->bdt->resizeColumnsToContents();
        header << "W" << "N" << "E" << "S";
        ui->bdt->setHorizontalHeaderLabels(header);
        ui->bdt->setShowGrid(false);
    //
    ui->bdt->setItem( 0, 0, new QTableWidgetItem(""));
    int len = config::bds.size();
    int newcont = -1, newdouble = -1, newredouble = -1;
    for(int i = 0; i < len; ++i){
        contract = config::bds[i].getcont();
        ui->bdt->setItem( (i+1)/4, (i+1)%4, new QTableWidgetItem(contract));
        if(contract.compare("PASS") != 0 && contract.compare("XX") != 0 && contract.compare("X") != 0) newcont = i;
        if(contract.compare("X") == 0) newdouble = i;
        if(contract.compare("XX") == 0) newredouble = i;
        ui->bdt->item((i+1)/4, (i+1)%4)->setTextAlignment(Qt::AlignCenter);
        ui->bdt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    if(newcont%2 != len%2 && newcont != -1 && newdouble < newcont){
        ui->x->setEnabled(true);
    }else{
        ui->x->setEnabled(false);
    }
    if(newdouble > newcont && newdouble%2 != len%2 && newredouble < newdouble){
        ui->xx->setEnabled(true);
    }else{
        ui->xx->setEnabled(false);
    }
    if(config::bds.size() >= 4){
        if(config::bds[config::bds.size()-1].getcont() == "PASS" && config::bds[config::bds.size()-2].getcont() == "PASS" && config::bds[config::bds.size()-3].getcont() == "PASS"){
            checkbd(7, 4);
            ui->pass->setEnabled(false);
        }
    }
    ui->bdt->setCurrentCell((config::bds.size())/4, (config::bds.size())%4);
    MainWindow::on_bdt_cellClicked(config::bds.size()/4, (config::bds.size())%4);
}
void MainWindow::on_bdt_cellClicked(int row, int column){
    int pos = ((row*4)-1)+column;
    QStringList msgbox;
    if(pos < 0 || pos >= config::bds.size()) return;
    else {
        ui->paper->clear();
        ui->paper->addItem(QString(config::bds[pos].getcont()) + ":");
        msgbox = config::bds[pos].getexp().split("|", QString::SkipEmptyParts);
        for(int i = 0; i < msgbox.size(); ++i)
            ui->paper->addItem(QString::number(i+1)+") "+msgbox[i]);
    }
}
void MainWindow::on_nt1_clicked(){
    config::bds.append(continfo(1, 4, ""));
    checkbd(1, 4);
    checkbds();
}
void MainWindow::on_s1_clicked(){
    config::bds.append(continfo(1, 0, ""));
    checkbd(1, 0);
    checkbds();
}
void MainWindow::on_h1_clicked(){
    config::bds.append(continfo(1, 1, ""));
    checkbd(1, 1);
    checkbds();
}
void MainWindow::on_d1_clicked(){
    config::bds.append(continfo(1, 2, ""));
    checkbd(1, 2);
    checkbds();
}
void MainWindow::on_c1_clicked(){
    config::bds.append(continfo(1, 3, ""));
    checkbd(1, 3);
    checkbds();
}
void MainWindow::on_nt2_clicked(){
    config::bds.append(continfo(2, 4, ""));
    checkbd(2, 4);
    checkbds();
}
void MainWindow::on_s2_clicked(){
    config::bds.append(continfo(2, 0, ""));
    checkbd(2, 0);
    checkbds();
}
void MainWindow::on_h2_clicked(){
    config::bds.append(continfo(2, 1, ""));
    checkbd(2, 1);
    checkbds();
}
void MainWindow::on_d2_clicked(){
    config::bds.append(continfo(2, 2, ""));
    checkbd(2, 2);
    checkbds();
}
void MainWindow::on_c2_clicked(){
    config::bds.append(continfo(2, 3, ""));
    checkbd(2, 3);
    checkbds();
}
void MainWindow::on_nt3_clicked(){
    config::bds.append(continfo(3, 4, ""));
    checkbd(3, 4);
    checkbds();
}
void MainWindow::on_s3_clicked(){
    config::bds.append(continfo(3, 0, ""));
    checkbd(3, 0);
    checkbds();
}
void MainWindow::on_h3_clicked(){
    config::bds.append(continfo(3, 1, ""));
    checkbd(3, 1);
    checkbds();
}
void MainWindow::on_d3_clicked(){
    config::bds.append(continfo(3, 2, ""));
    checkbd(3, 2);
    checkbds();
}
void MainWindow::on_c3_clicked(){
    config::bds.append(continfo(3, 3, ""));
    checkbd(3, 3);
    checkbds();
}
void MainWindow::on_nt4_clicked(){
    config::bds.append(continfo(4, 4, ""));
    checkbd(4, 4);
    checkbds();
}
void MainWindow::on_s4_clicked(){
    config::bds.append(continfo(4, 0, ""));
    checkbd(4, 0);
    checkbds();
}
void MainWindow::on_h4_clicked(){
    config::bds.append(continfo(4, 1, ""));
    checkbd(4, 1);
    checkbds();
}
void MainWindow::on_d4_clicked(){
    config::bds.append(continfo(4, 2, ""));
    checkbd(4, 2);
    checkbds();
}
void MainWindow::on_c4_clicked(){
    config::bds.append(continfo(4, 3, ""));
    checkbd(4, 3);
    checkbds();
}
void MainWindow::on_nt5_clicked(){
    config::bds.append(continfo(5, 4, ""));
    checkbd(5, 4);
    checkbds();
}
void MainWindow::on_s5_clicked(){
    config::bds.append(continfo(5, 0, ""));
    checkbd(5, 0);
    checkbds();
}
void MainWindow::on_h5_clicked(){
    config::bds.append(continfo(5, 1, ""));
    checkbd(5, 1);
    checkbds();
}
void MainWindow::on_d5_clicked(){
    config::bds.append(continfo(5, 2, ""));
    checkbd(5, 2);
    checkbds();
}
void MainWindow::on_c5_clicked(){
    config::bds.append(continfo(5, 3, ""));
    checkbd(5, 3);
    checkbds();
}
void MainWindow::on_nt6_clicked(){
    config::bds.append(continfo(6, 4, ""));
    checkbd(6, 4);
    checkbds();
}
void MainWindow::on_s6_clicked(){
    config::bds.append(continfo(6, 0, ""));
    checkbd(6, 0);
    checkbds();
}
void MainWindow::on_h6_clicked(){
    config::bds.append(continfo(6, 1, ""));
    checkbd(6, 1);
    checkbds();
}
void MainWindow::on_d6_clicked(){
    config::bds.append(continfo(6, 2, ""));
    checkbd(6, 2);
    checkbds();
}
void MainWindow::on_c6_clicked(){
    config::bds.append(continfo(6, 3, ""));
    checkbd(6, 3);
    checkbds();
}
void MainWindow::on_nt7_clicked(){
    config::bds.append(continfo(7, 4, ""));
    checkbd(7, 4);
    checkbds();
}
void MainWindow::on_s7_clicked(){
    config::bds.append(continfo(7, 0, ""));
    checkbd(7, 0);
    checkbds();
}
void MainWindow::on_h7_clicked(){
    config::bds.append(continfo(7, 1, ""));
    checkbd(7, 1);
    checkbds();
}
void MainWindow::on_d7_clicked(){
    config::bds.append(continfo(7, 2, ""));
    checkbd(7, 2);
    checkbds();
}
void MainWindow::on_c7_clicked(){
    config::bds.append(continfo(7, 3, ""));
    checkbd(7, 3);
    checkbds();
}
void MainWindow::on_pass_clicked(){
    config::bds.append(continfo("PASS"));
    checkbds();
}
void MainWindow::on_xx_clicked(){
    config::bds.append(continfo("XX"));
    checkbds();
}

void MainWindow::on_x_clicked(){
    config::bds.append(continfo("X"));
    checkbds();
}
void MainWindow::on_ns_vul_clicked(){
    if(ui->ns_vul->isChecked()){
        ui->ns_vul->setStyleSheet("background-color: rgb(255, 0, 0); border: none;");
        config::ns_vul = true;
    }
    else {
        ui->ns_vul->setStyleSheet("background-color: light gray; ");
        config::ns_vul = false;
    }
}
void MainWindow::on_ew_vul_clicked(){
    if(ui->ew_vul->isChecked()){
        ui->ew_vul->setStyleSheet("background-color: rgb(255, 0, 0); border: none;");
        config::ew_vul = true;
    }else{
        ui->ew_vul->setStyleSheet("background-color: light gray; ");
        config::ew_vul = false;
    }
}

// Mixed
void MainWindow::on_pb_bal_clicked(){
    ui->edit_distr->setText("(4333)+(4432)+(5332)+(5422)");
}
void MainWindow::on_pb_del_clicked(){
    int cur = ui->tab_dealer_sethand->currentIndex();
    if(cur == 0){
        if(ui->list_nor_setting->currentRow() != 0)
            ui->list_nor_setting->takeItem(ui->list_nor_setting->currentRow());
    }else if(cur == 1){
        int row = ui->paper->currentRow();
        if(row <= 0) return;
        else{
            int pos = (((ui->bdt->currentRow())*4)-1+(ui->bdt->currentColumn()));
            QStringList expbox = config::bds[pos].getexp().split("|", QString::SkipEmptyParts);
            QString newexp = "";
            for(int i = 0; i < expbox.size(); ++i)
                if(i != row-1) newexp = newexp + "|" + expbox[i];
            config::bds[pos].setexp(newexp);
        }
        MainWindow::on_bdt_cellClicked(ui->bdt->currentRow(), ui->bdt->currentColumn());
    }else{
        ui->statusBar->showMessage("Wrong! with deal.");
    }
}
void MainWindow::on_pb_clear_clicked(){
    ui->cb_s_lo->setCurrentIndex(0);
    ui->cb_s_hi->setCurrentIndex(13);
    ui->cb_h_lo->setCurrentIndex(0);
    ui->cb_h_hi->setCurrentIndex(13);
    ui->cb_d_lo->setCurrentIndex(0);
    ui->cb_d_hi->setCurrentIndex(13);
    ui->cb_c_lo->setCurrentIndex(0);
    ui->cb_c_hi->setCurrentIndex(13);
    ui->cb_M_lo->setCurrentIndex(0);
    ui->cb_M_hi->setCurrentIndex(13);
    ui->cb_m_lo->setCurrentIndex(0);
    ui->cb_m_hi->setCurrentIndex(13);
    ui->cb_hcp_lo->setCurrentIndex(0);
    ui->cb_hcp_hi->setCurrentIndex(37);
    ui->edit_distr->setText("");
}
void MainWindow::on_pb_undo_clicked(){
    int bdtsize;
    if(config::bds.isEmpty()) return;
    else{
        config::bds.removeLast();
        if(ui->bdt->currentColumn() != 0)
            MainWindow::on_bdt_cellClicked(ui->bdt->currentRow(), ui->bdt->currentColumn()-1);
        else MainWindow::on_bdt_cellClicked(ui->bdt->currentRow()-1, 3);
        if(ui->bdt->currentRow() == 0 && ui->bdt->currentColumn() == 1)
            ui->paper->clear();
    }
    ui->bdt->clear();
    resetpb();
    checkbds();
    bdtsize = config::bds.size();
    for(int i = 0; i < bdtsize; ++i){
        int lv = config::bds[i].getlevel(), suit = config::bds[i].getsuit();
        if(lv == suit && suit == -1)
            continue;
        else{
            checkbd(lv, suit);
            checkbds();
        }
    }
}
void MainWindow::on_pb_reset_clicked(){
    /*QColor hehe = QWidget::palette().color(QWidget::backgroundRole());
    ui->bds->insertPlainText(QString::number(hehe.red()) + "\n");
    ui->bds->insertPlainText(QString::number(hehe.blue()) + "\n");
    ui->bds->insertPlainText(QString::number(hehe.green()) + "\n");*/
    QListWidgetItem *item = new QListWidgetItem;
    QFont font;
    config::bds.clear();
    ui->paper->clear();
    ui->bdt->clear();
    ui->list_nor_setting->clear();
    font.setBold(true);
    item->setText("New");
    item->setTextAlignment(Qt::AlignHCenter);
    item->setFont(font);
    ui->list_nor_setting->addItem(item);
    ui->list_nor_setting->setCurrentRow(0);
    checkbds();
    resetpb();
    on_pb_clear_clicked();
}
void MainWindow::on_pb_sub_clicked(std::string pos, int s_lo, int s_hi, int h_lo, int h_hi, int d_lo, int d_hi, int c_lo, int c_hi, int M_lo, int M_hi, int m_lo, int m_hi, int hcp_lo, int hcp_hi, std::string edit_distr){
	/*	Set the ui things by argument
	 *	Write it next time.
	 * */
    int cur = ui->tab_dealer_sethand->currentIndex();
    QString cond = "";
	QString p = QString::fromStdString(pos + "/");
	QString distr = QString::fromStdString(edit_distr);
	qDebug() << p;
	config::check_pos = p;
	ui->cb_s_lo->setCurrentIndex(s_lo);
	ui->cb_s_hi->setCurrentIndex(s_hi);
	ui->cb_c_lo->setCurrentIndex(c_lo);
	ui->cb_c_hi->setCurrentIndex(c_hi);
	ui->cb_d_lo->setCurrentIndex(d_lo);
	ui->cb_d_hi->setCurrentIndex(d_hi);
	ui->cb_h_lo->setCurrentIndex(h_lo);
	ui->cb_h_hi->setCurrentIndex(h_hi);
	ui->cb_M_lo->setCurrentIndex(M_lo);
	ui->cb_M_hi->setCurrentIndex(M_hi);
	ui->cb_m_lo->setCurrentIndex(m_lo);
	ui->cb_m_hi->setCurrentIndex(m_hi);
	ui->cb_hcp_lo->setCurrentIndex(hcp_lo);
	ui->cb_hcp_hi->setCurrentIndex(hcp_hi);
	ui->edit_distr->setText(distr);
    cond = ui->cb_s_lo->currentText() + "-" + ui->cb_s_hi->currentText() + "/" +
            ui->cb_h_lo->currentText() + "-" + ui->cb_h_hi->currentText() + "/" +
            ui->cb_d_lo->currentText() + "-" + ui->cb_d_hi->currentText() + "/" +
            ui->cb_c_lo->currentText() + "-" + ui->cb_c_hi->currentText() + "/" +
            ui->cb_M_lo->currentText() + "-" + ui->cb_M_hi->currentText() + "/" +
            ui->cb_m_lo->currentText() + "-" + ui->cb_m_hi->currentText() + "/" +
            ui->cb_hcp_lo->currentText() + "-" + ui->cb_hcp_hi->currentText() + "/" +
            ui->edit_distr->text() + "/";
	qDebug() << config::check_pos + cond;
    if(cur == 0){
        if(ui->list_nor_setting->currentRow() == 0)
            ui->list_nor_setting->addItem(config::check_pos + cond);
        else{
            int temp_current_row = ui->list_nor_setting->currentRow();
            ui->list_nor_setting->takeItem(temp_current_row);
            ui->list_nor_setting->insertItem(temp_current_row, config::check_pos + cond);
            ui->list_nor_setting->setCurrentRow(0);
        }
    }else if(cur == 1){
        int row = ui->bdt->currentRow();
        if((row == 0 && ui->bdt->currentColumn() == 0) || config::bds.size()-1 < (ui->bdt->currentRow()*4-1+ui->bdt->currentColumn())) return;
        else
            config::bds[(row*4)-1+(ui->bdt->currentColumn())].setexp(config::bds[(row*4)-1+(ui->bdt->currentColumn())].getexp() + "|" + cond);
        MainWindow::on_bdt_cellClicked(ui->bdt->currentRow(), ui->bdt->currentColumn());
    }else{
        ui->statusBar->showMessage("Wrong!");
    }
}

// MAIN
void MainWindow::on_btn_deal_click_clicked(std::string edit_n, std::string edit_e, std::string edit_s, std::string edit_w){
    table main_board;
    QLabel *prolab = new QLabel(this);
    QProgressBar *probar = new QProgressBar(this);

    ui->statusBar->addWidget(prolab);
    ui->statusBar->addWidget(probar);
    ui->brow_dealer_msg->clear();
    ui->brow_anlys_msg->clear();
    ui->brow_anlys_infomsg->clear();
    ui->brow_anlys_sugmsg->clear();
    ui->edit_anlys_bdah->clear();
	ui->edit_n->setText(QString::fromStdString(edit_n));
	ui->edit_s->setText(QString::fromStdString(edit_s));
	ui->edit_w->setText(QString::fromStdString(edit_w));
	ui->edit_e->setText(QString::fromStdString(edit_e));
//	if(!main_board.setting_shuffle(ui->brow_dealer_msg, ui->brow_anlys_msg, ui->list_nor_setting, ui->edit_n, ui->edit_e, ui->edit_s, ui->edit_w, probar, config::bds.size() > 0 ? 1:0)){
	if(!main_board.setting_shuffle(ui->brow_dealer_msg, ui->brow_anlys_msg, ui->list_nor_setting, ui->edit_n, ui->edit_e, ui->edit_s, ui->edit_w, probar, config::bds.size() > 0 ? 1:0)){
        anlys::hcpsd(ui->brow_dealer_msg);
        //init_anlys_infomsg();
        if(config::bds.size() > 0){
            QList<QTableWidget*> tablemsg;
            init_anlys_bdahmsg(config::bds.size()%4);
            tablemsg.push_back(ui->ddsresult);
            tablemsg.push_back(ui->ddsresult_n);
            tablemsg.push_back(ui->ddsresult_e);
            tablemsg.push_back(ui->ddsresult_s);
            tablemsg.push_back(ui->ddsresult_w);
            ui->tab_main->setCurrentIndex(1);
            ui->edit_anlys_filename->setText(config::cfg + ".Cboards");
            anlys::basic_anlys(ui->brow_anlys_msg, ui->brow_anlys_infomsg, ui->brow_anlys_sugmsg, tablemsg, ui->ns_vul->isChecked() == true ? 2 : 1, ui->ew_vul->isChecked() == true ? 2 : 1, ((ui->n->text().isEmpty() == true ? "" : ui->edit_n->text()) + (ui->e->text().isEmpty() == true ? "|" : "|" + ui->edit_e->text()) + (ui->s->text().isEmpty() == true ? "|" : "|" + ui->edit_s->text()) + (ui->w->text().isEmpty() == true ? "|" : "|" + ui->edit_w->text())), probar);
        }
    }else{
        // Error
    }
    delete  probar;
    delete  prolab;
}
// MAIN

// For anlys
void MainWindow::on_pb_anlys_file_open_clicked(){
    QString cfg = "";
    ui->edit_anlys_filename->clear();
    if(!QDir("files").exists())
        cfg = QFileDialog::getOpenFileName(this,tr("Open File"),".","Boards (*.boards)");
    else
        cfg = QFileDialog::getOpenFileName(this,tr("Open File"),"./files/","Boards (*.boards)");
    ui->edit_anlys_filename->setText(cfg);
    config::cfg = cfg;
}
void MainWindow::init_anlys_bdahmsg(int pos){
    QTextEdit *msg = ui->edit_anlys_bdah;

    QFont myfont;
    QStringList pos_set_hand = {ui->edit_n->text(), ui->edit_e->text(), ui->edit_s->text(), ui->edit_w->text()};
    QStringList color_set = {"#000000","#ff0000","#ff3600","#404040"};
    QStringList suit_set = {"♠", "♥", "♦", "♣"};

    msg->setFont(myfont);
    for(int i = 0; i < 4; ++i){
        msg->insertPlainText(QString("").leftJustified(2, '\t'));
        msg->setTextColor(QColor(color_set[i]));
        msg->insertPlainText(QString(suit_set[i])+"  ");
        msg->setTextColor(QColor(0, 0, 0));
        msg->insertPlainText(pos_set_hand[pos].section('.', i, i));
        msg->insertPlainText("\n");
    }

    QTextTableFormat *maintype = new QTextTableFormat();
    QVector<QTextLength> lengset;
    maintype->setAlignment(Qt::AlignCenter);
    lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
    lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
    lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
    lengset.push_back(QTextLength(QTextLength::FixedLength, 80));
    maintype->setColumnWidthConstraints(lengset);
    maintype->setBorderBrush(Qt::NoBrush);
    maintype->setBorder(0);
    QTextBlockFormat centerAlign;
    centerAlign.setAlignment(Qt::AlignCenter);
    QTextTable *table = msg->textCursor().insertTable(((config::bds.size()+1)/4)+2 , 4, *maintype);
    table->cellAt(0, 0).firstCursorPosition().insertText("West");
    table->cellAt(0, 1).firstCursorPosition().insertText("North");
    table->cellAt(0, 2).firstCursorPosition().insertText("East");
    table->cellAt(0, 3).firstCursorPosition().insertText("South");
    for(int i = 0 ; i < config::bds.size(); ++i){
            table->cellAt(((i+1)/4)+1, (i+1)%4).firstCursorPosition().insertText(config::bds[i].getcont());
    }
}
