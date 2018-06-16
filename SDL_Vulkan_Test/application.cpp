#include "application.hpp"

#include <cassert>
#include <cstdlib>
#include <array>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
  
  struct Vertex
  {
    glm::vec2 pos;
    glm::vec3 color;

    static auto get_binding_description()
    {
      VkVertexInputBindingDescription l_binding_description {};
      l_binding_description.binding = 0;
      l_binding_description.stride = sizeof(Vertex);
      l_binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

      return l_binding_description;
    }

    static auto get_attribute_descriptions() 
    {
      std::array<VkVertexInputAttributeDescription, 2> l_attribute_descriptions = {};
      l_attribute_descriptions[0].binding = 0;
      l_attribute_descriptions[0].location = 0;
      l_attribute_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
      l_attribute_descriptions[0].offset = offsetof(Vertex, pos);

      l_attribute_descriptions[1].binding = 0;
      l_attribute_descriptions[1].location = 1;
      l_attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
      l_attribute_descriptions[1].offset = offsetof(Vertex, color);

      return l_attribute_descriptions;
    }
  };
  /*
  static std::vector<Vertex> const c_vertices =
  {
    { { 0.0f, -0.5f },{ 1.0f, 0.0f, 1.0f } },
    { { 0.5f, 0.5f },{ 0.0f, 1.0f, 0.0f } },
    { { -0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f } }
  };
  */
  static std::vector<Vertex> const c_vertices = 
  {
    { { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f } },
    { { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f } },
    { { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f } },
    { { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f } }
  };
  static std::vector<uint16_t> const c_indices = 
  {
    0, 1, 2, 2, 3, 0
  };

  struct Uniform_Buffer_Object 
  {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
  };



  // Make sure environment variable VK_LAYER_PATH is set to the Vulkan binary path
  // e.g. 

  std::vector<const char*> const c_validation_layers = {"VK_LAYER_LUNARG_standard_validation"};

#ifdef NDEBUG
  constexpr bool c_enable_validation_layers = false;
#else
  constexpr bool c_enable_validation_layers = true;
#endif

  constexpr size_t c_frames_in_flight{ 2 };
  constexpr uint32_t c_start_width{ 800 };
  constexpr uint32_t c_start_height{ 600 };
  
  static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg, void* a_user_data)
  {
    std::cerr << "[validation layer] " << a_msg << std::endl << std::endl;

    return VK_FALSE;
  }
}

namespace
{
#define CASE_ENUM_STRING(a_arg) case a_arg: return u8###a_arg;

  char const* sdl_event_c_string(SDL_EventType a_event_type)
  {
    switch (a_event_type)
    {
      CASE_ENUM_STRING(SDL_QUIT)
        CASE_ENUM_STRING(SDL_APP_TERMINATING)
        CASE_ENUM_STRING(SDL_APP_LOWMEMORY)
        CASE_ENUM_STRING(SDL_APP_WILLENTERBACKGROUND)
        CASE_ENUM_STRING(SDL_APP_DIDENTERBACKGROUND)
        CASE_ENUM_STRING(SDL_APP_WILLENTERFOREGROUND)
        CASE_ENUM_STRING(SDL_APP_DIDENTERFOREGROUND)
        CASE_ENUM_STRING(SDL_WINDOWEVENT)
        CASE_ENUM_STRING(SDL_SYSWMEVENT)

    default: return u8"Bad SDL_EventType";
    }
  }
  std::string sdl_event_string(SDL_EventType a_event_type)
  {
    return std::string{ sdl_event_c_string(a_event_type) };
  }

  char const* sdl_window_event_c_string(SDL_WindowEventID a_event_id)
  {
    switch (a_event_id)
    {
      CASE_ENUM_STRING(SDL_WINDOWEVENT_NONE)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_SHOWN)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_HIDDEN)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_EXPOSED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_MOVED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_RESIZED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_SIZE_CHANGED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_MINIMIZED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_MAXIMIZED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_RESTORED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_ENTER)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_LEAVE)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_FOCUS_GAINED)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_FOCUS_LOST)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_CLOSE)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_TAKE_FOCUS)
        CASE_ENUM_STRING(SDL_WINDOWEVENT_HIT_TEST)

    default: return u8"Bad SDL_WindowEventID";
    }
  }
  std::string sdl_window_event_string(SDL_WindowEventID a_event_id)
  {
    return std::string{ sdl_window_event_c_string(a_event_id) };
  }
}

#define LOCAL_VULKAN_INTANCE_FUNC(_name) PFN_##_name l_##_name = (PFN_##_name)(m_get_instance_func(m_instance, #_name));

//---------------------------------------------------------------------------
// Application::Implementation
//---------------------------------------------------------------------------
// Hide all the implementation details and private functions for the 
// application state.

#define DECLARE_VULKAN_FUNC(a_func_name) static PFN_##a_func_name a_func_name{nullptr};

namespace sdlxvulkan
{
  // The function that will get the others.
  DECLARE_VULKAN_FUNC(vkGetInstanceProcAddr)

  // Functions that don't need an instance to use
  DECLARE_VULKAN_FUNC(vkCreateInstance)
  DECLARE_VULKAN_FUNC(vkEnumerateInstanceExtensionProperties)
  DECLARE_VULKAN_FUNC(vkEnumerateInstanceLayerProperties)
  DECLARE_VULKAN_FUNC(vkEnumerateInstanceVersion)

  // These relate to an instance
  DECLARE_VULKAN_FUNC(vkCreateDevice)
  DECLARE_VULKAN_FUNC(vkCreateDebugReportCallbackEXT)
  DECLARE_VULKAN_FUNC(vkDestroyDebugReportCallbackEXT)
  DECLARE_VULKAN_FUNC(vkDestroyInstance)
  DECLARE_VULKAN_FUNC(vkDestroySurfaceKHR)
  DECLARE_VULKAN_FUNC(vkEnumerateDeviceExtensionProperties)
  DECLARE_VULKAN_FUNC(vkEnumeratePhysicalDevices)
  DECLARE_VULKAN_FUNC(vkGetDeviceProcAddr)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceFeatures)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceProperties)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceMemoryProperties)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceQueueFamilyProperties)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfaceFormatsKHR)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfacePresentModesKHR)
  DECLARE_VULKAN_FUNC(vkGetPhysicalDeviceSurfaceSupportKHR)
    
  // These relate to a device
  DECLARE_VULKAN_FUNC(vkAcquireNextImageKHR)
  DECLARE_VULKAN_FUNC(vkAllocateCommandBuffers)
  DECLARE_VULKAN_FUNC(vkAllocateDescriptorSets)
  DECLARE_VULKAN_FUNC(vkAllocateMemory)
  DECLARE_VULKAN_FUNC(vkBeginCommandBuffer)
  DECLARE_VULKAN_FUNC(vkBindBufferMemory)
  DECLARE_VULKAN_FUNC(vkBindImageMemory)
  DECLARE_VULKAN_FUNC(vkCmdBeginRenderPass)
  DECLARE_VULKAN_FUNC(vkCmdBindPipeline)
  DECLARE_VULKAN_FUNC(vkCmdBindDescriptorSets)
  DECLARE_VULKAN_FUNC(vkCmdBindVertexBuffers)
  DECLARE_VULKAN_FUNC(vkCmdClearColorImage)
  DECLARE_VULKAN_FUNC(vkCmdCopyBuffer)
  DECLARE_VULKAN_FUNC(vkCmdDraw)
  DECLARE_VULKAN_FUNC(vkCmdEndRenderPass)
  DECLARE_VULKAN_FUNC(vkCmdPipelineBarrier)
  DECLARE_VULKAN_FUNC(vkCmdSetViewport)
  DECLARE_VULKAN_FUNC(vkCmdSetScissor)
  DECLARE_VULKAN_FUNC(vkCreateBuffer)
  DECLARE_VULKAN_FUNC(vkCreateCommandPool)
  DECLARE_VULKAN_FUNC(vkCreateDescriptorPool)
  DECLARE_VULKAN_FUNC(vkCreateDescriptorSetLayout)
  DECLARE_VULKAN_FUNC(vkCreateFence)
  DECLARE_VULKAN_FUNC(vkCreateFramebuffer)
  DECLARE_VULKAN_FUNC(vkCreateGraphicsPipelines)
  DECLARE_VULKAN_FUNC(vkCreateImageView)
  DECLARE_VULKAN_FUNC(vkCreatePipelineLayout)
  DECLARE_VULKAN_FUNC(vkCreateRenderPass)
  DECLARE_VULKAN_FUNC(vkCreateSemaphore)
  DECLARE_VULKAN_FUNC(vkCreateShaderModule)
  DECLARE_VULKAN_FUNC(vkCreateSwapchainKHR)
  DECLARE_VULKAN_FUNC(vkDestroyBuffer)
  DECLARE_VULKAN_FUNC(vkDestroyCommandPool)
  DECLARE_VULKAN_FUNC(vkDestroyDescriptorPool)
  DECLARE_VULKAN_FUNC(vkDestroyDescriptorSetLayout)
  DECLARE_VULKAN_FUNC(vkDestroyDevice)
  DECLARE_VULKAN_FUNC(vkDestroyFence)
  DECLARE_VULKAN_FUNC(vkDestroyFramebuffer)
  DECLARE_VULKAN_FUNC(vkDestroyImageView)
  DECLARE_VULKAN_FUNC(vkDestroyPipeline)
  DECLARE_VULKAN_FUNC(vkDestroyPipelineLayout)
  DECLARE_VULKAN_FUNC(vkDestroyRenderPass)
  DECLARE_VULKAN_FUNC(vkDestroySemaphore)
  DECLARE_VULKAN_FUNC(vkDestroyShaderModule)
  DECLARE_VULKAN_FUNC(vkDestroySwapchainKHR)
  DECLARE_VULKAN_FUNC(vkDeviceWaitIdle)
  DECLARE_VULKAN_FUNC(vkEndCommandBuffer)
  DECLARE_VULKAN_FUNC(vkFreeCommandBuffers)
  DECLARE_VULKAN_FUNC(vkFreeMemory)
  DECLARE_VULKAN_FUNC(vkGetBufferMemoryRequirements)
  DECLARE_VULKAN_FUNC(vkGetDeviceQueue)
  DECLARE_VULKAN_FUNC(vkGetFenceStatus)
  DECLARE_VULKAN_FUNC(vkGetImageMemoryRequirements)
  DECLARE_VULKAN_FUNC(vkGetSwapchainImagesKHR)
  DECLARE_VULKAN_FUNC(vkMapMemory)
  DECLARE_VULKAN_FUNC(vkQueuePresentKHR)
  DECLARE_VULKAN_FUNC(vkQueueSubmit)
  DECLARE_VULKAN_FUNC(vkResetCommandBuffer)
  DECLARE_VULKAN_FUNC(vkResetFences)
  DECLARE_VULKAN_FUNC(vkUnmapMemory)
  DECLARE_VULKAN_FUNC(vkUpdateDescriptorSets)
  DECLARE_VULKAN_FUNC(vkWaitForFences)

  

  void init_vulkan_get_proc(PFN_vkGetInstanceProcAddr a_getter);
  void init_vulkan_global_functions();
  void init_vulkan_instance_functions(VkInstance a_instance);
  void init_vulkan_device_functions(VkDevice a_device);
}

#undef DECLARE_VULKAN_FUNC

void sdlxvulkan::init_vulkan_get_proc(PFN_vkGetInstanceProcAddr a_getter)
{
  sdlxvulkan::vkGetInstanceProcAddr = a_getter;
}

#define INIT_VULKAN_GLOBAL_FUNC(a_func_name) a_func_name = (PFN_##a_func_name)(sdlxvulkan::vkGetInstanceProcAddr(VK_NULL_HANDLE, #a_func_name));

void sdlxvulkan::init_vulkan_global_functions()
{
  INIT_VULKAN_GLOBAL_FUNC(vkCreateInstance)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceExtensionProperties)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceLayerProperties)
  INIT_VULKAN_GLOBAL_FUNC(vkEnumerateInstanceVersion)
}

#undef INIT_VULKAN_GLOBAL_FUNC

#define INIT_VULKAN_INSTANCE_FUNC(a_func_name) a_func_name = (PFN_##a_func_name)(sdlxvulkan::vkGetInstanceProcAddr(a_instance, #a_func_name));

void sdlxvulkan::init_vulkan_instance_functions(VkInstance a_instance)
{
  INIT_VULKAN_INSTANCE_FUNC(vkCreateDevice)
  INIT_VULKAN_INSTANCE_FUNC(vkCreateDebugReportCallbackEXT)
  INIT_VULKAN_INSTANCE_FUNC(vkDestroyDebugReportCallbackEXT)
  INIT_VULKAN_INSTANCE_FUNC(vkDestroyInstance)
  INIT_VULKAN_INSTANCE_FUNC(vkDestroySurfaceKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkEnumerateDeviceExtensionProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkEnumeratePhysicalDevices)
  INIT_VULKAN_INSTANCE_FUNC(vkGetDeviceProcAddr)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceFeatures)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceMemoryProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceQueueFamilyProperties)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfaceFormatsKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfacePresentModesKHR)
  INIT_VULKAN_INSTANCE_FUNC(vkGetPhysicalDeviceSurfaceSupportKHR)
}

#undef INIT_VULKAN_INSTANCE_FUNC

#define INIT_VULKAN_DEVICE_FUNC(a_func_name) a_func_name = (PFN_##a_func_name)(sdlxvulkan::vkGetDeviceProcAddr(a_device, #a_func_name));

void sdlxvulkan::init_vulkan_device_functions(VkDevice a_device)
{
  INIT_VULKAN_DEVICE_FUNC(vkAcquireNextImageKHR)
  INIT_VULKAN_DEVICE_FUNC(vkAllocateCommandBuffers)
  INIT_VULKAN_DEVICE_FUNC(vkAllocateDescriptorSets)
  INIT_VULKAN_DEVICE_FUNC(vkAllocateMemory)
  INIT_VULKAN_DEVICE_FUNC(vkBeginCommandBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkBindBufferMemory)
  INIT_VULKAN_DEVICE_FUNC(vkBindImageMemory)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBeginRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindPipeline)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindDescriptorSets)
  INIT_VULKAN_DEVICE_FUNC(vkCmdBindVertexBuffers)
  INIT_VULKAN_DEVICE_FUNC(vkCmdClearColorImage)
  INIT_VULKAN_DEVICE_FUNC(vkCmdCopyBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCmdDraw)
  INIT_VULKAN_DEVICE_FUNC(vkCmdEndRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkCmdPipelineBarrier)
  INIT_VULKAN_DEVICE_FUNC(vkCmdSetViewport)
  INIT_VULKAN_DEVICE_FUNC(vkCmdSetScissor)
  INIT_VULKAN_DEVICE_FUNC(vkCreateBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCreateCommandPool)
  INIT_VULKAN_DEVICE_FUNC(vkCreateDescriptorPool)
  INIT_VULKAN_DEVICE_FUNC(vkCreateDescriptorSetLayout)
  INIT_VULKAN_DEVICE_FUNC(vkCreateFence)
  INIT_VULKAN_DEVICE_FUNC(vkCreateFramebuffer)
  INIT_VULKAN_DEVICE_FUNC(vkCreateGraphicsPipelines)
  INIT_VULKAN_DEVICE_FUNC(vkCreateImageView)
  INIT_VULKAN_DEVICE_FUNC(vkCreatePipelineLayout)
  INIT_VULKAN_DEVICE_FUNC(vkCreateRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkCreateSemaphore)
  INIT_VULKAN_DEVICE_FUNC(vkCreateShaderModule)
  INIT_VULKAN_DEVICE_FUNC(vkCreateSwapchainKHR)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyCommandPool)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyDescriptorPool)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyDescriptorSetLayout)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyDevice)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyFence)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyFramebuffer)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyImageView)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyPipeline)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyPipelineLayout)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyRenderPass)
  INIT_VULKAN_DEVICE_FUNC(vkDestroySemaphore)
  INIT_VULKAN_DEVICE_FUNC(vkDestroyShaderModule)
  INIT_VULKAN_DEVICE_FUNC(vkDestroySwapchainKHR)
  INIT_VULKAN_DEVICE_FUNC(vkDeviceWaitIdle)
  INIT_VULKAN_DEVICE_FUNC(vkEndCommandBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkFreeCommandBuffers)
  INIT_VULKAN_DEVICE_FUNC(vkFreeMemory)
  INIT_VULKAN_DEVICE_FUNC(vkGetBufferMemoryRequirements)
  INIT_VULKAN_DEVICE_FUNC(vkGetDeviceQueue)
  INIT_VULKAN_DEVICE_FUNC(vkGetFenceStatus)
  INIT_VULKAN_DEVICE_FUNC(vkGetImageMemoryRequirements)
  INIT_VULKAN_DEVICE_FUNC(vkGetSwapchainImagesKHR)
  INIT_VULKAN_DEVICE_FUNC(vkMapMemory)
  INIT_VULKAN_DEVICE_FUNC(vkQueuePresentKHR)
  INIT_VULKAN_DEVICE_FUNC(vkQueueSubmit)
  INIT_VULKAN_DEVICE_FUNC(vkResetCommandBuffer)
  INIT_VULKAN_DEVICE_FUNC(vkResetFences)
  INIT_VULKAN_DEVICE_FUNC(vkUnmapMemory)
  INIT_VULKAN_DEVICE_FUNC(vkUpdateDescriptorSets)
  INIT_VULKAN_DEVICE_FUNC(vkWaitForFences)
}

#undef INIT_VULKAN_DEVICE_FUNC


namespace sdlxvulkan
{
  std::string vulkan_result_string(VkResult a_value)
  {
    switch (a_value)
    {
    case(VK_SUCCESS): return "VK_SUCCESS";
    case(VK_NOT_READY): return "VK_NOT_READY ";
    case(VK_TIMEOUT): return "VK_TIMEOUT ";
    case(VK_EVENT_SET): return "VK_EVENT_SET ";
    case(VK_EVENT_RESET): return "VK_EVENT_RESET ";
    case(VK_INCOMPLETE): return "VK_INCOMPLETE ";
    case(VK_ERROR_OUT_OF_HOST_MEMORY): return "VK_ERROR_OUT_OF_HOST_MEMORY ";
    case(VK_ERROR_OUT_OF_DEVICE_MEMORY): return "VK_ERROR_OUT_OF_DEVICE_MEMORY ";
    case(VK_ERROR_INITIALIZATION_FAILED): return "VK_ERROR_INITIALIZATION_FAILED ";
    case(VK_ERROR_DEVICE_LOST): return "VK_ERROR_DEVICE_LOST ";
    case(VK_ERROR_MEMORY_MAP_FAILED): return "VK_ERROR_MEMORY_MAP_FAILED ";
    case(VK_ERROR_LAYER_NOT_PRESENT): return "VK_ERROR_LAYER_NOT_PRESENT ";
    case(VK_ERROR_EXTENSION_NOT_PRESENT): return "VK_ERROR_EXTENSION_NOT_PRESENT ";
    case(VK_ERROR_FEATURE_NOT_PRESENT): return "VK_ERROR_FEATURE_NOT_PRESENT ";
    case(VK_ERROR_INCOMPATIBLE_DRIVER): return "VK_ERROR_INCOMPATIBLE_DRIVER ";
    case(VK_ERROR_TOO_MANY_OBJECTS): return "VK_ERROR_TOO_MANY_OBJECTS ";
    case(VK_ERROR_FORMAT_NOT_SUPPORTED): return "VK_ERROR_FORMAT_NOT_SUPPORTED ";
    case(VK_ERROR_FRAGMENTED_POOL): return "VK_ERROR_FRAGMENTED_POOL ";
    case(VK_ERROR_OUT_OF_POOL_MEMORY): return "VK_ERROR_OUT_OF_POOL_MEMORY ";
    case(VK_ERROR_INVALID_EXTERNAL_HANDLE): return "VK_ERROR_INVALID_EXTERNAL_HANDLE ";
    case(VK_ERROR_SURFACE_LOST_KHR): return "VK_ERROR_SURFACE_LOST_KHR ";
    case(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR): return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR ";
    case(VK_SUBOPTIMAL_KHR): return "VK_SUBOPTIMAL_KHR ";
    case(VK_ERROR_OUT_OF_DATE_KHR): return "VK_ERROR_OUT_OF_DATE_KHR ";
    case(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR): return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR ";
    case(VK_ERROR_VALIDATION_FAILED_EXT): return "VK_ERROR_VALIDATION_FAILED_EXT ";
    case(VK_ERROR_INVALID_SHADER_NV): return "VK_ERROR_INVALID_SHADER_NV ";
    case(VK_ERROR_FRAGMENTATION_EXT): return "VK_ERROR_FRAGMENTATION_EXT ";
    case(VK_ERROR_NOT_PERMITTED_EXT): return "VK_ERROR_NOT_PERMITTED_EXT ";
    default: return "BAD VKRESULT";
    }
  }
  
  // Using the supplied properties, determine the right kind of memory to allocate.
  // Success sets a_typeindex to the value required to allocate the right type of memory. Failure returns false 
  // if no matching memory found.
  bool set_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkFlags a_requirements_mask, uint32_t* a_typeindex)
  {
    // Search memtypes to find first index with those properties
    for (uint32_t i = 0; i < a_properties.memoryTypeCount; i++)
    {
      if ((a_typebits & 1) == 1)
      {
        // Type is available, does it match user properties?
        if ((a_properties.memoryTypes[i].propertyFlags & a_requirements_mask) == a_requirements_mask)
        {
          *a_typeindex = i;
          return true;
        }
      }
      a_typebits >>= 1;
    }
    // No memory types matched, return failure
    return false;
  }

  uint32_t get_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkMemoryPropertyFlags  a_requirements)
  {
    // Search memtypes to find first index with those properties
    for (uint32_t i = 0; i < a_properties.memoryTypeCount; i++)
    {
      // If has 
      if (a_typebits & (1 << i))
      {
        // Type is available, does it match user properties?
        if ((a_properties.memoryTypes[i].propertyFlags & a_requirements) == a_requirements)
        {
          return i;
        }
      }
      a_typebits >>= 1;
    }
    // No memory types matched, return failure
    throw std::runtime_error{ "Vulkan: Failed to find a suitable memory type." };
  }

  
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



namespace sdlxvulkan
{

  static_assert(std::is_pointer_v<VkInstance>, "VkInstance is not a pointer type, don't do the next thing.");
  using Instance_Type = std::remove_pointer_t<VkInstance>;
  using Instance_Pointer = std::add_pointer_t<Instance_Type>;
  static_assert(std::is_same_v<VkInstance, Instance_Pointer>, "VkInstance is not the same type as deduced Instance_Pointer.");

  class Instance_Destroyer
  {
  public:
    void operator()(Instance_Pointer a_ptr)
    {
      vkDestroyInstance(a_ptr, nullptr);
    }
  };

  using Instance = std::unique_ptr<Instance_Type, Instance_Destroyer>;


  void f()
  {
    VkInstance l_input{ VK_NULL_HANDLE };
    Instance l_smart_instance{ l_input };
    VkInstance l_instance = l_smart_instance.get();
  }


  class Physical_Device
  {
  public:
    VkPhysicalDevice m_physical_device;
    VkPhysicalDeviceProperties m_properties;
    VkPhysicalDeviceMemoryProperties m_memory_properties;
    std::vector<VkExtensionProperties> m_extension_properties;

    Physical_Device(VkInstance a_instance, uint32_t a_index);
    ~Physical_Device();

    void refresh_surface(VkInstance a_instance, VkSurfaceKHR a_surface);
  };

  class Surface_Data
  {
  public:
    VkSurfaceCapabilitiesKHR m_surface_cababilites;
    std::vector<VkSurfaceFormatKHR> m_surface_formats;
    std::vector<VkPresentModeKHR> m_present_modes;

    Surface_Data(VkInstance a_instance, VkPhysicalDevice a_device, VkSurfaceKHR a_surface);
  };

  class Device
  {
  public:
    VkDevice m_device;
    VkCommandPool m_command_pool;

    Device(VkInstance a_instance, VkPhysicalDevice a_physical_device);
    ~Device();
  };

  class Swapchain
  {
  public:
    VkFormat m_format;
    VkPresentModeKHR m_present_mode;
    VkExtent2D m_extent;
    uint32_t m_image_count;
    VkSwapchainKHR m_swapchain;
    std::vector<VkImage> m_images;
    std::vector<VkImageView> m_image_views;

    // Render Pass
    VkRenderPass m_render_pass;

    // Pipeline
    VkViewport m_viewport;
    VkRect2D m_scissor;
    VkPipelineLayout m_pipeline_layout;
    VkPipeline m_pipeline;

    // Framebuffers
    std::vector<VkFramebuffer> m_swapchain_framebuffers;

    // Command Buffer(s)
    std::vector<VkCommandBuffer> m_command_buffers;

    Swapchain(VkDevice a_device, Surface_Data const& a_surface_data, uint32_t a_width, uint32_t a_height);
    ~Swapchain();
  };

  class Buffer;

  class Command_Pool;
  class Command_Buffer;
}


namespace sdlxvulkan
{
  class Application::Implementation
  {
  private:
    std::vector<std::string> m_args;

    // Window
    SDL_Window* m_window;
    static_assert(std::is_same_v<Uint32, uint32_t>, "SDL::Uint32 is not ::uint32_t");
    uint32_t m_window_id;
    uint32_t m_width;
    uint32_t m_height;

    // Instance
    VkInstance m_instance;

    // Debug Callback
    VkDebugReportCallbackEXT m_debug_callback;

    // Physical Device
    VkPhysicalDevice m_physical_device;
    VkPhysicalDeviceProperties m_physical_device_properties;
    VkPhysicalDeviceMemoryProperties m_physical_device_mem_properties;

    // Queue Families
    std::vector<VkQueueFamilyProperties> m_queue_familiy_properties;

    // Logical Device
    VkDevice m_device;

    // Graphics Queue
    uint32_t m_graphics_qf_index;
    VkQueue m_graphics_queue;
    
    // Command Pool
    VkCommandPool m_command_pool;

    // Vertex Buffer
    VkBuffer m_vertex_buffer;
    VkDeviceMemory m_vertex_buffer_memory;

    // Index Buffer
    VkBuffer m_index_buffer;
    VkDeviceMemory m_index_buffer_memory;

    // Uniform Buffer
    VkBuffer m_uniform_buffer;
    VkDeviceMemory m_uniform_buffer_memory;

    // Descriptor Pool
    VkDescriptorPool m_descriptor_pool;

    // Descriptor Set
    VkDescriptorSet m_descriptor_set;

    // Shaders
    VkShaderModule m_fragment_shader_module;
    VkShaderModule m_vertex_shader_module;
    VkPipelineShaderStageCreateInfo m_fragment_shader_stage_info;
    VkPipelineShaderStageCreateInfo m_vertex_shader_stage_info;
    std::array<VkPipelineShaderStageCreateInfo, 2> m_shader_stage_infos;

    // Surface
    VkSurfaceKHR m_surface;

    // Present Queue
    uint32_t m_present_qf_index;
    VkQueue m_present_queue;
    
    // Swapchain
    VkSurfaceCapabilitiesKHR m_swapchain_surface_cababilites;
    std::vector<VkSurfaceFormatKHR> m_swapchain_surface_formats;
    std::vector<VkPresentModeKHR> m_swapchain_present_modes;
    VkFormat m_swapchain_format;
    VkPresentModeKHR m_swapchain_present_mode;
    VkExtent2D m_swapchain_extent;
    uint32_t m_swapchain_image_count;
    VkSwapchainKHR m_swapchain;

    // Swapchain Images
    std::vector<VkImage> m_swapchain_images;
    std::vector<VkImageView> m_swapchain_image_views;
    
    // Render Pass
    VkRenderPass m_render_pass;

    // Descriptor Set Layout
    VkDescriptorSetLayout m_descriptor_set_layout;

    // Pipeline
    VkViewport m_viewport;
    VkRect2D m_scissor;
    VkPipelineLayout m_pipeline_layout;
    VkPipeline m_pipeline;

    // Framebuffers
    std::vector<VkFramebuffer> m_swapchain_framebuffers;
    
    // Command Buffer(s)
    std::vector<VkCommandBuffer> m_command_buffers;

    // Sync Objects
    std::vector<VkSemaphore> m_image_available_semaphores;
    std::vector<VkSemaphore> m_render_finished_semaphores;
    std::vector<VkFence> m_fences;
    size_t m_current_frame;

    /*
    VkSampleCountFlagBits m_sample_count;
    VkFormat m_depth_format;
    VkImage m_depth_image;
    VkDeviceMemory m_depth_memory;
    VkImageView m_depth_image_view;

    VkBuffer m_uniform_buffer;
    VkDeviceMemory m_uniform_memory;
    VkDescriptorBufferInfo m_uniform_buffer_info;

    glm::mat4 m_glm_projection;
    glm::mat4 m_glm_view;
    glm::mat4 m_glm_model;
    glm::mat4 m_glm_clip;
    glm::mat4 m_glm_mvp;

    uint32_t m_descriptor_set_count;
    std::vector<VkDescriptorSetLayout> m_descriptor_set_layouts;
    
    VkDescriptorPool m_descriptor_pool;
    std::vector<VkDescriptorSet> m_descriptor_sets;


    uint32_t m_current_buffer;
//    VkSemaphore m_image_available_semaphore;
    
    std::vector<VkFramebuffer> m_framebuffers;

    VkBuffer m_vertex_buffer;
    VkDeviceMemory m_vertex_buffer_memory;
    VkDescriptorBufferInfo m_vertex_buffer_info;

    VkVertexInputBindingDescription m_vertex_input_binding_desc;
    VkVertexInputAttributeDescription m_vertex_input_attributes_descs[2];
    
    
    uint32_t m_num_viewports;
    uint32_t m_num_scissors;
    */
  public:
    // Special 6
    //============================================================
    Implementation(int argc, char** argv);
    ~Implementation();

    Implementation(Implementation const& a_other) = delete;
    Implementation& operator=(Implementation const& a_other) = delete;

    Implementation(Implementation && a_other) = delete;
    Implementation& operator=(Implementation && a_other) = delete;


    // Interface
    //============================================================
    int execute();

    void init();
    void quit();

    void ignore_init();
    void ignore_quit();
    
    void main_loop();

    void init_system();
    void quit_system();

    void init_window();
    void quit_window();

    void init_instance();
    void quit_instance();

    void init_debug_callback();
    void quit_debug_callback();

    void init_physical_device();
    void quit_physical_device();
    
    void init_queue_families();
    void quit_queue_families();

    void init_logical_device();
    void quit_logical_device();

    void init_command_pool();
    void quit_command_pool();

    void init_vertex_buffer();
    void quit_vertex_buffer();

    void init_index_buffer();
    void quit_index_buffer();

    void init_uniform_buffer();
    void quit_uniform_buffer();

    void init_descriptor_pool();
    void quit_descriptor_pool();

    void init_descriptor_set();
    void quit_descriptor_set();
    
    void init_shader_modules();
    void quit_shader_modules();

    void init_graphics_queue();
    void quit_graphics_queue();

    void init_surface();
    void quit_surface();

    void init_present_queue();
    void quit_present_queue();

    void init_swapchain(VkSwapchainKHR a_old_swapchain = VK_NULL_HANDLE);
    void recreate_swapchain();
    void quit_swapchain();
    
    void init_swapchain_image_views();
    void quit_swapchain_image_views();

    void init_render_pass();
    void quit_render_pass();

    void init_descriptor_set_layout();
    void quit_descriptor_set_layout();

    void init_pipeline();
    void quit_pipeline();

    void init_framebuffer();
    void quit_framebuffer();
    
    void init_command_buffers();
    void quit_command_buffers();
    
    void do_commands();

    void init_sync_objects();
    void quit_sync_objects();

    void draw_frame();

    void update_uniform_buffer();

    void create_buffer(VkDeviceSize a_size, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_buffer_memory);

    //void copy_buffer(VkBuffer a_source, VkDeviceSize a_source_offset, VkBuffer a_dest, VkDeviceSize a_dest_offset, VkDeviceSize a_size);
    void copy_buffer(VkBuffer a_source, VkBuffer a_dest, VkDeviceSize a_size);
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------
namespace
{
  std::vector<std::string> make_arg_vector(int argc, char** argv)
  {
    std::vector<std::string> l_result{};
    l_result.reserve(argc);

    for (int i = 0; i != argc; ++i)
    {
      l_result.push_back(argv[i]);
    }

    return l_result;
  }

  std::string make_what(char const* a_func, char const* a_error)
  {
    std::string l_result{ a_func };
    l_result += " failure: ";
    l_result += a_error;
    return l_result;
  }
}


// Special 6
//============================================================
sdlxvulkan::Application::Implementation::Implementation(int argc, char** argv) :
  m_args{ make_arg_vector(argc, argv) },

  m_window{ nullptr },
  m_window_id{ 0 },
  m_width{ 0 },
  m_height{ 0 },

  m_instance{ VK_NULL_HANDLE },

  m_debug_callback{},
  m_physical_device{ VK_NULL_HANDLE },
  m_physical_device_properties{},
  m_physical_device_mem_properties{},

  m_queue_familiy_properties{},

  m_surface{ VK_NULL_HANDLE },

  m_device{ VK_NULL_HANDLE },

  m_graphics_qf_index{ UINT32_MAX },
  m_graphics_queue{},

  m_command_pool{},

  m_vertex_buffer{},
  m_vertex_buffer_memory{},

  m_index_buffer{},
  m_index_buffer_memory{},

  m_uniform_buffer{},
  m_uniform_buffer_memory{},

  m_descriptor_pool{},

  m_descriptor_set{},

  m_fragment_shader_module{},
  m_vertex_shader_module{},
  m_fragment_shader_stage_info{},
  m_vertex_shader_stage_info{},
  m_shader_stage_infos{},

  m_present_qf_index{ UINT32_MAX },
  m_present_queue{},
  
  m_swapchain_surface_cababilites{},
  m_swapchain_surface_formats{},
  m_swapchain_present_modes{},
  m_swapchain_format{},
  m_swapchain_present_mode{},
  m_swapchain_extent{},
  m_swapchain{ },
  m_swapchain_image_count{ 0 },

  m_swapchain_images{},
  m_swapchain_image_views{},


  // Render Pass
  m_render_pass{},

  m_descriptor_set_layout{},

  // Pipeline
  m_viewport{},
  m_scissor{},
  m_pipeline_layout{},
  m_pipeline{},

  m_swapchain_framebuffers{},
  
  m_command_buffers{},

  // Sync Objects
  m_image_available_semaphores{},
  m_render_finished_semaphores{},
  m_fences{},
  m_current_frame{}
  /*
  m_sample_count{ VK_SAMPLE_COUNT_1_BIT },
  m_depth_format{},
  m_depth_image{},
  m_depth_memory{},
  m_depth_image_view{},

  m_uniform_buffer{},
  m_uniform_memory{},
  m_uniform_buffer_info{},

  m_glm_projection{},
  m_glm_view{},
  m_glm_model{},
  m_glm_clip{},
  m_glm_mvp{},

  m_descriptor_set_count{},
  m_descriptor_set_layouts{},
  m_descriptor_pool{},
  m_descriptor_sets{},
  m_current_buffer{},
  //m_image_available_semaphore{},
  m_framebuffers{},

  m_vertex_buffer{},
  m_vertex_buffer_memory{},
  m_vertex_buffer_info{},

  m_vertex_input_binding_desc{},
  m_vertex_input_attributes_descs{},

  m_num_viewports{ 1 },
  m_num_scissors{ 1 }
  */
{
  std::cout << "Application::Implementation::Implementation(argc, * argv)" << std::endl;
  // Output the captured args to the console.
  std::cout << "Args:" << std::endl;
  for (auto const& i : m_args)
  {
    std::cout << i << std::endl;
  }
}

sdlxvulkan::Application::Implementation::~Implementation()
{
  std::cout << "Application::Implementation::~Implementation()" << std::endl;
  quit();
}

// Interface
//============================================================
int sdlxvulkan::Application::Implementation::execute()
{
  try
  {
    init();

    main_loop();

  }
  catch (std::runtime_error& a_exception)
  {
    std::cout << a_exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  // Everything worked.
  return EXIT_SUCCESS;
}


void sdlxvulkan::Application::Implementation::init()
{
  std::cout << "Application::Implementation::init()" << std::endl;

  init_system();
  init_window();
  init_instance();
  init_debug_callback();
  init_physical_device();
  init_surface();
  init_queue_families();
  init_logical_device();
  init_graphics_queue();
  init_command_pool();
  init_vertex_buffer();
  init_index_buffer();
  init_uniform_buffer();
  init_shader_modules();
  init_surface();
  init_present_queue();
  init_swapchain();
  init_swapchain_image_views();
  init_render_pass();
  init_descriptor_set_layout();
  init_descriptor_pool();
  init_descriptor_set();
  init_pipeline();
  init_framebuffer();
  init_command_buffers();
  init_sync_objects();

  do_commands();
}

void sdlxvulkan::Application::Implementation::ignore_init()
{
  /*
  //------------------------------------------------------------------------------------------------------------------------
  {
   
  }
  //------------------------------------------------------------------------------------------------------------------------
  

  //------------------------------------------------------------------------------------------------------------------------
  {
    
  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    std::cout << "Depth Buffer" << std::endl;
    // Depth Buffer
    //-------------

    // Set the depth format
    m_depth_format = VK_FORMAT_D16_UNORM;

    // Get properties for this format
    VkFormatProperties l_format_properties{};
    vkGetPhysicalDeviceFormatProperties(m_physical_device, m_depth_format, &l_format_properties);

    // Set up the image data for the depth buffer
    VkImageCreateInfo l_depth_image_info{};

    // This bit relies on the format properties
    if (l_format_properties.linearTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
    {
      l_depth_image_info.tiling = VK_IMAGE_TILING_LINEAR;
    }
    else if (l_format_properties.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
    {
      l_depth_image_info.tiling = VK_IMAGE_TILING_OPTIMAL;
    }
    else
    {
      // Try other depth formats?
      throw std::runtime_error{ "Vulkan: VK_FORMAT_D16_UNORM Unsupported." };
    }

    l_depth_image_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    l_depth_image_info.pNext = NULL;
    l_depth_image_info.flags = 0;
    l_depth_image_info.imageType = VK_IMAGE_TYPE_2D;
    l_depth_image_info.format = m_depth_format;
    l_depth_image_info.extent.width = m_width;
    l_depth_image_info.extent.height = m_height;
    l_depth_image_info.extent.depth = 1;
    l_depth_image_info.mipLevels = 1;
    l_depth_image_info.arrayLayers = 1;
    l_depth_image_info.samples = m_sample_count;
    l_depth_image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    l_depth_image_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_depth_image_info.queueFamilyIndexCount = 0;
    l_depth_image_info.pQueueFamilyIndices = NULL;
    l_depth_image_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    // Create the iamge
    if (vkCreateImage(m_device, &l_depth_image_info, NULL, &m_depth_image) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create depth buffer image." };
    }

    // Now we start work making some memory to use.
    // First figure out how much we need
    VkMemoryRequirements l_mem_reqs{};
    vkGetImageMemoryRequirements(m_device, m_depth_image, &l_mem_reqs);

    // Now setup for the allocation
    VkMemoryAllocateInfo l_mem_alloc_info = {};
    l_mem_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    l_mem_alloc_info.pNext = NULL;
    l_mem_alloc_info.allocationSize = l_mem_reqs.size;
    l_mem_alloc_info.memoryTypeIndex = 0;

    // Use the memory properties to determine the type of memory required 

    if (!set_memory_type_from_properties(m_physical_device_mem_properties, l_mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &l_mem_alloc_info.memoryTypeIndex))
    {
      throw std::runtime_error{ "Vulkan: Failed to find matching memory type on the phyisical device." };
    }

    // Allocate memory on the device
    if (vkAllocateMemory(m_device, &l_mem_alloc_info, NULL, &m_depth_memory) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to allocate depth buffer memory." };
    }

    // Bind the memory
    if (vkBindImageMemory(m_device, m_depth_image, m_depth_memory, 0) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to bind depth buffer memory." };
    }

    VkImageViewCreateInfo l_depth_image_view_info{};
    l_depth_image_view_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    l_depth_image_view_info.pNext = NULL;
    l_depth_image_view_info.flags = 0;
    l_depth_image_view_info.image = m_depth_image;
    l_depth_image_view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
    l_depth_image_view_info.format = m_depth_format;
    l_depth_image_view_info.components.r = VK_COMPONENT_SWIZZLE_R;
    l_depth_image_view_info.components.g = VK_COMPONENT_SWIZZLE_G;
    l_depth_image_view_info.components.b = VK_COMPONENT_SWIZZLE_B;
    l_depth_image_view_info.components.a = VK_COMPONENT_SWIZZLE_A;
    l_depth_image_view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    l_depth_image_view_info.subresourceRange.baseMipLevel = 0;
    l_depth_image_view_info.subresourceRange.levelCount = 1;
    l_depth_image_view_info.subresourceRange.baseArrayLayer = 0;
    l_depth_image_view_info.subresourceRange.layerCount = 1;

    // Create the image view
    if (vkCreateImageView(m_device, &l_depth_image_view_info, NULL, &m_depth_image_view) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create depth buffer image view." };
    }

    std::cout << "END" << std::endl;
  }
  //------------------------------------------------------------------------------------------------------------------------
  
  {
    // Uniform Buffer
    //-------------

    // Setup the data we are going to be using for rendering here

    m_glm_projection = 
      glm::perspective
      (
        glm::radians(45.0f), 
        1.0f, 
        0.1f, 
        100.0f
      );

    m_glm_view = 
      glm::lookAt
      (
        glm::vec3(-5, 3, -10),  // Camera is at (-5,3,-10), in World Space
        glm::vec3(0, 0, 0),     // and looks at the origin
        glm::vec3(0, -1, 0)     // Head is up (set to 0,-1,0 to look upside-down)
      );

    m_glm_model = glm::mat4(1.0f);

    // Vulkan clip space has inverted Y and half Z.
    m_glm_clip = 
      glm::mat4
      (
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.5f, 1.0f
      );

    m_glm_mvp = m_glm_clip * m_glm_projection * m_glm_view * m_glm_model;

    VkBufferCreateInfo l_buffer_info = {};
    l_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    l_buffer_info.pNext = NULL;
    l_buffer_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    l_buffer_info.size = sizeof(m_glm_mvp);
    l_buffer_info.queueFamilyIndexCount = 0;
    l_buffer_info.pQueueFamilyIndices = NULL;
    l_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_buffer_info.flags = 0;

    if (vkCreateBuffer(m_device, &l_buffer_info, NULL, &m_uniform_buffer) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create uniform buffer." };
    }
    
    VkMemoryRequirements l_mem_reqs{};
    vkGetBufferMemoryRequirements(m_device, m_uniform_buffer, &l_mem_reqs);

    VkMemoryAllocateInfo l_alloc_info = {};
    l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    l_alloc_info.pNext = NULL;
    l_alloc_info.memoryTypeIndex = 0;

    l_alloc_info.allocationSize = l_mem_reqs.size;


    if (!set_memory_type_from_properties(m_physical_device_mem_properties, l_mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &l_alloc_info.memoryTypeIndex))
    {
      throw std::runtime_error{ "Vulkan: Failed to find matching memory type on the phyisical device to allocate the uniform buffer." };
    }
    
    if (vkAllocateMemory(m_device, &l_alloc_info, NULL, &m_uniform_memory) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to allocate the uniform buffer." };
    }

    void* l_data{nullptr};
    // dunno about this cast
    if (vkMapMemory(m_device, m_uniform_memory, 0, l_mem_reqs.size, 0, &l_data) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to allocate the uniform buffer." };
    }

    memcpy(l_data, &m_glm_mvp, sizeof(m_glm_mvp));

    // unmap the memory after we have used it.
    vkUnmapMemory(m_device, m_uniform_memory);

    if (vkBindBufferMemory(m_device, m_uniform_buffer, m_uniform_memory, 0) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to bind the uniform buffer." };
    }

    m_uniform_buffer_info.buffer = m_uniform_buffer;
    m_uniform_buffer_info.offset = 0;
    m_uniform_buffer_info.range = sizeof(m_glm_mvp);

  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    // Pipeline Layout
    //-------------
    // Note that when we start using textures, this is where our sampler will need to be specified
    VkDescriptorSetLayoutBinding l_layout_binding = {};
    l_layout_binding.binding = 0;
    l_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_layout_binding.descriptorCount = 1;
    l_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    l_layout_binding.pImmutableSamplers = NULL;

    // Next take layout bindings and use them to create a descriptor set layout
    VkDescriptorSetLayoutCreateInfo l_descriptor_layout = {};
    l_descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    l_descriptor_layout.pNext = NULL;
    l_descriptor_layout.bindingCount = 1;
    l_descriptor_layout.pBindings = &l_layout_binding;

    // only one descriptor set right now.
    m_descriptor_set_count = 1;

    m_descriptor_set_layouts.resize(m_descriptor_set_count);

    if (vkCreateDescriptorSetLayout(m_device, &l_descriptor_layout, NULL, m_descriptor_set_layouts.data()) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create descriptor sets." };
    }

    // Now use the descriptor layout to create a pipeline layout 
    VkPipelineLayoutCreateInfo l_pipeline_layout_info = {};
    l_pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    l_pipeline_layout_info.pNext = NULL;
    l_pipeline_layout_info.pushConstantRangeCount = 0;
    l_pipeline_layout_info.pPushConstantRanges = NULL;
    l_pipeline_layout_info.setLayoutCount = m_descriptor_set_count;
    l_pipeline_layout_info.pSetLayouts = m_descriptor_set_layouts.data();
    
    if (vkCreatePipelineLayout(m_device, &l_pipeline_layout_info, NULL, &m_pipeline_layout) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create pipeline layout." };
    }
  }
  
  //------------------------------------------------------------------------------------------------------------------------
  {
    std::cout << "Uniform Buffer" << std::endl;
    // Uniform Buffer
    //-------------
    UniformBufferObject l_ubo = {};
    l_ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    l_ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    l_ubo.proj = glm::perspective(glm::radians(45.0f), m_width / (float)m_height, 0.1f, 10.0f);
    l_ubo.proj[1][1] *= -1;

    VkBufferCreateInfo l_buffer_info = {};
    l_buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    l_buffer_info.pNext = NULL;
    l_buffer_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    l_buffer_info.size = sizeof(l_ubo);
    l_buffer_info.queueFamilyIndexCount = 0;
    l_buffer_info.pQueueFamilyIndices = NULL;
    l_buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_buffer_info.flags = 0;

    if (vkCreateBuffer(m_device, &l_buffer_info, NULL, &m_uniform_buffer) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create uniform buffer." };
    }

    VkMemoryRequirements l_mem_reqs{};
    vkGetBufferMemoryRequirements(m_device, m_uniform_buffer, &l_mem_reqs);

    VkMemoryAllocateInfo l_alloc_info = {};
    l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    l_alloc_info.pNext = NULL;
    l_alloc_info.memoryTypeIndex = 0;

    l_alloc_info.allocationSize = l_mem_reqs.size;


    if (!set_memory_type_from_properties(m_physical_device_mem_properties, l_mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &l_alloc_info.memoryTypeIndex))
    {
      throw std::runtime_error{ "Vulkan: Failed to find matching memory type on the phyisical device to allocate the uniform buffer." };
    }

    if (vkAllocateMemory(m_device, &l_alloc_info, NULL, &m_uniform_memory) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to allocate the uniform buffer." };
    }
    
    void* l_data{ nullptr };
    // dunno about this cast
    if (vkMapMemory(m_device, m_uniform_memory, 0, sizeof(l_ubo), 0, &l_data) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to map the uniform buffer." };
    }
    
    memcpy(l_data, &l_ubo, sizeof(l_ubo));

    // unmap the memory after we have used it.
    vkUnmapMemory(m_device, m_uniform_memory);
    
    if (vkBindBufferMemory(m_device, m_uniform_buffer, m_uniform_memory, 0) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to bind the uniform buffer." };
    }

    m_uniform_buffer_info.buffer = m_uniform_buffer;
    m_uniform_buffer_info.offset = 0;
    m_uniform_buffer_info.range = sizeof(l_ubo);

    std::cout << "END" << std::endl;
  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    // Pipeline Layout
    //-------------
    // Note that when we start using textures, this is where our sampler will need to be specified
    VkDescriptorSetLayoutBinding l_layout_binding = {};
    l_layout_binding.binding = 0;
    l_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_layout_binding.descriptorCount = 1;
    l_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    l_layout_binding.pImmutableSamplers = NULL;

    // Next take layout bindings and use them to create a descriptor set layout
    VkDescriptorSetLayoutCreateInfo l_descriptor_layout = {};
    l_descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    l_descriptor_layout.pNext = NULL;
    l_descriptor_layout.bindingCount = 1;
    l_descriptor_layout.pBindings = &l_layout_binding;

    // only one descriptor set right now.
    m_descriptor_set_count = 1;

    m_descriptor_set_layouts.resize(m_descriptor_set_count);

    if (vkCreateDescriptorSetLayout(m_device, &l_descriptor_layout, NULL, m_descriptor_set_layouts.data()) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create descriptor sets." };
    }

    // Now use the descriptor layout to create a pipeline layout 
    VkPipelineLayoutCreateInfo l_pipeline_layout_info = {};
    l_pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    l_pipeline_layout_info.pNext = NULL;
    l_pipeline_layout_info.pushConstantRangeCount = 0;
    l_pipeline_layout_info.pPushConstantRanges = NULL;
    l_pipeline_layout_info.setLayoutCount = m_descriptor_set_count;
    l_pipeline_layout_info.pSetLayouts = m_descriptor_set_layouts.data();

    if (vkCreatePipelineLayout(m_device, &l_pipeline_layout_info, NULL, &m_pipeline_layout) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create pipeline layout." };
    }
  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    // Descriptor Pool
    //-------------

    VkDescriptorPoolSize l_type_count[1]{};
    l_type_count[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_type_count[0].descriptorCount = 1;

    VkDescriptorPoolCreateInfo l_descriptor_pool_info = {};
    l_descriptor_pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    l_descriptor_pool_info.pNext = NULL;
    l_descriptor_pool_info.maxSets = 1;
    l_descriptor_pool_info.poolSizeCount = 1;
    l_descriptor_pool_info.pPoolSizes = l_type_count;

    // Make the pool 
    if (vkCreateDescriptorPool(m_device, &l_descriptor_pool_info, NULL, &m_descriptor_pool) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create descriptor pool." };
    }
  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    // Descriptor Set
    //-------------
    // Now we actually allocate the descriptor sets

    VkDescriptorSetAllocateInfo l_alloc_info{};
    l_alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    l_alloc_info.pNext = NULL;
    l_alloc_info.descriptorPool = m_descriptor_pool;
    l_alloc_info.descriptorSetCount = m_descriptor_set_count;
    l_alloc_info.pSetLayouts = m_descriptor_set_layouts.data();

    m_descriptor_sets.resize(m_descriptor_set_count);
    if (vkAllocateDescriptorSets(m_device, &l_alloc_info, m_descriptor_sets.data()) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to allocate descriptor sets." };
    }
    // Destroyed by Descriptor Pool cleanup

    // Update the descriptor sets
    VkWriteDescriptorSet l_writes[1]{};

    l_writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    l_writes[0].pNext = NULL;
    l_writes[0].dstSet = m_descriptor_sets[0];
    l_writes[0].dstBinding = 0;
    l_writes[0].dstArrayElement = 0;
    l_writes[0].descriptorCount = 1;
    l_writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    l_writes[0].pImageInfo = nullptr;
    l_writes[0].pBufferInfo = &m_uniform_buffer_info;
    l_writes[0].pTexelBufferView = nullptr;

    // Send the data to the descriptor sets
    vkUpdateDescriptorSets(m_device, 1, l_writes, 0, NULL);

  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    // Render Pass
    //-------------
    // A semaphore (or fence) is required in order to acquire a
    // swapchain image to prepare it for use in a render pass.
    // The semaphore is normally used to hold back the rendering
    // operation until the image is actually available.
    // But since this sample does not render, the semaphore
    // ends up being unused.
    

    // Semaphore

    // This gets put directly after the swapchain in the examples...
    VkSemaphoreCreateInfo l_image_acquired_semaphore_info{};
    l_image_acquired_semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    l_image_acquired_semaphore_info.pNext = NULL;
    l_image_acquired_semaphore_info.flags = 0;

    if (vkCreateSemaphore(m_device, &l_image_acquired_semaphore_info, NULL, &m_image_available_semaphore) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to create semaphore." };
    }


    // Current Buffer

    // Aquire the next swapchain image so we can manipulate it
    if (vkAcquireNextImageKHR(m_device, m_swapchain, UINT64_MAX, m_image_available_semaphore, VK_NULL_HANDLE, &m_current_buffer) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to aquire swapchain image" };
    }

    // The initial layout for the color and depth attachments will be
    // LAYOUT_UNDEFINED because at the start of the renderpass, we don't
    // care about their contents. At the start of the subpass, the color
    // attachment's layout will be transitioned to LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    // and the depth stencil attachment's layout will be transitioned to
    // LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL.  At the end of the renderpass,
    // the color attachment's layout will be transitioned to
    // LAYOUT_PRESENT_SRC_KHR to be ready to present.  This is all done as part
    // of the renderpass, no barriers are necessary.
    VkAttachmentDescription l_attachments[2]{};
    l_attachments[0].format = m_swapchain_format;
    l_attachments[0].samples = m_sample_count;
    l_attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    l_attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    l_attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    l_attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    l_attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    l_attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    l_attachments[0].flags = 0;

    l_attachments[1].format = m_depth_format;
    l_attachments[1].samples = m_sample_count;
    l_attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    l_attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    l_attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    l_attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    l_attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    l_attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    l_attachments[1].flags = 0;

    VkAttachmentReference l_colour_reference = {};
    l_colour_reference.attachment = 0;
    l_colour_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference l_depth_reference = {};
    l_depth_reference.attachment = 1;
    l_depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription l_subpass = {};
    l_subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    l_subpass.flags = 0;
    l_subpass.inputAttachmentCount = 0;
    l_subpass.pInputAttachments = NULL;
    l_subpass.colorAttachmentCount = 1;
    l_subpass.pColorAttachments = &l_colour_reference;
    l_subpass.pResolveAttachments = NULL;
    l_subpass.pDepthStencilAttachment = &l_depth_reference;
    l_subpass.preserveAttachmentCount = 0;
    l_subpass.pPreserveAttachments = NULL;

    VkRenderPassCreateInfo l_render_pass_info = {};
    l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    l_render_pass_info.pNext = NULL;
    l_render_pass_info.attachmentCount = 2;
    l_render_pass_info.pAttachments = l_attachments;
    l_render_pass_info.subpassCount = 1;
    l_render_pass_info.pSubpasses = &l_subpass;
    l_render_pass_info.dependencyCount = 0;
    l_render_pass_info.pDependencies = NULL;


    // Aquire the next swapchain image so we can manipulate it
    if (vkCreateRenderPass(m_device, &l_render_pass_info, NULL, &m_render_pass) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to aquire swapchain image" };
    }

  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    

  }
  //------------------------------------------------------------------------------------------------------------------------

  //------------------------------------------------------------------------------------------------------------------------
  
  //----------------------------------------------------------------------------------------------------------------------
  {
    
  }
  //------------------------------------------------------------------------------------------------------------------------
  {
    std::cout << "Render Pass" << std::endl;
    // Begin the render pass
    //-------------

    // We cannot bind the vertex buffer until we begin a renderpass 
    VkClearValue l_clear_values[2]{};
    l_clear_values[0].color.float32[0] = 0.2f;
    l_clear_values[0].color.float32[1] = 0.2f;
    l_clear_values[0].color.float32[2] = 0.2f;
    l_clear_values[0].color.float32[3] = 0.2f;
    l_clear_values[1].depthStencil.depth = 1.0f;
    l_clear_values[1].depthStencil.stencil = 0;

    VkRenderPassBeginInfo l_render_pass_begin_info{};
    l_render_pass_begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    l_render_pass_begin_info.pNext = NULL;
    l_render_pass_begin_info.renderPass = m_render_pass;
    l_render_pass_begin_info.framebuffer = m_framebuffers[m_current_buffer];
    l_render_pass_begin_info.renderArea.offset.x = 0;
    l_render_pass_begin_info.renderArea.offset.y = 0;
    l_render_pass_begin_info.renderArea.extent.width = m_width;
    l_render_pass_begin_info.renderArea.extent.height = m_height;
    l_render_pass_begin_info.clearValueCount = 2;
    l_render_pass_begin_info.pClearValues = l_clear_values;


    // Start the Command Buffer
    VkCommandBufferBeginInfo l_cmd_buf_info = {};
    l_cmd_buf_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    l_cmd_buf_info.pNext = NULL;
    l_cmd_buf_info.flags = 0;
    l_cmd_buf_info.pInheritanceInfo = NULL;

    if (vkBeginCommandBuffer(m_command_buffer, &l_cmd_buf_info) != VK_SUCCESS)
    {
      throw std::runtime_error("Vulkan: Failed to begin the command buffer.");
    }


    // Begin the render pass
    vkCmdBeginRenderPass(m_command_buffer, &l_render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);
    
    // Bind the pipeline
    vkCmdBindPipeline(m_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
    
    // Bind the descriptor sets
    vkCmdBindDescriptorSets(m_command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout, 0, m_descriptor_set_count, m_descriptor_sets.data(), 0, nullptr);
    
    VkDeviceSize const l_offsets[1] = { 0 };

    // Bind the vertex buffers
    VkBuffer l_vertex_buffers[] = { m_vertex_buffer };
    vkCmdBindVertexBuffers(m_command_buffer, 0, 1, l_vertex_buffers, l_offsets);


    std::cout << "END" << std::endl;
  }
  //------------------------------------------------------------------------------------------------------------------------
  
  }
  //------------------------------------------------------------------------------------------------------------------------
  */
}

void sdlxvulkan::Application::Implementation::ignore_quit()
{
  /*
  std::cout << "Application::Implementation::quit()" << std::endl;


  // Destroy the pipeline
  vkDestroyPipeline(m_device, m_pipeline, NULL);

  // Destroy the vertex buffer
  vkDestroyBuffer(m_device, m_vertex_buffer, NULL);
  vkFreeMemory(m_device, m_vertex_buffer_memory, NULL);

  // Destroy the frambuffers
  for (uint32_t i = 0; i != m_framebuffers.size(); i++)
  {
    vkDestroyFramebuffer(m_device, m_framebuffers[i], NULL);
  }


  // Destroy the render pass
  vkDestroyRenderPass(m_device, m_render_pass, NULL);

  // Destroy the semaphore
  vkDestroySemaphore(m_device, m_image_available_semaphore, NULL);

  // Destroy the descriptor pool.
  // Don't seem to have to clean up the descriptor sets...
  vkDestroyDescriptorPool(m_device, m_descriptor_pool, NULL);

  // Destroy the pipeline layout
  for (uint32_t i = 0; i < m_descriptor_set_count; i++)
  {
    vkDestroyDescriptorSetLayout(m_device, m_descriptor_set_layouts[i], NULL);
  }

  // Destroy the uniform buffer
  vkDestroyBuffer(m_device, m_uniform_buffer, NULL);
  vkFreeMemory(m_device, m_uniform_memory, NULL);

  // Destroy the depth buffer
  vkDestroyImageView(m_device, m_depth_image_view, NULL);
  vkDestroyImage(m_device, m_depth_image, NULL);
  vkFreeMemory(m_device, m_depth_memory, NULL);
  */
}

void sdlxvulkan::Application::Implementation::quit()
{
  quit_sync_objects();
  quit_command_buffers();
  quit_framebuffer();
  quit_pipeline();
  quit_descriptor_set();
  quit_descriptor_pool();
  quit_descriptor_set_layout();
  quit_render_pass();
  quit_swapchain_image_views();
  quit_swapchain();
  quit_present_queue();
  quit_surface();
  quit_graphics_queue();
  quit_shader_modules();
  quit_uniform_buffer();
  quit_index_buffer();
  quit_vertex_buffer();
  quit_command_pool();
  quit_logical_device();
  quit_queue_families();
  quit_physical_device();
  quit_debug_callback();
  quit_instance();
  quit_window();
  quit_system();
}

void sdlxvulkan::Application::Implementation::main_loop()
{
  std::cout << "Application::Implementation::main_loop()" << std::endl;
  {
    int l_window_width{ 0 };
    int l_window_height{ 0 };
    SDL_GetWindowSize(m_window, &l_window_width, &l_window_height);
    std::cout << "window = " << l_window_width << "x" << l_window_height << std::endl;
    int l_draw_width{ 0 };
    int l_draw_height{ 0 };
    SDL_Vulkan_GetDrawableSize(m_window, &l_draw_width, &l_draw_height);
    std::cout << "draw = " << l_window_width << "x" << l_window_height << std::endl;
  }

  // a really basic render loop...
  SDL_Event l_event{};
  bool l_quit{ false };
  size_t l_frame_count{ 0 };
  auto l_last_time = std::chrono::steady_clock::now();
  auto l_now_time = l_last_time;
  while (!l_quit)
  {
    // FPS tracking
    l_now_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> l_dif = l_now_time - l_last_time;
    if (l_dif.count() >= 1.0)
    {
      std::cout << "FPS: " << l_frame_count << std::endl;
      l_frame_count = 0;
      l_last_time = l_now_time;
    }

    while (SDL_PollEvent(&l_event))
    {
      

      if (l_event.type == SDL_QUIT)
      {
        l_quit = true;
      }
      if (l_event.type == SDL_WINDOWEVENT && l_event.window.windowID == m_window_id)
      {
        //std::cout << sdl_window_event_string(static_cast<SDL_WindowEventID>(l_event.window.event)) << std::endl;
        if (l_event.window.event == SDL_WINDOWEVENT_RESIZED) // everytime the user resizes the window
        {
          int l_window_width{ l_event.window.data1 };
          int l_window_height{ l_event.window.data2 };
        
          int l_draw_width{ 0 };
          int l_draw_height{ 0 };

          SDL_Vulkan_GetDrawableSize(m_window, &l_draw_width, &l_draw_height);

          m_width = l_draw_width;
          m_height = l_draw_height;
          std::cout << "Window Resized:" << std::endl;
          std::cout << "window = " << l_window_width << "x" << l_window_height << std::endl;
          std::cout << "draw = " << l_window_width << "x" << l_window_height << std::endl;

          recreate_swapchain();
        }
      }
    }
    update_uniform_buffer();
    // Drawing
    draw_frame();
    ++l_frame_count;

    // Tick rate limit
    //SDL_Delay(16); //~60FPS
    //SDL_Delay(1);
    
  }
  vkDeviceWaitIdle(m_device);
}

void sdlxvulkan::Application::Implementation::init_system()
{
  // SDL
  //-------------
  // Initialise the system, stop if fails.
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
  {
    throw std::runtime_error("SDL: Initialisation failed.");
  }

  if (SDL_Vulkan_LoadLibrary(nullptr) != 0)
  {
    throw std::runtime_error("SDL: Could not load Vulkan.");
  }

  void* l_getter_address = SDL_Vulkan_GetVkGetInstanceProcAddr();
  if (l_getter_address == nullptr)
  {
    throw std::runtime_error("SDL: Could not get address of vkGetInstanceProcAddr.");
  }

  // Initialise the vulcan getter function
  init_vulkan_get_proc(static_cast<PFN_vkGetInstanceProcAddr>(l_getter_address));

  // Initialise the global vulkan functions.
  init_vulkan_global_functions();

  // Dump the Vulkan version for the loaded library
  uint32_t l_library_version{ 0 };
  if (vkEnumerateInstanceVersion(&l_library_version) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: could not get api version.");
  }
  std::cout << "Found Vulkan version: " << VK_VERSION_MAJOR(l_library_version) << "." << VK_VERSION_MINOR(l_library_version) << "." << VK_VERSION_PATCH(l_library_version) << std::endl; 

  std::cout << "System initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_system()
{
  // Unload SDL Vulkan
  SDL_Vulkan_UnloadLibrary();

  // Quit SDL
  SDL_Quit();
}

void sdlxvulkan::Application::Implementation::init_window()
{
  // SDL Window
  //-------------

  m_window = SDL_CreateWindow("SDL x Vulkan", 100, 100, c_start_width, c_start_height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  if (m_window == nullptr)
  {
    throw std::runtime_error("SDL: Failed to create window.");
  }
  m_window_id = SDL_GetWindowID(m_window);

  int l_width{0};
  int l_height{0};
  SDL_Vulkan_GetDrawableSize(m_window, &l_width, &l_height);

  m_width = static_cast<uint32_t>(l_width);
  m_height = static_cast<uint32_t>(l_height);

  std::cout << "Window initialised: id=" << m_window_id << " w=" << m_width << " h=" << m_height << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_window()
{
  // Destroy the window
  SDL_DestroyWindow(m_window);
}

void sdlxvulkan::Application::Implementation::init_instance()
{
  // Instance
  //-------------

  auto check_valiation_layer_support = []()->bool 
  {
    uint32_t l_layer_count{};
    vkEnumerateInstanceLayerProperties(&l_layer_count, nullptr);

    std::vector<VkLayerProperties> l_available_layers{ l_layer_count };

    vkEnumerateInstanceLayerProperties(&l_layer_count, l_available_layers.data());

    for (const char* layer_name : c_validation_layers) 
    {
      bool l_layer_found = false;

      for (const auto& l_layer_properties : l_available_layers)
      {
        if (strcmp(layer_name, l_layer_properties.layerName) == 0)
        {
          l_layer_found = true;
          break;
        }
      }

      if (!l_layer_found)
      {
        return false;
      }
    }

    return true;
  };


  // Validation layers
  if (c_enable_validation_layers && !check_valiation_layer_support())
  {
    throw std::runtime_error("Vulkan:: Validation layers requested, but not available!");
  }


  // Initialise an application info structure
  // INITIALISE EVERYTHING PROPERLY FOR VULKAN STRUCTS
  VkApplicationInfo l_app_info{};
  l_app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  l_app_info.pNext = NULL;
  l_app_info.pApplicationName = "SDL x Vulkan";
  l_app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  l_app_info.pEngineName = "No Engine";
  l_app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  l_app_info.apiVersion = VK_API_VERSION_1_1;

  // get the number of extensions 
  uint32_t l_extension_count{ 0 };
  if (SDL_Vulkan_GetInstanceExtensions(m_window, &l_extension_count, nullptr) != SDL_TRUE)
  {
    // failed to get extension count...
    throw std::runtime_error("SDL: Could not get Vulkan extension count.");
  }

  // make a vector of nullptr big enough to store the extension names
  std::vector<char const*> l_extension_names{ l_extension_count, nullptr };
  if (SDL_Vulkan_GetInstanceExtensions(m_window, &l_extension_count, l_extension_names.data()) != SDL_TRUE)
  {
    // failed to get all the extension names...
    throw std::runtime_error("SDL: Could not get all Vulkan extension names.");
  }

  if (c_enable_validation_layers)
  {
    l_extension_names.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
    //++l_extension_count;
  }



  std::cout << "SDL Vulkan Extensions:" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  for (auto l_ext : l_extension_names)
  {
    std::cout << l_ext << std::endl;
  }
  std::cout << std::endl;

  // If you want more extensions they get added in here, or after this
  //auto l_swapchain_ext = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
  //l_extension_names.push_back(l_swapchain_ext);


  // Initialise a create info struct.
  // INITIALISE EVERYTHING PROPERLY FOR VULKAN STRUCTS
  VkInstanceCreateInfo l_create_info{};
  l_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  l_create_info.pNext = NULL;
  l_create_info.flags = 0;
  l_create_info.pApplicationInfo = &l_app_info;
  if (c_enable_validation_layers)
  {
    l_create_info.enabledLayerCount = static_cast<uint32_t>(c_validation_layers.size());
    l_create_info.ppEnabledLayerNames = c_validation_layers.data();
  }
  else
  {
    l_create_info.enabledLayerCount = 0;
    l_create_info.ppEnabledLayerNames = NULL;
  }
  l_create_info.enabledExtensionCount = static_cast<uint32_t>(l_extension_names.size());
  l_create_info.ppEnabledExtensionNames = l_extension_names.data();

  if (vkCreateInstance(&l_create_info, nullptr, &m_instance) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create instance.");
  }
    
  // Initialise the intance vulkan functions.
  init_vulkan_instance_functions(m_instance);

  std::cout << "Instance initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_instance()
{
  // Destroy the Vulkan instance.
  // Must have killed all children before reaching this point.
  // Instance can be NULL
  vkDestroyInstance(m_instance, nullptr);
}

void sdlxvulkan::Application::Implementation::init_debug_callback()
{
  if (!c_enable_validation_layers)
  {
    return;
  }
  
  VkDebugReportCallbackCreateInfoEXT l_callback_info {};
  l_callback_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  l_callback_info.pNext = nullptr;
  l_callback_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
  l_callback_info.pfnCallback = debug_callback;
  l_callback_info.pUserData = nullptr;

  if (vkCreateDebugReportCallbackEXT(m_instance, &l_callback_info, nullptr, &m_debug_callback) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to set up debug callback!");
  }
  std::cout << "Debug Callback initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_debug_callback()
{
  if (c_enable_validation_layers)
  {
    vkDestroyDebugReportCallbackEXT(m_instance, m_debug_callback, nullptr);
  }
}

void sdlxvulkan::Application::Implementation::init_physical_device()
{
  // Physical Devices
  //-------------

  uint32_t l_device_count{ 0 };
  if (vkEnumeratePhysicalDevices(m_instance, &l_device_count, nullptr) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Could not get physical device count.");
  }

  std::vector<VkPhysicalDevice> l_devices{};
  l_devices.resize(l_device_count);
  if (vkEnumeratePhysicalDevices(m_instance, &l_device_count, l_devices.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Could not get all physical device info");
  }

  // Output the properties for all found devices
  std::cout << "Device Count = " << l_device_count << std::endl;

  //auto l_vkGetPhysicalDeviceProperties = (PFN_vkGetPhysicalDeviceProperties)(m_get_instance_func(m_instance, "vkGetPhysicalDeviceProperties"));

  for (std::size_t l_index = 0, l_end = l_devices.size(); l_index != l_end; ++l_index)
  {
    VkPhysicalDeviceProperties l_properties{};

    vkGetPhysicalDeviceProperties(l_devices[l_index], &l_properties);

    std::cout
      << "Device Index: " << l_index << std::endl
      // got to unpack this....
      << "API Version: " << VK_VERSION_MAJOR(l_properties.apiVersion) << "." << VK_VERSION_MINOR(l_properties.apiVersion) << "." << VK_VERSION_PATCH(l_properties.apiVersion) << std::endl
      << "Driver Version: " << VK_VERSION_MAJOR(l_properties.driverVersion) << "." << VK_VERSION_MINOR(l_properties.driverVersion) << "." << VK_VERSION_PATCH(l_properties.driverVersion) << std::endl
      //<< "Driver Version: " << l_properties.driverVersion << std::endl
      << "Vendor ID: " << l_properties.vendorID << std::endl
      << "Device ID: " << l_properties.deviceID << std::endl
      << "Device Name: " << l_properties.deviceName << std::endl
      << std::endl;
  }

  // Select a device.
  // For now just pick the first. Probably want to check for capabilities here.

  // Assume only one device, the first...
  assert(l_device_count == 1);
  assert(l_devices.size() == 1);

  // Select the physical device
  m_physical_device = l_devices[0];

  // Stash its properties
  vkGetPhysicalDeviceProperties(l_devices[0], &m_physical_device_properties);

  // Stash its memory properties
  vkGetPhysicalDeviceMemoryProperties(l_devices[0], &m_physical_device_mem_properties);



  // For giggles, query and output the device extensions
  uint32_t l_extension_count{0};
  if (vkEnumerateDeviceExtensionProperties(m_physical_device, nullptr, &l_extension_count, nullptr)!= VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Could not get physical device extension count.");
  }
  std::vector<VkExtensionProperties> l_extension_properties{};
  l_extension_properties.resize(l_extension_count);
  if (vkEnumerateDeviceExtensionProperties(m_physical_device, nullptr, &l_extension_count, l_extension_properties.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Could not get physical device extensions.");
  }

  std::cout << "Device Extensions:" << std::endl;
  for (auto const& l_extension : l_extension_properties)
  {
    std::cout << "\"" << l_extension.extensionName << "\" version=\"" << l_extension.specVersion << "\"" << std::endl;
  }
  std::cout << std::endl;

  // Proper device selection will require looking at these to find any required - like the swapchain


  std::cout << "Physical Device initialised, count = " << l_devices.size() << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_physical_device()
{
  // Don't need to do anything
}

void sdlxvulkan::Application::Implementation::init_queue_families()
{
  // Queue Families - Graphics and Presenting
  //-------------
  // go through all the queues on the device and look for one that can do graphics 
  // and presenting. If one isn't found, find seperate ones for each. The indexes
  // will be stashed.

  // - Have 2 index that start invalid.
  // - search for one that matches needed
  //  - fail if fails
  // - search for the other
  //  - fail if fails
  // - starting at greater index, search remaining for one with both
  //  - if found set both to that
  //  - else do nothing, alreadyt have indexes

  // Get the queue families count
  uint32_t l_qf_count{ 0 };
  vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &l_qf_count, nullptr);
  assert(l_qf_count >= 1);

  // Now get their details
  m_queue_familiy_properties.resize(l_qf_count);
  vkGetPhysicalDeviceQueueFamilyProperties(m_physical_device, &l_qf_count, m_queue_familiy_properties.data());
  assert(l_qf_count >= 1);
  assert(m_queue_familiy_properties.size() >= 1);

  std::cout << "Queue Family Count on device 0 = " << l_qf_count << std::endl;

  //------------------------------------------------------------------------------------------------------------------------
  // Find a graphics queue
  //-------------
  // Look through the queue families to see if one has the right flag.
  for (uint32_t l_index = 0, l_end = static_cast<uint32_t>(m_queue_familiy_properties.size()); l_index < l_end; l_index++)
  {
    if (m_queue_familiy_properties[l_index].queueFlags & VK_QUEUE_GRAPHICS_BIT)
    {
      // Set the index of the found queue so we can use it
      m_graphics_qf_index = l_index;
      break;
    }
  }
  // We better have found one
  if (m_graphics_qf_index == UINT32_MAX)
  {
    throw std::runtime_error("Vulkan: Failed to find a command queue that supports graphics.");
  }

  //------------------------------------------------------------------------------------------------------------------------


  std::cout << "Queue Families initialised, count = " << m_queue_familiy_properties.size() << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_queue_families()
{
  // Do nothing
}

void sdlxvulkan::Application::Implementation::init_logical_device()
{
  // Logical Device
  //-------------


  float l_queue_priorities[1] = { 0.0 };
  // Configure our queue info
  VkDeviceQueueCreateInfo l_queue_info{};
  l_queue_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  l_queue_info.pNext = NULL;
  l_queue_info.flags = 0; //?
  l_queue_info.queueFamilyIndex = m_graphics_qf_index;
  l_queue_info.queueCount = 1;
  l_queue_info.pQueuePriorities = l_queue_priorities;

  char const* l_device_extensions[1]{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

  // Make some device info
  VkDeviceCreateInfo l_device_info = {};
  l_device_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  l_device_info.pNext = NULL;
  l_device_info.queueCreateInfoCount = 1;
  l_device_info.pQueueCreateInfos = &l_queue_info;
  l_device_info.enabledExtensionCount = 1;
  l_device_info.ppEnabledExtensionNames = l_device_extensions;
  l_device_info.enabledLayerCount = 0;
  l_device_info.ppEnabledLayerNames = NULL;
  l_device_info.pEnabledFeatures = NULL;


  // Create the device
  if (vkCreateDevice(m_physical_device, &l_device_info, NULL, &m_device) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create logical device.");
  }

  // Initialise the device vulkan functions.
  init_vulkan_device_functions(m_device);

  std::cout << "Logical Device initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_logical_device()
{
  // Destroy the logical device.
  vkDestroyDevice(m_device, nullptr);
}


void sdlxvulkan::Application::Implementation::init_command_pool()
{
  // Command Buffer Pool
  //-------------

  // Initialise some creation info
  VkCommandPoolCreateInfo l_command_pool_info{};
  l_command_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  l_command_pool_info.pNext = NULL;
  l_command_pool_info.flags = 0; // optional
                                 //l_command_pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;             // hint that this is often used.
                                 //l_command_pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;  // allow buffers to be rerecorded individually (uh?)
  l_command_pool_info.queueFamilyIndex = m_graphics_qf_index;

  // Make the pool using the device.
  if (vkCreateCommandPool(m_device, &l_command_pool_info, nullptr, &m_command_pool) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create command pool.");
  }
  std::cout << "Command Pool initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_command_pool()
{
  // Destroy the command pool
  vkDestroyCommandPool(m_device, m_command_pool, nullptr);
}


void sdlxvulkan::Application::Implementation::init_vertex_buffer()
{
  VkDeviceSize l_buffer_size = sizeof(c_vertices[0]) * c_vertices.size();
    
  // Staging buffer - Temporary object
  VkBuffer l_staging_buffer{};
  VkDeviceMemory l_staging_buffer_memory{};
  VkBufferUsageFlags l_staging_buffer_usage_flags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags l_staging_buffer_property_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  create_buffer(l_buffer_size, l_staging_buffer_usage_flags, l_staging_buffer_property_flags, l_staging_buffer, l_staging_buffer_memory);
  
  // Map data to it
  void *l_staging_data{ nullptr };
  if (vkMapMemory(m_device, l_staging_buffer_memory, 0, l_buffer_size, 0, &l_staging_data) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Vertex Buffer: Failed to map the staging buffer." };
  }

  //memcpy(l_data, g_vertex_buffer_solid_face_colors_data, sizeof(g_vertex_buffer_solid_face_colors_data));
  memcpy(l_staging_data, c_vertices.data(), static_cast<size_t>(l_buffer_size));

  // unmap the memory after we have used it.
  vkUnmapMemory(m_device, l_staging_buffer_memory);
  

  // Vertex buffer
  VkBufferUsageFlags l_vertex_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  VkMemoryPropertyFlags l_vertex_property_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  create_buffer(l_buffer_size, l_vertex_usage_flags, l_vertex_property_flags, m_vertex_buffer, m_vertex_buffer_memory);
     
  copy_buffer(l_staging_buffer, m_vertex_buffer, l_buffer_size);

  vkDestroyBuffer(m_device, l_staging_buffer, nullptr);
  vkFreeMemory(m_device, l_staging_buffer_memory, nullptr);    
}

void sdlxvulkan::Application::Implementation::quit_vertex_buffer()
{
  vkDestroyBuffer(m_device, m_vertex_buffer, nullptr);
  vkFreeMemory(m_device, m_vertex_buffer_memory, nullptr);
}

void sdlxvulkan::Application::Implementation::init_index_buffer()
{
  // Like the vertex buffer but with the index data.
  VkDeviceSize l_buffer_size = sizeof(c_indices[0]) * c_indices.size();

  // Staging buffer - Temporary object
  VkBuffer l_staging_buffer{};
  VkDeviceMemory l_staging_buffer_memory{};
  VkBufferUsageFlags l_staging_buffer_usage_flags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags l_staging_buffer_property_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

  create_buffer(l_buffer_size, l_staging_buffer_usage_flags, l_staging_buffer_property_flags, l_staging_buffer, l_staging_buffer_memory);

  // Map data to it
  void *l_staging_data{ nullptr };
  if (vkMapMemory(m_device, l_staging_buffer_memory, 0, l_buffer_size, 0, &l_staging_data) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Index Buffer: Failed to map the staging buffer." };
  }

  //memcpy(l_data, g_vertex_buffer_solid_face_colors_data, sizeof(g_vertex_buffer_solid_face_colors_data));
  memcpy(l_staging_data, c_indices.data(), static_cast<size_t>(l_buffer_size));

  // unmap the memory after we have used it.
  vkUnmapMemory(m_device, l_staging_buffer_memory);
  
  // Index buffer
  VkBufferUsageFlags l_index_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  VkMemoryPropertyFlags l_index_property_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  create_buffer(l_buffer_size, l_index_usage_flags, l_index_property_flags, m_index_buffer, m_index_buffer_memory);

  copy_buffer(l_staging_buffer, m_index_buffer, l_buffer_size);

  vkDestroyBuffer(m_device, l_staging_buffer, nullptr);
  vkFreeMemory(m_device, l_staging_buffer_memory, nullptr);
}

void sdlxvulkan::Application::Implementation::quit_index_buffer()
{
  vkDestroyBuffer(m_device, m_index_buffer, nullptr);
  vkFreeMemory(m_device, m_index_buffer_memory, nullptr);
}

void sdlxvulkan::Application::Implementation::init_uniform_buffer()
{
  VkDeviceSize l_buffer_size = sizeof(Uniform_Buffer_Object);
  VkBufferUsageFlags l_uniform_usage_flags = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  VkMemoryPropertyFlags l_uniform_property_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  create_buffer(l_buffer_size, l_uniform_usage_flags, l_uniform_property_flags, m_uniform_buffer, m_uniform_buffer_memory);
}

void sdlxvulkan::Application::Implementation::quit_uniform_buffer()
{
  vkDestroyBuffer(m_device, m_uniform_buffer, nullptr);
  vkFreeMemory(m_device, m_uniform_buffer_memory, nullptr);
}

void sdlxvulkan::Application::Implementation::init_descriptor_pool()
{
  VkDescriptorPoolSize l_pool_size{};
  l_pool_size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  l_pool_size.descriptorCount = 1;

  VkDescriptorPoolCreateInfo l_pool_info{};
  l_pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  l_pool_info.pNext = nullptr;
  l_pool_info.maxSets = 1;
  l_pool_info.flags = 0;
  l_pool_info.poolSizeCount = 1;
  l_pool_info.pPoolSizes = &l_pool_size;
  
  if (vkCreateDescriptorPool(m_device, &l_pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create descriptor pool.");
  }
}

void sdlxvulkan::Application::Implementation::quit_descriptor_pool()
{
  vkDestroyDescriptorPool(m_device, m_descriptor_pool, nullptr);
}

void sdlxvulkan::Application::Implementation::init_descriptor_set()
{
  // Depends:
  // m_device
  // m_descriptor_pool
  // m_descriptor_set_layout

  VkDescriptorSetLayout l_layouts[]{ m_descriptor_set_layout };
  VkDescriptorSetAllocateInfo l_alloc_info = {};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.descriptorPool = m_descriptor_pool;
  l_alloc_info.descriptorSetCount = 1;
  l_alloc_info.pSetLayouts = l_layouts;

  if (vkAllocateDescriptorSets(m_device, &l_alloc_info, &m_descriptor_set) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to allocate descriptor set.");
  }

  VkDescriptorBufferInfo l_buffer_info{};
  l_buffer_info.buffer = m_uniform_buffer;
  l_buffer_info.offset = 0;
  l_buffer_info.range = sizeof(Uniform_Buffer_Object);

  VkWriteDescriptorSet l_descriptor_write {};
  l_descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  l_descriptor_write.pNext = nullptr;
  l_descriptor_write.dstSet = m_descriptor_set;
  l_descriptor_write.dstBinding = 0;
  l_descriptor_write.dstArrayElement = 0;
  l_descriptor_write.descriptorCount = 1;
  l_descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  l_descriptor_write.pImageInfo = nullptr; // optional
  l_descriptor_write.pBufferInfo = &l_buffer_info;
  l_descriptor_write.pTexelBufferView = nullptr; // optional

  vkUpdateDescriptorSets(m_device, 1, &l_descriptor_write, 0, nullptr);
}

void sdlxvulkan::Application::Implementation::quit_descriptor_set()
{
  // destroyed when m_descriptor_pool is destroyed
}

void sdlxvulkan::Application::Implementation::init_shader_modules()
{
  // Shaders
  //-------------
  // Going to deviate from the example in a big way here. In it they make the shaders entirely in the program,
  // but we are going to use externally compiled ones because it won't need to include god knows what to do,
  // and will probably match what we'll do in other projects.

  // Have 2 shaders that are built and copied to the target directory:
  // frag.spv
  // vert.spv

  VkShaderModuleCreateInfo l_module_Info{};

  auto make_shader_module = [this](VkDevice a_device, std::string const& a_filepath) -> VkShaderModule
  {
    auto l_path = get_shader_filepath(this->m_args[0], a_filepath);
    auto l_spv_data = get_file_bytes(l_path);

    VkShaderModuleCreateInfo l_module_info;
    l_module_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    l_module_info.pNext = NULL;
    l_module_info.flags = 0;
    l_module_info.codeSize = l_spv_data.size();
    l_module_info.pCode = reinterpret_cast<uint32_t const*>(l_spv_data.data());

    VkShaderModule l_result{};
    if (vkCreateShaderModule(a_device, &l_module_info, nullptr, &l_result) != VK_SUCCESS)
    {
      throw std::runtime_error{ std::string{ "Vulkan: Failed create shader module: " } +a_filepath };
    }
    std::cout << "Created shader module for " << l_path << std::endl;
    return l_result;
  };

  // Make the vertex shader
  char const c_vertex_shader_file[]{ "shader.vert.spv" };

  m_vertex_shader_module = make_shader_module(m_device, c_vertex_shader_file);


  // Make the fragment shader
  char const c_fragment_shader_file[]{ "shader.frag.spv" };

  m_fragment_shader_module = make_shader_module(m_device, c_fragment_shader_file);


  m_fragment_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  m_fragment_shader_stage_info.pNext = NULL;
  m_fragment_shader_stage_info.flags = 0;
  m_fragment_shader_stage_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  m_fragment_shader_stage_info.module = m_fragment_shader_module;
  m_fragment_shader_stage_info.pName = "main";
  m_fragment_shader_stage_info.pSpecializationInfo = NULL;

  m_vertex_shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  m_vertex_shader_stage_info.pNext = NULL;
  m_vertex_shader_stage_info.flags = 0;
  m_vertex_shader_stage_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
  m_vertex_shader_stage_info.module = m_vertex_shader_module;
  m_vertex_shader_stage_info.pName = "main";
  m_vertex_shader_stage_info.pSpecializationInfo = NULL;

  // Pack them
  m_shader_stage_infos[0] = m_fragment_shader_stage_info;
  m_shader_stage_infos[1] = m_vertex_shader_stage_info;

  std::cout << "Shaders initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_shader_modules()
{
  // Destroy the shaders
  vkDestroyShaderModule(m_device, m_fragment_shader_module, nullptr);
  vkDestroyShaderModule(m_device, m_vertex_shader_module, nullptr);
}

void sdlxvulkan::Application::Implementation::init_graphics_queue()
{
  vkGetDeviceQueue(m_device, m_graphics_qf_index, 0, &m_graphics_queue);

  std::cout << "Graphics Queue initialised, index = " << m_graphics_qf_index << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_graphics_queue()
{
  // Do nothing
}

void sdlxvulkan::Application::Implementation::init_surface()
{
  // Surface
  //-------------

  if (SDL_Vulkan_CreateSurface(m_window, m_instance, &m_surface) != SDL_TRUE)
  {
    throw std::runtime_error("SDL: Failed to create a Vulkan surface.");
  }
  std::cout << "Surface initialised" << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_surface()
{
  // Destroy the Vulkan surface.
  vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

void sdlxvulkan::Application::Implementation::init_present_queue()
{
  // Presenting
  //-------------
  //auto l_vkGetPhysicalDeviceSurfaceSupportKHR = (PFN_vkGetPhysicalDeviceSurfaceSupportKHR)(m_get_instance_func(m_instance, "vkGetPhysicalDeviceSurfaceSupportKHR"));


  // Look through the queue families to see if one has the right flag.
  auto const l_qf_count = static_cast<uint32_t>(m_queue_familiy_properties.size());


  VkBool32 l_qf_can_present{ VK_FALSE };
  for (uint32_t i = 0; i < l_qf_count; i++)
  {
    // find out if it can...
    vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device, i, m_surface, &l_qf_can_present);
    if (l_qf_can_present == VK_TRUE)
    {
      // Set the index of the found queue so we can use it
      m_present_qf_index = i;
      break;
    }
  }
  // We better have found one
  if (m_present_qf_index == UINT32_MAX)
  {
    throw std::runtime_error("Vulkan: Failed to find a command queue that supports presenting.");
  }
  //assert(l_qf_count >= 1);

  // If not already the same, search the rest starting at the latter
  if (m_graphics_qf_index != m_present_qf_index)
  {
    for (uint32_t i = (m_graphics_qf_index < m_present_qf_index ? m_present_qf_index : m_graphics_qf_index); i != l_qf_count; ++i)
    {
      vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device, i, m_surface, &l_qf_can_present);
      if ((l_qf_can_present == VK_TRUE) && (m_queue_familiy_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT))
      {
        m_graphics_qf_index = i;
        m_present_qf_index = i;
        break;
      }
    }
  }
  //assert(l_qf_count >= 1);

  std::cout << "Present Queue = " << m_present_qf_index << std::endl;

  // Do we really need to bother with this check?
  // Could just get the queue regardless
  if (m_graphics_qf_index == m_present_qf_index)
  {
    m_present_queue = m_graphics_queue;
  }
  else
  {
    vkGetDeviceQueue(m_device, m_present_qf_index, 0, &m_present_queue);
  }
  std::cout << "Present Queue initialised, index = " << m_present_qf_index << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_present_queue()
{
  // Do nothing
}

void sdlxvulkan::Application::Implementation::init_swapchain(VkSwapchainKHR a_old_swapchain)
{
  // Surface Capabilities
  //-------------

  // Get all the things we will need to look at to configure the swapchain

  // Get the capabilities
  if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physical_device, m_surface, &m_swapchain_surface_cababilites) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface capabilites.");
  }


  // Get the formats that can be used with this device/surface combo.
  uint32_t l_surface_format_count{ 0 };
  if (vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface, &l_surface_format_count, NULL) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface format count.");
  }

  m_swapchain_surface_formats.resize(l_surface_format_count);
  if (vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface, &l_surface_format_count, m_swapchain_surface_formats.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface formats.");
  }


  // Get the present modes
  uint32_t l_present_mode_count{ 0 };
  if (vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, m_surface, &l_present_mode_count, NULL) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface present mode count.");
  }

  m_swapchain_present_modes.resize(l_present_mode_count);
  if (vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, m_surface, &l_present_mode_count, m_swapchain_present_modes.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface present modes.");
  }


  // Use these to find out if the selected device can actually do what we want here


  // These next 3 blocks are descrete operations to determine settings.
  //-------------

  {
    // Select a Format
    //-------------

    // As per documentation we should get at least VK_FORMAT_UNDEFINED back
    if (m_swapchain_surface_formats.empty())
    {
      throw std::runtime_error("Vulkan: No surface formats supplied, there should be at least one.");
    }

    // Select a Format
    // the other tutorial pays attention to more of the VkSurfaceFormatKHR struct...

    // If only an undefined one is returned then nothing is prefered and pick one
    // Otherwise select a format
    if (m_swapchain_surface_formats.size() == 1 && m_swapchain_surface_formats[0].format == VK_FORMAT_UNDEFINED)
    {
      m_swapchain_format = VK_FORMAT_B8G8R8A8_UNORM;
    }
    else
    {
      // currently just pick the first.
      m_swapchain_format = m_swapchain_surface_formats[0].format;
    }
  }

  //-------------
  
  {
    // Select Present Mode
    //-------------

    // Start with this mode
    m_swapchain_present_mode = VK_PRESENT_MODE_FIFO_KHR;

    for (auto const& l_present_mode : m_swapchain_present_modes)
    {
      if (m_swapchain_present_mode == VK_PRESENT_MODE_MAILBOX_KHR) // if we find this it is our prefered mode
      {
        m_swapchain_present_mode = l_present_mode;
        break;
      }
      else if (l_present_mode == VK_PRESENT_MODE_IMMEDIATE_KHR) // if we find this set to it but keep looking
      {
        m_swapchain_present_mode = l_present_mode;
      }
    }
  }

  //-------------

  {
    // Configure Extent
    //-------------

    // width and height are either both 0xFFFFFFFF, or both not 0xFFFFFFFF.
    if (m_swapchain_surface_cababilites.currentExtent.width == 0xFFFFFFFF)
    {
      // If the surface size is undefined, the size is set to the size of the images requested.
      m_swapchain_extent.width = m_width;
      m_swapchain_extent.height = m_height;

      // If the requested sizes are smaller than the device can go, we clamp to the minimum values.
      if (m_swapchain_extent.width < m_swapchain_surface_cababilites.minImageExtent.width)
      {
        m_swapchain_extent.width = m_swapchain_surface_cababilites.minImageExtent.width;
      }
      else if (m_swapchain_extent.width > m_swapchain_surface_cababilites.maxImageExtent.width)
      {
        m_swapchain_extent.width = m_swapchain_surface_cababilites.maxImageExtent.width;
      }

      if (m_swapchain_extent.height < m_swapchain_surface_cababilites.minImageExtent.height)
      {
        m_swapchain_extent.height = m_swapchain_surface_cababilites.minImageExtent.height;
      }
      else if (m_swapchain_extent.height > m_swapchain_surface_cababilites.maxImageExtent.height)
      {
        m_swapchain_extent.height = m_swapchain_surface_cababilites.maxImageExtent.height;
      }
    }
    else
    {
      // If the surface size is defined, the swap chain size must match
      m_swapchain_extent = m_swapchain_surface_cababilites.currentExtent;
    }
  }
  //-------------


  // Determine the number of VkImage's to use in the swap chain.
  // We need to acquire only 1 presentable image at at time.
  // Asking for minImageCount images ensures that we can acquire
  // 1 presentable image as long as we present it before attempting
  // to acquire another.
  m_swapchain_image_count = m_swapchain_surface_cababilites.minImageCount + 1;
  //std::cout << "Swapchain image count = " << l_desired_number_of_swap_chain_images << std::endl;

  VkSurfaceTransformFlagBitsKHR l_pre_transform{};
  if ((m_swapchain_surface_cababilites.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) > 0)
  {
    l_pre_transform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  }
  else
  {
    l_pre_transform = m_swapchain_surface_cababilites.currentTransform;
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
    if (m_swapchain_surface_cababilites.supportedCompositeAlpha & l_composite_alpha_flags[i])
    {
      l_composite_alpha = l_composite_alpha_flags[i];
      break;
    }
  }
  */
  VkCompositeAlphaFlagBitsKHR l_composite_alpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

  // Swapchain Creation
  //-------------
  // Reordered from the tutorial to the order in the documentation.

  VkSwapchainCreateInfoKHR l_swapchain_info = {};
  l_swapchain_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  l_swapchain_info.pNext = nullptr;
  l_swapchain_info.flags = 0;
  l_swapchain_info.surface = m_surface;
  l_swapchain_info.minImageCount = m_swapchain_image_count;
  l_swapchain_info.imageFormat = m_swapchain_format;
  l_swapchain_info.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
  l_swapchain_info.imageExtent = m_swapchain_extent;
  l_swapchain_info.imageArrayLayers = 1;
  l_swapchain_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  uint32_t l_queue_familiy_indicies[2] = { m_graphics_qf_index, m_present_qf_index };

  if (m_graphics_qf_index != m_present_qf_index)
  {
    // If the graphics and present queues are from different queue families,
    // we either have to explicitly transfer ownership of images between
    // the queues, or we have to create the swapchain with imageSharingMode
    // as VK_SHARING_MODE_CONCURRENT
    l_swapchain_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    l_swapchain_info.queueFamilyIndexCount = 2;
    l_swapchain_info.pQueueFamilyIndices = l_queue_familiy_indicies;
  }
  else
  {
    l_swapchain_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    l_swapchain_info.queueFamilyIndexCount = 0; // does not appliy in this mode
    l_swapchain_info.pQueueFamilyIndices = NULL; // does not appliy in this mode
  }

  l_swapchain_info.preTransform = l_pre_transform;
  l_swapchain_info.compositeAlpha = l_composite_alpha;
  l_swapchain_info.presentMode = m_swapchain_present_mode;
  l_swapchain_info.clipped = VK_TRUE;
  l_swapchain_info.oldSwapchain = a_old_swapchain;


  // Now do the actual making.
  VkResult l_result = vkCreateSwapchainKHR(m_device, &l_swapchain_info, nullptr, &m_swapchain);
  if (l_result != VK_SUCCESS)
  {
    throw std::runtime_error{ std::string{ "Vulkan: Failed to create swapchain. " } +vulkan_result_string(l_result) };
  }


  uint32_t l_actual_image_count{ 0 };
  if (vkGetSwapchainImagesKHR(m_device, m_swapchain, &l_actual_image_count, nullptr) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get swapchain images." };
  }

  std::cout << "requested = " << m_swapchain_image_count << std::endl;
  std::cout << "actual = " << m_swapchain_image_count << std::endl;

  // Now make the images. These have no special cleanup.
  m_swapchain_images.resize(m_swapchain_image_count);
  if (vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_swapchain_image_count, m_swapchain_images.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get swapchain images." };
  }

  std::cout << "Swapchain Image initialised, count = " << m_swapchain_images.size() << std::endl;
}

void sdlxvulkan::Application::Implementation::recreate_swapchain()
{
  vkDeviceWaitIdle(m_device);

  quit_command_buffers();
  quit_framebuffer();
  quit_pipeline();
  //quit_descriptor_set_layout();
  quit_render_pass();
  quit_swapchain_image_views();

  VkSwapchainKHR l_old_swapchain{ m_swapchain };
  init_swapchain(l_old_swapchain); 
  vkDestroySwapchainKHR(m_device, l_old_swapchain, nullptr);

  init_swapchain_image_views();
  init_render_pass();
  //init_descriptor_set_layout();
  init_pipeline();
  init_framebuffer();
  init_command_buffers();

  do_commands();
}

void sdlxvulkan::Application::Implementation::quit_swapchain()
{
  // Destroy the swapchain
  vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
}

void sdlxvulkan::Application::Implementation::init_swapchain_image_views()
{
  // Swapchain Images
  //-------------

  //if (vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_swapchain_image_count, NULL) != VK_SUCCESS)
  //{
   // throw std::runtime_error{ "Vulkan: Failed to get swapchain image count." };
  //}

  //std::cout << "Swapchain image count = " << m_swapchain_image_count << std::endl;


  // To get 
  m_swapchain_image_views.resize(m_swapchain_images.size());

  for (std::size_t l_index = 0; l_index != m_swapchain_images.size(); l_index++)
  {
    VkImageViewCreateInfo l_color_image_view = {};
    l_color_image_view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    l_color_image_view.pNext = NULL;
    l_color_image_view.flags = 0;
    l_color_image_view.image = m_swapchain_images[l_index];
    l_color_image_view.viewType = VK_IMAGE_VIEW_TYPE_2D;
    l_color_image_view.format = m_swapchain_format;
    l_color_image_view.components.r = VK_COMPONENT_SWIZZLE_R;
    l_color_image_view.components.g = VK_COMPONENT_SWIZZLE_G;
    l_color_image_view.components.b = VK_COMPONENT_SWIZZLE_B;
    l_color_image_view.components.a = VK_COMPONENT_SWIZZLE_A;
    l_color_image_view.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    l_color_image_view.subresourceRange.baseMipLevel = 0;
    l_color_image_view.subresourceRange.levelCount = 1;
    l_color_image_view.subresourceRange.baseArrayLayer = 0;
    l_color_image_view.subresourceRange.layerCount = 1;

    if (vkCreateImageView(m_device, &l_color_image_view, nullptr, &m_swapchain_image_views[l_index]) != VK_SUCCESS)
    {
      throw std::runtime_error{ "Vulkan: Failed to get swapchain image views." };
    }
  }

  std::cout << "Swapchain Image Views initialised, count = " << m_swapchain_image_views.size() << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_swapchain_image_views()
{
  // Destroy the swapchain image views
  for (auto const& l_image_view : m_swapchain_image_views)
  {
    vkDestroyImageView(m_device, l_image_view, nullptr);
  }
}

void sdlxvulkan::Application::Implementation::init_render_pass()
{
  VkAttachmentDescription l_colour_attachment{};
  l_colour_attachment.flags = 0;
  l_colour_attachment.format = m_swapchain_format;
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

  VkSubpassDescription  l_subpass_desc{};
  l_subpass_desc.flags = 0;
  l_subpass_desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  l_subpass_desc.inputAttachmentCount = 0;
  l_subpass_desc.pInputAttachments = nullptr;
  l_subpass_desc.colorAttachmentCount = 1;
  l_subpass_desc.pColorAttachments = &l_colour_attachment_ref;
  l_subpass_desc.pResolveAttachments = nullptr;
  l_subpass_desc.pDepthStencilAttachment = nullptr;
  l_subpass_desc.preserveAttachmentCount = 0;
  l_subpass_desc.pPreserveAttachments = nullptr;

  VkSubpassDependency l_dependency {};
  l_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  l_dependency.dstSubpass = 0;
  l_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  l_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  l_dependency.srcAccessMask = 0;
  l_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
  l_dependency.dependencyFlags = 0;


  VkRenderPassCreateInfo l_render_pass_info = {};
  l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  l_render_pass_info.pNext = NULL;
  l_render_pass_info.flags = 0;
  l_render_pass_info.attachmentCount = 1;
  l_render_pass_info.pAttachments = &l_colour_attachment;
  l_render_pass_info.subpassCount = 1;
  l_render_pass_info.pSubpasses = &l_subpass_desc;
  l_render_pass_info.dependencyCount = 1;
  l_render_pass_info.pDependencies = &l_dependency;


  if (vkCreateRenderPass(m_device, &l_render_pass_info, nullptr, &m_render_pass) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create render pass." };
  }

  std::cout << "Render Pass initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_render_pass()
{
  vkDestroyRenderPass(m_device, m_render_pass, nullptr);
}

void sdlxvulkan::Application::Implementation::init_descriptor_set_layout()
{
  VkDescriptorSetLayoutBinding l_ubo_layout_binding{};
  l_ubo_layout_binding.binding = 0;
  l_ubo_layout_binding.descriptorCount = 1;
  l_ubo_layout_binding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  l_ubo_layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  l_ubo_layout_binding.pImmutableSamplers = nullptr; // not relevent here
  
  VkDescriptorSetLayoutCreateInfo l_layout_info{};
  l_layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  l_layout_info.pNext = nullptr;
  l_layout_info.flags = 0;
  l_layout_info.bindingCount = 1;
  l_layout_info.pBindings = &l_ubo_layout_binding;

  if (vkCreateDescriptorSetLayout(m_device, &l_layout_info, nullptr, &m_descriptor_set_layout) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create descriptor set layout.");
  }
}

void sdlxvulkan::Application::Implementation::quit_descriptor_set_layout()
{
  vkDestroyDescriptorSetLayout(m_device, m_descriptor_set_layout, nullptr);
}


void sdlxvulkan::Application::Implementation::init_pipeline()
{
  // Pipeline Stuff
  //-------------

  // Vertex Input
  auto l_binding_description = Vertex::get_binding_description();
  auto l_attribute_descriptions = Vertex::get_attribute_descriptions();

  VkPipelineVertexInputStateCreateInfo l_vertex_input_state{};
  l_vertex_input_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  l_vertex_input_state.pNext = NULL;
  l_vertex_input_state.flags = 0;
  //l_vertex_input_state.vertexBindingDescriptionCount = 0;
  //l_vertex_input_state.pVertexBindingDescriptions = nullptr;
  //l_vertex_input_state.vertexAttributeDescriptionCount = 0;
  //l_vertex_input_state.pVertexAttributeDescriptions = nullptr;
  l_vertex_input_state.vertexBindingDescriptionCount = 1;
  l_vertex_input_state.pVertexBindingDescriptions = &l_binding_description; // optional
  l_vertex_input_state.vertexAttributeDescriptionCount = 2;
  l_vertex_input_state.pVertexAttributeDescriptions = l_attribute_descriptions.data(); // optional


  //Input Assembly

  VkPipelineInputAssemblyStateCreateInfo l_input_assembly_state{};
  l_input_assembly_state.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  l_input_assembly_state.pNext = NULL;
  l_input_assembly_state.flags = 0;
  l_input_assembly_state.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  l_input_assembly_state.primitiveRestartEnable = VK_FALSE;


  // Viewport
  m_viewport.x = 0.0f;
  m_viewport.y = 0.0f;
  m_viewport.width = static_cast<float>(m_swapchain_extent.width);
  m_viewport.height = static_cast<float>(m_swapchain_extent.height);
  m_viewport.minDepth = 0.0f;
  m_viewport.maxDepth = 1.0f;

  //vkCmdSetViewport(m_command_buffer, 0, m_num_viewports, &m_viewport);

  // Scissors
  m_scissor.extent = m_swapchain_extent;
  m_scissor.offset = { 0,0 };

  //vkCmdSetScissor(m_command_buffer, 0, m_num_scissors, &m_scissor);
  
  VkPipelineViewportStateCreateInfo l_viewport_state{};
  l_viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  l_viewport_state.pNext = NULL;
  l_viewport_state.flags = 0;
  l_viewport_state.viewportCount = 1;
  l_viewport_state.pViewports = &m_viewport; // beware array pointer
  l_viewport_state.scissorCount = 1;
  l_viewport_state.pScissors = &m_scissor; // beware array pointer


  // Rasterizer

  VkPipelineRasterizationStateCreateInfo l_rasterization_state{};
  l_rasterization_state.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  l_rasterization_state.pNext = NULL;
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
  l_multisample_state.pNext = NULL;
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
  l_colour_blend_state.pNext = NULL;
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

  // Need to set these if we want to cahnge the few things that can be changed, like
  // the viewport size, without having to remake the entire pipeline
  
  VkDynamicState l_dynamic_states[] = 
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_LINE_WIDTH
  };

  VkPipelineDynamicStateCreateInfo l_dynamic_state = {};
  l_dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  l_dynamic_state.pNext = NULL;
  l_dynamic_state.dynamicStateCount = 2;
  l_dynamic_state.pDynamicStates = l_dynamic_states;

  
  // Pipeline layout
  VkPipelineLayoutCreateInfo l_pipeline_layout_info{};
  l_pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  l_pipeline_layout_info.pNext = NULL;
  l_pipeline_layout_info.flags = 0;
  l_pipeline_layout_info.setLayoutCount = 1;
  l_pipeline_layout_info.pSetLayouts = &m_descriptor_set_layout;
  l_pipeline_layout_info.pushConstantRangeCount = 0;
  l_pipeline_layout_info.pPushConstantRanges = nullptr;

  if (vkCreatePipelineLayout(m_device, &l_pipeline_layout_info, nullptr, &m_pipeline_layout) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create pipeline layout." };
  }
  
  // Pipeline  
  VkGraphicsPipelineCreateInfo l_pipeline_info{};
  l_pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  l_pipeline_info.pNext = NULL;
  l_pipeline_info.flags = 0;
  l_pipeline_info.stageCount = 2;
  l_pipeline_info.pStages = m_shader_stage_infos.data();
  l_pipeline_info.pVertexInputState = &l_vertex_input_state;
  l_pipeline_info.pInputAssemblyState = &l_input_assembly_state;
  l_pipeline_info.pTessellationState = NULL;
  l_pipeline_info.pViewportState = &l_viewport_state;
  l_pipeline_info.pRasterizationState = &l_rasterization_state;
  l_pipeline_info.pMultisampleState = &l_multisample_state;
  l_pipeline_info.pDepthStencilState = nullptr;//&l_depth_stencil_state;
  l_pipeline_info.pColorBlendState = &l_colour_blend_state;
  l_pipeline_info.pDynamicState = nullptr;// &l_dynamic_state;// not using right now
  l_pipeline_info.layout = m_pipeline_layout;
  l_pipeline_info.renderPass = m_render_pass;
  l_pipeline_info.subpass = 0;
  l_pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // optional
  l_pipeline_info.basePipelineIndex = -1; // optional
  

  if(vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &l_pipeline_info, nullptr, &m_pipeline) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create graphics pipeline." };
  }
  std::cout << "Pipeline initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_pipeline()
{
  vkDestroyPipeline(m_device, m_pipeline, nullptr);
  vkDestroyPipelineLayout(m_device, m_pipeline_layout, nullptr);
}

void sdlxvulkan::Application::Implementation::init_framebuffer()
{
  m_swapchain_framebuffers.resize(m_swapchain_image_views.size());

  for (size_t i = 0; i != m_swapchain_image_views.size(); i++) 
  {
    VkImageView attachments[]{ m_swapchain_image_views[i] };

    VkFramebufferCreateInfo l_framebuffer_info {};
    l_framebuffer_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    l_framebuffer_info.renderPass = m_render_pass;
    l_framebuffer_info.attachmentCount = 1;
    l_framebuffer_info.pAttachments = attachments;
    l_framebuffer_info.width = m_swapchain_extent.width;
    l_framebuffer_info.height = m_swapchain_extent.height;
    l_framebuffer_info.layers = 1;

    if (vkCreateFramebuffer(m_device, &l_framebuffer_info, nullptr, &m_swapchain_framebuffers[i]) != VK_SUCCESS) 
    {
      throw std::runtime_error("Vulkan: Failed to create a framebuffer.");
    }
  }
  std::cout << "Framebuffers initialised, count = " << m_swapchain_framebuffers.size() << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_framebuffer()
{
  for (auto l_framebuffer : m_swapchain_framebuffers) 
  {
    vkDestroyFramebuffer(m_device, l_framebuffer, nullptr);
  }
}


void sdlxvulkan::Application::Implementation::init_command_buffers()
{
  // one per swapchain image
  m_command_buffers.resize(m_swapchain_framebuffers.size());
  
  VkCommandBufferAllocateInfo l_command_buffer_allocate_info = {};
  l_command_buffer_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_command_buffer_allocate_info.pNext = NULL;
  l_command_buffer_allocate_info.commandPool = m_command_pool;
  l_command_buffer_allocate_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  l_command_buffer_allocate_info.commandBufferCount = static_cast<uint32_t>(m_command_buffers.size());

  
  //auto l_vkAllocateCommandBuffers = (PFN_vkAllocateCommandBuffers)(m_get_instance_func(m_instance, "vkAllocateCommandBuffers"));
  // BEWARE the last arg is expected to be a pointer to an array if more than one...
  if (vkAllocateCommandBuffers(m_device, &l_command_buffer_allocate_info, m_command_buffers.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create command buffers.");
  }
  //m_command_buffer = m_command_buffers[0];

  std::cout << "Command Buffers initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_command_buffers()
{
  // Destroy the command buffers
  // BEWARE the last arg is expected to be a pointer to an array if more than one...
  vkFreeCommandBuffers(m_device, m_command_pool, static_cast<uint32_t>(m_command_buffers.size()), m_command_buffers.data());
}


void sdlxvulkan::Application::Implementation::do_commands()
{
  for (size_t l_index = 0; l_index != m_command_buffers.size(); l_index++)
  {
    VkCommandBufferBeginInfo l_begin_info = {};
    l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    l_begin_info.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(m_command_buffers[l_index], &l_begin_info) != VK_SUCCESS) 
    {
      throw std::runtime_error("Vulkan: Failed to begin recording command buffer.");
    }

    VkClearValue l_clear_colour = { 0.0f, 0.0f, 0.0f, 1.0f };

    VkRenderPassBeginInfo l_render_pass_info = {};
    l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    l_render_pass_info.renderPass = m_render_pass;
    l_render_pass_info.framebuffer = m_swapchain_framebuffers[l_index];
    l_render_pass_info.renderArea.offset = { 0, 0 };
    l_render_pass_info.renderArea.extent = m_swapchain_extent;
    l_render_pass_info.clearValueCount = 1;
    l_render_pass_info.pClearValues = &l_clear_colour;

    vkCmdBeginRenderPass(m_command_buffers[l_index], &l_render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(m_command_buffers[l_index], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);

    //vkCmdDraw(m_command_buffers[l_index], 3, 1, 0, 0);

    VkBuffer l_vertex_buffers[] { m_vertex_buffer };
    VkDeviceSize l_offsets[] = { 0 };
    vkCmdBindVertexBuffers(m_command_buffers[l_index], 0, 1, l_vertex_buffers, l_offsets);

    // Bind the index buffer - there can be only one
    vkCmdBindIndexBuffer(m_command_buffers[l_index], m_index_buffer, 0, VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets(m_command_buffers[l_index], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout, 0, 1, &m_descriptor_set, 0, nullptr);

    // Now we draw using the indices
    vkCmdDrawIndexed(m_command_buffers[l_index], static_cast<uint32_t>(c_indices.size()), 1, 0, 0, 0);



    // Draw triangles using these verts.
    //uint32_t const l_vertex_count = static_cast<uint32_t>(c_vertices.size());
    //uint32_t const l_triangle_count = l_vertex_count / 3;
    //std::cout << "Command to draw " << l_vertex_count << " verticies, " << l_triangle_count << " triangles" << std::endl;
    //vkCmdDraw(m_command_buffers[l_index], l_vertex_count, 1, 0, 0);


    vkCmdEndRenderPass(m_command_buffers[l_index]);

    if (vkEndCommandBuffer(m_command_buffers[l_index]) != VK_SUCCESS)
    {
      throw std::runtime_error("Vulkan: Failed to record command buffer.");
    }

    std::cout << "Commands recorded to index = " << l_index << std::endl;
  }
}

void sdlxvulkan::Application::Implementation::init_sync_objects()
{
  m_render_finished_semaphores.resize(c_frames_in_flight);
  m_image_available_semaphores.resize(c_frames_in_flight);
  m_fences.resize(c_frames_in_flight);

  VkSemaphoreCreateInfo l_semaphore_info {};
  l_semaphore_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  l_semaphore_info.pNext = nullptr;
  l_semaphore_info.flags = 0;

  VkFenceCreateInfo l_fence_info {};
  l_fence_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  l_fence_info.pNext = nullptr;
  l_fence_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  for (size_t l_index = 0; l_index != c_frames_in_flight; ++l_index)
  {
    if (vkCreateSemaphore(m_device, &l_semaphore_info, nullptr, &m_image_available_semaphores[l_index]) != VK_SUCCESS ||
      vkCreateSemaphore(m_device, &l_semaphore_info, nullptr, &m_render_finished_semaphores[l_index]) != VK_SUCCESS ||
      vkCreateFence(m_device, &l_fence_info, nullptr, &m_fences[l_index]) != VK_SUCCESS)
    {

      throw std::runtime_error("Vulkan: Failed to create sync objects for a frame.");
    }
  }
  std::cout << "Sync objects initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_sync_objects()
{
  for (size_t l_index = 0; l_index != c_frames_in_flight; ++l_index)
  {
    vkDestroyFence(m_device, m_fences[l_index], nullptr);
    vkDestroySemaphore(m_device, m_render_finished_semaphores[l_index], nullptr);
    vkDestroySemaphore(m_device, m_image_available_semaphores[l_index], nullptr);
  }  
}

void sdlxvulkan::Application::Implementation::draw_frame()
{
  //std::cout << "Draw Frame Start" << std::endl;
  vkWaitForFences(m_device, 1, &m_fences[m_current_frame], VK_TRUE, std::numeric_limits<uint64_t>::max());
  //std::cout << "waiting for fence "<< m_fences[m_current_frame] << std::endl;
  //vkResetFences(m_device, 1, &m_fences[m_current_frame]);
  if (vkResetFences(m_device, 1, &m_fences[m_current_frame]) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to reset fence." };
  }
  //std::cout << "fence done" << std::endl;

  uint32_t l_image_index{0};
  VkResult l_result = vkAcquireNextImageKHR(m_device, m_swapchain, std::numeric_limits<uint64_t>::max(), m_image_available_semaphores[m_current_frame], VK_NULL_HANDLE, &l_image_index);
  if (l_result != VK_SUCCESS)
  {
    std::cout << vulkan_result_string(l_result) << std::endl;
    if (l_result != VK_SUBOPTIMAL_KHR)
    {
      throw std::runtime_error("Vulkan:: Failed to acquire swap chain image.");
    }
  }

  //std::cout << "current frame = " << m_current_frame << " aquired = " << l_image_index << std::endl;
  // Submit the command quue

  // going to use semaphores to synchronise

  VkSemaphore l_wait_semaphores[] = { m_image_available_semaphores[m_current_frame] };
  VkPipelineStageFlags l_wait_stages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT }; 
  VkSemaphore l_signal_semaphores[] = { m_render_finished_semaphores[m_current_frame] };

  VkSubmitInfo l_submit_info {};
  l_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  l_submit_info.pNext = nullptr;
  l_submit_info.waitSemaphoreCount = 1;
  l_submit_info.pWaitSemaphores = l_wait_semaphores;
  l_submit_info.pWaitDstStageMask = l_wait_stages;
  l_submit_info.commandBufferCount = 1;
  l_submit_info.pCommandBuffers = &m_command_buffers[l_image_index];
  l_submit_info.signalSemaphoreCount = 1;
  l_submit_info.pSignalSemaphores = l_signal_semaphores;


  // Finally we send the commands off to be done
  if (vkQueueSubmit(m_graphics_queue, 1, &l_submit_info, m_fences[m_current_frame]) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to submit command queue." };
  }
  //std::cout << "queue submitted" << std::endl;


  // Present the swapchain image
  //-------------

  VkSwapchainKHR l_swap_chains[] { m_swapchain };

  VkPresentInfoKHR l_present_info{};
  l_present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  l_present_info.pNext = NULL;
  l_present_info.waitSemaphoreCount = 1;
  l_present_info.pWaitSemaphores = l_signal_semaphores;
  l_present_info.swapchainCount = 1;
  l_present_info.pSwapchains = l_swap_chains;
  l_present_info.pImageIndices = &l_image_index;
  l_present_info.pResults = nullptr; // optional

  if (vkQueuePresentKHR(m_present_queue, &l_present_info) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to present image." };
  }
  //std::cout << "image presented" << std::endl;

  //std::cout << "frame: " << m_current_frame;
  m_current_frame = (m_current_frame + 1) % c_frames_in_flight;
  //std::cout << "->" << m_current_frame << std::endl;
}

void sdlxvulkan::Application::Implementation::update_uniform_buffer()
{
  static auto s_start_time = std::chrono::high_resolution_clock::now();

  auto l_current_time = std::chrono::high_resolution_clock::now();
  float l_time = std::chrono::duration<float, std::chrono::seconds::period>(l_current_time - s_start_time).count();

  Uniform_Buffer_Object l_ubo{};
  l_ubo.model = glm::rotate(glm::mat4(1.0f), l_time * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

  l_ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

  l_ubo.proj = glm::perspective(glm::radians(45.0f), m_swapchain_extent.width / static_cast<float>(m_swapchain_extent.height), 0.1f, 10.0f);

  l_ubo.proj[1][1] *= -1;
  
  void* l_data;
  vkMapMemory(m_device, m_uniform_buffer_memory, 0, sizeof(l_ubo), 0, &l_data);
  memcpy(l_data, &l_ubo, sizeof(l_ubo));
  vkUnmapMemory(m_device, m_uniform_buffer_memory);
}

void sdlxvulkan::Application::Implementation::create_buffer(VkDeviceSize a_size, VkBufferUsageFlags a_usage, VkMemoryPropertyFlags a_properties, VkBuffer& a_buffer, VkDeviceMemory& a_buffer_memory)
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

  if (vkCreateBuffer(m_device, &l_buffer_info, nullptr, &a_buffer) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: failed to create a buffer.");
  }

  VkMemoryRequirements l_mem_reqs{};
  vkGetBufferMemoryRequirements(m_device, a_buffer, &l_mem_reqs);

  VkMemoryAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.allocationSize = l_mem_reqs.size;
  l_alloc_info.memoryTypeIndex = get_memory_type_from_properties(m_physical_device_mem_properties, l_mem_reqs.memoryTypeBits, a_properties);
  /*
  if (!set_memory_type_from_properties(m_physical_device_mem_properties, l_mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &l_alloc_info.memoryTypeIndex))
  {
    throw std::runtime_error{ "Vulkan: Failed to find matching memory type on the phyisical device to allocate a buffer." };
  }*/

  // Allocate the memory
  if (vkAllocateMemory(m_device, &l_alloc_info, NULL, &a_buffer_memory) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to allocate buffer memory." };
  }
  assert(a_buffer != VK_NULL_HANDLE);
  assert(a_buffer_memory != VK_NULL_HANDLE);
  // Bind it
  if (vkBindBufferMemory(m_device, a_buffer, a_buffer_memory, 0) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to bind a buffer." };
  }

}

void sdlxvulkan::Application::Implementation::copy_buffer(VkBuffer a_source, VkBuffer a_dest, VkDeviceSize a_size)
{
  std::cout << "begin buffer copy, size = " << a_size << std::endl;
  VkCommandBufferAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.commandPool = m_command_pool;
  l_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  l_alloc_info.commandBufferCount = 1;

  VkCommandBuffer l_command_buffers[1]{};
  vkAllocateCommandBuffers(m_device, &l_alloc_info, l_command_buffers);
  assert(l_command_buffers[0] != VK_NULL_HANDLE);

  VkCommandBufferBeginInfo l_begin_info{};
  l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.pNext = nullptr;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  l_begin_info.pInheritanceInfo = nullptr;


  if (vkBeginCommandBuffer(l_command_buffers[0], &l_begin_info) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Copying Buffer: Failed to begin command buffer." };
  }
  //vkBeginCommandBuffer(l_command_buffers[0], &l_begin_info);

  VkBufferCopy l_copy_regions[1]{};
  l_copy_regions[0].srcOffset = 0; // Optional
  l_copy_regions[0].dstOffset = 0; // Optional
  l_copy_regions[0].size = a_size;

  vkCmdCopyBuffer(l_command_buffers[0], a_source, a_dest, 1, l_copy_regions);

  vkEndCommandBuffer(l_command_buffers[0]);

  VkSubmitInfo l_submit_info = {};
  l_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  l_submit_info.pNext = nullptr;
  l_submit_info.waitSemaphoreCount = 0;
  l_submit_info.pWaitSemaphores = nullptr;
  l_submit_info.pWaitDstStageMask = 0;
  l_submit_info.commandBufferCount = 1;
  l_submit_info.pCommandBuffers = l_command_buffers;
  l_submit_info.signalSemaphoreCount = 0;
  l_submit_info.pSignalSemaphores = nullptr;

  std::cout << "submit" << std::endl;
  if (vkQueueSubmit(m_graphics_queue, 1, &l_submit_info, VK_NULL_HANDLE) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Copying Buffer: Failed to submit command buffer." };
  }
  //vkQueueSubmit(this->m_graphics_queue, 1, &l_submit_info, VK_NULL_HANDLE);
  vkQueueWaitIdle(this->m_graphics_queue);

  vkFreeCommandBuffers(this->m_device, this->m_command_pool, 1, l_command_buffers);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Application
//---------------------------------------------------------------------------
// Manages the application.

// Special 6
//============================================================
sdlxvulkan::Application::Application(int argc, char** argv) :
  m_implementation{ std::make_unique<Implementation>(argc, argv) }
{
}

sdlxvulkan::Application::~Application() = default;

// Interface
//============================================================
int sdlxvulkan::Application::execute()
{
  return imp()->execute();
}