#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

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
	motor = std::make_unique<Motor>(portname,'1');
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

