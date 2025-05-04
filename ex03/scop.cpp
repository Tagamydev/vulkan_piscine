/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samusanc <samusanc@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:33:57 by samusanc          #+#    #+#             */
/*   Updated: 2025/05/04 17:24:16 by samusanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.hpp"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <exception>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace scop{

	window::window(int w, int h, std::string name) : _width(w), _height(h), _name(name) { initWindow(); }

	window::~window() {
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

	void window::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
		if (glfwCreateWindowSurface(instance, _window, nullptr, surface) != VK_SUCCESS)
			throw std::runtime_error("fail to create window surface");
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

	pipeline::pipeline(scop::device &selectedDevice, std::string vertFilepath, std::string fragFilepath, const PipelineConfigInfo &configInfo) {
		this->_device = &selectedDevice;
		createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
	}

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

	void	pipeline::createGraphicsPipeline(std::string& vertFilepath, std::string& fragFilepath, const PipelineConfigInfo &configInfo) {
		auto x = readFile(vertFilepath);
		auto y = readFile(fragFilepath);


	};

	void	pipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
		VkShaderModuleCreateInfo	createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		if (vkCreateShaderModule(_device->_device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS)
			throw std::runtime_error("failed to create shader module");
	}

	void	initViewportDefaultConfig(PipelineConfigInfo &result, uint32_t width, uint32_t height) {
		VkViewport							&viewport = result.viewport;
		VkRect2D							&scissor = result.scissor;
		VkPipelineViewportStateCreateInfo	&info = result.viewportInfo;

		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(width);
		viewport.height = static_cast<float>(height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		scissor.offset = {0, 0};
		scissor.extent = {width, height};
		info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		info.viewportCount = 1;
		info.pViewports = &result.viewport;
		info.scissorCount = 1;
		info.pScissors = &result.scissor;
	}

	void	initAssemblyDefaultConfig(PipelineConfigInfo &result) {
		VkPipelineInputAssemblyStateCreateInfo	&assembly = result.inputAssemblyInfo;

		assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		assembly.primitiveRestartEnable = VK_FALSE;
	}

	void	initRasterizationDefaultConfig(PipelineConfigInfo &result) {
		VkPipelineRasterizationStateCreateInfo	&info = result.rasterizationInfo;

		info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		info.depthClampEnable = VK_FALSE;
		info.rasterizerDiscardEnable = VK_FALSE;
		info.polygonMode = VK_POLYGON_MODE_FILL;
		info.lineWidth = 1.0f;
		info.cullMode = VK_CULL_MODE_NONE;
		info.frontFace = VK_FRONT_FACE_CLOCKWISE;
		info.depthBiasEnable = VK_FALSE;
		info.depthBiasConstantFactor = 0.0f;
		info.depthBiasClamp = 0.0f;
		info.depthBiasSlopeFactor = 0.0f;
	}

	void	initMultisampleDefaultConfig(PipelineConfigInfo &result) {
		VkPipelineMultisampleStateCreateInfo	&info = result.multisampleInfo;

		info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		info.sampleShadingEnable = VK_FALSE;
		info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		info.minSampleShading = 1.0f;
		info.pSampleMask = nullptr;
		info.alphaToCoverageEnable = VK_FALSE;
		info.alphaToOneEnable = VK_FALSE;
	}

	void	initColorBlendDefaultConfig(PipelineConfigInfo &result) {
		VkPipelineColorBlendAttachmentState		&attachment = result.colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo		&info = result.colorBlendInfo;

		attachment.colorWriteMask = 
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
			VK_COLOR_COMPONENT_A_BIT;
		attachment.blendEnable = VK_FALSE;
		attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		attachment.colorBlendOp = VK_BLEND_OP_ADD;
		attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
		attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
		attachment.alphaBlendOp = VK_BLEND_OP_ADD;

		info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		info.logicOpEnable = VK_FALSE;
		info.logicOp = VK_LOGIC_OP_COPY;
		info.attachmentCount = 1;
		info.pAttachments = &result.colorBlendAttachment;
		info.blendConstants[0] = 0.0f;
		info.blendConstants[1] = 0.0f;
		info.blendConstants[2] = 0.0f;
		info.blendConstants[3] = 0.0f;
	}

	void	initDepthStencilDefaultConfig(PipelineConfigInfo &result) {
		VkPipelineDepthStencilStateCreateInfo		&info = result.depthStencilInfo;

		info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		info.depthTestEnable = VK_TRUE;
		info.depthWriteEnable = VK_TRUE;
		info.depthCompareOp = VK_COMPARE_OP_LESS;
		info.depthBoundsTestEnable = VK_FALSE;
		info.minDepthBounds = 0.0f;
		info.maxDepthBounds = 1.0f;
		info.stencilTestEnable = VK_FALSE;
		info.front = {};
		info.back = {};
	}

	PipelineConfigInfo pipeline::defaultPiplineConfigInfo(uint32_t width, uint32_t height) {
		// pipeline = assembly -> rasterization ->
		PipelineConfigInfo						result;

		initViewportDefaultConfig(result, width, height);
		initAssemblyDefaultConfig(result);
		initRasterizationDefaultConfig(result);
		initMultisampleDefaultConfig(result);
		initColorBlendDefaultConfig(result);
		initDepthStencilDefaultConfig(result);
		return result;
	}
	//Scop::Scop() {};

	void app::run() {
		while (!_window.shouldClose())
		{
			glfwPollEvents();
		}
	}
}
