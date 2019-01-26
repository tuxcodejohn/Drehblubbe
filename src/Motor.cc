#include "Motor.h"

void Motor::send_cmd(std::string cmd)
{
	auto linecmd = fmt::format("#{}{}\r",id_,cmd);
	logfun_(fmt::format("TX:[[#{}{}]]",id_,cmd));
	serport_.write(linecmd.data(), linecmd.size());
}


Motor::Motor( const QString& serport_desc , char id,
			std::function<void(const std::string&)> logfun):
		id_(id),
		logfun_(logfun)
{
	serport_.setPortName(serport_desc);
	serport_.setFlowControl(QSerialPort::NoFlowControl);
	serport_.setBaudRate(QSerialPort::Baud19200);
	serport_.setDataBits(QSerialPort::Data8);
	serport_.setParity(QSerialPort::NoParity);
	serport_.setStopBits(QSerialPort::OneStop);
	serport_.open(QIODevice::ReadWrite);
	linebuf_.clear();

	connect(&serport_, &QSerialPort::readyRead, this , &Motor::handleReadyRead);
	connect(&serport_, static_cast<void(QSerialPort::*)(QSerialPort::SerialPortError)>
							(&QSerialPort::error),
		this, &Motor::handleError);


}


void Motor::start_motor()
{
	send_cmd("A");
}


void Motor::stop_motor()
{
	send_cmd("S");
}

void Motor::dir_clockwise()
{
	send_cmd("d0");
}

void Motor::dir_counterclockwise()
{
	send_cmd("d1");
}

void Motor::set_max_freq(unsigned spd)
{
	send_cmd(fmt::format("o{:d}",spd));
}
	
void Motor::handleReadyRead(){
	std::cout << "Mark" << __LINE__ << __FUNCTION__ << std::endl;
	 auto read_bytes = serport_.readAll();
	 for(const auto& byte: read_bytes){
		 linebuf_.append(1,static_cast<char>(byte));
		 if(byte == '\r'){
			 logfun_(linebuf_);
			 linebuf_.clear();
			 continue;
		 }
		 if(linebuf_.size() > 74){
			 linebuf_.append(1,'\n');
			 logfun_(linebuf_);
			 linebuf_.clear();
		 }
	 }
}

void Motor::handleError(QSerialPort::SerialPortError error){
	 if (error  == QSerialPort::ReadError) {
		logfun_(fmt::format("ERROR: error occurred while reading"
			" the data from port {}. -> {} \n",
			serport_.portName().toUtf8().constData(),
			serport_.errorString().toUtf8().constData() ));
	 }
}

