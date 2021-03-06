#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include "Motor.h"

#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow 
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
		
		void append_to_log(const std::string& s);

	private slots:
		void on_close_port_btn_clicked();
		void on_open_port_btn_clicked();
		void on_stop_btn_clicked();
		void on_start_btn_clicked();
		void on_counterclockwise_btn_clicked();
		void on_clockwise_btn_clicked();
		void on_send_btn_clicked();
		void on_plus_btn_clicked();
		void on_minus_btn_clicked();

		void on_set_step_btn_clicked();

		void changed_freq_dial(int );

	private:
		Ui::MainWindow *ui;

		std::unique_ptr<Motor> motor;

};

#endif // MAINWINDOW_H
