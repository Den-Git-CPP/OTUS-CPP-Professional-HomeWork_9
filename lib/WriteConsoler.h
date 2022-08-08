#pragma once
#include <iostream>
#include <ostream>
#include <sstream>
#include "StreamWriter.h"
#include "ThreadPool.h"
/**
 * @brief Класс вывода блока команд в консоль.
 */
class WriteConsoler: public StreamWriter, public ThreadPool<> {
public:
  /**
   * @brief Консруктор.
   * @param os - поток для вывода.
   */
	explicit WriteConsoler(std::ostream& os = std::cout): os_(os), metrics_ {"log"} {
	}

	~WriteConsoler() override {
		stop();
	}
	/**
	 * @brief Запись блока команд в поток.
	 * @param context_id - id контекста из которого производится вывод.
	 * @param bulk - блок команд.
	 */
	void write(uint8_t context_id, const Bulk& bulk) final;
	/**
	 * @brief Дать метрики работы потоков.
	 * @return метрики по каждому из потоков.
	 */
	Metrics& get_metrics() final;

private:
	std::ostream& os_;
	std::mutex metrics_mutex_ {};
	Metrics metrics_;
};