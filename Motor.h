#pragma once

#include <QSerialPort>
#include <QString>

#include <fmt/format.h>
#include <iostream>

class Motor
{
	QSerialPort serport_;

	char id_;

	public:

	void send_cmd(std::string cmd)
	{
		auto linecmd = fmt::format("#{}{}\r",id_,cmd);
		std::cout << fmt::format("writing to serport: [[#{}{}]]",id_,cmd) << std::endl;
		serport_.write(linecmd.data(), linecmd.size());
	}


	public:
	Motor( const QString& serport_desc , char id = '1'):
		id_(id)
	{
		serport_.setPortName(serport_desc);
		serport_.setFlowControl(QSerialPort::NoFlowControl);
		serport_.setBaudRate(QSerialPort::Baud19200);
		serport_.setDataBits(QSerialPort::Data8);
		serport_.setParity(QSerialPort::NoParity);
		serport_.setStopBits(QSerialPort::OneStop);
		serport_.open(QIODevice::ReadWrite);
	}


	void start_motor()
	{
		send_cmd("A");
	}


	void stop_motor()
	{
		send_cmd("S");
	}
	
	void dir_clockwise()
	{
		send_cmd("d0");
	}

	void dir_counterclockwise()
	{
		send_cmd("d1");
	}

	void set_max_freq(unsigned spd)
	{
		send_cmd(fmt::format("o{:d}",spd));
	}
	

};
