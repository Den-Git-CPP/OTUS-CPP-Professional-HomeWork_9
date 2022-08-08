#pragma once
#include <fstream>
#include "StreamWriter.h"
#include "ThreadPool.h"
/**
 * @brief Класс вывода блока команд в файл.
 */
class WriteFiler: public StreamWriter, public ThreadPool<2> {
public:
	explicit WriteFiler(): metrics_ {"file"} {}

	~WriteFiler() override {
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
	std::mutex metrics_mutex_ {};
	Metrics metrics_;
};