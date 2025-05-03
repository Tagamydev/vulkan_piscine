/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:33:57 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/03 17:36:23 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"
#include <GLFW/glfw3.h>

ScopWindow::ScopWindow(int w, int h, std::string name) : _width(w), _height(h), _name(name) { initWindow(); }

ScopWindow::~ScopWindow() {
	glfwDestroyWindow(_window);
	glfwTerminate();
}

void ScopWindow::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(_width, _height, _name.c_str(), nullptr, nullptr);
}

bool ScopWindow::shouldClose() {
	return glfwWindowShouldClose(_window);
}

//Scop::Scop() {};

void Scop::run() {
	while (!_window.shouldClose())
	{
		glfwPollEvents();
	}
}
