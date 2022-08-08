#pragma once
#include<memory>
#include "StreamWriter.h"
/// Тип обозревателя.
using observer_t = std::unique_ptr<StreamWriter>;
/**
 * @brief Интерфейс обозреваемого.
 */
class Observer {
public:
	virtual ~Observer() = default;
	/**
	 * @brief Подписка на получение блоков команд на вывод.
	 * @param observer - подписчик.
	 */
	virtual void subscribe(observer_t observer) = 0;
	/**
	 * @brief Публикация блока команд.
	 * @param bulk - блок команд.
	 */
	virtual void publish(const Bulk& bulk) = 0;
};


