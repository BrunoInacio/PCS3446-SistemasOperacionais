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
#include "processor.hpp"

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

	Processor cpu = Processor();
	Job job = Job();
	job.totalCycles = 30;

	std::cout << job.totalCycles << std::endl;
	cpu.runJob(&job);
	std::cout << job.totalCycles << std::endl;



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
