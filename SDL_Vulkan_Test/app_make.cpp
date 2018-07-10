#include "app_make.hpp"

#include "system.hpp"
#include "window.hpp"
#include "device_functions.hpp"
#include <iostream>
#include <array>

#include "app_files.hpp"


sdlxvulkan::Handle<VkInstance> sdlxvulkan::app_make_instance
(
  System const& a_system,
  Window const& a_window,
  std::vector<std::string> const& a_extension_names,
  std::vector<std::string> const& a_layer_names,
  std::string const& a_application_name,
  uint32_t a_application_version,
  std::string const& a_engine_name,
  uint32_t a_engine_version,
  uint32_t a_vulkan_version,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  // If validation layers supplied, and the ones requested are not available, stop.
  if (!a_layer_names.empty() && !a_system.supports_layers(a_layer_names))
  {
    throw std::runtime_error{ "sdlxvulkan::Instance: Validation layers requested, but not available." };
  }

  std::cout << "Requested Instance Layers:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_layer : a_layer_names)
  {
    std::cout << l_layer << std::endl;

  }
  std::cout << std::endl;


  std::cout << "Requested Instance Extensions:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_ext : a_extension_names)
  {
    std::cout << l_ext << std::endl;

  }
  std::cout << std::endl;

  // get all the extensions required
  auto l_required_extensions = a_window.required_instance_extensions();

  std::cout << "Required Instance Extensions:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_ext : l_required_extensions)
  {
    std::cout << l_ext << std::endl;

  }
  std::cout << std::endl;


  // add the specified ones to these if they are not already present
  for (auto const& l_ext : a_extension_names)
  {
    if (std::find(l_required_extensions.cbegin(), l_required_extensions.cend(), l_ext) == l_required_extensions.cend())
    {
      l_required_extensions.push_back(l_ext);
    }
  }
  /*
  std::cout << "Final Extensions:" << std::endl;
  std::cout << "========================================" << std::endl;
  for (auto const& l_ext : l_required_extensions)
  {
  std::cout << l_ext << std::endl;

  }
  std::cout << std::endl;
  */

  // Initialise an application info structure
  // INITIALISE EVERYTHING PROPERLY FOR VULKAN STRUCTS
  VkApplicationInfo l_app_info{};
  l_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  l_app_info.pNext = nullptr;
  l_app_info.pApplicationName = a_application_name.c_str();
  l_app_info.applicationVersion = a_application_version;
  l_app_info.pEngineName = a_engine_name.c_str();
  l_app_info.engineVersion = a_engine_version;
  l_app_info.apiVersion = a_vulkan_version;

  // need to change the type of these
  std::vector<char const*> l_final_layers{};
  l_final_layers.reserve(a_layer_names.size());
  for (auto const& l_layer : a_layer_names)
  {
    l_final_layers.push_back(l_layer.c_str());
  }


  // and these
  std::vector<char const*> l_final_extensions{};
  l_final_extensions.reserve(l_required_extensions.size());
  for (auto const& l_ext : l_required_extensions)
  {
    l_final_extensions.push_back(l_ext.c_str());
  }

  // Initialise a create info struct.
  // INITIALISE EVERYTHING PROPERLY FOR VULKAN STRUCTS
  VkInstanceCreateInfo l_create_info{};
  l_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  l_create_info.pNext = nullptr;
  l_create_info.flags = 0;
  l_create_info.pApplicationInfo = &l_app_info;
  // if there are no layer names there are no layers.
  if (a_layer_names.empty())
  {
    l_create_info.enabledLayerCount = 0;
    l_create_info.ppEnabledLayerNames = nullptr;

  }
  // else there are.
  else
  {
    l_create_info.enabledLayerCount = static_cast<uint32_t>(l_final_layers.size());
    l_create_info.ppEnabledLayerNames = l_final_layers.data();
  }
  l_create_info.enabledExtensionCount = static_cast<uint32_t>(l_final_extensions.size());
  l_create_info.ppEnabledExtensionNames = l_final_extensions.data();

  return make_instance(a_system, a_window, l_create_info, a_allocation_callbacks);
}

sdlxvulkan::Handle<VkDebugReportCallbackEXT> sdlxvulkan::app_make_debug_report_callback_ext
(
  Handle<VkInstance> const& a_instance,
  VkDebugReportFlagsEXT a_flags,
  PFN_vkDebugReportCallbackEXT a_callback,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  VkDebugReportCallbackCreateInfoEXT l_callback_info{};
  l_callback_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  l_callback_info.pNext = nullptr;
  l_callback_info.flags = a_flags;
  l_callback_info.pfnCallback = a_callback;
  l_callback_info.pUserData = nullptr;

  return make_debug_report_callback_ext(a_instance, l_callback_info, a_allocation_callbacks);
}

VkPhysicalDeviceFeatures sdlxvulkan::app_make_required_device_features(VkPhysicalDeviceFeatures const& a_supported_features)
{
  assert(a_supported_features.samplerAnisotropy == VK_TRUE);

  VkPhysicalDeviceFeatures l_required{};
  l_required.robustBufferAccess = VK_FALSE;
  l_required.fullDrawIndexUint32 = VK_FALSE;
  l_required.imageCubeArray = VK_FALSE;
  l_required.independentBlend = VK_FALSE;
  l_required.geometryShader = VK_FALSE;
  l_required.tessellationShader = VK_FALSE;
  l_required.sampleRateShading = VK_FALSE;
  l_required.dualSrcBlend = VK_FALSE;
  l_required.logicOp = VK_FALSE;
  l_required.multiDrawIndirect = VK_FALSE;
  l_required.drawIndirectFirstInstance = VK_FALSE;
  l_required.depthClamp = VK_FALSE;
  l_required.depthBiasClamp = VK_FALSE;
  l_required.fillModeNonSolid = VK_FALSE;
  l_required.depthBounds = VK_FALSE;
  l_required.wideLines = VK_FALSE;
  l_required.largePoints = VK_FALSE;
  l_required.alphaToOne = VK_FALSE;
  l_required.multiViewport = VK_FALSE;
  l_required.samplerAnisotropy = VK_TRUE; // for the sampler
  l_required.textureCompressionETC2 = VK_FALSE;
  l_required.textureCompressionASTC_LDR = VK_FALSE;
  l_required.textureCompressionBC = VK_FALSE;
  l_required.occlusionQueryPrecise = VK_FALSE;
  l_required.pipelineStatisticsQuery = VK_FALSE;
  l_required.vertexPipelineStoresAndAtomics = VK_FALSE;
  l_required.fragmentStoresAndAtomics = VK_FALSE;
  l_required.shaderTessellationAndGeometryPointSize = VK_FALSE;
  l_required.shaderImageGatherExtended = VK_FALSE;
  l_required.shaderStorageImageExtendedFormats = VK_FALSE;
  l_required.shaderStorageImageMultisample = VK_FALSE;
  l_required.shaderStorageImageReadWithoutFormat = VK_FALSE;
  l_required.shaderStorageImageWriteWithoutFormat = VK_FALSE;
  l_required.shaderUniformBufferArrayDynamicIndexing = VK_FALSE;
  l_required.shaderSampledImageArrayDynamicIndexing = VK_FALSE;
  l_required.shaderStorageBufferArrayDynamicIndexing = VK_FALSE;
  l_required.shaderStorageImageArrayDynamicIndexing = VK_FALSE;
  l_required.shaderClipDistance = VK_FALSE;
  l_required.shaderCullDistance = VK_FALSE;
  l_required.shaderFloat64 = VK_FALSE;
  l_required.shaderInt64 = VK_FALSE;
  l_required.shaderInt16 = VK_FALSE;
  l_required.shaderResourceResidency = VK_FALSE;
  l_required.shaderResourceMinLod = VK_FALSE;
  l_required.sparseBinding = VK_FALSE;
  l_required.sparseResidencyBuffer = VK_FALSE;
  l_required.sparseResidencyImage2D = VK_FALSE;
  l_required.sparseResidencyImage3D = VK_FALSE;
  l_required.sparseResidency2Samples = VK_FALSE;
  l_required.sparseResidency4Samples = VK_FALSE;
  l_required.sparseResidency8Samples = VK_FALSE;
  l_required.sparseResidency16Samples = VK_FALSE;
  l_required.sparseResidencyAliased = VK_FALSE;
  l_required.variableMultisampleRate = VK_FALSE;
  l_required.inheritedQueries = VK_FALSE;

  return l_required;
}

sdlxvulkan::Handle<VkDevice> sdlxvulkan::app_make_device
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  uint32_t a_graphics_qfi,
  uint32_t a_present_qfi,
  VkPhysicalDeviceFeatures const& a_features,
  std::vector<std::string> const& a_extensions,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  float l_queue_priorities[1] = { 0.0 };

  std::array<VkDeviceQueueCreateInfo,2> l_queue_infos{};

  // first is graphics
  l_queue_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_infos[0].pNext = nullptr;
  l_queue_infos[0].flags = 0;
  l_queue_infos[0].queueFamilyIndex = a_graphics_qfi;
  l_queue_infos[0].queueCount = 1; // if we want more queues...
  l_queue_infos[0].pQueuePriorities = l_queue_priorities;

  // second is presenting
  l_queue_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_infos[1].pNext = nullptr;
  l_queue_infos[1].flags = 0;
  l_queue_infos[1].queueFamilyIndex = a_present_qfi;
  l_queue_infos[1].queueCount = 1; // if we want more queues...
  l_queue_infos[1].pQueuePriorities = l_queue_priorities;
  

  std::vector<char const*> l_device_extensions{};
  uint32_t l_device_extension_count = static_cast<uint32_t>(a_extensions.size());
  //std::vector<char const*> l_extensions{};
  l_device_extensions.reserve(a_extensions.size());
  for (auto const& l_ext : a_extensions)
  {
    l_device_extensions.push_back(l_ext.c_str());
  }

  // Make some device info
  VkDeviceCreateInfo l_device_info = {};
  l_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  l_device_info.pNext = nullptr;
  l_device_info.flags = 0;

  if (a_graphics_qfi == a_present_qfi)
  {
    l_device_info.queueCreateInfoCount = 1;
  }
  else
  {
    l_device_info.queueCreateInfoCount = 2;
  }
  l_device_info.pQueueCreateInfos = l_queue_infos.data();
  l_device_info.enabledLayerCount = 0;          // Deprecated, IGNORE
  l_device_info.ppEnabledLayerNames = nullptr;  // Deprecated, IGNORE
  l_device_info.enabledExtensionCount = l_device_extension_count;
  l_device_info.ppEnabledExtensionNames = l_device_extensions.data();
  l_device_info.pEnabledFeatures = &a_features;

  return make_device(a_physical_device, l_device_info, a_allocation_callbacks);
}


// Initialise with a VkSharingMode value of VK_SHARING_MODE_EXCLUSIVE.
sdlxvulkan::Handle<VkBuffer> sdlxvulkan::app_make_buffer_exclusive
(
  Handle<VkDevice> const& a_device,
  VkDeviceSize a_size,
  VkBufferUsageFlags a_usage,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  VkBufferCreateInfo l_buffer_info{};
  l_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  l_buffer_info.pNext = nullptr;
  l_buffer_info.flags = 0;
  l_buffer_info.size = a_size;
  l_buffer_info.usage = a_usage;
  l_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  l_buffer_info.queueFamilyIndexCount = 0;
  l_buffer_info.pQueueFamilyIndices = nullptr;

  return make_buffer(a_device, l_buffer_info, a_allocation_callbacks);
}

// Initialise with a VkSharingMode value of VK_SHARING_MODE_CONCURRENT. 
// a_queue_family_indicies must have at least 2 unique values, which are
// each less than the queue family property count of the physical device
// this is used with.
sdlxvulkan::Handle<VkBuffer> sdlxvulkan::app_make_buffer_concurrent
(
  Handle<VkDevice> const& a_device,
  VkDeviceSize a_size,
  VkBufferUsageFlags a_usage,
  std::vector<uint32_t> const& a_queue_family_indicies,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  assert(a_queue_family_indicies.size() > 1);

  VkBufferCreateInfo l_buffer_info{};
  l_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  l_buffer_info.pNext = nullptr;
  l_buffer_info.flags = 0;
  l_buffer_info.size = a_size;
  l_buffer_info.usage = a_usage;
  l_buffer_info.sharingMode = VK_SHARING_MODE_CONCURRENT;
  l_buffer_info.queueFamilyIndexCount = static_cast<uint32_t>(a_queue_family_indicies.size());
  l_buffer_info.pQueueFamilyIndices = a_queue_family_indicies.data();

  return make_buffer(a_device, l_buffer_info, a_allocation_callbacks);
}

sdlxvulkan::Buffer_Pair sdlxvulkan::app_make_buffer_memory_exclusive_pair
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  VkDeviceSize a_size,
  VkBufferUsageFlags a_usage,
  VkMemoryPropertyFlags a_properties
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  Buffer_Pair l_result{};
  // Create the buffer
  l_result.buffer = app_make_buffer_exclusive(a_device, a_size, a_usage);

  // Get its memory requirements
  VkMemoryRequirements l_mem_reqs{};
  l_functions->vkGetBufferMemoryRequirements(a_device, l_result.buffer, &l_mem_reqs);
  uint32_t l_mem_type = get_memory_type_from_properties(get_physical_device_memory_properties(a_physical_device), l_mem_reqs.memoryTypeBits, a_properties);

  // Make its memory
  l_result.memory = app_make_device_memory(a_device, l_mem_reqs.size, l_mem_type);

  // Bind the buffer and memory
  if (l_functions->vkBindBufferMemory(a_device, l_result.buffer, l_result.memory, 0) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to bind a buffer." };
  }

  return l_result;
}

void sdlxvulkan::app_copy_buffer
(
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  Handle<VkBuffer> const& a_source,
  Handle<VkBuffer> const& a_dest,
  VkDeviceSize a_size
)
{
  assert(a_device);
  assert(a_command_pool);
  assert(a_queue);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(l_functions->vkBeginCommandBuffer != nullptr);
  assert(l_functions->vkCmdCopyBuffer != nullptr);
  assert(l_functions->vkEndCommandBuffer != nullptr);
  assert(l_functions->vkQueueSubmit != nullptr);
  assert(l_functions->vkQueueWaitIdle != nullptr);

  VkCommandBufferAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.commandPool = a_command_pool;
  l_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  l_alloc_info.commandBufferCount = 1;

  Handle<VkCommandBuffer> l_command_buffer = make_command_buffer(a_command_pool, l_alloc_info);

  VkCommandBufferBeginInfo l_begin_info{};
  l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.pNext = nullptr;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  l_begin_info.pInheritanceInfo = nullptr;


  if (l_functions->vkBeginCommandBuffer(l_command_buffer, &l_begin_info) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Copying Buffer: Failed to begin command buffer." };
  }
  //vkBeginCommandBuffer(l_command_buffers[0], &l_begin_info);

  std::array<VkBufferCopy, 1> l_copy_regions{};
  l_copy_regions[0].srcOffset = 0; // Optional
  l_copy_regions[0].dstOffset = 0; // Optional
  l_copy_regions[0].size = a_size;

  l_functions->vkCmdCopyBuffer(l_command_buffer, a_source, a_dest, 1, l_copy_regions.data());

  l_functions->vkEndCommandBuffer(l_command_buffer);

  std::array<VkCommandBuffer, 1> l_command_buffers_temp{ l_command_buffer };

  VkSubmitInfo l_submit_info = {};
  l_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  l_submit_info.pNext = nullptr;
  l_submit_info.waitSemaphoreCount = 0;
  l_submit_info.pWaitSemaphores = nullptr;
  l_submit_info.pWaitDstStageMask = 0;
  l_submit_info.commandBufferCount = 1;
  l_submit_info.pCommandBuffers = l_command_buffers_temp.data();
  l_submit_info.signalSemaphoreCount = 0;
  l_submit_info.pSignalSemaphores = nullptr;

  std::cout << "submit" << std::endl;
  if (l_functions->vkQueueSubmit(a_queue, 1, &l_submit_info, VK_NULL_HANDLE) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Copying Buffer: Failed to submit command buffer." };
  }

  l_functions->vkQueueWaitIdle(a_queue); 
}

// Make a batch of self-destroying VkCommandBuffer.
// Destruction is independent for each so there's no batch freeing.
std::vector<sdlxvulkan::Handle<VkCommandBuffer>> sdlxvulkan::app_make_command_buffers
(
  Handle<VkCommandPool> const& a_command_pool,
  VkCommandBufferLevel a_level,
  uint32_t a_count
)
{
  VkCommandBufferAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.commandPool = a_command_pool.get();
  l_alloc_info.level = a_level;
  l_alloc_info.commandBufferCount = a_count;

  return make_command_buffers(a_command_pool, l_alloc_info);
}

sdlxvulkan::Handle<VkCommandBuffer> sdlxvulkan::app_make_begin_one_time_command_buffer
(
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool
)
{
  assert(a_device);
  assert(a_command_pool);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  VkCommandBufferAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.commandPool = a_command_pool;
  l_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  l_alloc_info.commandBufferCount = 1;

  Handle<VkCommandBuffer> l_result = make_command_buffer(a_command_pool, l_alloc_info);

  VkCommandBufferBeginInfo l_begin_info{};
  l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.pNext = nullptr;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  l_begin_info.pInheritanceInfo = nullptr;

  l_functions->vkBeginCommandBuffer(l_result, &l_begin_info);

  return l_result;
}
/*
void sdlxvulkan::app_begin_one_time_command_buffer
(
  Handle<VkDevice> const& a_device,
  Handle<VkCommandBuffer> const& a_command_buffer
)
{
  assert(a_device);
  assert(a_command_buffer);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  VkCommandBufferBeginInfo l_begin_info{};
  l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.pNext = nullptr;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  l_begin_info.pInheritanceInfo = nullptr;

  l_functions->vkBeginCommandBuffer(a_command_buffer, &l_begin_info);
}
*/
void sdlxvulkan::app_end_submit_one_time_command_buffer
(
  Handle<VkDevice> const& a_device,
  Handle<VkCommandBuffer> const& a_command_buffer,
  Handle<VkQueue> const& a_queue
)
{
  assert(a_device);
  assert(a_command_buffer);
  assert(a_queue);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  l_functions->vkEndCommandBuffer(a_command_buffer);

  std::array<VkCommandBuffer, 1> l_raw{ a_command_buffer.get() };
  VkSubmitInfo l_submit_info{};
  l_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  l_submit_info.pNext = nullptr;
  l_submit_info.waitSemaphoreCount = 0;
  l_submit_info.pWaitSemaphores = nullptr;
  l_submit_info.pWaitDstStageMask = nullptr;
  l_submit_info.commandBufferCount = 1;
  l_submit_info.pCommandBuffers = l_raw.data();
  l_submit_info.signalSemaphoreCount = 0;
  l_submit_info.pSignalSemaphores = nullptr;

  l_functions->vkQueueSubmit(a_queue, 1, &l_submit_info, VK_NULL_HANDLE);
  l_functions->vkQueueWaitIdle(a_queue);
}


sdlxvulkan::Handle<VkCommandPool> sdlxvulkan::app_make_command_pool
(
  Handle<VkDevice> const& a_device,
  uint32_t a_queue_family_index,
  VkCommandPoolCreateFlags a_flags,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  // Initialise some creation info
  VkCommandPoolCreateInfo l_command_pool_info{};
  l_command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  l_command_pool_info.pNext = nullptr;
  l_command_pool_info.flags = a_flags;
  l_command_pool_info.queueFamilyIndex = a_queue_family_index;

  return make_command_pool(a_device, l_command_pool_info, a_allocation_callbacks);
}


sdlxvulkan::Handle<VkDeviceMemory> sdlxvulkan::app_make_device_memory
(
  Handle<VkDevice> const& a_device,
  VkDeviceSize  a_size,
  uint32_t a_memory_type_index,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  VkMemoryAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.allocationSize = a_size;
  l_alloc_info.memoryTypeIndex = a_memory_type_index;

  return make_device_memory(a_device, l_alloc_info, a_allocation_callbacks);
}


sdlxvulkan::Handle<VkShaderModule> sdlxvulkan::app_make_shader_module_from_file
(
  Handle<VkDevice> const& a_device,
  std::string const& a_exepath,
  std::string const& a_filepath
)
{
  auto l_path = get_filepath(a_exepath, a_filepath);
  auto l_spv_data = get_file_bytes(l_path);

  VkShaderModuleCreateInfo l_module_info;
  l_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  l_module_info.pNext = NULL;
  l_module_info.flags = 0;
  l_module_info.codeSize = l_spv_data.size();
  l_module_info.pCode = reinterpret_cast<uint32_t const*>(l_spv_data.data());

  return make_shader_module(a_device, l_module_info);
}


sdlxvulkan::Handle<VkPipelineCache>sdlxvulkan::app_make_pipeline_cache
(
  Handle<VkDevice> const& a_device
)
{
  VkPipelineCacheCreateInfo l_create_info{};
  l_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
  l_create_info.pNext = nullptr;
  l_create_info.flags = 0;
  l_create_info.initialDataSize = 0;
  l_create_info.pInitialData = nullptr;

  return make_pipeline_cache(a_device, l_create_info);
}

sdlxvulkan::Image_Pair sdlxvulkan::app_make_image
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  uint32_t a_width,
  uint32_t a_height,
  VkFormat a_format,
  VkImageTiling a_tiling,
  VkImageUsageFlags a_usage,
  VkMemoryPropertyFlags a_properties
)
{
  assert(a_physical_device);
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(l_functions->vkGetImageMemoryRequirements != nullptr);
  assert(l_functions->vkBindImageMemory != nullptr);

  VkImageCreateInfo l_image_info = {};
  l_image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  l_image_info.imageType = VK_IMAGE_TYPE_2D;
  l_image_info.extent.width = a_width;
  l_image_info.extent.height = a_height;
  l_image_info.extent.depth = 1;
  l_image_info.mipLevels = 1;
  l_image_info.arrayLayers = 1;
  l_image_info.format = a_format;
  l_image_info.tiling = a_tiling;
  l_image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  l_image_info.usage = a_usage;
  l_image_info.samples = VK_SAMPLE_COUNT_1_BIT;
  l_image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  Image_Pair l_result{};

  l_result.image = make_image(a_device, l_image_info);

  VkMemoryRequirements l_mem_reqs{};
  l_functions->vkGetImageMemoryRequirements(a_device, l_result.image, &l_mem_reqs);

  VkMemoryAllocateInfo l_alloc_info = {};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_alloc_info.allocationSize = l_mem_reqs.size;
  l_alloc_info.memoryTypeIndex = get_memory_type_from_properties(get_physical_device_memory_properties(a_physical_device), l_mem_reqs.memoryTypeBits, a_properties);

  l_result.memory = make_device_memory(a_device, l_alloc_info);

  l_functions->vkBindImageMemory(a_device, l_result.image, l_result.memory, 0);

  return l_result;
}


sdlxvulkan::Handle<VkImageView> sdlxvulkan::app_make_image_view
(
  Handle<VkImage> const& a_image,
  VkFormat a_format
)
{
  VkImageViewCreateInfo l_image_view_info {};
  l_image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  l_image_view_info.pNext = nullptr;
  l_image_view_info.flags = 0;
  l_image_view_info.image = a_image;
  l_image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
  l_image_view_info.format = a_format;
  l_image_view_info.components.r = VK_COMPONENT_SWIZZLE_R;
  l_image_view_info.components.g = VK_COMPONENT_SWIZZLE_G;
  l_image_view_info.components.b = VK_COMPONENT_SWIZZLE_B;
  l_image_view_info.components.a = VK_COMPONENT_SWIZZLE_A;
  l_image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  l_image_view_info.subresourceRange.baseMipLevel = 0;
  l_image_view_info.subresourceRange.levelCount = 1;
  l_image_view_info.subresourceRange.baseArrayLayer = 0;
  l_image_view_info.subresourceRange.layerCount = 1;

  return make_image_view(a_image, l_image_view_info);
}


sdlxvulkan::Image_Pair sdlxvulkan::app_make_texture_image
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  std::string const& a_filepath
)
{
  assert(a_physical_device);
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(l_functions->vkMapMemory != nullptr);
  assert(l_functions->vkUnmapMemory != nullptr);

  STB_Image l_image_data{ a_filepath };
  assert(l_image_data.size() != 0);

  // Make a staging buffer
  Buffer_Pair l_staging_buffer = app_make_buffer_memory_exclusive_pair(a_physical_device, a_device, l_image_data.size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  // Fill it with the image data in RGBA format
  void* l_data{nullptr};
  l_functions->vkMapMemory(a_device, l_staging_buffer.memory, 0, l_image_data.size(), 0, &l_data);
  memcpy(l_data, l_image_data.data(), l_image_data.size());
  l_functions->vkUnmapMemory(a_device, l_staging_buffer.memory);

  uint32_t const l_width{ static_cast<uint32_t>(l_image_data.width()) };
  uint32_t const l_height{ static_cast<uint32_t>(l_image_data.height()) };

  Image_Pair l_image = app_make_image
  (
    a_physical_device, 
    a_device, 
    l_width,
    l_height,
    VK_FORMAT_R8G8B8A8_UNORM, 
    VK_IMAGE_TILING_OPTIMAL,
    VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
  );

  // Transisiton ready for copying  
  app_transition_image_layout(a_device, a_command_pool, a_queue, l_image.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  
  // Copy the data
  app_copy_buffer_to_image(a_device, a_command_pool, a_queue, l_staging_buffer.buffer, l_image.image, l_width, l_height);
  
  // Transition ready for use
  app_transition_image_layout(a_device, a_command_pool, a_queue, l_image.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  
  return l_image;
}


void sdlxvulkan::app_transition_image_layout
(
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  Handle<VkImage> const& a_image,
  VkFormat a_format,
  VkImageLayout a_old_layout,
  VkImageLayout a_new_layout
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(a_command_pool);
  assert(a_queue);
  assert(a_image);

  auto l_command_buffer = app_make_begin_one_time_command_buffer(a_device, a_command_pool);

  VkImageMemoryBarrier l_barrier{};
  l_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  l_barrier.pNext = nullptr; 
  l_barrier.srcAccessMask = 0; // see below
  l_barrier.dstAccessMask = 0; // see below
  l_barrier.oldLayout = a_old_layout;
  l_barrier.newLayout = a_new_layout;
  l_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  l_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  l_barrier.image = a_image;
  l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  l_barrier.subresourceRange.baseMipLevel = 0;
  l_barrier.subresourceRange.levelCount = 1;
  l_barrier.subresourceRange.baseArrayLayer = 0;
  l_barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags l_sources_stage{};
  VkPipelineStageFlags l_destination_stage{};

  if (a_old_layout == VK_IMAGE_LAYOUT_UNDEFINED && a_new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) 
  {
    l_barrier.srcAccessMask = 0;
    l_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    l_sources_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    l_destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }
  else if (a_old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && a_new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) 
  {
    l_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    l_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    l_sources_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    l_destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  }
  else 
  {
    throw std::invalid_argument{ "unsupported layout transition!" };
  }


  l_functions->vkCmdPipelineBarrier
  (
    l_command_buffer,
    l_sources_stage, l_destination_stage,
    0,
    0, nullptr,
    0, nullptr,
    1, &l_barrier
  );

  app_end_submit_one_time_command_buffer(a_device, l_command_buffer, a_queue);
}


void sdlxvulkan::app_copy_buffer_to_image
(
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  Handle<VkBuffer> const& a_buffer,
  Handle<VkImage> const& a_image,
  uint32_t a_width,
  uint32_t a_height
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(a_command_pool);
  assert(a_queue);
  assert(a_buffer);
  assert(a_image);

  auto l_command_buffer = app_make_begin_one_time_command_buffer(a_device, a_command_pool);

  VkBufferImageCopy l_region{};
  l_region.bufferOffset = 0;
  l_region.bufferRowLength = 0;
  l_region.bufferImageHeight = 0;

  l_region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  l_region.imageSubresource.mipLevel = 0;
  l_region.imageSubresource.baseArrayLayer = 0;
  l_region.imageSubresource.layerCount = 1;

  l_region.imageOffset = { 0, 0, 0 };
  l_region.imageExtent = { a_width, a_height, 1 };

  l_functions->vkCmdCopyBufferToImage
  (
    l_command_buffer,
    a_buffer,
    a_image,
    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
    1,
    &l_region
  );

  app_end_submit_one_time_command_buffer(a_device, l_command_buffer, a_queue);
}


sdlxvulkan::Handle<VkSampler> sdlxvulkan::app_make_sampler
(
  Handle<VkDevice> const& a_device,
  VkPhysicalDeviceFeatures const& a_features
)
{
  VkSamplerCreateInfo l_sampler_info {};
  l_sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  l_sampler_info.pNext = nullptr;
  l_sampler_info.flags = 0;
  l_sampler_info.magFilter = VK_FILTER_LINEAR;
  l_sampler_info.minFilter = VK_FILTER_LINEAR;
  l_sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
  l_sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  l_sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  l_sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  l_sampler_info.mipLodBias = 0.0f;
  if (a_features.samplerAnisotropy == VK_TRUE)
  {
    // Needs the device feature for anisotropy
    l_sampler_info.anisotropyEnable = VK_TRUE; 
    l_sampler_info.maxAnisotropy = 16;
  }
  else
  {
    l_sampler_info.anisotropyEnable = VK_FALSE;
    l_sampler_info.maxAnisotropy = 1;
  }
  l_sampler_info.compareEnable = VK_FALSE;
  l_sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
  l_sampler_info.minLod = 0.0f;
  l_sampler_info.maxLod = 0.0f;
  l_sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  l_sampler_info.unnormalizedCoordinates = VK_FALSE;

  return make_sampler(a_device, l_sampler_info);
}