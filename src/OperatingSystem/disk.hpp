/**
 * disk.hpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#pragma once

#include "event.hpp"

#include <tuple>

/**
 * 'size': Tamanho do disco em MB.
 * 'readSpeed': Velocidade de leitura em MB/s.
 * 'writeSpeed': Velocidade de escrita em MB/s.
 * 'responseTime': Tempo de resposta em ms.
 */
class Disk {
public:
    Disk(double size, double readSpeed, double writeSpeed, double responseTime);
    ~Disk() {};

    enum class IO;

    const double size;

    PredictedEvent processIO(int id, Disk::IO operation, double size);
    PredictedEvent completeIO();

    void info();

private:

    bool isRunning;
    int jobID;

    double readSpeed;
    double writeSpeed;

    double responseTime;

    double totalRead;
    double totalWrite;

    int readTime(double size) const;
    int writeTime(double size) const;
};

enum class Disk::IO {
    READ,
    WRITE
};
