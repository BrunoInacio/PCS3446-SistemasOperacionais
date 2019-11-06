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
	Disk(double size, double readSpeed, double writeSpeed, double responseTime) :
		size(size), readSpeed(readSpeed / 1000.), writeSpeed(writeSpeed / 1000.),
		responseTime(responseTime), isRunning(0), jobID(0) {};
	~Disk() {};

	enum class IO;

	std::tuple<int, Event, int> processIO(int id, Disk::IO operation, double size);
	std::tuple<int, Event, int> completeIO();

private:
	const double size;

	bool isRunning;
	int jobID;

	double readSpeed;
	double writeSpeed;

	double responseTime;

	int readTime(double size) const;
	int writeTime(double size) const;
};

enum class Disk::IO {
	READ,
	WRITE
};
