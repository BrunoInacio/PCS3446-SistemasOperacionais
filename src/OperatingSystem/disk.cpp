/**
 * disk.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "disk.hpp"

/**
 * Inicia o processamento de uma operação 'operation' de um arquivo
 * de tamanho 'size'. Enquanto a operação estiver em andamento, o disco 
 * é considerado ocupado e não pode fazer outra operação.
 * Retorna uma tupla referente ao próximo evento.
 */
std::tuple<int, Event, double> Disk::processIO(int jobID, Disk::IO operation, double size) {
	if (this->isRunning)
		throw Error::DISK_UNAVAILABLE;

	switch (operation) {
	case Disk::IO::READ:
		this->isRunning = true;
		this->jobID = jobID;
		return std::make_tuple(jobID, Event::IO_COMPLETE, this->readTime(size));

	case Disk::IO::WRITE:
		this->isRunning = true;
		this->jobID = jobID;
		return std::make_tuple(jobID, Event::IO_COMPLETE, this->writeTime(size));

	default:
		throw "Operação inválida no disco.";
	}
}


/**
 * Finaliza a operação de IO, liberando o uso do disco.
 * Retorna o 'jobID' do job que estava realizando operação no disco.
 */
int Disk::completeIO() {
	this->isRunning = false;

	auto jobID = this->jobID;
	this->jobID = 0;

	return jobID;
}


/**
 * Calcula o tempo de leitura de um arquivo de tamanho 'size'.
 */
double Disk::readTime(double size) const {
	return this->responseTime + size / this->readSpeed;
}


/**
 * Calcula o tempo de escrita de um arquivo de tamanho 'size'.
 */
double Disk::writeTime(double size) const {
	return this->responseTime + size / this->writeSpeed;
}
