/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:33:57 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/03 22:43:34 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"
#include <GLFW/glfw3.h>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace scop{

	window::window(int w, int h, std::string name) : _width(w), _height(h), _name(name) { initWindow(); }

	window::~window() {
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void window::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		_window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
	}

	bool window::shouldClose() {
		return glfwWindowShouldClose(_window);
	}

	pipeline::pipeline(std::string vertFilepath, std::string fragFilepath) { createGraphicsPipeline(vertFilepath, fragFilepath); };

	std::vector<char> pipeline::readFile(const std::string& filepath) {
		std::ifstream file{filepath, std::ios::ate | std::ios::binary};

		if (!file.is_open())
			throw std::runtime_error("failed to open file: " + filepath);

		size_t	fileSize = static_cast<size_t>(file.tellg());
		std::vector<char>	buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return (buffer);
	}

	void	pipeline::createGraphicsPipeline(std::string& vertFilepath, std::string& fragFilepath) {
		auto x = readFile(vertFilepath);
		auto y = readFile(fragFilepath);
	};

	//Scop::Scop() {};

	void app::run() {
		while (!_window.shouldClose())
		{
			glfwPollEvents();
		}
	}
}
