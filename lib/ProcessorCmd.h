#pragma once
#include "async.h"
#include <mutex>
#include <set>
#include "ContextCmd.h"
/**
 * @brief Класс обработчика команд.
 */
class ProcessorCmd {
public:
  /**
   * @brief Дать объект класса CmdProcessor.
   * @return объект класса CmdProcessor.
   */
	static ProcessorCmd& get_instance();
	/**
	 * @brief Создать контекст обработки блоков команд.
	 * @param bulk_size - размер блока команд.
	 * @return handle контекста обработки команд.
	 */
	async::handle_t create_context(size_t bulk_size);
	/**
	 * @brief Уничтожить контекст обработки блоков команд.
	 * @param handle - handle контекста обработки команд.
	 */
	void destroy_context(const async::handle_t& handle);
	/**
	 * @brief Обработать входные данные, содержащие команды.
	 * @param handle - handle контекста обработки команд.
	 * @param data - обрабатываемые данные.
	 * @param size - размер данных.
	 */
	void process(const async::handle_t& handle, const char* data, std::size_t size);

private:
	ProcessorCmd() = default;
	~ProcessorCmd() = default;

	std::mutex contexts_mutex_ {};
	std::map<async::handle_t, std::shared_ptr<ContextCmd>> contexts_;
	uint8_t context_id_ {};
};