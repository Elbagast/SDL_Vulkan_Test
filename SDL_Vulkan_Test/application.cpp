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

#include "system.hpp"
#include "window.hpp"
#include "instance.hpp"
#include "surface.hpp"
#include "debug_callback.hpp"
#include "event_string.hpp"
#include "functions.hpp"
#include "physical_device.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
//#include <vulkan/vulkan_win32.h>

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


#ifdef NDEBUG
  constexpr bool c_enable_validation_layers = false;
  std::vector<std::string> const c_extension_names{  };
  std::vector<std::string> const c_validation_layers { };
#else
  constexpr bool c_enable_validation_layers = true;
  std::vector<std::string> const c_extension_names{ VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
  std::vector<std::string> const c_validation_layers = { "VK_LAYER_LUNARG_standard_validation" };
  //std::vector<std::string> const c_extension_names{  };
  //std::vector<std::string> const c_validation_layers = {  };
#endif

  constexpr size_t c_frames_in_flight{ 2 };
  constexpr uint32_t c_start_width{ 800 };
  constexpr uint32_t c_start_height{ 600 };

  std::string const c_application_name = "SDL x Vulkan";
  uint32_t const c_application_version = VK_MAKE_VERSION(1, 0, 0);
  std::string const c_engine_name = "No Engine";
  uint32_t const c_engine_version = VK_MAKE_VERSION(1, 0, 0);
  uint32_t const c_vulkan_version = VK_API_VERSION_1_1;
  
  static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg, void* a_user_data)
  {
    std::cerr << "[validation layer] " << a_msg << std::endl << std::endl;

    return VK_FALSE;
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
  static Device_Functions s_device_functions{};
  
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
  class Application::Implementation
  {
  private:
    std::vector<std::string> m_args;

    System m_system;
    Window m_window;
    Instance m_instance;
    Debug_Callback m_debug_callback;
    Surface m_surface;

    Physical_Device m_physical_device;

    // Logical Device
    VkDevice m_device;

    // Graphics Queue
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
    
    // Present Queue
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

    void main_loop();

    void init();
    void quit();
        
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
  m_system{ SDL_INIT_VIDEO | SDL_INIT_EVENTS },
  m_window{ m_system, "SDL x Vulkan", 100, 100, c_start_width, c_start_height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN },
  
  m_instance{ m_system, m_window, c_extension_names, c_validation_layers, c_application_name, c_application_version, c_engine_name, c_engine_version, c_vulkan_version },
  m_debug_callback{ m_instance, debug_callback, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT },
  m_surface{ m_window, m_instance },
  m_physical_device{ m_instance.get_first_physical_device(), m_instance, m_surface },
  //m_physical_device{ VK_NULL_HANDLE },
  //m_physical_device_properties{},
  //m_physical_device_mem_properties{},

  //m_queue_familiy_properties{},


  m_device{ VK_NULL_HANDLE },

  //m_graphics_qf_index{ UINT32_MAX },
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

  //m_present_qf_index{ UINT32_MAX },
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

  init_logical_device();
  init_graphics_queue();
  init_command_pool();
  init_vertex_buffer();
  init_index_buffer();
  init_uniform_buffer();
  init_shader_modules();
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
  quit_graphics_queue();
  quit_shader_modules();
  quit_uniform_buffer();
  quit_index_buffer();
  quit_vertex_buffer();
  quit_command_pool();
  quit_logical_device();
  //quit_queue_families();
  //quit_physical_device();
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
  //update_uniform_buffer();
  // a really basic render loop...
  SDL_Event l_event{};
  bool l_quit{ false };
  size_t l_frame_count{ 0 };
  auto l_start_time = std::chrono::steady_clock::now();
  auto l_last_time = l_start_time;
  auto l_now_time = l_last_time;
  while (!l_quit)
  {
    /*
    // FPS tracking
    l_now_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> l_dif = l_now_time - l_last_time;
    if (l_dif.count() >= 1.0)
    {
      std::cout << "FPS: " << l_frame_count << std::endl;
      l_frame_count = 0;
      l_last_time = l_now_time;
    }*/

    while (SDL_PollEvent(&l_event))
    {
      

      if (l_event.type == SDL_QUIT)
      {
        l_quit = true;
      }
      else if (l_event.type == SDL_WINDOWEVENT && l_event.window.windowID == m_window.id())
      {
        //std::cout << sdl_window_event_string(static_cast<SDL_WindowEventID>(l_event.window.event)) << std::endl;
        if (l_event.window.event == SDL_WINDOWEVENT_RESIZED) // everytime the user resizes the window
        {
          int l_window_width{ l_event.window.data1 };
          int l_window_height{ l_event.window.data2 };
        
          int l_draw_width{ 0 };
          int l_draw_height{ 0 };

          SDL_Vulkan_GetDrawableSize(m_window, &l_draw_width, &l_draw_height);

          //m_width = l_draw_width;
          //m_height = l_draw_height;
          std::cout << "Window Resized:" << std::endl;
          std::cout << "window = " << l_window_width << "x" << l_window_height << std::endl;
          std::cout << "draw = " << l_window_width << "x" << l_window_height << std::endl;

          recreate_swapchain();
        }
      }
      else if (l_event.type == SDL_KEYDOWN)
      {
        std::cout << "Keydown: ";
        if (l_event.key.keysym.sym == SDLK_f)
        {
          std::cout << "f" << std::endl;
          // Fake fullscreen - use the same resolution
          //Uint32 l_fullscreen_flag = SDL_WINDOW_FULLSCREEN;
          // Fullscreen at desktop size
          Uint32 l_fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
          // Bitwise and results in a non-zero value if the bits are present in both
          bool l_is_fullscreen = SDL_GetWindowFlags(m_window) & l_fullscreen_flag;
          SDL_SetWindowFullscreen(m_window, l_is_fullscreen ? 0 : l_fullscreen_flag);
          SDL_ShowCursor(l_is_fullscreen);
        }
      }
    }
    update_uniform_buffer();
    // Drawing
    draw_frame();
    ++l_frame_count;


    // Benchmarking
    l_now_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> l_dif = l_now_time - l_start_time;
    if (l_dif.count() >= 10.0)
    {
      l_quit = true;
    }


    // Tick rate limit
    //SDL_Delay(32); //~30FPS
    //SDL_Delay(16); //~60FPS
    //SDL_Delay(1);
    
  }
  std::chrono::duration<double> l_elapsed = l_now_time - l_start_time;
  auto l_elapsed_time = l_elapsed.count();
  std::cout << "Time: " << l_elapsed_time << std::endl;
  std::cout << "Frames: " << l_frame_count << std::endl;
  std::cout << "FPS: " << l_frame_count/ l_elapsed_time << std::endl;


  vkDeviceWaitIdle(m_device);
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
  l_queue_info.queueFamilyIndex = m_physical_device.graphics_qfi();
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
  init_device_functions(s_device_functions, m_device, m_instance.vk_functions());

  std::cout << "Logical Device initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_logical_device()
{
  // Destroy the logical device.
  s_device_functions.vkDestroyDevice(m_device, nullptr);
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
  l_command_pool_info.queueFamilyIndex = m_physical_device.graphics_qfi();

  // Make the pool using the device.
  if (s_device_functions.vkCreateCommandPool(m_device, &l_command_pool_info, nullptr, &m_command_pool) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create command pool.");
  }
  std::cout << "Command Pool initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_command_pool()
{
  // Destroy the command pool
  s_device_functions.vkDestroyCommandPool(m_device, m_command_pool, nullptr);
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
  if (s_device_functions.vkMapMemory(m_device, l_staging_buffer_memory, 0, l_buffer_size, 0, &l_staging_data) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Vertex Buffer: Failed to map the staging buffer." };
  }

  //memcpy(l_data, g_vertex_buffer_solid_face_colors_data, sizeof(g_vertex_buffer_solid_face_colors_data));
  memcpy(l_staging_data, c_vertices.data(), static_cast<size_t>(l_buffer_size));

  // unmap the memory after we have used it.
  s_device_functions.vkUnmapMemory(m_device, l_staging_buffer_memory);
  

  // Vertex buffer
  VkBufferUsageFlags l_vertex_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  VkMemoryPropertyFlags l_vertex_property_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  create_buffer(l_buffer_size, l_vertex_usage_flags, l_vertex_property_flags, m_vertex_buffer, m_vertex_buffer_memory);
     
  copy_buffer(l_staging_buffer, m_vertex_buffer, l_buffer_size);

  s_device_functions.vkDestroyBuffer(m_device, l_staging_buffer, nullptr);
  s_device_functions.vkFreeMemory(m_device, l_staging_buffer_memory, nullptr);
}

void sdlxvulkan::Application::Implementation::quit_vertex_buffer()
{
  s_device_functions.vkDestroyBuffer(m_device, m_vertex_buffer, nullptr);
  s_device_functions.vkFreeMemory(m_device, m_vertex_buffer_memory, nullptr);
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
  if (s_device_functions.vkMapMemory(m_device, l_staging_buffer_memory, 0, l_buffer_size, 0, &l_staging_data) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Index Buffer: Failed to map the staging buffer." };
  }

  //memcpy(l_data, g_vertex_buffer_solid_face_colors_data, sizeof(g_vertex_buffer_solid_face_colors_data));
  memcpy(l_staging_data, c_indices.data(), static_cast<size_t>(l_buffer_size));

  // unmap the memory after we have used it.
  s_device_functions.vkUnmapMemory(m_device, l_staging_buffer_memory);
  
  // Index buffer
  VkBufferUsageFlags l_index_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
  VkMemoryPropertyFlags l_index_property_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  create_buffer(l_buffer_size, l_index_usage_flags, l_index_property_flags, m_index_buffer, m_index_buffer_memory);

  copy_buffer(l_staging_buffer, m_index_buffer, l_buffer_size);

  s_device_functions.vkDestroyBuffer(m_device, l_staging_buffer, nullptr);
  s_device_functions.vkFreeMemory(m_device, l_staging_buffer_memory, nullptr);
}

void sdlxvulkan::Application::Implementation::quit_index_buffer()
{
  s_device_functions.vkDestroyBuffer(m_device, m_index_buffer, nullptr);
  s_device_functions.vkFreeMemory(m_device, m_index_buffer_memory, nullptr);
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
  s_device_functions.vkDestroyBuffer(m_device, m_uniform_buffer, nullptr);
  s_device_functions.vkFreeMemory(m_device, m_uniform_buffer_memory, nullptr);
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
  
  if (s_device_functions.vkCreateDescriptorPool(m_device, &l_pool_info, nullptr, &m_descriptor_pool) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create descriptor pool.");
  }
}

void sdlxvulkan::Application::Implementation::quit_descriptor_pool()
{
  s_device_functions.vkDestroyDescriptorPool(m_device, m_descriptor_pool, nullptr);
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

  if (s_device_functions.vkAllocateDescriptorSets(m_device, &l_alloc_info, &m_descriptor_set) != VK_SUCCESS)
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

  s_device_functions.vkUpdateDescriptorSets(m_device, 1, &l_descriptor_write, 0, nullptr);
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
  s_device_functions.vkDestroyShaderModule(m_device, m_fragment_shader_module, nullptr);
  s_device_functions.vkDestroyShaderModule(m_device, m_vertex_shader_module, nullptr);
}

void sdlxvulkan::Application::Implementation::init_graphics_queue()
{
  s_device_functions.vkGetDeviceQueue(m_device, m_physical_device.graphics_qfi(), 0, &m_graphics_queue);

  std::cout << "Graphics Queue initialised, index = " << m_physical_device.graphics_qfi() << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_graphics_queue()
{
  // Do nothing
}

void sdlxvulkan::Application::Implementation::init_surface()
{
  // Surface
  //-------------
  /*
  std::cout << "<<<<<<<<<<<" << std::endl;
  if (SDL_Vulkan_CreateSurface(m_window, m_instance, &m_surface) != SDL_TRUE)
  {
    throw std::runtime_error("SDL: Failed to create a Vulkan surface.");
  }
  std::cout << "Surface initialised" << std::endl;
  */
}

void sdlxvulkan::Application::Implementation::quit_surface()
{
  // Destroy the Vulkan surface.
  //vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
}

void sdlxvulkan::Application::Implementation::init_present_queue()
{
  // Presenting
  //-------------
  
  // Do we really need to bother with this check?
  // Could just get the queue regardless
  if (m_physical_device.present_qfi() == m_physical_device.graphics_qfi())
  {
    m_present_queue = m_graphics_queue;
  }
  else
  {
    s_device_functions.vkGetDeviceQueue(m_device, m_physical_device.present_qfi(), 0, &m_present_queue);
  }
  std::cout << "Present Queue initialised, index = " << m_physical_device.present_qfi() << std::endl;
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
  if (m_instance.vk_functions().vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physical_device, m_surface, &m_swapchain_surface_cababilites) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface capabilites.");
  }


  // Get the formats that can be used with this device/surface combo.
  uint32_t l_surface_format_count{ 0 };
  if (m_instance.vk_functions().vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface, &l_surface_format_count, NULL) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface format count.");
  }

  m_swapchain_surface_formats.resize(l_surface_format_count);
  if (m_instance.vk_functions().vkGetPhysicalDeviceSurfaceFormatsKHR(m_physical_device, m_surface, &l_surface_format_count, m_swapchain_surface_formats.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface formats.");
  }


  // Get the present modes
  uint32_t l_present_mode_count{ 0 };
  if (m_instance.vk_functions().vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, m_surface, &l_present_mode_count, NULL) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to get surface present mode count.");
  }

  m_swapchain_present_modes.resize(l_present_mode_count);
  if (m_instance.vk_functions().vkGetPhysicalDeviceSurfacePresentModesKHR(m_physical_device, m_surface, &l_present_mode_count, m_swapchain_present_modes.data()) != VK_SUCCESS)
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
      m_swapchain_extent.width = m_window.draw_width();
      m_swapchain_extent.height = m_window.draw_height();

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

  uint32_t l_queue_familiy_indicies[2] = { m_physical_device.graphics_qfi(), m_physical_device.present_qfi() };

  if (m_physical_device.graphics_qfi() != m_physical_device.present_qfi())
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
  VkResult l_result = s_device_functions.vkCreateSwapchainKHR(m_device, &l_swapchain_info, nullptr, &m_swapchain);
  if (l_result != VK_SUCCESS)
  {
    throw std::runtime_error{ std::string{ "Vulkan: Failed to create swapchain. " } +vulkan_result_string(l_result) };
  }


  uint32_t l_actual_image_count{ 0 };
  if (s_device_functions.vkGetSwapchainImagesKHR(m_device, m_swapchain, &l_actual_image_count, nullptr) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to get swapchain images." };
  }

  std::cout << "requested = " << m_swapchain_image_count << std::endl;
  std::cout << "actual = " << m_swapchain_image_count << std::endl;

  // Now make the images. These have no special cleanup.
  m_swapchain_images.resize(m_swapchain_image_count);
  if (s_device_functions.vkGetSwapchainImagesKHR(m_device, m_swapchain, &m_swapchain_image_count, m_swapchain_images.data()) != VK_SUCCESS)
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
  s_device_functions.vkDestroySwapchainKHR(m_device, l_old_swapchain, nullptr);

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
  s_device_functions.vkDestroySwapchainKHR(m_device, m_swapchain, nullptr);
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

    if (s_device_functions.vkCreateImageView(m_device, &l_color_image_view, nullptr, &m_swapchain_image_views[l_index]) != VK_SUCCESS)
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
    s_device_functions.vkDestroyImageView(m_device, l_image_view, nullptr);
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


  if (s_device_functions.vkCreateRenderPass(m_device, &l_render_pass_info, nullptr, &m_render_pass) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create render pass." };
  }

  std::cout << "Render Pass initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_render_pass()
{
  s_device_functions.vkDestroyRenderPass(m_device, m_render_pass, nullptr);
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

  if (s_device_functions.vkCreateDescriptorSetLayout(m_device, &l_layout_info, nullptr, &m_descriptor_set_layout) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to create descriptor set layout.");
  }
}

void sdlxvulkan::Application::Implementation::quit_descriptor_set_layout()
{
  s_device_functions.vkDestroyDescriptorSetLayout(m_device, m_descriptor_set_layout, nullptr);
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
  

  if(s_device_functions.vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &l_pipeline_info, nullptr, &m_pipeline) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to create graphics pipeline." };
  }
  std::cout << "Pipeline initialised." << std::endl;
}

void sdlxvulkan::Application::Implementation::quit_pipeline()
{
  s_device_functions.vkDestroyPipeline(m_device, m_pipeline, nullptr);
  s_device_functions.vkDestroyPipelineLayout(m_device, m_pipeline_layout, nullptr);
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
    s_device_functions.vkDestroyFramebuffer(m_device, l_framebuffer, nullptr);
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
  if (s_device_functions.vkAllocateCommandBuffers(m_device, &l_command_buffer_allocate_info, m_command_buffers.data()) != VK_SUCCESS)
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
  s_device_functions.vkFreeCommandBuffers(m_device, m_command_pool, static_cast<uint32_t>(m_command_buffers.size()), m_command_buffers.data());
}


void sdlxvulkan::Application::Implementation::do_commands()
{
  for (size_t l_index = 0; l_index != m_command_buffers.size(); l_index++)
  {
    VkCommandBufferBeginInfo l_begin_info = {};
    l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    l_begin_info.pInheritanceInfo = nullptr; // Optional

    if (s_device_functions.vkBeginCommandBuffer(m_command_buffers[l_index], &l_begin_info) != VK_SUCCESS)
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

    s_device_functions.vkCmdBeginRenderPass(m_command_buffers[l_index], &l_render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

    s_device_functions.vkCmdBindPipeline(m_command_buffers[l_index], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);

    //vkCmdDraw(m_command_buffers[l_index], 3, 1, 0, 0);

    VkBuffer l_vertex_buffers[] { m_vertex_buffer };
    VkDeviceSize l_offsets[] = { 0 };
    s_device_functions.vkCmdBindVertexBuffers(m_command_buffers[l_index], 0, 1, l_vertex_buffers, l_offsets);

    // Bind the index buffer - there can be only one
    s_device_functions.vkCmdBindIndexBuffer(m_command_buffers[l_index], m_index_buffer, 0, VK_INDEX_TYPE_UINT16);

    s_device_functions.vkCmdBindDescriptorSets(m_command_buffers[l_index], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout, 0, 1, &m_descriptor_set, 0, nullptr);

    // Now we draw using the indices
    s_device_functions.vkCmdDrawIndexed(m_command_buffers[l_index], static_cast<uint32_t>(c_indices.size()), 1, 0, 0, 0);



    // Draw triangles using these verts.
    //uint32_t const l_vertex_count = static_cast<uint32_t>(c_vertices.size());
    //uint32_t const l_triangle_count = l_vertex_count / 3;
    //std::cout << "Command to draw " << l_vertex_count << " verticies, " << l_triangle_count << " triangles" << std::endl;
    //vkCmdDraw(m_command_buffers[l_index], l_vertex_count, 1, 0, 0);


    s_device_functions.vkCmdEndRenderPass(m_command_buffers[l_index]);

    if (s_device_functions.vkEndCommandBuffer(m_command_buffers[l_index]) != VK_SUCCESS)
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
    if (s_device_functions.vkCreateSemaphore(m_device, &l_semaphore_info, nullptr, &m_image_available_semaphores[l_index]) != VK_SUCCESS ||
      s_device_functions.vkCreateSemaphore(m_device, &l_semaphore_info, nullptr, &m_render_finished_semaphores[l_index]) != VK_SUCCESS ||
      s_device_functions.vkCreateFence(m_device, &l_fence_info, nullptr, &m_fences[l_index]) != VK_SUCCESS)
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
    s_device_functions.vkDestroyFence(m_device, m_fences[l_index], nullptr);
    s_device_functions.vkDestroySemaphore(m_device, m_render_finished_semaphores[l_index], nullptr);
    s_device_functions.vkDestroySemaphore(m_device, m_image_available_semaphores[l_index], nullptr);
  }  
}

void sdlxvulkan::Application::Implementation::draw_frame()
{
  //std::cout << "Draw Frame Start" << std::endl;
  s_device_functions.vkWaitForFences(m_device, 1, &m_fences[m_current_frame], VK_TRUE, std::numeric_limits<uint64_t>::max());
  //std::cout << "waiting for fence "<< m_fences[m_current_frame] << std::endl;
  //vkResetFences(m_device, 1, &m_fences[m_current_frame]);
  if (s_device_functions.vkResetFences(m_device, 1, &m_fences[m_current_frame]) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to reset fence." };
  }
  //std::cout << "fence done" << std::endl;

  uint32_t l_image_index{0};
  VkResult l_result = s_device_functions.vkAcquireNextImageKHR(m_device, m_swapchain, std::numeric_limits<uint64_t>::max(), m_image_available_semaphores[m_current_frame], VK_NULL_HANDLE, &l_image_index);
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
  if (s_device_functions.vkQueueSubmit(m_graphics_queue, 1, &l_submit_info, m_fences[m_current_frame]) != VK_SUCCESS)
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
  s_device_functions.vkMapMemory(m_device, m_uniform_buffer_memory, 0, sizeof(l_ubo), 0, &l_data);
  memcpy(l_data, &l_ubo, sizeof(l_ubo));
  s_device_functions.vkUnmapMemory(m_device, m_uniform_buffer_memory);
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
  s_device_functions.vkGetBufferMemoryRequirements(m_device, a_buffer, &l_mem_reqs);

  VkMemoryAllocateInfo l_alloc_info{};
  l_alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  l_alloc_info.pNext = nullptr;
  l_alloc_info.allocationSize = l_mem_reqs.size;
  l_alloc_info.memoryTypeIndex = m_physical_device.get_memory_type_from_properties(l_mem_reqs.memoryTypeBits, a_properties);
  /*
  if (!set_memory_type_from_properties(m_physical_device_mem_properties, l_mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &l_alloc_info.memoryTypeIndex))
  {
    throw std::runtime_error{ "Vulkan: Failed to find matching memory type on the phyisical device to allocate a buffer." };
  }*/

  // Allocate the memory
  if (s_device_functions.vkAllocateMemory(m_device, &l_alloc_info, NULL, &a_buffer_memory) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to allocate buffer memory." };
  }
  assert(a_buffer != VK_NULL_HANDLE);
  assert(a_buffer_memory != VK_NULL_HANDLE);
  // Bind it
  if (s_device_functions.vkBindBufferMemory(m_device, a_buffer, a_buffer_memory, 0) != VK_SUCCESS)
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
  s_device_functions.vkAllocateCommandBuffers(m_device, &l_alloc_info, l_command_buffers);
  assert(l_command_buffers[0] != VK_NULL_HANDLE);

  VkCommandBufferBeginInfo l_begin_info{};
  l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.pNext = nullptr;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  l_begin_info.pInheritanceInfo = nullptr;


  if (s_device_functions.vkBeginCommandBuffer(l_command_buffers[0], &l_begin_info) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Copying Buffer: Failed to begin command buffer." };
  }
  //vkBeginCommandBuffer(l_command_buffers[0], &l_begin_info);

  VkBufferCopy l_copy_regions[1]{};
  l_copy_regions[0].srcOffset = 0; // Optional
  l_copy_regions[0].dstOffset = 0; // Optional
  l_copy_regions[0].size = a_size;

  s_device_functions.vkCmdCopyBuffer(l_command_buffers[0], a_source, a_dest, 1, l_copy_regions);

  s_device_functions.vkEndCommandBuffer(l_command_buffers[0]);

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
  if (s_device_functions.vkQueueSubmit(m_graphics_queue, 1, &l_submit_info, VK_NULL_HANDLE) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Copying Buffer: Failed to submit command buffer." };
  }
  //vkQueueSubmit(this->m_graphics_queue, 1, &l_submit_info, VK_NULL_HANDLE);
  s_device_functions.vkQueueWaitIdle(this->m_graphics_queue);

  s_device_functions.vkFreeCommandBuffers(this->m_device, this->m_command_pool, 1, l_command_buffers);
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