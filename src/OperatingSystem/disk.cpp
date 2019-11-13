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
      readSpeed(readSpeed),
      writeSpeed(writeSpeed),
      responseTime(responseTime),
      isRunning(0),
      jobID(0),
      totalRead(0.0),
      totalWrite(0.0) {
}

/**
 * Inicia o processamento de uma operação 'operation' de um arquivo
 * de tamanho 'size'. Enquanto a operação estiver em andamento, o disco 
 * é considerado ocupado e não pode fazer outra operação.
 * Retorna uma tupla referente ao próximo evento.
 */
PredictedEvent Disk::processIO(int jobID, Disk::IO operation, double size) {
    if (this->isRunning)
        throw Error::DISK_UNAVAILABLE;

    PredictedEvent nextEvent;

    switch (operation) {
    case Disk::IO::READ:
        this->totalRead += size;
        nextEvent = { jobID, this->readTime(size), Event::IO_COMPLETE };
        break;

    case Disk::IO::WRITE:
        this->totalWrite += size;
        nextEvent = { jobID, this->writeTime(size), Event::IO_COMPLETE };
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
PredictedEvent Disk::completeIO() {
    this->isRunning = false;

    auto jobID = this->jobID;
    this->jobID = 0;

    return { jobID, 0, Event::CPU_RUN };
}


/**
 * Calcula o tempo de leitura de um arquivo de tamanho 'size'.
 */
int Disk::readTime(double size) const {
    return static_cast<int>(this->responseTime + 1000. * size / this->readSpeed);
}


/**
 * Calcula o tempo de escrita de um arquivo de tamanho 'size'.
 */
int Disk::writeTime(double size) const {
    return static_cast<int>(this->responseTime + 1000. * size / this->writeSpeed);
}


/**
 * Exibe informações referentes ao disco.
 */
void Disk::info() {
    std::cout << "=== Disco ===" << std::endl;
    std::cout << "Tamanho total: " << this->size << " MB" << std::endl;
    std::cout << "Velocidade de leitura: " << std::setprecision(2) << this->readSpeed << " MB/s" << std::endl;
    std::cout << "Velocidade de escrita: " << std::setprecision(2) << this->writeSpeed << " MB/s" << std::endl;
    std::cout << "Total de leituras feitas: " << std::setprecision(2) << this->totalRead << " MB" << std::endl;
    std::cout << "Total de escritas feitas: " << std::setprecision(2) << this->totalWrite << " MB" << std::endl;

    std::cout << std::endl;
}
