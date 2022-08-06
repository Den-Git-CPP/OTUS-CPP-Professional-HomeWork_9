#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>

#include "Observer.h"

/**
 * @brief Класс накапливает пачку команд и раздает подписчикам информацию о накопленных данных
 *
 */
class Accumulator_Commands
{
public:

	/**
	 * @brief Перегруженный конструктор класса для создания с заданным количеством команд
	 *
	 * @param commands_in_pull количество команд
	 */
	Accumulator_Commands(int commands_in_pull)
		: _number_commands_in_pull{commands_in_pull}
	{
		clear_bulk();
	};
	~Accumulator_Commands(){};
	
	/**
	 * @brief функция определяет состояние накопителя команд
	 *
	 * @return true если команды отсутствуют
	 * @return false если накоплено более одной команды
	 */
	bool empty();
	
	/**
	 * @brief функция добавляет введенную команду в накопитель
	 *
	 */
	void add_commands();
	
	/**
	 * @brief  функция очищает накопитель от введенных ранее команд
	 *
	 */
	void clear_bulk();
	
	/**
	 * @brief  функция  очищает накопитель от введенных ранее команд
	 *
	 */
	void out_and_clear_bulk();
	
	/**
	 * @brief функция обрабатывает введенные команды
	 *
	 */
	void work_with_commands();
	
	/**
	 * @brief функция добавляет подписчика класса Observer
	 *
	 * @param ob
	 */
	void add_subscriber(Observer *ob);
	/**
	 * @brief функция очищает очередб подписчиков
	 * 
	 */
	void remove_subscriber();

	/**
	 * @brief функция оповещает о накопленных команда подписчиков
	 *
	 */
	void notify_subscriber();

private:
	Accumulator_Commands() = default;
	int _number_commands{0};
	int _number_commands_in_pull{0};
	int _number_brackets{0};
	/**
	 * @brief Время первой команды
	 * 
	 */
	long long int _time_first_command{0};
	std::string _commands{};
	/**
	 * @brief Накопитель команд
	 * 
	 */
	std::vector<std::string> _all_commands;
	/**
	 * @brief Накопитель подписчиков
	 * 
	 */
	std::vector<Observer *> subscriber;
};