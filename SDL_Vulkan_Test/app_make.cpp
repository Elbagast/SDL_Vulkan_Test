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


sdlxvulkan::Handle<VkImage> sdlxvulkan::app_make_image
(
  Handle<VkDevice> const& a_device,
  uint32_t a_width,
  uint32_t a_height,
  VkFormat a_format,
  VkImageTiling a_tiling,
  VkImageUsageFlags a_usage
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

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

  return make_image(a_device, l_image_info);
}

sdlxvulkan::Handle<VkImageView> sdlxvulkan::app_make_image_view
(
  Handle<VkImage> const& a_image,
  VkFormat a_format,
  VkImageAspectFlags a_aspect_flags
)
{
  VkImageViewCreateInfo l_image_view_info{};
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
  l_image_view_info.subresourceRange.aspectMask = a_aspect_flags;
  l_image_view_info.subresourceRange.baseMipLevel = 0;
  l_image_view_info.subresourceRange.levelCount = 1;
  l_image_view_info.subresourceRange.baseArrayLayer = 0;
  l_image_view_info.subresourceRange.layerCount = 1;

  return make_image_view(a_image, l_image_view_info);
}


sdlxvulkan::Handle<VkDeviceMemory> sdlxvulkan::app_make_bind_image_memory
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  Handle<VkImage> const& a_image,
  VkMemoryPropertyFlags a_properties
)
{
  assert(a_physical_device);
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(l_functions->vkGetImageMemoryRequirements != nullptr);
  assert(l_functions->vkBindImageMemory != nullptr);
  
  VkMemoryRequirements l_mem_reqs{};
  l_functions->vkGetImageMemoryRequirements(a_device, a_image, &l_mem_reqs);

  VkMemoryAllocateInfo l_alloc_info = {};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_alloc_info.allocationSize = l_mem_reqs.size;
  l_alloc_info.memoryTypeIndex = get_memory_type_from_properties(get_physical_device_memory_properties(a_physical_device), l_mem_reqs.memoryTypeBits, a_properties);

  auto l_result = make_device_memory(a_device, l_alloc_info);

  l_functions->vkBindImageMemory(a_device, a_image, l_result, 0);

  return l_result;
}


sdlxvulkan::Image_Pair sdlxvulkan::app_make_image_pair
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

  Image_Pair l_result{};

  l_result.image = app_make_image(a_device, a_width, a_height, a_format, a_tiling, a_usage);
  l_result.memory = app_make_bind_image_memory(a_physical_device, a_device, l_result.image, a_properties);

  return l_result;
}

sdlxvulkan::Image_Trio sdlxvulkan::app_make_image_trio
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  uint32_t a_width,
  uint32_t a_height,
  VkFormat a_format,
  VkImageTiling a_tiling,
  VkImageUsageFlags a_usage,
  VkMemoryPropertyFlags a_properties,
  VkImageAspectFlags a_aspect_flags
)
{
  assert(a_physical_device);
  assert(a_device);

  Image_Trio l_result{};

  l_result.image = app_make_image(a_device, a_width, a_height, a_format, a_tiling, a_usage);
  l_result.memory = app_make_bind_image_memory(a_physical_device, a_device, l_result.image, a_properties);
  l_result.view = app_make_image_view(l_result.image, a_format, a_aspect_flags);

  return l_result;
}


sdlxvulkan::Image_Pair sdlxvulkan::app_make_texture_image_pair
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

  Image_Pair l_image = app_make_image_pair
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


sdlxvulkan::Image_Trio sdlxvulkan::app_make_texture_image_trio
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
  void* l_data{ nullptr };
  l_functions->vkMapMemory(a_device, l_staging_buffer.memory, 0, l_image_data.size(), 0, &l_data);
  memcpy(l_data, l_image_data.data(), l_image_data.size());
  l_functions->vkUnmapMemory(a_device, l_staging_buffer.memory);

  uint32_t const l_width{ static_cast<uint32_t>(l_image_data.width()) };
  uint32_t const l_height{ static_cast<uint32_t>(l_image_data.height()) };

  Image_Trio l_result{};
  
  l_result.image = app_make_image(a_device, l_width, l_height, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
  l_result.memory = app_make_bind_image_memory(a_physical_device, a_device, l_result.image, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  // Transisiton ready for copying  
  app_transition_image_layout(a_device, a_command_pool, a_queue, l_result.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  // Copy the data
  app_copy_buffer_to_image(a_device, a_command_pool, a_queue, l_staging_buffer.buffer, l_result.image, l_width, l_height);

  // Transition ready for use
  app_transition_image_layout(a_device, a_command_pool, a_queue, l_result.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  
  l_result.view = app_make_image_view(l_result.image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT);
  
  return l_result;
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

  if (a_new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
  {
    l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

    if (has_stencil_component(a_format))
    {
      l_barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
    }
  }
  else 
  {
    l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  }

  //l_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
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
  else if (a_old_layout == VK_IMAGE_LAYOUT_UNDEFINED && a_new_layout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
  {
    l_barrier.srcAccessMask = 0;
    l_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    l_sources_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    l_destination_stage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
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
  l_sampler_info.magFilter = VK_FILTER_LINEAR; // VkFilter value
  l_sampler_info.minFilter = VK_FILTER_LINEAR; // VkFilter value
  l_sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR; // VkSamplerMipmapMode value
  l_sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT; // VkSamplerAddressMode value
  l_sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT; // VkSamplerAddressMode value
  l_sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT; // VkSamplerAddressMode value
  l_sampler_info.mipLodBias = 0.0f;
  if (a_features.samplerAnisotropy == VK_TRUE)
  {
    // Needs the device feature for anisotropy
    l_sampler_info.anisotropyEnable = VK_TRUE; 
    l_sampler_info.maxAnisotropy = 16.0f;
  }
  else
  {
    l_sampler_info.anisotropyEnable = VK_FALSE;
    l_sampler_info.maxAnisotropy = 1.0f;
  }
  l_sampler_info.compareEnable = VK_FALSE;
  l_sampler_info.compareOp = VK_COMPARE_OP_ALWAYS;
  l_sampler_info.minLod = 0.0f;
  l_sampler_info.maxLod = 0.0f; // need to know about texture mipmaps
  l_sampler_info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  l_sampler_info.unnormalizedCoordinates = VK_FALSE;

  return make_sampler(a_device, l_sampler_info);
}


VkFormat sdlxvulkan::find_depth_format(Handle<VkPhysicalDevice> const& a_physical_device)
{
  return find_supported_format
  (
    a_physical_device,
    { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
    VK_IMAGE_TILING_OPTIMAL,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
  );
}

bool sdlxvulkan::has_stencil_component(VkFormat a_format)
{
  return a_format == VK_FORMAT_D32_SFLOAT_S8_UINT || a_format == VK_FORMAT_D24_UNORM_S8_UINT;
}


sdlxvulkan::Image_Trio sdlxvulkan::app_make_depth_image_trio
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  uint32_t a_width,
  uint32_t a_height
)
{
  assert(a_physical_device);
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  
  auto l_format = find_depth_format(a_physical_device);
  
  auto l_result = app_make_image_trio
  (
    a_physical_device, 
    a_device, 
    a_width, 
    a_height, 
    l_format, 
    VK_IMAGE_TILING_OPTIMAL,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
    VK_IMAGE_ASPECT_DEPTH_BIT
  );

  app_transition_image_layout
  (
    a_device, 
    a_command_pool, 
    a_queue,
    l_result.image,
    l_format,
    VK_IMAGE_LAYOUT_UNDEFINED,
    VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
  );

  return l_result;
}

sdlxvulkan::Handle<VkDescriptorSetLayout> sdlxvulkan::app_make_descriptor_set_layout
(
  Handle<VkDevice> const& a_device
)
{
  VkDescriptorSetLayoutBinding l_ubo_layout_binding{};
  l_ubo_layout_binding.binding = 0;
  l_ubo_layout_binding.descriptorCount = 1;
  l_ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  l_ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  l_ubo_layout_binding.pImmutableSamplers = nullptr; // not relevent here

  VkDescriptorSetLayoutBinding l_sampler_layout_binding{};
  l_sampler_layout_binding.binding = 1;
  l_sampler_layout_binding.descriptorCount = 1;
  l_sampler_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  l_sampler_layout_binding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  l_sampler_layout_binding.pImmutableSamplers = nullptr; // not relevent here

  std::array<VkDescriptorSetLayoutBinding, 2> l_bindings{ l_ubo_layout_binding, l_sampler_layout_binding };

  VkDescriptorSetLayoutCreateInfo l_layout_info{};
  l_layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  l_layout_info.pNext = nullptr;
  l_layout_info.flags = 0;
  l_layout_info.bindingCount = static_cast<uint32_t>(l_bindings.size());
  l_layout_info.pBindings = l_bindings.data();

  return make_descriptor_set_layout(a_device, l_layout_info);
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
  l_module_info.pNext = nullptr;
  l_module_info.flags = 0;
  l_module_info.codeSize = l_spv_data.size();
  l_module_info.pCode = reinterpret_cast<uint32_t const*>(l_spv_data.data());

  return make_shader_module(a_device, l_module_info);
}

sdlxvulkan::Shader_Pair sdlxvulkan::app_make_shader_pair
(
  Handle<VkDevice> const& a_device,
  VkShaderStageFlagBits a_stage,
  std::string const& a_exepath,
  std::string const& a_filename
)
{
  assert(a_device);

  Shader_Pair l_result{};
  l_result.shader_module = app_make_shader_module_from_file(a_device, a_exepath, a_filename);

  l_result.pipeline_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  l_result.pipeline_info.pNext = nullptr;
  l_result.pipeline_info.flags = 0;
  l_result.pipeline_info.stage = a_stage; // could probably pick this based on the file extension
  l_result.pipeline_info.module = l_result.shader_module;
  l_result.pipeline_info.pName = "main";
  l_result.pipeline_info.pSpecializationInfo = nullptr;

  return l_result;
}

sdlxvulkan::Shader_Group sdlxvulkan::app_make_shader_group
(
  Handle<VkDevice> const& a_device,
  std::string const& a_exepath
)
{
  assert(a_device);

  static std::string const s_fragment_shader_file{ "shader.frag.spv" };
  static std::string const s_vertex_shader_file{ "shader.vert.spv" };

  Shader_Group l_result{};
  l_result.fragment = app_make_shader_pair(a_device, VK_SHADER_STAGE_FRAGMENT_BIT, a_exepath, s_fragment_shader_file);
  l_result.vertex = app_make_shader_pair(a_device, VK_SHADER_STAGE_VERTEX_BIT, a_exepath, s_vertex_shader_file);
  l_result.pipeline_infos[0] = l_result.fragment.pipeline_info;
  l_result.pipeline_infos[1] = l_result.vertex.pipeline_info;

  return l_result;
}


sdlxvulkan::Swapchain sdlxvulkan::app_make_swapchain
(
  Window const& a_window,
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  Handle<VkSurfaceKHR> const& a_surface,
  uint32_t a_graphics_qfi,
  uint32_t a_present_qfi,
  Swapchain const& a_old_swapchain
)
{
  Swapchain l_result{};

  // Surface Capabilities
  //-------------

  l_result.surface_cababilites = get_surface_cababilites(a_physical_device, a_surface);
  l_result.surface_formats = get_surface_formats(a_physical_device, a_surface);
  l_result.present_modes = get_present_modes(a_physical_device, a_surface);

  // Select a Format
  //-------------

  // As per documentation we should get at least VK_FORMAT_UNDEFINED back
  if (l_result.surface_formats.empty())
  {
    throw std::runtime_error("Vulkan: No surface formats supplied, there should be at least one.");
  }
  // Select a Format
  // the other tutorial pays attention to more of the VkSurfaceFormatKHR struct...

  // If only an undefined one is returned then nothing is prefered and pick one
  // Otherwise select a format
  if (l_result.surface_formats.size() == 1 && l_result.surface_formats[0].format == VK_FORMAT_UNDEFINED)
  {
    l_result.format = VK_FORMAT_B8G8R8A8_UNORM;
  }
  else
  {
    // currently just pick the first.
    l_result.format = l_result.surface_formats[0].format;
  }

  // Select Present Mode
  //-------------

  // Start with this mode
  l_result.present_mode = VK_PRESENT_MODE_FIFO_KHR;

  for (auto const& l_present_mode : l_result.present_modes)
  {
    if (l_result.present_mode == VK_PRESENT_MODE_MAILBOX_KHR) // if we find this it is our prefered mode
    {
      l_result.present_mode = l_present_mode;
      break;
    }
    else if (l_present_mode == VK_PRESENT_MODE_IMMEDIATE_KHR) // if we find this set to it but keep looking
    {
      l_result.present_mode = l_present_mode;
    }
  }

  // Configure Extent
  //-------------

  // width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
  if (l_result.surface_cababilites.currentExtent.width == 0xFFFFFFFF)
  {
    // If the surface size is undefined, the size is set to the size of the images requested.
    l_result.extent.width = a_window.draw_width();
    l_result.extent.height = a_window.draw_height();

    // If the requested sizes are smaller than the device can go, we clamp to the minimum values.
    if (l_result.extent.width < l_result.surface_cababilites.minImageExtent.width)
    {
      l_result.extent.width = l_result.surface_cababilites.minImageExtent.width;
    }
    else if (l_result.extent.width > l_result.surface_cababilites.maxImageExtent.width)
    {
      l_result.extent.width = l_result.surface_cababilites.maxImageExtent.width;
    }

    if (l_result.extent.height < l_result.surface_cababilites.minImageExtent.height)
    {
      l_result.extent.height = l_result.surface_cababilites.minImageExtent.height;
    }
    else if (l_result.extent.height > l_result.surface_cababilites.maxImageExtent.height)
    {
      l_result.extent.height = l_result.surface_cababilites.maxImageExtent.height;
    }
  }
  else
  {
    // If the surface size is defined, the swap chain size must match
    l_result.extent = l_result.surface_cababilites.currentExtent;
  }

  // Determine the number of VkImage's to use in the swap chain.
  // We need to acquire only 1 presentable image at at time.
  // Asking for minImageCount images ensures that we can acquire
  // 1 presentable image as long as we present it before attempting
  // to acquire another.
  uint32_t l_requested_image_count = l_result.surface_cababilites.minImageCount + 1;
  
  VkSurfaceTransformFlagBitsKHR l_pre_transform{};
  if ((l_result.surface_cababilites.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) > 0)
  {
    l_pre_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  }
  else
  {
    l_pre_transform = l_result.surface_cababilites.currentTransform;
  }


  // Find a supported composite alpha mode - one of these is guaranteed to be set.

  /*
  // All of the flags
  VkCompositeAlphaFlagBitsKHR l_composite_alpha_flags[4] =
  {
    VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
    VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
    VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
    VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
  };

  // Start with the first one
  VkCompositeAlphaFlagBitsKHR l_composite_alpha = l_composite_alpha_flags[0];

  // Go through and see which is the right one.
  for (uint32_t i = 0; i < sizeof(l_composite_alpha_flags); i++)
  {
    if (l_result.surface_cababilites.supportedCompositeAlpha & l_composite_alpha_flags[i])
    {
      l_composite_alpha = l_composite_alpha_flags[i];
      break;
    }
  }
  */
  VkCompositeAlphaFlagBitsKHR l_composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;


  // Swapchain Creation
  VkSwapchainCreateInfoKHR l_swapchain_info{};
  l_swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  l_swapchain_info.pNext = nullptr;
  l_swapchain_info.flags = 0;
  l_swapchain_info.surface = a_surface;
  l_swapchain_info.minImageCount = l_requested_image_count;
  l_swapchain_info.imageFormat = l_result.format;
  l_swapchain_info.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
  l_swapchain_info.imageExtent = l_result.extent;
  l_swapchain_info.imageArrayLayers = 1;
  l_swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  std::array<uint32_t,2> l_queue_familiy_indicies { a_graphics_qfi, a_present_qfi };

  if (a_graphics_qfi != a_present_qfi)
  {
    // If the graphics and present queues are from different queue families,
    // we either have to explicitly transfer ownership of images between
    // the queues, or we have to create the swapchain with imageSharingMode
    // as VK_SHARING_MODE_CONCURRENT
    l_swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    l_swapchain_info.queueFamilyIndexCount = static_cast<uint32_t>(l_queue_familiy_indicies.size());
    l_swapchain_info.pQueueFamilyIndices = l_queue_familiy_indicies.data();
  }
  else
  {
    l_swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_swapchain_info.queueFamilyIndexCount = 0; // does not appliy in this mode
    l_swapchain_info.pQueueFamilyIndices = nullptr; // does not appliy in this mode
  }

  l_swapchain_info.preTransform = l_pre_transform;
  l_swapchain_info.compositeAlpha = l_composite_alpha;
  l_swapchain_info.presentMode = l_result.present_mode;
  l_swapchain_info.clipped = VK_TRUE;
  l_swapchain_info.oldSwapchain = a_old_swapchain.handle;

  // Make a new swapchain. The making references the old one that was supplied, 
  // that is the current value of m_swapchain.
  l_result.handle = make_swapchain_khr(a_device, l_swapchain_info);
  assert(l_result.handle);

  uint32_t l_actual_image_count = get_swapchain_image_count_khr(l_result.handle);

  // Do we care if it isn't what we requested?
  // probably not since we are requesting a minimum number.
  //assert(l_result.image_count == l_actual_image_count);

  l_result.image_count = l_actual_image_count;

  // Now make the images. These have no special cleanup.
  l_result.images = get_swapchain_images_khr(l_result.handle);
  assert(l_result.images.size() == l_actual_image_count);

  l_result.image_views.reserve(l_actual_image_count);
  for (auto const& l_image : l_result.images)
  {
    auto l_image_view = app_make_image_view(l_image, l_result.format, VK_IMAGE_ASPECT_COLOR_BIT);

    l_result.image_views.push_back(std::move(l_image_view));
  }
  assert(l_result.image_views.size() == l_actual_image_count);
  
  return l_result;
}

VkViewport sdlxvulkan::app_make_viewport
(
  Swapchain const& a_swapchain
)
{
  VkViewport l_result{};
  l_result.x = 0.0f;
  l_result.y = 0.0f;
  l_result.width = static_cast<float>(a_swapchain.extent.width);
  l_result.height = static_cast<float>(a_swapchain.extent.height);
  l_result.minDepth = 0.0f;
  l_result.maxDepth = 1.0f;

  // Testing viewport
  // this puts it in the top left quadrant.
  //l_result.width = static_cast<float>(a_swapchain.extent.width)/2;
  //l_result.height = static_cast<float>(a_swapchain.extent.height)/2;

  // this puts it in the top left half.
  //l_result.width = static_cast<float>(a_swapchain.extent.width) / 2;

  return l_result;
}

VkRect2D sdlxvulkan::app_make_scissor
(
  Swapchain const& a_swapchain
)
{
  VkRect2D l_result{};
  l_result.extent = a_swapchain.extent;
  l_result.offset = { 0,0 };

  // Testing scissoring
  // This draws in the top left quadrant.
  //l_result.extent.width = a_swapchain.extent.width / 2;
  //l_result.extent.height = a_swapchain.extent.height / 2;

  return l_result;
}

// use the swapchain format
sdlxvulkan::Handle<VkRenderPass> sdlxvulkan::app_make_render_pass
(
  Handle<VkDevice> const& a_device,
  VkFormat a_format,
  VkFormat a_depth_format
)
{
  VkAttachmentDescription l_colour_attachment{};
  l_colour_attachment.flags = 0;
  l_colour_attachment.format = a_format;
  l_colour_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  l_colour_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  l_colour_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  l_colour_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  l_colour_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  l_colour_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  l_colour_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  VkAttachmentReference l_colour_attachment_ref{};
  l_colour_attachment_ref.attachment = 0;
  l_colour_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


  VkAttachmentDescription l_depth_attachment{};
  l_depth_attachment.flags = 0;
  l_depth_attachment.format = a_depth_format;
  l_depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  l_depth_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  l_depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  l_depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  l_depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  l_depth_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  l_depth_attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference l_depth_attachment_ref{};
  l_depth_attachment_ref.attachment = 1;
  l_depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


  VkSubpassDescription  l_subpass_desc{};
  l_subpass_desc.flags = 0;
  l_subpass_desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  l_subpass_desc.inputAttachmentCount = 0;
  l_subpass_desc.pInputAttachments = nullptr;
  l_subpass_desc.colorAttachmentCount = 1;
  l_subpass_desc.pColorAttachments = &l_colour_attachment_ref;
  l_subpass_desc.pResolveAttachments = nullptr;
  l_subpass_desc.pDepthStencilAttachment = &l_depth_attachment_ref;
  l_subpass_desc.preserveAttachmentCount = 0;
  l_subpass_desc.pPreserveAttachments = nullptr;

  VkSubpassDependency l_dependency{};
  l_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  l_dependency.dstSubpass = 0;
  l_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  l_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  l_dependency.srcAccessMask = 0;
  l_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  l_dependency.dependencyFlags = 0;

  std::array<VkAttachmentDescription, 2> l_attachments { l_colour_attachment, l_depth_attachment };

  VkRenderPassCreateInfo l_render_pass_info = {};
  l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  l_render_pass_info.pNext = nullptr;
  l_render_pass_info.flags = 0;
  l_render_pass_info.attachmentCount = static_cast<uint32_t>(l_attachments.size());
  l_render_pass_info.pAttachments = l_attachments.data();
  l_render_pass_info.subpassCount = 1;
  l_render_pass_info.pSubpasses = &l_subpass_desc;
  l_render_pass_info.dependencyCount = 1;
  l_render_pass_info.pDependencies = &l_dependency;

  return make_render_pass(a_device, l_render_pass_info);
}

sdlxvulkan::Handle<VkPipelineLayout> sdlxvulkan::app_make_pipeline_layout
(
  Handle<VkDevice> const& a_device,
  Handle<VkDescriptorSetLayout> const& a_descriptor_set_layout
)
{
  std::array<VkDescriptorSetLayout, 1> l_layouts{ a_descriptor_set_layout };

  VkPipelineLayoutCreateInfo l_pipeline_layout_info{};
  l_pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  l_pipeline_layout_info.pNext = nullptr;
  l_pipeline_layout_info.flags = 0;
  l_pipeline_layout_info.setLayoutCount = static_cast<uint32_t>(l_layouts.size());
  l_pipeline_layout_info.pSetLayouts = l_layouts.data();
  l_pipeline_layout_info.pushConstantRangeCount = 0;
  l_pipeline_layout_info.pPushConstantRanges = nullptr;

  return make_pipeline_layout(a_device, l_pipeline_layout_info);
}


sdlxvulkan::Handle<VkPipeline> sdlxvulkan::app_make_pipeline
(
  Handle<VkDevice> const& a_device,
  Handle<VkPipelineCache> const& a_pipeline_cache,
  Handle<VkPipelineLayout> const& a_pipeline_layout,
  Handle<VkRenderPass> const& a_render_pass,
  Shader_Group const& a_shader_group,
  std::vector<VkVertexInputBindingDescription> const& a_vertex_binding_descs,
  std::vector<VkVertexInputAttributeDescription> const& a_vertex_attribute_descs,
  std::vector<VkViewport> const& a_viewports,
  std::vector<VkRect2D> const& a_scissors
)
{
  // Describe the vertex data
  VkPipelineVertexInputStateCreateInfo l_vertex_input_state{};
  l_vertex_input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  l_vertex_input_state.pNext = nullptr;
  l_vertex_input_state.flags = 0;
  l_vertex_input_state.vertexBindingDescriptionCount = static_cast<uint32_t>(a_vertex_binding_descs.size());
  l_vertex_input_state.pVertexBindingDescriptions = a_vertex_binding_descs.data();
  l_vertex_input_state.vertexAttributeDescriptionCount = static_cast<uint32_t>(a_vertex_attribute_descs.size());
  l_vertex_input_state.pVertexAttributeDescriptions = a_vertex_attribute_descs.data();

  //Input Assembly
  VkPipelineInputAssemblyStateCreateInfo l_input_assembly_state{};
  l_input_assembly_state.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  l_input_assembly_state.pNext = nullptr;
  l_input_assembly_state.flags = 0;
  l_input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  l_input_assembly_state.primitiveRestartEnable = VK_FALSE;

  // Viewport state
  VkPipelineViewportStateCreateInfo l_viewport_state{};
  l_viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  l_viewport_state.pNext = nullptr;
  l_viewport_state.flags = 0;
  l_viewport_state.viewportCount = static_cast<uint32_t>(a_viewports.size());
  l_viewport_state.pViewports = a_viewports.data();
  l_viewport_state.scissorCount = static_cast<uint32_t>(a_scissors.size());
  l_viewport_state.pScissors = a_scissors.data();

  // Rasterizer
  VkPipelineRasterizationStateCreateInfo l_rasterization_state{};
  l_rasterization_state.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  l_rasterization_state.pNext = nullptr;
  l_rasterization_state.flags = 0;
  l_rasterization_state.depthClampEnable = VK_FALSE;
  l_rasterization_state.rasterizerDiscardEnable = VK_FALSE;
  l_rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
  l_rasterization_state.cullMode = VK_CULL_MODE_BACK_BIT;
  //l_rasterization_state.frontFace = VK_FRONT_FACE_CLOCKWISE;
  l_rasterization_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  l_rasterization_state.depthBiasEnable = VK_FALSE; // optional
  l_rasterization_state.depthBiasConstantFactor = 0.0f; // optional
  l_rasterization_state.depthBiasClamp = 0.0f; // optional
  l_rasterization_state.depthBiasSlopeFactor = 0.0f; // optional
  l_rasterization_state.lineWidth = 1.0f;
  
  // Multisampling
  VkPipelineMultisampleStateCreateInfo l_multisample_state{};
  l_multisample_state.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  l_multisample_state.pNext = nullptr;
  l_multisample_state.flags = 0;
  l_multisample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  l_multisample_state.sampleShadingEnable = VK_FALSE;
  l_multisample_state.minSampleShading = 1.0f; // optional
  l_multisample_state.pSampleMask = nullptr; // optional
  l_multisample_state.alphaToCoverageEnable = VK_FALSE; // optional
  l_multisample_state.alphaToOneEnable = VK_FALSE; // optional

  // Depth and Stencil
  /*
  VkPipelineDepthStencilStateCreateInfo l_depth_stencil_state;
  l_depth_stencil_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  l_depth_stencil_state.pNext = NULL;
  l_depth_stencil_state.flags = 0;
  l_depth_stencil_state.depthTestEnable = VK_TRUE;
  l_depth_stencil_state.depthWriteEnable = VK_TRUE;
  l_depth_stencil_state.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
  l_depth_stencil_state.depthBoundsTestEnable = VK_FALSE;
  l_depth_stencil_state.minDepthBounds = 0;
  l_depth_stencil_state.maxDepthBounds = 0;
  l_depth_stencil_state.stencilTestEnable = VK_FALSE;
  l_depth_stencil_state.back.failOp = VK_STENCIL_OP_KEEP;
  l_depth_stencil_state.back.passOp = VK_STENCIL_OP_KEEP;
  l_depth_stencil_state.back.compareOp = VK_COMPARE_OP_ALWAYS;
  l_depth_stencil_state.back.compareMask = 0;
  l_depth_stencil_state.back.reference = 0;
  l_depth_stencil_state.back.depthFailOp = VK_STENCIL_OP_KEEP;
  l_depth_stencil_state.back.writeMask = 0;
  l_depth_stencil_state.front = l_depth_stencil_state.back;
  */

  // Colour Blending
  VkPipelineColorBlendAttachmentState l_colour_blend_attachment_state{};
  l_colour_blend_attachment_state.blendEnable = VK_FALSE;
  l_colour_blend_attachment_state.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
  l_colour_blend_attachment_state.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  l_colour_blend_attachment_state.colorBlendOp = VK_BLEND_OP_ADD;
  l_colour_blend_attachment_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  l_colour_blend_attachment_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  l_colour_blend_attachment_state.alphaBlendOp = VK_BLEND_OP_ADD;
  l_colour_blend_attachment_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;


  VkPipelineColorBlendStateCreateInfo l_colour_blend_state{};
  l_colour_blend_state.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  l_colour_blend_state.pNext = nullptr;
  l_colour_blend_state.flags = 0;
  l_colour_blend_state.logicOpEnable = VK_FALSE;
  l_colour_blend_state.logicOp = VK_LOGIC_OP_COPY; // optional
  l_colour_blend_state.attachmentCount = 1;
  l_colour_blend_state.pAttachments = &l_colour_blend_attachment_state;
  l_colour_blend_state.blendConstants[0] = 0.0f; // optional
  l_colour_blend_state.blendConstants[1] = 0.0f; // optional
  l_colour_blend_state.blendConstants[2] = 0.0f; // optional
  l_colour_blend_state.blendConstants[3] = 0.0f; // optional

  // Pipeline  
  VkGraphicsPipelineCreateInfo l_pipeline_info{};
  l_pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  l_pipeline_info.pNext = nullptr;
  l_pipeline_info.flags = 0;
  l_pipeline_info.stageCount = static_cast<uint32_t>(a_shader_group.pipeline_infos.size());
  l_pipeline_info.pStages = a_shader_group.pipeline_infos.data();
  l_pipeline_info.pVertexInputState = &l_vertex_input_state;
  l_pipeline_info.pInputAssemblyState = &l_input_assembly_state;
  l_pipeline_info.pTessellationState = nullptr;
  l_pipeline_info.pViewportState = &l_viewport_state;
  l_pipeline_info.pRasterizationState = &l_rasterization_state;
  l_pipeline_info.pMultisampleState = &l_multisample_state;
  l_pipeline_info.pDepthStencilState = nullptr;//&l_depth_stencil_state;
  l_pipeline_info.pColorBlendState = &l_colour_blend_state;
  l_pipeline_info.pDynamicState = nullptr;
  l_pipeline_info.layout = a_pipeline_layout;
  l_pipeline_info.renderPass = a_render_pass;
  l_pipeline_info.subpass = 0;
  l_pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // optional
  l_pipeline_info.basePipelineIndex = -1; // optional

  return make_graphics_pipeline(a_device, a_pipeline_cache, l_pipeline_info);
}


// Dynamic pipeline that needs to be supplied with a viewport and a scissor 
sdlxvulkan::Handle<VkPipeline> sdlxvulkan::app_make_dynamic_pipeline
(
  Handle<VkDevice> const& a_device,
  Handle<VkPipelineCache> const& a_pipeline_cache,
  Handle<VkPipelineLayout> const& a_pipeline_layout,
  Handle<VkRenderPass> const& a_render_pass,
  Shader_Group const& a_shader_group,
  std::vector<VkVertexInputBindingDescription> const& a_vertex_binding_descs,
  std::vector<VkVertexInputAttributeDescription> const& a_vertex_attribute_descs
)
{
  // Describe the vertex data
  VkPipelineVertexInputStateCreateInfo l_vertex_input_state{};
  l_vertex_input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  l_vertex_input_state.pNext = nullptr;
  l_vertex_input_state.flags = 0;
  l_vertex_input_state.vertexBindingDescriptionCount = static_cast<uint32_t>(a_vertex_binding_descs.size());
  l_vertex_input_state.pVertexBindingDescriptions = a_vertex_binding_descs.data();
  l_vertex_input_state.vertexAttributeDescriptionCount = static_cast<uint32_t>(a_vertex_attribute_descs.size());
  l_vertex_input_state.pVertexAttributeDescriptions = a_vertex_attribute_descs.data();

  //Input Assembly
  VkPipelineInputAssemblyStateCreateInfo l_input_assembly_state{};
  l_input_assembly_state.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  l_input_assembly_state.pNext = nullptr;
  l_input_assembly_state.flags = 0;
  l_input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  l_input_assembly_state.primitiveRestartEnable = VK_FALSE;

  // Viewport state
  VkPipelineViewportStateCreateInfo l_viewport_state{};
  l_viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  l_viewport_state.pNext = nullptr;
  l_viewport_state.flags = 0;
  l_viewport_state.viewportCount = 1;
  l_viewport_state.pViewports = nullptr; // not supplied if dynamic
  l_viewport_state.scissorCount = 1;
  l_viewport_state.pScissors = nullptr; // not supplied if dynamic

  // Rasterizer
  VkPipelineRasterizationStateCreateInfo l_rasterization_state{};
  l_rasterization_state.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  l_rasterization_state.pNext = nullptr;
  l_rasterization_state.flags = 0;
  l_rasterization_state.depthClampEnable = VK_FALSE;
  l_rasterization_state.rasterizerDiscardEnable = VK_FALSE;
  l_rasterization_state.polygonMode = VK_POLYGON_MODE_FILL;
  l_rasterization_state.cullMode = VK_CULL_MODE_BACK_BIT;
  //l_rasterization_state.frontFace = VK_FRONT_FACE_CLOCKWISE;
  l_rasterization_state.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  l_rasterization_state.depthBiasEnable = VK_FALSE; // optional
  l_rasterization_state.depthBiasConstantFactor = 0.0f; // optional
  l_rasterization_state.depthBiasClamp = 0.0f; // optional
  l_rasterization_state.depthBiasSlopeFactor = 0.0f; // optional
  l_rasterization_state.lineWidth = 1.0f;

  // Multisampling
  VkPipelineMultisampleStateCreateInfo l_multisample_state{};
  l_multisample_state.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  l_multisample_state.pNext = nullptr;
  l_multisample_state.flags = 0;
  l_multisample_state.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  l_multisample_state.sampleShadingEnable = VK_FALSE;
  l_multisample_state.minSampleShading = 1.0f; // optional
  l_multisample_state.pSampleMask = nullptr; // optional
  l_multisample_state.alphaToCoverageEnable = VK_FALSE; // optional
  l_multisample_state.alphaToOneEnable = VK_FALSE; // optional

  // Depth and Stencil  
  VkPipelineDepthStencilStateCreateInfo l_depth_stencil_state;
  l_depth_stencil_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  l_depth_stencil_state.pNext = nullptr;
  l_depth_stencil_state.flags = 0;
  l_depth_stencil_state.depthTestEnable = VK_TRUE;
  l_depth_stencil_state.depthWriteEnable = VK_TRUE;
  l_depth_stencil_state.depthCompareOp = VK_COMPARE_OP_LESS;
  l_depth_stencil_state.depthBoundsTestEnable = VK_FALSE;
  l_depth_stencil_state.stencilTestEnable = VK_FALSE;
  l_depth_stencil_state.front = {};// l_depth_stencil_state.back;
  l_depth_stencil_state.back = {};
  //l_depth_stencil_state.back.failOp = VK_STENCIL_OP_KEEP;
  //l_depth_stencil_state.back.passOp = VK_STENCIL_OP_KEEP;
  //l_depth_stencil_state.back.compareOp = VK_COMPARE_OP_ALWAYS;
  //l_depth_stencil_state.back.compareMask = 0;
  //l_depth_stencil_state.back.reference = 0;
  //l_depth_stencil_state.back.depthFailOp = VK_STENCIL_OP_KEEP;
  //l_depth_stencil_state.back.writeMask = 0;
  l_depth_stencil_state.minDepthBounds = 0.0f; // optional
  l_depth_stencil_state.maxDepthBounds = 1.0f; // optional
  
                                                   // Colour Blending
  VkPipelineColorBlendAttachmentState l_colour_blend_attachment_state{};
  l_colour_blend_attachment_state.blendEnable = VK_FALSE;
  l_colour_blend_attachment_state.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
  l_colour_blend_attachment_state.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
  l_colour_blend_attachment_state.colorBlendOp = VK_BLEND_OP_ADD;
  l_colour_blend_attachment_state.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
  l_colour_blend_attachment_state.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
  l_colour_blend_attachment_state.alphaBlendOp = VK_BLEND_OP_ADD;
  l_colour_blend_attachment_state.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;


  VkPipelineColorBlendStateCreateInfo l_colour_blend_state{};
  l_colour_blend_state.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  l_colour_blend_state.pNext = nullptr;
  l_colour_blend_state.flags = 0;
  l_colour_blend_state.logicOpEnable = VK_FALSE;
  l_colour_blend_state.logicOp = VK_LOGIC_OP_COPY; // optional
  l_colour_blend_state.attachmentCount = 1;
  l_colour_blend_state.pAttachments = &l_colour_blend_attachment_state;
  l_colour_blend_state.blendConstants[0] = 0.0f; // optional
  l_colour_blend_state.blendConstants[1] = 0.0f; // optional
  l_colour_blend_state.blendConstants[2] = 0.0f; // optional
  l_colour_blend_state.blendConstants[3] = 0.0f; // optional


  // Dynamic State

  // Need to set these if we want to change the few things that can be changed, like
  // the viewport size, without having to remake the entire pipeline

  VkDynamicState l_dynamic_states[]
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };

  VkPipelineDynamicStateCreateInfo l_dynamic_state{};
  l_dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  l_dynamic_state.pNext = nullptr;
  l_dynamic_state.flags = 0;
  l_dynamic_state.dynamicStateCount = 2;
  l_dynamic_state.pDynamicStates = l_dynamic_states;

  // Pipeline  
  VkGraphicsPipelineCreateInfo l_pipeline_info{};
  l_pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  l_pipeline_info.pNext = nullptr;
  l_pipeline_info.flags = 0;
  l_pipeline_info.stageCount = static_cast<uint32_t>(a_shader_group.pipeline_infos.size());
  l_pipeline_info.pStages = a_shader_group.pipeline_infos.data();
  l_pipeline_info.pVertexInputState = &l_vertex_input_state;
  l_pipeline_info.pInputAssemblyState = &l_input_assembly_state;
  l_pipeline_info.pTessellationState = nullptr;
  l_pipeline_info.pViewportState = &l_viewport_state;
  l_pipeline_info.pRasterizationState = &l_rasterization_state;
  l_pipeline_info.pMultisampleState = &l_multisample_state;
  l_pipeline_info.pDepthStencilState = &l_depth_stencil_state;
  l_pipeline_info.pColorBlendState = &l_colour_blend_state;
  l_pipeline_info.pDynamicState = &l_dynamic_state; // so we can change the viewport on the fly, but have to supply them...
  l_pipeline_info.layout = a_pipeline_layout;
  l_pipeline_info.renderPass = a_render_pass;
  l_pipeline_info.subpass = 0;
  l_pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // optional
  l_pipeline_info.basePipelineIndex = -1; // optional

  return make_graphics_pipeline(a_device, a_pipeline_cache, l_pipeline_info);
}

std::vector<sdlxvulkan::Handle<VkFramebuffer>> sdlxvulkan::app_make_swapchain_framebuffers
(
  Handle<VkDevice> const& a_device,
  Swapchain const& a_swapchain,
  Handle<VkRenderPass> const& a_render_pass,
  Image_Trio const& a_depth_trio
)
{
  std::vector<Handle<VkFramebuffer>> l_result{};
  l_result.reserve(a_swapchain.image_count);

  for (auto const& l_swapchain_image_view : a_swapchain.image_views)
    //for (size_t i = 0; i != m_swapchain_image_views.size(); i++) 
  {
    std::array<VkImageView, 2> l_attachments{ l_swapchain_image_view, a_depth_trio.view };

    VkFramebufferCreateInfo l_framebuffer_info{};
    l_framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    l_framebuffer_info.renderPass = a_render_pass;
    l_framebuffer_info.attachmentCount = static_cast<uint32_t>(l_attachments.size());
    l_framebuffer_info.pAttachments = l_attachments.data();
    l_framebuffer_info.width = a_swapchain.extent.width;
    l_framebuffer_info.height = a_swapchain.extent.height;
    l_framebuffer_info.layers = 1;

    l_result.push_back(make_framebuffer(a_device, l_framebuffer_info));
  }

  return l_result;
}

std::vector<sdlxvulkan::Buffer_Pair> sdlxvulkan::app_make_uniforms
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  uint32_t a_count,
  VkDeviceSize a_size
)
{
  assert(a_physical_device);
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);
  assert(a_size != 0);

  std::vector<Buffer_Pair> l_uniforms{};
  l_uniforms.reserve(a_count);

  VkBufferUsageFlags l_uniform_usage_flags = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  VkMemoryPropertyFlags l_uniform_property_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  for (uint32_t l_index = 0; l_index != a_count; ++l_index)
  {
    l_uniforms.push_back(app_make_buffer_memory_exclusive_pair(a_physical_device, a_device, a_size, l_uniform_usage_flags, l_uniform_property_flags));
  }
  return l_uniforms;
}

sdlxvulkan::Handle<VkDescriptorPool> sdlxvulkan::app_make_descriptor_pool
(
  Handle<VkDevice> const& a_device,
  uint32_t a_count
)
{
  std::array<VkDescriptorPoolSize, 2> l_pool_sizes{};

  // ubo
  l_pool_sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  l_pool_sizes[0].descriptorCount = a_count;

  // sampler
  l_pool_sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  l_pool_sizes[1].descriptorCount = a_count;

  VkDescriptorPoolCreateInfo l_pool_info{};
  l_pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  l_pool_info.pNext = nullptr;
  l_pool_info.flags = 0;
  l_pool_info.maxSets = a_count;
  l_pool_info.poolSizeCount = static_cast<uint32_t>(l_pool_sizes.size());
  l_pool_info.pPoolSizes = l_pool_sizes.data();

  return make_descriptor_pool(a_device, l_pool_info);
}

std::vector<sdlxvulkan::Handle<VkDescriptorSet>> sdlxvulkan::app_make_descriptor_sets
(
  Handle<VkDevice> const& a_device,
  Handle<VkDescriptorSetLayout> const& a_descriptor_set_layout,
  Handle<VkDescriptorPool> const& a_descriptor_pool,
  Swapchain const& a_swapchain,
  Image_Trio const& a_texture,
  Handle<VkSampler> const& a_sampler,
  std::vector<Buffer_Pair> const& a_uniforms,
  VkDeviceSize a_uniform_size
)
{
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  // for use in alloc, same layout for each
  std::vector<VkDescriptorSetLayout> l_layouts{ a_swapchain.image_count, a_descriptor_set_layout };
  VkDescriptorSetAllocateInfo l_alloc_info = {};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.descriptorPool = a_descriptor_pool;
  l_alloc_info.descriptorSetCount = a_swapchain.image_count;
  l_alloc_info.pSetLayouts = l_layouts.data();

  auto l_descriptor_sets = make_descriptor_sets(a_descriptor_pool, l_alloc_info);

  assert(!a_uniforms.empty());

  for (uint32_t l_index = 0; l_index != a_swapchain.image_count; ++l_index)
  {
    VkDescriptorBufferInfo l_buffer_info{};
    l_buffer_info.buffer = a_uniforms[l_index].buffer;
    l_buffer_info.offset = 0;
    l_buffer_info.range = a_uniform_size;

    VkDescriptorImageInfo l_image_info = {};
    l_image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    l_image_info.imageView = a_texture.view;
    l_image_info.sampler = a_sampler;

    std::array<VkWriteDescriptorSet, 2> l_descriptor_writes{};

    // for the ubo
    l_descriptor_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    l_descriptor_writes[0].pNext = nullptr;
    l_descriptor_writes[0].dstSet = l_descriptor_sets[l_index];
    l_descriptor_writes[0].dstBinding = 0;
    l_descriptor_writes[0].dstArrayElement = 0;
    l_descriptor_writes[0].descriptorCount = 1;
    l_descriptor_writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_descriptor_writes[0].pImageInfo = nullptr; // optional
    l_descriptor_writes[0].pBufferInfo = &l_buffer_info;
    l_descriptor_writes[0].pTexelBufferView = nullptr; // optional

                                                       // for the sampler
    l_descriptor_writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    l_descriptor_writes[1].pNext = nullptr;
    l_descriptor_writes[1].dstSet = l_descriptor_sets[l_index];
    l_descriptor_writes[1].dstBinding = 1;
    l_descriptor_writes[1].dstArrayElement = 0;
    l_descriptor_writes[1].descriptorCount = 1;
    l_descriptor_writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    l_descriptor_writes[1].pImageInfo = &l_image_info; // optional
    l_descriptor_writes[1].pBufferInfo = nullptr;
    l_descriptor_writes[1].pTexelBufferView = nullptr; // optional

    l_functions->vkUpdateDescriptorSets(a_device, static_cast<uint32_t>(l_descriptor_writes.size()), l_descriptor_writes.data(), 0, nullptr);
  }
  return l_descriptor_sets;
}


std::vector<sdlxvulkan::Handle<VkSemaphore>> sdlxvulkan::app_make_semaphores
(
  Handle<VkDevice> const& a_device,
  uint32_t a_count
)
{
  VkSemaphoreCreateInfo l_semaphore_info{};
  l_semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  l_semaphore_info.pNext = nullptr;
  l_semaphore_info.flags = 0;

  std::vector<Handle<VkSemaphore>> l_result{};
  l_result.resize(a_count);
  for (auto& l_semaphore : l_result)
  {
    l_semaphore = make_semaphore(a_device, l_semaphore_info);
  }
  return l_result;
}

std::vector<sdlxvulkan::Handle<VkFence>> sdlxvulkan::app_make_fences
(
  Handle<VkDevice> const& a_device,
  uint32_t a_count,
  VkFenceCreateFlags a_flags
)
{
  VkFenceCreateInfo l_fence_info{};
  l_fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  l_fence_info.pNext = nullptr;
  l_fence_info.flags = a_flags;

  std::vector<Handle<VkFence>> l_result{};
  l_result.resize(a_count);
  for (auto& l_fence : l_result)
  {
    l_fence = make_fence(a_device, l_fence_info);
  }
  return l_result;
}



sdlxvulkan::Buffer_Pair sdlxvulkan::app_make_load_staging_buffer_pair
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  VkDeviceSize a_size,
  void const* a_data
)
{
  assert(a_physical_device);
  assert(a_device);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  VkBufferUsageFlags l_usage_flags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags l_property_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  auto l_staging_pair = app_make_buffer_memory_exclusive_pair(a_physical_device, a_device, a_size, l_usage_flags, l_property_flags);

  // Map data to it
  void *l_staging_data{ nullptr };
  if (l_functions->vkMapMemory(a_device, l_staging_pair.memory, 0, a_size, 0, &l_staging_data) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to map a staging buffer." };
  }

  // copy the data
  memcpy(l_staging_data, a_data, static_cast<size_t>(a_size));

  // unmap the memory after we have used it.
  l_functions->vkUnmapMemory(a_device, l_staging_pair.memory);
  
  return l_staging_pair;
}


sdlxvulkan::Buffer_Pair sdlxvulkan::app_make_vertex_buffer_pair
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  VkDeviceSize a_size,
  void const* a_data
)
{
  assert(a_physical_device);
  assert(a_device);
  assert(a_command_pool);
  assert(a_queue);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  auto l_staging_pair = app_make_load_staging_buffer_pair(a_physical_device, a_device, a_size, a_data);
  
  // Vertex buffer
  VkBufferUsageFlags l_vertex_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  VkMemoryPropertyFlags l_vertex_property_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  auto l_vertex_pair = app_make_buffer_memory_exclusive_pair(a_physical_device, a_device, a_size, l_vertex_usage_flags, l_vertex_property_flags);

  app_copy_buffer(a_device, a_command_pool, a_queue, l_staging_pair.buffer, l_vertex_pair.buffer, a_size);

  return l_vertex_pair;
}

sdlxvulkan::Buffer_Pair sdlxvulkan::app_make_index_buffer_pair
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  Handle<VkDevice> const& a_device,
  Handle<VkCommandPool> const& a_command_pool,
  Handle<VkQueue> const& a_queue,
  VkDeviceSize a_size,
  void const* a_data
)
{
  assert(a_physical_device);
  assert(a_device);
  assert(a_command_pool);
  assert(a_queue);
  auto l_functions = get_device_functions(a_device);
  assert(l_functions);

  auto l_staging_pair = app_make_load_staging_buffer_pair(a_physical_device, a_device, a_size, a_data);

  VkBufferUsageFlags l_index_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  VkMemoryPropertyFlags l_index_property_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  auto l_index_pair = app_make_buffer_memory_exclusive_pair(a_physical_device, a_device, a_size, l_index_usage_flags, l_index_property_flags);
  
  app_copy_buffer(a_device, a_command_pool, a_queue, l_staging_pair.buffer, l_index_pair.buffer, a_size);

  return l_index_pair;
}