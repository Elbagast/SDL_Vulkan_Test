#include "app_make.hpp"

#include "system.hpp"
#include "window.hpp"
#include "device_functions.hpp"
#include <iostream>
#include <array>
#include <filesystem>
#include <fstream>


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


sdlxvulkan::Handle<VkDevice> sdlxvulkan::app_make_device
(
  Handle<VkPhysicalDevice> const& a_physical_device,
  uint32_t a_graphics_qfi,
  uint32_t a_present_qfi,
  std::vector<std::string> const& a_extensions,
  VkAllocationCallbacks const* a_allocation_callbacks
)
{
  float l_queue_priorities[1] = { 0.0 };

  VkDeviceQueueCreateInfo l_queue_infos[2]{};

  // first is graphics
  l_queue_infos[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_infos[0].pNext = nullptr;
  l_queue_infos[0].flags = 0;
  l_queue_infos[0].queueFamilyIndex = a_graphics_qfi;
  l_queue_infos[0].queueCount = 1;
  l_queue_infos[0].pQueuePriorities = l_queue_priorities;

  // second is presenting
  l_queue_infos[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_infos[1].pNext = nullptr;
  l_queue_infos[1].flags = 0;
  l_queue_infos[1].queueFamilyIndex = a_present_qfi;
  l_queue_infos[1].queueCount = 1;
  l_queue_infos[1].pQueuePriorities = l_queue_priorities;

  // Logical Device
  //-------------

  // Configure our queue info
  VkDeviceQueueCreateInfo l_queue_info{};
  l_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_info.pNext = nullptr;
  l_queue_info.flags = 0;
  l_queue_info.queueFamilyIndex = a_graphics_qfi;
  l_queue_info.queueCount = 1;
  l_queue_info.pQueuePriorities = l_queue_priorities;


  std::vector<char const*> l_device_extensions{};
  uint32_t l_device_extension_count = static_cast<uint32_t>(a_extensions.size());
  std::vector<char const*> l_extensions{};
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
  l_device_info.pQueueCreateInfos = l_queue_infos;
  l_device_info.enabledLayerCount = 0;          // Deprecated, IGNORE
  l_device_info.ppEnabledLayerNames = nullptr;  // Deprecated, IGNORE
  l_device_info.enabledExtensionCount = l_device_extension_count;
  l_device_info.ppEnabledExtensionNames = l_device_extensions.data();
  l_device_info.pEnabledFeatures = nullptr;

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
  std::vector<uint32_t> a_queue_family_indicies,
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



namespace
{
  std::string get_shader_filepath(std::string const& a_arg0, std::string const& a_filename)
  {
    using namespace std::experimental::filesystem;
    path const l_directory{ u8path(a_arg0).remove_filename() };
    path l_filepath{ l_directory / u8path(a_filename) };

    std::string l_result{ l_filepath.u8string() };

    if (!exists(l_filepath))
    {
      throw std::runtime_error{ std::string{ "Filesystem: Shader file does not exist: " } +l_result };
    }
    // Open the file and get the data...
    //std::cout << "Getting shader file: " << l_result << std::endl;

    return l_result;
  };

  std::vector<char> get_file_bytes(std::string const& a_filepath)
  {
    // Open the file and seek to the end
    std::ifstream l_filestream{ a_filepath, std::ios::ate | std::ios::binary };
    if (!l_filestream.is_open())
    {
      throw std::runtime_error{ std::string{ "Filesystem: Could not open file " } +a_filepath };
    }

    // Get the file size in bytes
    std::size_t l_file_size = l_filestream.tellg();
    std::vector<char> l_file_buffer{};
    l_file_buffer.resize(l_file_size);

    // Go to the start
    l_filestream.seekg(0);

    // get all the file at once
    l_filestream.read(l_file_buffer.data(), l_file_size);

    l_filestream.close();

    return l_file_buffer;
  }
}

sdlxvulkan::Handle<VkShaderModule> sdlxvulkan::app_make_shader_module_from_file
(
  Handle<VkDevice> const& a_device,
  std::string const& a_exepath,
  std::string const& a_filepath
)
{
  auto l_path = get_shader_filepath(a_exepath, a_filepath);
  auto l_spv_data = get_file_bytes(l_path);

  VkShaderModuleCreateInfo l_module_info;
  l_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  l_module_info.pNext = NULL;
  l_module_info.flags = 0;
  l_module_info.codeSize = l_spv_data.size();
  l_module_info.pCode = reinterpret_cast<uint32_t const*>(l_spv_data.data());

  return make_shader_module(a_device, l_module_info);
}