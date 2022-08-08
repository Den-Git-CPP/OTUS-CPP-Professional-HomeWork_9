#pragma once
#include <ctime>
#include <string>
#include <vector>
#include "Bulk.h"
#include "Metrics.h"
/**
 * @brief Интерфейс для классов выводящих блок команд в поток.
 */
class StreamWriter {
public:
	virtual ~StreamWriter() = default;
	/**
	 * @brief Запись блока команд в поток.
	 * @param context_id - id контекста из которого производится вывод.
	 * @param bulk - блок команд.
	 */
	virtual void write(uint8_t context_id, const Bulk& bulk) = 0;
	/**
	 * @brief Дать метрики работы потоков.
	 * @return метрики.
	 */
	virtual Metrics& get_metrics() = 0;
};
