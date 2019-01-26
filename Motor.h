#pragma once

#include <QSerialPort>
#include <QString>
#include <string>

#include <fmt/format.h>
#include <iostream>
#include <functional>

class Motor: public QObject
{
Q_OBJECT

	QSerialPort serport_;
	char id_;

	std::string linebuf_;

	std::function<void(const std::string&)> logfun_;

public:
	void send_cmd(std::string cmd);

	Motor( const QString& serport_desc , char id,
			std::function<void(const std::string&)> logfun);

	void start_motor();
	void stop_motor();
	void dir_clockwise();
	void dir_counterclockwise();
	void set_max_freq(unsigned spd);
private slots:

        void handleReadyRead();
	void handleError(QSerialPort::SerialPortError error);

};
