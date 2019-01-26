#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);
        QList<QSerialPortInfo> qspinfolist = QSerialPortInfo::availablePorts();

        for(auto & qsp_info: qspinfolist){
                ui->port_selector->insertItem(0,qsp_info.portName());
        }

}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_open_port_btn_clicked()
{
	auto portname = ui->port_selector->currentText();
	portname.prepend("/dev/");

	motor = std::make_unique<Motor>(portname,'1',
			[this](const std::string& s){
				append_to_log(s);
			});
}

void MainWindow::on_close_port_btn_clicked()
{
	motor.reset();
}

void MainWindow::on_start_btn_clicked()
{
	if(motor){
		motor->start_motor();
	}
}

void MainWindow::on_stop_btn_clicked()
{
	if(motor){
		motor->stop_motor();
	}
}

void MainWindow::on_counterclockwise_btn_clicked()
{
	if(motor){
		motor->dir_counterclockwise();
	}
}

void MainWindow::on_clockwise_btn_clicked()
{
	if(motor){
		motor->dir_clockwise();
	}
}


void MainWindow::changed_freq_dial(int freq)
{
	if(motor){
		motor->set_max_freq(freq);
	}
}

void MainWindow::on_send_btn_clicked()
{
	std::string cmdtxt = ui->cmd_input->text().toUtf8().constData();
	append_to_log(fmt::format("INP:{}",cmdtxt));
	if(motor){
		motor->send_cmd(cmdtxt);
	}
	ui->cmd_input->clear();
}

void MainWindow::append_to_log(const std::string& s)
{
	ui->log->append(QString::fromStdString(s));
}

void MainWindow::on_set_step_btn_clicked()
{
	auto stepping = (1 << ui->stepping_selector->value());
	append_to_log(fmt::format("I set up for stepping with 1/{:d} steps"
				,stepping));
	if(stepping >= 2 && stepping <= 255 && motor){
		motor->send_cmd(fmt::format("g{:d}",stepping));
	}

}

void MainWindow::on_plus_btn_clicked()
{
	if(motor){
		motor->send_cmd("+");
	}
}


void MainWindow::on_minus_btn_clicked()
{
	if(motor){
		motor->send_cmd("-");
	}
}
