#pragma once
#include <ostream>
#include <vector>
#include <ctime>
#include <string>

#include "Observer.h"

/**
 * @brief Класс блока команд 
 *
 */
class Accumulator_Commands
{
public:
	Accumulator_Commands()= default;
	~Accumulator_Commands()= default;
	/**
	 * @brief функция добавляет введенную команду в накопитель
	 *
	 */
	void add_commands(const std::string& cmd);
	/**
	 * @brief  функция очищает накопитель от введенных ранее команд
	 *
	 */
	void clear_bulk();
	/**
     * @brief Дать размер блока команд.
     * @return размер блока команд.
	 */
    size_t size() const;
	/**
	 * @brief Время первой команды
	 * 
	 */
	std::time_t time() const;
  	/**
     * @brief Дать все команды блока.
     * @return команды блока.
     */
    std::vector<std::string> get_cmds() const;
    /**
     * @brief Оператор вывода в поток блока команд.
     * @return
     */
	friend std::ostream& operator <<(std::ostream& os, const Accumulator_Commands& bulk);

private:
	/**
	 * @brief Накопитель команд
	 * 
	 */
	std::vector<std::string> pool_all_commands;
	std::time_t time_{};
};