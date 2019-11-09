/**
 * disk.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "disk.hpp"

#include <iostream>
#include <iomanip>


Disk::Disk(double size, double readSpeed, double writeSpeed, double responseTime)
    : size(size),
      readSpeed(readSpeed / 1000.),
      writeSpeed(writeSpeed / 1000.),
      responseTime(responseTime),
      isRunning(0),
      jobID(0),
      totalRead(0),
      totalWrite(0) {
}

/**
 * Inicia o processamento de uma operação 'operation' de um arquivo
 * de tamanho 'size'. Enquanto a operação estiver em andamento, o disco 
 * é considerado ocupado e não pode fazer outra operação.
 * Retorna uma tupla referente ao próximo evento.
 */
std::tuple<int, Event, int> Disk::processIO(int jobID, Disk::IO operation, double size) {
    if (this->isRunning)
        throw Error::DISK_UNAVAILABLE;

    std::tuple<int, Event, int> nextEvent;

    switch (operation) {
    case Disk::IO::READ:
        this->totalRead += size;
        nextEvent = std::make_tuple(jobID, Event::IO_COMPLETE, this->readTime(size));
        break;

    case Disk::IO::WRITE:
        this->totalWrite += size;
        nextEvent = std::make_tuple(jobID, Event::IO_COMPLETE, this->writeTime(size));
        break;

    default:
        throw "Operação inválida no disco.";
    }

    this->isRunning = true;
    this->jobID = jobID;

    return nextEvent;
}


/**
 * Finaliza a operação de IO, liberando o uso do disco.
 * Retorna o 'jobID' do job que estava realizando operação no disco.
 */
std::tuple<int, Event, int> Disk::completeIO() {
    this->isRunning = false;

    auto jobID = this->jobID;
    this->jobID = 0;

    return std::make_tuple(jobID, Event::CPU_RUN, 0);
}


/**
 * Calcula o tempo de leitura de um arquivo de tamanho 'size'.
 */
int Disk::readTime(double size) const {
    return static_cast<int>(this->responseTime + size / this->readSpeed);
}


/**
 * Calcula o tempo de escrita de um arquivo de tamanho 'size'.
 */
int Disk::writeTime(double size) const {
    return static_cast<int>(this->responseTime + size / this->writeSpeed);
}


/**
 * Exibe informações referentes ao disco.
 */
void Disk::info() {
    std::cout << "=== Disco ===" << std::endl;
    std::cout << "Tamanho total: " << this->size << "MB" << std::endl;
    std::cout << "Velocidade de leitura: " << this->readSpeed << "MB/s" << std::endl;
    std::cout << "Velocidade de escrita: " << this->writeSpeed << "MB/s" << std::endl;
    std::cout << "Total de leituras feitas: " << this->totalRead << "MB" << std::endl;
    std::cout << "Total de escritas feitas: " << this->totalWrite << "MB" << std::endl;

    std::cout << std::endl;
}
