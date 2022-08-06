#pragma once
#include<iostream>
#include <fstream>
#include<vector>
#include <filesystem>

#include"Observer.h"
#include "Accumulator_Commands.h"
/**
 * @brief Класс-подписчик для вывода данных в файл
 * 
 */
class Logger_in_File: public Observer
{
public:
/**
 * @brief Перегруженный конструктор для подписки в классе издателя
 * 
 */
	Logger_in_File(Accumulator_Commands* loger) {
		loger->add_subscriber(this);
	}
	~Logger_in_File()=default;
/**
 * @brief Фуункция вывода в файл данных
 * 
 * @param time_first_command время первой командв используется для составления имени файла
 * @param v_stream_command   все веденные команды для вывода в консоль
 */
	void notify(const long long int& time_first_command,
				const std::vector<std::string>& v_stream_command);
private:
	Logger_in_File() = default;
	Logger_in_File(const Logger_in_File& root) = delete;
	Logger_in_File& operator=(const Logger_in_File&) = delete;
	Logger_in_File(Logger_in_File&& root) = delete;
	Logger_in_File& operator=(Logger_in_File&&) = delete;
};
