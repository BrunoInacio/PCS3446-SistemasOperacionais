/**
 * disk.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "disk.hpp"
#include "event.hpp"

/**
 * Inicia o processamento de uma operação 'operation' de um arquivo
 * de tamanho 'size'. Enquanto a operação estiver em andamento, o disco 
 * é considerado ocupado e não pode fazer outra operação.
 * Retorna o tempo necessário para executar a operação solicitada.
 */
double Disk::processIO(int id, Disk::IO operation, double size) {
	if (this->isRunning)
		throw Event::DISK_UNAVAILABLE;

	switch (operation) {
	case Disk::IO::READ:
		this->isRunning = true;
		this->id = id;
		return this->readTime(size);

	case Disk::IO::WRITE:
		this->isRunning = true;
		this->id = id;
		return this->writeTime(size);

	default:
		throw "Operação inválida no disco.";
	}
}


/**
 * Finaliza a operação de IO, liberando o uso do disco.
 * Retorna o 'id' do job que estava realizando operação no disco.
 */
int Disk::completeIO() {
	this->isRunning = false;
	return this->id;
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
