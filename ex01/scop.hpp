/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:26:38 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/03 22:40:45 by samusanc         ###   ########.fr       */
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
# include <vector>
# include <fstream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace scop {

	class window{

		public:
			window(int w, int h, std::string name);
			~window();
			bool	shouldClose();
			window(const window &) = delete;
			window &operator=(const window &) = delete;

		private:
			void	initWindow();

			const int	_width;
			const int	_height;

			std::string	_name;
			GLFWwindow	*_window;
	};

	class pipeline{
		public:
			pipeline(std::string vertFilepath, std::string fragFilepath);
			
		private:
			static std::vector<char> readFile(const std::string& filepath);
			void createGraphicsPipeline(std::string& vertFilepath, std::string& fragFilepath);

	};

	class app {

		public:
			void	run();

		private:
			scop::window	_window{WIDTH, HEIGHT, "scop"};
			scop::pipeline	_pipeline{"shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv"};
	};
}

#endif
