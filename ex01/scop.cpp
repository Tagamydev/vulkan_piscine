/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:33:57 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/03 18:19:21 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"
#include <GLFW/glfw3.h>

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

	//Scop::Scop() {};

	void app::run() {
		while (!_window.shouldClose())
		{
			glfwPollEvents();
		}
	}
}
