/**
 * interface.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "interface.hpp"

#include "operatingSystem.hpp"
#include "job.hpp"
#include "memory.hpp"
#include "disk.hpp"

#include <iostream>


 /**
  * Inicia a interface.
  */
void Interface::start() {
	std::cout << "Bem vindo ao Sistema Operacional!" << std::endl;
	this->menu();
}


void Interface::menu() {
	OperatingSystem OS = OperatingSystem();

	std::cout << "\nO Sistema Operacional esta em execucao!" << std::endl;

	Memory mem = Memory(100);
	mem.allocate(21, 40);
	mem.allocate(31, 20);
	mem.allocate(11, 15);
	mem.allocate(25, 25);
	mem.free(31);
	mem.free(11);

	Disk disk = Disk(1000, 80, 20, 15);
	std::cout << disk.processIO(1, Disk::IO::READ, 80) << std::endl;
	disk.completeIO();
	std::cout << disk.processIO(1, Disk::IO::WRITE, 40) << std::endl;

	for (const auto& process : mem.getInfo())
		std::cout << process.first << process.second << " MB" << std::endl;
	auto a = mem.getInfo();
	a[4] = 30;
	for (const auto& process : a)
		std::cout << process.first << process.second << " MB" << std::endl;
	mem.log();


	int menu;
	enum options { EXIT, ADD, KILL, LOG };

	while (true) {
		std::cout << std::endl;
		std::cout << EXIT << ". Sair" << std::endl;
		std::cout << ADD << ". Adicionar jobs ao SO." << std::endl;
		std::cout << KILL << ". Interromper um job em execucao." << std::endl;
		std::cout << LOG << ". Visualizar informacoes sobre os jobs no SO." << std::endl;
		std::cout << "\nDigite o numero da opcao desejada: ";

		switch (std::cin >> menu; menu) {
		case ADD: {
			break;
		}

		case KILL: {
			std::cout << "Digite a ID do job que deseja interromper: " << std::endl;

			int jobId;
			std::cin >> jobId;

			OS.killJob(jobId);
			break;
		}

		case LOG:
			OS.printJobs(); // 0xSTATE
			break;

		case EXIT:
		default:
			return;
		}
	}

	return;
}


/**
 * Realiza a chamada para a interface.
 */
int main() {
	Interface pc;
	pc.start();

	return 0;
}
