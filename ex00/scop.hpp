/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:26:38 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/03 17:42:05 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef SCOP_HPP
# define SCOP_HPP

# include <vulkan/vulkan.h>
# include <GLFW/glfw3.h>
# include <stdexcept>
# include <iostream>
# include <string>
# include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class ScopWindow{
	public:
		ScopWindow(int w, int h, std::string name);
		~ScopWindow();
		bool	shouldClose();
		ScopWindow(const ScopWindow &) = delete;
		ScopWindow &operator=(const ScopWindow &) = delete;

	private:
		void	initWindow();

		const int	_width;
		const int	_height;

		std::string	_name;
		GLFWwindow	*_window;
};

class Scop {
	public:
		void	run();
	private:
		ScopWindow	_window{WIDTH, HEIGHT, "scop"};
};

#endif
