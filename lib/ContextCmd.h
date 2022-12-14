#pragma once
#include <functional>
#include <list>
#include <memory>
#include <algorithm>
#include <istream>
#include <iostream>
#include <thread>

#include "Bulk.h"
#include "InterpreterCmd.h"
#include "Observer.h"
#include "Metrics.h"
/**
 * @brief Класс котнекста обработчика команд.
 */
class ContextCmd: public Observer {
public:
  /**
   * @brief Конструктор.
   * @param bulk_size - макисмальный размер блока команд.
   */
	explicit ContextCmd(size_t bulk_size, uint8_t id):
		interpreter_ {bulk_size}, metrics_ {"main"}, id_ {id} {
	}

	~ContextCmd() override = default;
	/**
	 * @brief Подписка на получение блоков команд на вывод.
	 * @param observer - подписчик.
	 */
	void subscribe(observer_t observer) final;
	/**
	 * @brief Обработка входной команды.
	 * @param data - входной данные, содержащие команды.
	 * @param size - размер входных данных.
	 * @param finish_bulk - принудительное завершение блока команд.
	 */
	void process(const char* data, std::size_t size, bool finish_bulk = false);
	/**
	 * @brief Вывод метрик в поток.
	 * @param os - выходной поток.
	 */
	void print_metrics(std::ostream& os);

private:
  /**
   * @brief Публикация блока команд.
   * @param bulk - блок команд.
   */
	void publish(const Bulk& bulk) final;
	/// Список обозревателей, ожидающих вывод содержимого пула.
	std::list<observer_t> observers_ {};
	/// Блок команд.
	Bulk bulk_ {};
	/// Интерпретатор команд.
	InterpreterCmd interpreter_;
	/// Метрики основного потока.
	Metrics metrics_;
	/// Строка, содержащая данные со входными командами.
	std::string data_;
	/// id контекста.
	uint8_t id_;
};


