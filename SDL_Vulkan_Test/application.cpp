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

#include "app_make.hpp"
#include "app_files.hpp"
#include "event_string.hpp"
#include "global_functions.hpp"
#include "instance_functions.hpp"
#include "device_functions.hpp"
#include "vulkan_io.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
  
  struct Vertex
  {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

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
      std::array<VkVertexInputAttributeDescription, 3> l_attribute_descriptions {};

      l_attribute_descriptions[0].binding = 0;
      l_attribute_descriptions[0].location = 0;
      l_attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
      l_attribute_descriptions[0].offset = offsetof(Vertex, pos);

      l_attribute_descriptions[1].binding = 0;
      l_attribute_descriptions[1].location = 1;
      l_attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
      l_attribute_descriptions[1].offset = offsetof(Vertex, color);

      l_attribute_descriptions[2].binding = 0;
      l_attribute_descriptions[2].location = 2;
      l_attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
      l_attribute_descriptions[2].offset = offsetof(Vertex, texCoord);

      return l_attribute_descriptions;
    }

    static auto get_attribute_descriptions_vector()
    {
      std::vector<VkVertexInputAttributeDescription> l_attribute_descriptions{};
      l_attribute_descriptions.resize(3);

      l_attribute_descriptions[0].binding = 0;
      l_attribute_descriptions[0].location = 0;
      l_attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
      l_attribute_descriptions[0].offset = offsetof(Vertex, pos);

      l_attribute_descriptions[1].binding = 0;
      l_attribute_descriptions[1].location = 1;
      l_attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
      l_attribute_descriptions[1].offset = offsetof(Vertex, color);

      l_attribute_descriptions[2].binding = 0;
      l_attribute_descriptions[2].location = 2;
      l_attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
      l_attribute_descriptions[2].offset = offsetof(Vertex, texCoord);

      return l_attribute_descriptions;
    }
  };

  static std::vector<Vertex> const c_vertices = 
  {
    { { -0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
    { { 0.5f, -0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
    { { 0.5f, 0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
    { { -0.5f, 0.5f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },

    { { -0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
    { { 0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
    { { 0.5f, 0.5f, -0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
    { { -0.5f, 0.5f, -0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
  };
  static std::vector<uint16_t> const c_indices = 
  {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
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
  

  std::vector<std::string> const c_device_extension_names{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
  
  // Callback function that is given to Vulkan. It will interpret
  // the user data void* as an Abstract_Debug_Callback* and call
  // Abstract_Debug_Callback::do_callback on it with the arguments.
  // Always returns VK_FALSE.
  VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg, void* a_user_data)
  {
    std::cerr << "DEBUG: " << a_msg << std::endl << std::endl;
    return VK_FALSE;
  }
}

//---------------------------------------------------------------------------
// Application::Implementation
//---------------------------------------------------------------------------
// Hide all the implementation details and private functions for the 
// application state.

namespace sdlxvulkan
{
  class Application::Implementation
  {
  private:
    std::vector<std::string> m_args;

    System m_system;
    Window m_window;
    Handle<VkInstance> m_instance;
    Instance_Functions const* m_instance_functions;

    Handle<VkDebugReportCallbackEXT> m_debug_callback;
    Handle<VkSurfaceKHR> m_surface;

    //--------------------
    // Physical Device

    Handle<VkPhysicalDevice> m_physical_device;

    // Caching...
    VkPhysicalDeviceFeatures m_supported_features;
    VkPhysicalDeviceFeatures m_required_features;
    VkFormat m_depth_format;

    //--------------------
    // Logical device

    uint32_t m_graphics_qfi;
    uint32_t m_present_qfi;

    Handle<VkDevice> m_device;
    Device_Functions const* m_device_functions;

    Handle<VkQueue> m_graphics_queue;
    Handle<VkQueue> m_present_queue;

    Handle<VkCommandPool> m_command_pool;

    //--------------------

    Handle<VkDescriptorSetLayout> m_descriptor_set_layout;

    Shader_Group m_shaders;

    //--------------------
    // Textures
    //STB_Image m_texture_data;
    Image_Trio m_texture;
    Handle<VkSampler> m_sampler;

    //--------------------
    // Swapchain
    Swapchain m_swapchain;

    Buffer_Pair m_vertex;
    Buffer_Pair m_index;

    std::vector<Buffer_Pair> m_uniforms;

    Image_Trio m_depth;
    
    Handle<VkDescriptorPool> m_descriptor_pool;
    std::vector<Handle<VkDescriptorSet>> m_descriptor_sets;

    Handle<VkRenderPass> m_render_pass;
    
    // Pipeline
    VkViewport m_viewport;
    VkRect2D m_scissor;
    Handle<VkPipelineLayout> m_pipeline_layout;
    Handle<VkPipelineCache> m_pipeline_cache;
    Handle<VkPipeline> m_pipeline;

    // Framebuffers
    std::vector<Handle<VkFramebuffer>> m_swapchain_framebuffers;
    
    // Command Buffer(s)
    std::vector<Handle<VkCommandBuffer>> m_command_buffers;

    // Sync Objects
    std::vector<Handle<VkSemaphore>> m_image_available_semaphores;
    std::vector<Handle<VkSemaphore>> m_render_finished_semaphores;
    std::vector<Handle<VkFence>> m_fences;
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
                
    void resize();
            
    void write_commands();
    
    void draw_frame();

    void update_uniform_buffer();
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
  
  m_instance{ app_make_instance(m_system, m_window, c_extension_names, c_validation_layers, c_application_name, c_application_version, c_engine_name, c_engine_version, c_vulkan_version) },
  m_instance_functions{ get_instance_functions(m_instance) },
  m_debug_callback{ app_make_debug_report_callback_ext(m_instance, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, debug_callback) },
  m_surface{ make_surface_khr(m_instance, m_window) },
  m_physical_device{ get_physical_devices(m_instance).front() },
  m_supported_features{ get_physical_device_features(m_physical_device) },
  m_required_features{ app_make_required_device_features(m_supported_features) },
  m_depth_format{ find_depth_format(m_physical_device) },

  // If we wanted to manage queue families in more detail then stuff goes here.
  m_graphics_qfi{ first_graphics_qfi(m_physical_device) },
  m_present_qfi{ first_present_qfi(m_physical_device, m_surface) },
  m_device{ app_make_device(m_physical_device, m_graphics_qfi, m_present_qfi, m_required_features, c_device_extension_names) },
  m_device_functions{ get_device_functions(m_device) },

  m_graphics_queue{ make_queue(m_device, m_graphics_qfi, 0) },
  m_present_queue{ make_queue(m_device, m_present_qfi, 0) },

  m_command_pool{ app_make_command_pool(m_device, m_graphics_qfi, 0) },
  
  m_descriptor_set_layout{ app_make_descriptor_set_layout(m_device) },

  m_shaders{ app_make_shader_group(m_device, m_args[0]) },
  
  //m_texture_data{ get_filepath(m_args[0], u8"texture.jpg") },
  m_texture{ app_make_texture_image_trio(m_physical_device, m_device, m_command_pool, m_graphics_queue, get_filepath(m_args[0], u8"texture.jpg")) },
  m_sampler{ app_make_sampler(m_device, m_required_features) },

  m_swapchain{ app_make_swapchain(m_window, m_physical_device, m_device, m_surface, m_graphics_qfi, m_present_qfi) },
  
  m_vertex{ app_make_vertex_buffer_pair(m_physical_device, m_device, m_command_pool, m_graphics_queue, sizeof(c_vertices[0]) * c_vertices.size(), c_vertices.data()) },
  
  m_index{ app_make_index_buffer_pair(m_physical_device, m_device, m_command_pool, m_graphics_queue, sizeof(c_indices[0]) * c_indices.size(), c_indices.data()) },

  m_uniforms{ app_make_uniforms(m_physical_device, m_device, m_swapchain.image_count, sizeof(Uniform_Buffer_Object)) },

  m_depth{ app_make_depth_image_trio(m_physical_device, m_device, m_command_pool, m_graphics_queue, m_swapchain.extent.width, m_swapchain.extent.height) },

  m_descriptor_pool{ app_make_descriptor_pool(m_device, m_swapchain.image_count) },

  m_descriptor_sets{ app_make_descriptor_sets(m_device, m_descriptor_set_layout, m_descriptor_pool, m_swapchain, m_texture, m_sampler, m_uniforms, sizeof(Uniform_Buffer_Object)) },

  // Render Pass
  m_render_pass{ app_make_render_pass(m_device, m_swapchain.format, m_depth_format) },

  // Pipeline
  m_viewport{ app_make_viewport(m_swapchain) },
  m_scissor{ app_make_scissor(m_swapchain) },
  m_pipeline_cache{ app_make_pipeline_cache(m_device) },
  m_pipeline_layout{ app_make_pipeline_layout(m_device, m_descriptor_set_layout) },
  m_pipeline{ app_make_dynamic_pipeline(m_device, m_pipeline_cache, m_pipeline_layout, m_render_pass, m_shaders, {Vertex::get_binding_description()}, Vertex::get_attribute_descriptions_vector()) },//, { m_viewport }, { m_scissor }) },

  m_swapchain_framebuffers{ app_make_swapchain_framebuffers(m_device, m_swapchain, m_render_pass, m_depth) },

  m_command_buffers{ app_make_command_buffers(m_command_pool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, m_swapchain.image_count) },

  // Sync Objects
  m_image_available_semaphores{ app_make_semaphores(m_device, m_swapchain.image_count) },
  m_render_finished_semaphores{ app_make_semaphores(m_device, m_swapchain.image_count) },
  m_fences{ app_make_fences(m_device, m_swapchain.image_count, VK_FENCE_CREATE_SIGNALED_BIT) },
  m_current_frame{0}
{
  std::cout << "Application::Implementation::Implementation(argc, * argv)" << std::endl;
  // Output the captured args to the console.
  std::cout << "Args:" << std::endl;
  for (auto const& i : m_args)
  {
    std::cout << i << std::endl;
  }

  write_commands();
}

sdlxvulkan::Application::Implementation::~Implementation() = default;

// Interface
//============================================================
int sdlxvulkan::Application::Implementation::execute()
{
  try
  {
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

          resize();
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

void sdlxvulkan::Application::Implementation::resize()
{
  std::cout << "sdlxvulkan::Application::Implementation::do_resize()" << std::endl;

  // Wait for nothing to be going on so stuff doesn't break
  m_device_functions->vkDeviceWaitIdle(m_device);

  // Reset all the associated command buffers instead of completely remaking them
  m_device_functions->vkResetCommandPool(m_device, m_command_pool, 0);

  // At this point the window size has changed already.
  auto l_width = static_cast<uint32_t>(m_window.draw_width());
  auto l_height = static_cast<uint32_t>(m_window.draw_height());

  // Windows 10 will auto-scale the image but it looks crap so we want to change the
  // render image to the new size. Since the current setup is still valid, but not
  // optimal, we build then swap in things that need to change.

  auto l_new_swapchain = app_make_swapchain(m_window, m_physical_device, m_device, m_surface, m_graphics_qfi, m_present_qfi, m_swapchain);
  auto l_new_viewport = app_make_viewport(l_new_swapchain);
  auto l_new_scissor = app_make_scissor(l_new_swapchain);

  // Conditional remake of renderpass.
  Handle<VkRenderPass> l_new_render_pass{};

  // Only make a new one if the swapchain format changed.
  if (l_new_swapchain.format != m_swapchain.format)
  {
    std::cout << "render pass changed" << std::endl;
    l_new_render_pass = app_make_render_pass(m_device, l_new_swapchain.format, m_depth_format);
  }
  else
  {
    // or check before swapping?
    l_new_render_pass = m_render_pass;
  }

  // Conditional pipeline rebuild
  Handle<VkPipeline> l_new_pipeline{};

  // If the format changed then the render pass changed, which means
  // we have no choice but to rebuild the pipeline entirely.
  if (l_new_render_pass != m_render_pass)
  {
    l_new_pipeline = app_make_dynamic_pipeline(m_device, m_pipeline_cache, m_pipeline_layout, l_new_render_pass, m_shaders, { Vertex::get_binding_description() }, Vertex::get_attribute_descriptions_vector());// , { l_new_viewport }, { l_new_scissor });
  }
  // Else we only have dynamic changes that get handled in drawing.
  else
  {
    // or check before swapping?
    l_new_pipeline = m_pipeline;
  }

  // Make a new depth buffer because it must have the new size.
  auto l_new_depth = app_make_depth_image_trio(m_physical_device, m_device, m_command_pool, m_graphics_queue, l_new_swapchain.extent.width, l_new_swapchain.extent.height);

  // Remake the framebuffers since they rely on the new swapchain
  auto l_new_swapchain_framebuffers = app_make_swapchain_framebuffers(m_device, l_new_swapchain, l_new_render_pass, l_new_depth);

  // swap in
  std::swap(l_new_swapchain, m_swapchain);
  std::swap(l_new_viewport, m_viewport);
  std::swap(l_new_scissor, m_scissor);
  std::swap(l_new_render_pass, m_render_pass);
  std::swap(l_new_pipeline, m_pipeline);
  std::swap(l_new_depth, m_depth);
  std::swap(l_new_swapchain_framebuffers, m_swapchain_framebuffers);
  
  // rebuild the commands since these don't change each frame right now.
  write_commands();
}


void sdlxvulkan::Application::Implementation::write_commands()
{
  // Currently just preloads the draw commands into all the command buffers.
  for (size_t l_index = 0; l_index != m_command_buffers.size(); l_index++)
  {
    VkCommandBufferBeginInfo l_begin_info = {};
    l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    l_begin_info.pInheritanceInfo = nullptr; // Optional

    if (m_device_functions->vkBeginCommandBuffer(m_command_buffers[l_index], &l_begin_info) != VK_SUCCESS)
    {
      throw std::runtime_error("Vulkan: Failed to begin recording command buffer.");
    }

    // got to do this every time things get drawn with a dynamic pipeline.
    m_device_functions->vkCmdSetViewport(m_command_buffers[l_index], 0, 1, &m_viewport);
    m_device_functions->vkCmdSetScissor(m_command_buffers[l_index], 0, 1, &m_scissor);

    
    std::array<VkClearValue, 2> l_clear_values = {};

    // colour image
    l_clear_values[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
    l_clear_values[0].depthStencil = { 0.0f, 0 }; // ignored

    // depth image
    l_clear_values[0].color = { 0.0f, 0.0f, 0.0f, 0.0f }; // ignored
    l_clear_values[1].depthStencil = { 1.0f, 0 };

    VkRenderPassBeginInfo l_render_pass_info = {};
    l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    l_render_pass_info.renderPass = m_render_pass;
    l_render_pass_info.framebuffer = m_swapchain_framebuffers[l_index];
    l_render_pass_info.renderArea.offset = { 0, 0 };
    l_render_pass_info.renderArea.extent = m_swapchain.extent;
    l_render_pass_info.clearValueCount = static_cast<uint32_t>(l_clear_values.size());
    l_render_pass_info.pClearValues = l_clear_values.data();

    m_device_functions->vkCmdBeginRenderPass(m_command_buffers[l_index], &l_render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

    m_device_functions->vkCmdBindPipeline(m_command_buffers[l_index], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
    
    VkBuffer l_vertex_buffers[] { m_vertex.buffer };
    VkDeviceSize l_offsets[] = { 0 };
    m_device_functions->vkCmdBindVertexBuffers(m_command_buffers[l_index], 0, 1, l_vertex_buffers, l_offsets);

    // Bind the index buffer - there can be only one
    m_device_functions->vkCmdBindIndexBuffer(m_command_buffers[l_index], m_index.buffer, 0, VK_INDEX_TYPE_UINT16);

    std::array<VkDescriptorSet, 1> l_descriptor_set{ m_descriptor_sets[l_index] };

    m_device_functions->vkCmdBindDescriptorSets(m_command_buffers[l_index], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout, 0, 1, l_descriptor_set.data(), 0, nullptr);

    // Now we draw using the indices
    m_device_functions->vkCmdDrawIndexed(m_command_buffers[l_index], static_cast<uint32_t>(c_indices.size()), 1, 0, 0, 0);
    
    m_device_functions->vkCmdEndRenderPass(m_command_buffers[l_index]);

    if (m_device_functions->vkEndCommandBuffer(m_command_buffers[l_index]) != VK_SUCCESS)
    {
      throw std::runtime_error("Vulkan: Failed to record command buffer.");
    }

    std::cout << "Commands recorded to index = " << l_index << std::endl;
  }
}

void sdlxvulkan::Application::Implementation::draw_frame()
{
  //std::cout << "Draw Frame Start" << std::endl;
  std::array<VkFence, 1> l_fences{ m_fences[m_current_frame] };
  m_device_functions->vkWaitForFences(m_device, 1, l_fences.data(), VK_TRUE, std::numeric_limits<uint64_t>::max());
  //std::cout << "waiting for fence "<< m_fences[m_current_frame] << std::endl;
  //vkResetFences(m_device, 1, &m_fences[m_current_frame]);
  if (m_device_functions->vkResetFences(m_device, 1, l_fences.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to reset fence." };
  }
  //std::cout << "fence done" << std::endl;

  uint32_t l_image_index{0};
  VkResult l_result = m_device_functions->vkAcquireNextImageKHR(m_device, m_swapchain.handle, std::numeric_limits<uint64_t>::max(), m_image_available_semaphores[m_current_frame], VK_NULL_HANDLE, &l_image_index);
  if (l_result != VK_SUCCESS)
  {
    std::cout << vkresult_string(l_result) << std::endl;
    if (l_result != VK_SUBOPTIMAL_KHR)
    {
      throw std::runtime_error("Vulkan:: Failed to acquire swap chain image.");
    }
  }

  //std::cout << "current frame = " << m_current_frame << " aquired = " << l_image_index << std::endl;
  // Submit the command quue

  // going to use semaphores to synchronise
  
  std::array<VkSemaphore, 1> l_wait_semaphores { m_image_available_semaphores[m_current_frame] };
  std::array<VkPipelineStageFlags, 1> l_wait_stages { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
  std::array<VkSemaphore, 1> l_signal_semaphores { m_render_finished_semaphores[m_current_frame] };

  assert(!m_command_buffers.empty());
  VkCommandBuffer l_command_buffers[1]{};
  l_command_buffers[0] = m_command_buffers[l_image_index];

  VkSubmitInfo l_submit_info {};
  l_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  l_submit_info.pNext = nullptr;
  l_submit_info.waitSemaphoreCount = 1;
  l_submit_info.pWaitSemaphores = l_wait_semaphores.data();
  l_submit_info.pWaitDstStageMask = l_wait_stages.data();
  l_submit_info.commandBufferCount = 1;
  l_submit_info.pCommandBuffers = l_command_buffers;
  l_submit_info.signalSemaphoreCount = 1;
  l_submit_info.pSignalSemaphores = l_signal_semaphores.data();


  // Finally we send the commands off to be done
  if (m_device_functions->vkQueueSubmit(m_graphics_queue, 1, &l_submit_info, m_fences[m_current_frame]) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to submit command queue." };
  }
  //std::cout << "queue submitted" << std::endl;


  // Present the swapchain image
  //-------------
  
  std::array<VkSwapchainKHR, 1> l_swapchains { m_swapchain.handle };

  VkPresentInfoKHR l_present_info{};
  l_present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  l_present_info.pNext = nullptr;
  l_present_info.waitSemaphoreCount = 1;
  l_present_info.pWaitSemaphores = l_signal_semaphores.data(); // This is the part that means we wait til render is done
  l_present_info.swapchainCount = 1;
  l_present_info.pSwapchains = l_swapchains.data();
  l_present_info.pImageIndices = &l_image_index;
  l_present_info.pResults = nullptr; // optional

  if (m_device_functions->vkQueuePresentKHR(m_present_queue, &l_present_info) != VK_SUCCESS)
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

  l_ubo.proj = glm::perspective(glm::radians(45.0f), m_swapchain.extent.width / static_cast<float>(m_swapchain.extent.height), 0.1f, 10.0f);

  l_ubo.proj[1][1] *= -1;
  
  void* l_data{};
  m_device_functions->vkMapMemory(m_device, m_uniforms[m_current_frame].memory, 0, sizeof(l_ubo), 0, &l_data);
  memcpy(l_data, &l_ubo, sizeof(l_ubo));
  m_device_functions->vkUnmapMemory(m_device, m_uniforms[m_current_frame].memory);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Application
//---------------------------------------------------------------------------
// Manages the application.


// Special 6
//============================================================
sdlxvulkan::Application::Application(int argc, char** argv) :
  m_implementation{ nullptr }
{
  try
  {
    m_implementation = std::make_unique<Implementation>(argc, argv);
  }
  catch (...)
  {
    std::cout << "Could not initialise." << std::endl;
  }
}

sdlxvulkan::Application::~Application() = default;

// Interface
//============================================================
int sdlxvulkan::Application::execute()
{
  if (m_implementation)
  {
    return imp()->execute();
  }
  else
  {
    return EXIT_FAILURE;
  }
}