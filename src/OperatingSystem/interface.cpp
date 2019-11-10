/**
 * interface.cpp
 * PCS 3216 - Sistemas Operacionais - 2019
 * Bruno Brandão Inácio
 */

#include "interface.hpp"

#include "event.hpp"
#include "memory.hpp"
#include "disk.hpp"
#include "processor.hpp"
#include "job.hpp"

#include <iostream>


 /**
  * Inicia a interface.
  */
void Interface::start() {
    std::cout << "Bem vindo ao Sistema Operacional!" << std::endl;
    this->addHardware();

    this->menu();
}


/**
 * Adiciona hardware para o sistema que será simulado.
 */
void Interface::addHardware() {
    this->OS.addProcessor(Processor());
    this->OS.addMemory(Memory(2000));
    this->OS.addDisk(Disk(100E3, 80E3, 80E3, 15));
}


/**
 * Menu para controle do Sistema Operacional.
 */
void Interface::menu() {
    int menu;
    enum options { EXIT, ADD, RUN, EVENTS, JOBS, INFO };

    while (true) {
        std::cout << std::endl;
        std::cout << EXIT << ". Sair" << std::endl;
        std::cout << ADD << ". Adicionar jobs ao SO." << std::endl;
        std::cout << RUN << ". Rodar simulacao." << std::endl;
        std::cout << EVENTS << ". Visualizar informacoes sobre futuros eventos." << std::endl;
        std::cout << JOBS << ". Visualizar informacoes sobre todos os jobs." << std::endl;
        std::cout << INFO << ". Visualizar informacoes sobre o uso do sistema." << std::endl;
        std::cout << "\nDigite o numero da opcao desejada: ";

        switch (std::cin >> menu; menu) {
        case ADD:
            int numJobs;
            std::cout << "Quantos jobs deseja adicionar ao SO?" << std::endl;
            std::cin >> numJobs;

            this->events.addStochasticJobs(numJobs);
            break;

        case RUN:
            int time;
            std::cout << "Por quanto tempo deseja executar o sistema operacional?" << std::endl;
            std::cin >> time;

            this->events.run(time);
            break;

        case EVENTS:
            this->events.info();
            break;

        case JOBS:
            this->events.infoJobs();
            break;

        case INFO:
            this->OS.info();
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
