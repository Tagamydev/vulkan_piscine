/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 23:26:38 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/04 15:40:50 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cstdint>
#ifndef SCOP_HPP
# define SCOP_HPP

# include <vulkan/vulkan.h>
# include <vulkan/vulkan_core.h>
# include <GLFW/glfw3.h>
# include <stdexcept>
# include <iostream>
# include <string>
# include <cstdlib>
# include <vector>
# include <fstream>
# include "device.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace scop {

	struct PipelineConfigInfo
	{
		VkViewport								viewport;
		VkRect2D								scissor;
		VkPipelineViewportStateCreateInfo		viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo	inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo	rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo	multisampleInfo;
		VkPipelineColorBlendAttachmentState		colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo		colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo	depthStencilInfo;
		VkPipelineLayout						pipelineLayout = nullptr;
		VkRenderPass							renderPass = nullptr;
		uint32_t								subpass = 0;
	};

	class device;

	class window{

		public:

			window(int w, int h, std::string name);
			~window();
			bool	shouldClose();
			window(const window &) = delete;
			window &operator=(const window &) = delete;
			void	createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

			const int	_width;
			const int	_height;

		private:

			void	initWindow();


			std::string	_name;
			GLFWwindow	*_window;
	};

	class pipeline{

		public:

			pipeline(
				scop::device &selectedDevice,
				std::string vertFilepath,
				std::string fragFilepath,
				const PipelineConfigInfo &configInfo
			);
			~pipeline() {};

			pipeline(const pipeline &) = delete;
			pipeline &operator=(const pipeline &) = delete;

			static PipelineConfigInfo defaultPiplineConfigInfo(uint32_t width, uint32_t height);
		
		private:

			static std::vector<char> readFile(const std::string& filepath);

			void	createGraphicsPipeline(
				std::string& vertFilepath,
				std::string& fragFilepath,
				const PipelineConfigInfo &configInfo
			);
			void	createShaderModule(
				const std::vector<char>& code,
				VkShaderModule* shaderModule
			);

			scop::device	*_device;
			VkPipeline		_graphicsPipeline;
			VkShaderModule	_vertShaderModule;
			VkShaderModule	_fragShaderModule;
	};

	class app {

		public:

			void	run();

		private:

			scop::window	_window{WIDTH, HEIGHT, "scop"};
			scop::device	_device{this->_window};
			scop::pipeline	_pipeline{
				this->_device, 
				"shaders/simple_shader.vert.spv",
				"shaders/simple_shader.frag.spv",
				scop::pipeline::defaultPiplineConfigInfo(_window._width, _window._height)
			};
	};
}

#endif
