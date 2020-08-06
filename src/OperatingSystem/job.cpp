/**
 * job.cpp
 * PCS 3446 - Sistemas Operacionais - 2019
 * Bruno Brand�o In�cio
 */

#include "job.hpp"

#include <algorithm>


/**
 * Construtor que recebe 'totalTime', 'memoryUsed', 'totalIO' e 'priority'.
 */
Job::Job(int totalProcessTime, int memoryUsed, Job::Priority priority)
    : id(lastId++),
      totalProcessTime(totalProcessTime),
      memoryUsed(memoryUsed),
      priority(priority),
      state(State::SUBMIT),
      processedTime(0) {
    this->operations.push_back({ totalProcessTime, Job::OperationType::FINISH });
}

/**
 * Adiciona uma opera��o � lista de opera��es que devem ser realizadas pelo job.
 */
void Job::addOperation(Operation operation) {
    auto position = std::lower_bound(this->operations.begin(), this->operations.end(), operation);
    this->operations.insert(position, operation);
}

/**
 * Realiza o processamento de 'duration' de tempo.
 */
void Job::process(int duration) {
    this->processedTime += duration;
}

/**
 * Obt�m a pr�xima opera��o que deve ser realizada pelo 'job'.
 * Por exemplo, opera��es de IO ou finaliza��o do processamento.
 */
Job::Operation Job::getNextOperation() {
    for (const auto [time, operation, value]: this->operations)
        if (this->processedTime < time)
            return { time - this->processedTime, operation, value };

    return { 0, Job::OperationType::FINISH };
}
