#pragma once

#include <iostream>

/**
 * @brief Вывод обычных сообщений
 * 
 */
#define INFO(msg) std::cout << msg << std::endl

/**
 * @brief Вывод сообщений ошибок
 * 
 */
#define ERR_INFO(msg) std::cerr << msg << std::endl

/**
 * @brief Вывод отладочных сообщений
 * 
 */
#ifndef NDEBUG
#define DEB_INFO(msg) std::cout << msg << std::endl
#else
#define DEB_INFO(msg)
#endif