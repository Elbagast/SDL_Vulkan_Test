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
#include "make_default.hpp"
#include "vulkan_io.hpp"

#include <SDL.h>
#include <SDL_vulkan.h>
#include <vulkan/vulkan.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace sdlxvulkan
{
  namespace
  {

    struct Example_Vertex
    {
      glm::vec3 pos;
      glm::vec3 color;
      glm::vec2 texCoord;

      static auto get_binding_description()
      {
        VkVertexInputBindingDescription l_binding_description{};
        l_binding_description.binding = 0;
        l_binding_description.stride = sizeof(Example_Vertex);
        l_binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return l_binding_description;
      }

      static auto get_attribute_descriptions()
      {
        std::array<VkVertexInputAttributeDescription, 3> l_attribute_descriptions{};

        l_attribute_descriptions[0].binding = 0;
        l_attribute_descriptions[0].location = 0;
        l_attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        l_attribute_descriptions[0].offset = offsetof(Example_Vertex, pos);

        l_attribute_descriptions[1].binding = 0;
        l_attribute_descriptions[1].location = 1;
        l_attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        l_attribute_descriptions[1].offset = offsetof(Example_Vertex, color);

        l_attribute_descriptions[2].binding = 0;
        l_attribute_descriptions[2].location = 2;
        l_attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        l_attribute_descriptions[2].offset = offsetof(Example_Vertex, texCoord);

        return l_attribute_descriptions;
      }

      static auto get_attribute_descriptions_vector()
      {
        std::vector<VkVertexInputAttributeDescription> l_attribute_descriptions{};
        l_attribute_descriptions.resize(3);

        l_attribute_descriptions[0].binding = 0;
        l_attribute_descriptions[0].location = 0;
        l_attribute_descriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        l_attribute_descriptions[0].offset = offsetof(Example_Vertex, pos);

        l_attribute_descriptions[1].binding = 0;
        l_attribute_descriptions[1].location = 1;
        l_attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        l_attribute_descriptions[1].offset = offsetof(Example_Vertex, color);

        l_attribute_descriptions[2].binding = 0;
        l_attribute_descriptions[2].location = 2;
        l_attribute_descriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        l_attribute_descriptions[2].offset = offsetof(Example_Vertex, texCoord);

        return l_attribute_descriptions;
      }
    };

    static std::vector<Example_Vertex> const c_vertices =
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
    static std::vector<uint32_t> const c_indices =
    {
      0, 1, 2, 2, 3, 0,
      4, 5, 6, 6, 7, 4
    };

    struct Example_Uniform_Buffer_Object
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
    std::vector<std::string> const c_validation_layers{ };
#else
    constexpr bool c_enable_validation_layers = true;
    std::vector<std::string> const c_extension_names{ VK_EXT_DEBUG_REPORT_EXTENSION_NAME };
    std::vector<std::string> const c_validation_layers = { "VK_LAYER_LUNARG_standard_validation" };
    //std::vector<std::string> const c_extension_names{  };
    //std::vector<std::string> const c_validation_layers = {  };
#endif

    // This is the number of frames we will buffer for. The swap chain MIGHT 
    // have a different number.
    constexpr size_t c_frames_in_flight{ 2 };

    // Top left corner position of the window from the top left corner 
    constexpr int c_start_x_pos{ 100 };
    constexpr int c_start_y_pos{ 100 };

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
}

namespace sdlxvulkan
{
  class Abstract_Event_Handler
  {
  public:
    virtual ~Abstract_Event_Handler() = default;

    virtual void handle_event(SDL_Event const& a_event) = 0;
  };

  class Event_Logger :
    public Abstract_Event_Handler
  {
  private:
    std::ostream& m_ostream;
  public:
    explicit Event_Logger(std::ostream& a_ostream) :
      m_ostream{ a_ostream }
    {}

    ~Event_Logger() override = default;

    void handle_event(SDL_Event const& a_event) override
    {
      auto l_type = static_cast<SDL_EventType>(a_event.type);

      switch (l_type)
      {
      // Quit Event
      case SDL_QUIT:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.quit.timestamp
          << " ]"
          << std::endl;
        break;

      // Application Events
      // Have no special data and are largely platform specific (iOS)
      case SDL_APP_TERMINATING:
      case SDL_APP_LOWMEMORY:
      case SDL_APP_WILLENTERBACKGROUND:
      case SDL_APP_DIDENTERBACKGROUND:
      case SDL_APP_WILLENTERFOREGROUND:
      case SDL_APP_DIDENTERFOREGROUND:
        m_ostream 
          << to_c_string(l_type) 
          << std::endl;
        break;

      // Window Events
      case SDL_WINDOWEVENT:
        m_ostream 
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.window.timestamp
          << " windowid=" << a_event.window.windowID
          << " event= " << to_c_string(static_cast<SDL_WindowEventID>(a_event.window.event))
          << " data1= " << a_event.window.data1
          << " data2= " << a_event.window.data2
          << " ]"
          << std::endl;
        break;

      // This event is disabled by default...
      case SDL_SYSWMEVENT:
        m_ostream 
          << to_c_string(l_type) 
          << " ["
          << " timestamp=" << a_event.syswm.timestamp
          << " system message ptr=" << a_event.syswm.msg // non-portable data
          << " ]" 
          << std::endl;
        break;

      // Keyboard Events
      case SDL_KEYDOWN: // fall through to next as it has the same data
      case SDL_KEYUP:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " state=" << (a_event.key.state == 0 ? false : true)
          << " repeat=" << (a_event.key.repeat == 0 ? false : true)
          << " scancode=" << to_c_string(a_event.key.keysym.scancode)
          << " keycode=" << a_event.key.keysym.sym // need to decode this...
          << " keymods=[ " << all_keymods(a_event.key.keysym.mod) 
          << "] ]"
          << std::endl;
        break;

      case SDL_TEXTEDITING:

      case SDL_TEXTINPUT:

      // When the OS has changed the keymap
      // Nothing special here
      case SDL_KEYMAPCHANGED:
        m_ostream
          << to_c_string(l_type)
          << std::endl;
        break;

      // Mouse Events
      case SDL_MOUSEMOTION:
        m_ostream 
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.motion.timestamp
          << " windowid=" << a_event.motion.windowID
          << " mouseid=" << a_event.motion.which // could be a touch input
          << " buttons=[ " << all_mouse_buttons(a_event.motion.state) << "]"
          << " pos=[ " << a_event.motion.x << "," << a_event.motion.y << " ]"// window coord
          << " mov=[ " << a_event.motion.xrel << "," << a_event.motion.yrel << " ]" // movement since last move
          << " ]"
          << std::endl;
        break;

      case SDL_MOUSEBUTTONDOWN: // fall through to next as it has the same data
      case SDL_MOUSEBUTTONUP:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.button.timestamp
          << " windowid=" << a_event.button.windowID
          << " mouseid=" << a_event.button.which // could be a touch input
          << " button=" << mouse_button_to_c_string(a_event.button.button) 
          << " pressed=" << (a_event.button.state == 0 ? false : true)
          << " clicks=" << static_cast<int>(a_event.button.clicks)
          << " pos=[ " << a_event.button.x << "," << a_event.button.y << " ]"// window coord
          << " ]"
          << std::endl;
        break;

      case SDL_MOUSEWHEEL:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.wheel.timestamp
          << " windowid=" << a_event.wheel.windowID
          << " mouseid=" << a_event.wheel.which // could be a touch input
          << " x=" << a_event.wheel.x // +right, -left
          << " y=" << a_event.wheel.y // +up, -down, unless flipped
          << " flipped=" << (a_event.wheel.direction == SDL_MOUSEWHEEL_NORMAL ? false : true)
          << " ]"
          << std::endl;
        break;

      // Joystick Events
      case SDL_JOYAXISMOTION:

      case SDL_JOYBALLMOTION:

      case SDL_JOYHATMOTION :

      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:

      case SDL_JOYDEVICEADDED:
      case SDL_JOYDEVICEREMOVED:

      // Controller Events
      case SDL_CONTROLLERAXISMOTION:

      case SDL_CONTROLLERBUTTONDOWN:
      case SDL_CONTROLLERBUTTONUP:

      case SDL_CONTROLLERDEVICEADDED:
      case SDL_CONTROLLERDEVICEREMOVED:
      case SDL_CONTROLLERDEVICEREMAPPED:

      // Touch Events
      case SDL_FINGERDOWN:
      case SDL_FINGERUP:
      case SDL_FINGERMOTION:

      // Gesture Events
      case SDL_DOLLARGESTURE:
      case SDL_DOLLARRECORD:

      case SDL_MULTIGESTURE:

      // Clipboard Events
      // Nothing special here, have to get the clipboard data elsewhere.
      case SDL_CLIPBOARDUPDATE:
        m_ostream
          << to_c_string(l_type)
          << std::endl;
        break;

      // Drag and Drop Events
      // Got to enable these events to use them.
      // i.e.
      // SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
      case SDL_DROPFILE: // fall through to next as it has the same data
      case SDL_DROPTEXT: // fall through to next as it has the same data
      case SDL_DROPBEGIN: // fall through to next as it has the same data
      case SDL_DROPCOMPLETE:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.drop.timestamp
          << " file=" << a_event.drop.file // oh shit this has to be freed..........LEAK HERE
          << " windowid=" << a_event.drop.windowID
          << " ]"
          << std::endl;
        // hmmm...need to call this if done with the event
        //SDL_free(a_event.drop.file);
        break;

      // Audio Hotplug Events
      case SDL_AUDIODEVICEADDED: // fall through to next as it has the same data
      case SDL_AUDIODEVICEREMOVED:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " timestamp=" << a_event.adevice.timestamp
          << " index=" << a_event.adevice.which // index in previous call to get audio devices
          << " iscapture=" << (a_event.adevice.iscapture == 0 ? false : true) // true if microphone
          << " ]"
          << std::endl;
        break;

      // Render Events
      case SDL_RENDER_TARGETS_RESET:
        m_ostream
          << to_c_string(l_type)
          << std::endl;
        break;

      case SDL_RENDER_DEVICE_RESET:
        m_ostream
          << to_c_string(l_type)
          << std::endl;
        break;

      // User Events
      case SDL_USEREVENT:
        m_ostream
          << to_c_string(l_type)
          << " ["
          << " type=" << a_event.user.type
          << " timestamp=" << a_event.user.timestamp
          << " windowid=" << a_event.user.windowID
          << " code=" << a_event.user.code
          << " data1=" << a_event.user.data1
          << " data2=" << a_event.user.data2
          << " iscapture=" << (a_event.adevice.iscapture == 0 ? false : true) // true if microphone
          << " ]"
          << std::endl;

      default:
        m_ostream 
          << to_c_string(l_type) 
          << std::endl;
        break;
      }      
    }
  };
  
  class Event_Pump
  {
  private:
    std::uintmax_t m_next_tick;
    std::uintmax_t m_previous_tick;
    std::vector<SDL_EventType> m_previous_tick_event_types;

  public:
    Event_Pump() :
      m_next_tick{ 0 },
      m_previous_tick{ 0 },
      m_previous_tick_event_types{}
    {
      // We probably don't need room for many.
      m_previous_tick_event_types.reserve(16);
    }

    // Number of the last tick that had it's events processed.
    std::uintmax_t previous_tick() const noexcept
    {
      return m_previous_tick;
    }
    // Number of the next tick to be processed.
    std::uintmax_t current_tick() const noexcept
    {
      return m_next_tick;
    }
    // Number of events that the last tick had.
    std::size_t previous_tick_event_count() const noexcept
    {
      return m_previous_tick_event_types.size();
    }
    // The event types for the last tick processed
    std::vector<SDL_EventType> const& previous_tick_event_types() const noexcept
    {
      return m_previous_tick_event_types;
    }
    // Process all available events, then update the tick tracking.
    void do_tick_events(Abstract_Event_Handler& a_handler)
    {
      m_previous_tick_event_types.clear();

      // We will poll into this object.
      SDL_Event l_event{};
      // And count the events.
      std::size_t l_tick_event_count{ 0 };
      // Could track event types too...

      // While there are events poll all of them
      while (SDL_PollEvent(&l_event) != 0)
      {
        m_previous_tick_event_types.push_back(static_cast<SDL_EventType>(l_event.type));
        // Could wrap the event here rather than sending the raw data.
        a_handler.handle_event(l_event);
        //++l_tick_event_count;

        // Need to clean up some kinds of events. Doing this here means we are
        // done with it. If the event was wrapped the destructor would handle this.
        if (l_event.type <= SDL_DROPFILE && l_event.type >= SDL_DROPCOMPLETE)
        {
          SDL_free(l_event.drop.file);
        }
      }

      // Alter state tracking
      //m_previous_tick_event_count = l_tick_event_count;
      m_previous_tick = m_next_tick;
      ++m_next_tick;
    }
  };
}

//---------------------------------------------------------------------------
// Application::Implementation
//---------------------------------------------------------------------------
// Hide all the implementation details and private functions for the 
// application state.

namespace sdlxvulkan
{
  class Application::Implementation :
    public Abstract_Event_Handler
  {
  private:
    std::vector<std::string> m_args;
    Event_Pump m_event_pump;
    Event_Logger m_event_logger;
    bool m_quit;

    System m_system;
    Window m_window;
    Handle<VkInstance> m_instance;
    Instance_Functions const* m_instance_functions;

    Handle<VkDebugReportCallbackEXT> m_debug_callback;
    Handle<VkSurfaceKHR> m_surface;

    //--------------------
    // Physical Device

    VkPhysicalDevice m_physical_device;

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

    VkQueue m_graphics_queue;
    VkQueue m_present_queue;

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
    Example_Uniform_Buffer_Object m_ubo;

    Image_Trio m_depth;
    
    Handle<VkDescriptorPool> m_descriptor_pool;
    std::vector<VkDescriptorSet> m_descriptor_sets;

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
    //Handle<VkCommandBuffer> m_fixed_command_buffer;

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
    void handle_event(SDL_Event const& a_event) override;

    int execute();

    void main_loop();
                
    void resize();
            
    void write_fixed_commands();
    void write_frame_commands(uint32_t a_swapchain_image_index);
    
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
  Abstract_Event_Handler(),
  m_args{ make_arg_vector(argc, argv) },
  m_event_pump{},
  m_event_logger{std::cout},
  m_quit{false},
  m_system{ SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER },
  m_window{ m_system, c_application_name, c_start_x_pos, c_start_y_pos, c_start_width, c_start_height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN },
  
  m_instance{ app_make_instance(m_system, m_window, c_extension_names, c_validation_layers, c_application_name, c_application_version, c_engine_name, c_engine_version, c_vulkan_version) },
  m_instance_functions{ get_instance_functions(m_instance) },
  m_debug_callback{ app_make_debug_report_callback_ext(m_instance, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, debug_callback) },
  m_surface{ make_surface_khr(m_instance, m_window) },
  m_physical_device{ get_physical_devices(m_instance).front() },
  m_supported_features{ get_physical_device_features(m_instance, m_physical_device) },
  m_required_features{ app_make_required_device_features(m_supported_features) },
  m_depth_format{ find_depth_format(m_instance, m_physical_device) },

  // If we wanted to manage queue families in more detail then stuff goes here.
  m_graphics_qfi{ first_graphics_qfi(m_instance, m_physical_device) },
  m_present_qfi{ first_present_qfi(m_instance, m_physical_device, m_surface) },
  m_device{ app_make_device(m_instance, m_physical_device, m_graphics_qfi, m_present_qfi, m_required_features, c_device_extension_names) },
  m_device_functions{ get_device_functions(m_device) },

  m_graphics_queue{ make_queue(m_device, m_graphics_qfi, 0) },
  m_present_queue{ make_queue(m_device, m_present_qfi, 0) },

  m_command_pool{ app_make_command_pool(m_device, m_graphics_qfi, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT) },
  
  m_descriptor_set_layout{ app_make_descriptor_set_layout(m_device) },

  m_shaders{ app_make_shader_group(m_device, m_args[0]) },
  
  //m_texture_data{ get_filepath(m_args[0], u8"texture.jpg") },
  m_texture{ app_make_texture_image_trio(m_instance, m_physical_device, m_device, m_command_pool, m_graphics_queue, get_filepath(m_args[0], u8"textures\\example.jpg")) },
  m_sampler{ app_make_sampler(m_device, m_required_features) },

  m_swapchain{ app_make_swapchain(m_instance, m_physical_device, m_device, m_surface, m_graphics_qfi, m_present_qfi, c_frames_in_flight, app_get_window_draw_width(m_window), app_get_window_draw_height(m_window)) },
  
  m_vertex{ app_make_vertex_buffer_pair(m_instance, m_physical_device, m_device, m_command_pool, m_graphics_queue, sizeof(c_vertices[0]) * c_vertices.size(), c_vertices.data()) },
  
  m_index{ app_make_index_buffer_pair(m_instance, m_physical_device, m_device, m_command_pool, m_graphics_queue, sizeof(c_indices[0]) * c_indices.size(), c_indices.data()) },

  m_uniforms{ app_make_uniforms(m_instance, m_physical_device, m_device, c_frames_in_flight, sizeof(Example_Uniform_Buffer_Object)) },
  m_ubo{},

  m_depth{ app_make_depth_image_trio(m_instance, m_physical_device, m_device, m_command_pool, m_graphics_queue, m_swapchain.extent.width, m_swapchain.extent.height) },

  m_descriptor_pool{ app_make_descriptor_pool(m_device, c_frames_in_flight) },

  m_descriptor_sets{ app_make_descriptor_sets(m_device, m_descriptor_set_layout, m_descriptor_pool, m_texture, m_sampler, m_uniforms, sizeof(Example_Uniform_Buffer_Object), c_frames_in_flight) },

  // Render Pass
  m_render_pass{ app_make_render_pass(m_device, m_swapchain.format, m_depth_format) },

  // Pipeline
  m_viewport{ app_make_viewport(m_swapchain) },
  m_scissor{ app_make_scissor(m_swapchain) },
  m_pipeline_cache{ app_make_pipeline_cache(m_device) },
  m_pipeline_layout{ app_make_pipeline_layout(m_device, m_descriptor_set_layout) },
  m_pipeline{ app_make_dynamic_pipeline(m_device, m_pipeline_cache, m_pipeline_layout, m_render_pass, m_shaders, {Example_Vertex::get_binding_description()}, Example_Vertex::get_attribute_descriptions_vector()) },//, { m_viewport }, { m_scissor }) },

  m_swapchain_framebuffers{ app_make_swapchain_framebuffers(m_device, m_swapchain, m_render_pass, m_depth) }, // make at render time?...

  m_command_buffers{ app_make_primary_command_buffers(m_device, m_command_pool, c_frames_in_flight) },
 
  // Sync Objects
  m_image_available_semaphores{ app_make_semaphores(m_device, c_frames_in_flight) },
  m_render_finished_semaphores{ app_make_semaphores(m_device, c_frames_in_flight) },
  m_fences{ app_make_fences(m_device, c_frames_in_flight, VK_FENCE_CREATE_SIGNALED_BIT) },
  m_current_frame{0}
{
  std::cout << "Application::Implementation::Implementation(argc, * argv)" << std::endl;
  // Output the captured args to the console.
  std::cout << "Args:" << std::endl;
  for (auto const& i : m_args)
  {
    std::cout << i << std::endl;
  }

  //write_commands();
  write_fixed_commands();
}

sdlxvulkan::Application::Implementation::~Implementation() = default;

// Interface
//============================================================
void sdlxvulkan::Application::Implementation::handle_event(SDL_Event const& a_event)
{
  m_event_logger.handle_event(a_event);

  if (a_event.type == SDL_QUIT)
  {
    m_quit = true;
  }
  else if (a_event.type == SDL_WINDOWEVENT && a_event.window.windowID == m_window.id())
  {
    //std::cout << sdl_window_event_string(static_cast<SDL_WindowEventID>(l_event.window.event)) << std::endl;
    if (a_event.window.event == SDL_WINDOWEVENT_RESIZED) // everytime the user resizes the window
    {
      int l_window_width{ a_event.window.data1 };
      int l_window_height{ a_event.window.data2 };

      int l_draw_width{ 0 };
      int l_draw_height{ 0 };

      SDL_Vulkan_GetDrawableSize(m_window, &l_draw_width, &l_draw_height);

      //m_width = l_draw_width;
      //m_height = l_draw_height;
      //std::cout << "Window Resized:" << std::endl;
      //std::cout << "window = " << l_window_width << "x" << l_window_height << std::endl;
      //std::cout << "draw = " << l_window_width << "x" << l_window_height << std::endl;

      resize();
    }
  }
  else if (a_event.type == SDL_KEYDOWN)
  {
    //std::cout << "Keydown: ";
    if (a_event.key.keysym.sym == SDLK_f)
    {
      //std::cout << "f" << std::endl;
      // Fake fullscreen - use the same resolution
      //Uint32 l_fullscreen_flag = SDL_WINDOW_FULLSCREEN;
      // Fullscreen at desktop size
      Uint32 l_fullscreen_flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
      // Bitwise and results in a non-zero value if the bits are present in both
      bool l_is_fullscreen = SDL_GetWindowFlags(m_window) & l_fullscreen_flag;
      SDL_SetWindowFullscreen(m_window, l_is_fullscreen ? 0 : l_fullscreen_flag);
      SDL_ShowCursor(l_is_fullscreen);
    }
    else if (a_event.key.keysym.sym == SDLK_q)
    {
      m_quit = true;
    }
  }
}

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
  catch (...)
  {
    std::cout << u8"Unknown failure." << std::endl;
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
  //SDL_Event l_event{};
  //bool l_quit{ false };
  size_t l_frame_count{ 0 };
  auto l_start_time = std::chrono::steady_clock::now();
  auto l_last_time = l_start_time;
  auto l_now_time = l_last_time;

  // event processing tracking
  //std::size_t l_tick_count{ 0 };
  //bool l_tick_processed{ false };
  //std::size_t l_tick_event_count{ 0 };


  while (!m_quit)
  {
    // Do any events.
    m_event_pump.do_tick_events(*this);
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

    // log event processing
    if (m_event_pump.previous_tick_event_count() != 0)
    {
      std::cout << "tick #" << m_event_pump.previous_tick() << " had " << m_event_pump.previous_tick_event_count() << " events: ";
      for (auto l_event_type : m_event_pump.previous_tick_event_types())
      {
        std::cout << to_c_string(l_event_type) << " ";
      }
      std::cout << std::endl;
    }

    // state updating
    update_uniform_buffer();


    // Drawing
    //write_commands();
    draw_frame();
    ++l_frame_count;


    
    // Benchmarking
    //std::chrono::duration<double> l_dif = l_now_time - l_start_time;
    l_now_time = std::chrono::steady_clock::now();
    //if (l_dif.count() >= 10.0)
    //{
    //  m_quit = true;
    //}
    
    // Tick rate limit
    //SDL_Delay(32); //~30FPS
    //SDL_Delay(16); //~60FPS
    //SDL_Delay(8); //~120FPS
    //SDL_Delay(1);    
  }
  std::chrono::duration<double> l_elapsed = l_now_time - l_start_time;
  auto l_elapsed_time = l_elapsed.count();
  std::cout << "Time: " << l_elapsed_time << std::endl;
  std::cout << "Frames: " << l_frame_count << std::endl;
  std::cout << "FPS: " << l_frame_count/ l_elapsed_time << std::endl;
  
  // Wait for the device to be done before ending.
  vkDeviceWaitIdle(m_device);
}

void sdlxvulkan::Application::Implementation::resize()
{
  std::cout << "sdlxvulkan::Application::Implementation::do_resize()" << std::endl;

  // Wait for nothing to be going on so stuff doesn't break
  m_device_functions->vkDeviceWaitIdle(m_device);

  // Reset all the associated command buffers instead of completely remaking them
  //m_device_functions->vkResetCommandPool(m_device, m_command_pool, 0);

  // At this point the window size has changed already.
  auto l_width = app_get_window_draw_width(m_window);
  auto l_height = app_get_window_draw_height(m_window);
  // not currently cached...

  // Windows 10 will auto-scale the image but it looks crap so we want to change the
  // render image to the new size. Since the current setup is still valid, but not
  // optimal, we build then swap in things that need to change.

  auto l_new_swapchain = app_make_swapchain(m_instance, m_physical_device, m_device, m_surface, m_graphics_qfi, m_present_qfi, c_frames_in_flight, l_width, l_height, m_swapchain.handle);
  auto l_new_viewport = app_make_viewport(l_new_swapchain);
  auto l_new_scissor = app_make_scissor(l_new_swapchain);

  // Conditional remake of renderpass.
  Handle<VkRenderPass> l_new_render_pass{};

  // Only make a new one if the swapchain format changed.
  if (l_new_swapchain.format != m_swapchain.format)
  {
    //std::cout << "render pass changed" << std::endl;
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
    l_new_pipeline = app_make_dynamic_pipeline(m_device, m_pipeline_cache, m_pipeline_layout, l_new_render_pass, m_shaders, { Example_Vertex::get_binding_description() }, Example_Vertex::get_attribute_descriptions_vector());// , { l_new_viewport }, { l_new_scissor });
  }
  // Else we only have dynamic changes that get handled in drawing.
  else
  {
    // or check before swapping?
    l_new_pipeline = m_pipeline;
  }

  // Make a new depth buffer because it must have the new size.
  auto l_new_depth = app_make_depth_image_trio(m_instance, m_physical_device, m_device, m_command_pool, m_graphics_queue, l_new_swapchain.extent.width, l_new_swapchain.extent.height);

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
  
  //write_fixed_commands();
  // rebuild the commands since these don't change each frame right now.
  //write_commands();
}

void sdlxvulkan::Application::Implementation::write_fixed_commands()
{
  // Put all of the commands that won't change each frame in a secondary
  // command buffer that will only be used by the frame primary command
  // buffer.
  // Apparently this doesn't do what I thought it does.
  /*
  m_device_functions->vkResetCommandBuffer(m_fixed_command_buffer, 0);
  
  VkCommandBufferInheritanceInfo l_inheritance_info{};
  l_inheritance_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  l_inheritance_info.pNext = nullptr;
  l_inheritance_info.renderPass = m_render_pass; // if running inside a render pass
  l_inheritance_info.subpass = 0;
  l_inheritance_info.framebuffer = VK_NULL_HANDLE;
  l_inheritance_info.occlusionQueryEnable = VK_FALSE;
  l_inheritance_info.queryFlags =  0;
  l_inheritance_info.pipelineStatistics = 0;
  
  VkCommandBufferBeginInfo l_begin_info {};
  l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT | VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
  l_begin_info.pInheritanceInfo =  &l_inheritance_info; // Required for secondary command buffers

  if (m_device_functions->vkBeginCommandBuffer(m_fixed_command_buffer, &l_begin_info) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to begin recording command buffer.");
  }

  // This ended up being a failed experiment.

  if (m_device_functions->vkEndCommandBuffer(m_fixed_command_buffer) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to record command buffer.");
  }
  */
}

void sdlxvulkan::Application::Implementation::write_frame_commands(uint32_t a_swapchain_image_index)
{
  // if we want to detcach this from the swapchain we need to supply the following:
  // - VkFramebuffer to render into
  // - VkExtent of the entire render area
  // - VkViewport(s) for the pipeline(s) to use (currently just derived from the swapchain and cached)
  // - VkScissor(s) for the pipeline(s) to use (currently just derived from the swapchain and cached)

  // Reset so we can write again
  m_device_functions->vkResetCommandBuffer(m_command_buffers[m_current_frame], 0);
    
  // Begin the command buffer
  VkCommandBufferBeginInfo l_begin_info = make_default<VkCommandBufferBeginInfo>();
  //l_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  l_begin_info.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
  l_begin_info.pInheritanceInfo = nullptr; // Optional

  if (m_device_functions->vkBeginCommandBuffer(m_command_buffers[m_current_frame], &l_begin_info) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to begin recording command buffer.");
  }

  // BEWARE: VkClearValue is a union, set ONLY ONE MEMBER
  std::array<VkClearValue, 2> l_clear_values {};

  // colour image
  // THIS IS ALSO A UNION: can be float, int32_t, uint32_t
  // Non-float usage depends on the image format...
  l_clear_values[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
  //l_clear_values[0].depthStencil = { 0.0f, 0 }; // ignored

  // depth image
  //l_clear_values[1].color = { 0.0f, 0.0f, 0.0f, 0.0f }; // ignored
  l_clear_values[1].depthStencil = { 1.0f, 0 };

  /*
  // Try and draw a background image
  VkImageBlit l_region{};
  l_region.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  l_region.srcSubresource.mipLevel = 0;
  l_region.srcSubresource.baseArrayLayer = 0;
  l_region.srcSubresource.layerCount = 1;
  l_region.srcOffsets[0] = { 0,0,0 };
  l_region.srcOffsets[1] = { 512,512,1 }; //z must be 1 here for 1D, 2D images
  l_region.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  l_region.dstSubresource.mipLevel = 0;
  l_region.dstSubresource.baseArrayLayer = 0;
  l_region.dstSubresource.layerCount = 1;
  l_region.dstOffsets[0] = { 0,0,0 };
  l_region.dstOffsets[1] = { static_cast<int32_t>(m_swapchain.extent.width), static_cast<int32_t>(m_swapchain.extent.height),1 }; //z must be 1 here for 1D, 2D images
  
  // Can't do this in a render pass.
  // Also the framebuffer gets cleared at the start of a renderpass...
  m_device_functions->vkCmdBlitImage(m_command_buffers[m_current_frame], m_texture.image, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, m_swapchain.images[a_swapchain_image_index], VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, 1, &l_region, VK_FILTER_LINEAR);
  
  // Ok this isn't the way to do this for a swapchain image
  */

  // Begin the render pass
  VkRenderPassBeginInfo l_render_pass_info = make_default<VkRenderPassBeginInfo>();
  //l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  l_render_pass_info.renderPass = m_render_pass;
  l_render_pass_info.framebuffer = m_swapchain_framebuffers[a_swapchain_image_index];
  l_render_pass_info.renderArea.offset.x = 0;
  l_render_pass_info.renderArea.offset.y = 0;
  l_render_pass_info.renderArea.extent = m_swapchain.extent;
  l_render_pass_info.clearValueCount = static_cast<uint32_t>(l_clear_values.size());
  l_render_pass_info.pClearValues = l_clear_values.data();
  
  m_device_functions->vkCmdBeginRenderPass(m_command_buffers[m_current_frame], &l_render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

  // Bind a graphics pipeline - have to do this inside the render pass
  m_device_functions->vkCmdBindPipeline(m_command_buffers[m_current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
  // Got to do this every time things get drawn with a dynamic pipeline.
  // These only do anything if a pipeline is bound in the same command buffer.
  m_device_functions->vkCmdSetViewport(m_command_buffers[m_current_frame], 0, 1, &m_viewport);

  m_device_functions->vkCmdSetScissor(m_command_buffers[m_current_frame], 0, 1, &m_scissor);


  // NEED TO USE A GEOMETRY SHADER FOR THIS
  /*
  // Let's try using multiple scissors
  uint32_t const l_half_x{ m_swapchain.extent.width / 2 };
  uint32_t const l_half_y{ m_swapchain.extent.height / 2 };

  // Need multiple viewports too?...
  std::array<VkViewport, 2> l_viewports{};
  //l_viewports[0] = m_viewport;
  //l_viewports[1] = m_viewport;
  l_viewports[0].x = 0.0f;
  l_viewports[0].y = 0.0f;
  l_viewports[0].width = static_cast<float>(l_half_x);
  l_viewports[0].height = static_cast<float>(l_half_y);
  l_viewports[0].minDepth = 0.0f;
  l_viewports[0].maxDepth = 1.0f;

  l_viewports[1].x = 0.5f;
  l_viewports[1].y = 0.5f;
  l_viewports[1].width = static_cast<float>(l_half_x);
  l_viewports[1].height = static_cast<float>(l_half_y);
  l_viewports[1].minDepth = 0.0f;
  l_viewports[1].maxDepth = 1.0f;
  
  m_device_functions->vkCmdSetViewport(m_command_buffers[m_current_frame], 0, static_cast<uint32_t>(l_viewports.size()), l_viewports.data());

  std::array<VkRect2D, 2> l_scissors{};
  
  // Top left quadrant
  l_scissors[0].offset.x = 0;
  l_scissors[0].offset.y = 0;
  l_scissors[0].extent.width = l_half_x;
  l_scissors[0].extent.height = l_half_y;
  
  // bottom right qudrant
  l_scissors[1].offset.x = l_half_x;
  l_scissors[1].offset.y = l_half_y;
  l_scissors[1].extent.width = l_half_x;
  l_scissors[1].extent.height = l_half_y;

  m_device_functions->vkCmdSetScissor(m_command_buffers[m_current_frame], 0, static_cast<uint32_t>(l_scissors.size()), l_scissors.data());
  */

  // Bind vertex buffers
  std::array<VkBuffer,1> l_vertex_buffers{ m_vertex.buffer };
  std::array<VkDeviceSize, 1> l_offsets { 0 };
  m_device_functions->vkCmdBindVertexBuffers(m_command_buffers[m_current_frame], 0, static_cast<uint32_t>(l_vertex_buffers.size()), l_vertex_buffers.data(), l_offsets.data());
  
  // Bind the index buffer - there can be only one
  m_device_functions->vkCmdBindIndexBuffer(m_command_buffers[m_current_frame], m_index.buffer, 0, VK_INDEX_TYPE_UINT32);

  // Bind descriptor sets
  std::array<VkDescriptorSet, 1> l_descriptor_set{ m_descriptor_sets[m_current_frame] };
  m_device_functions->vkCmdBindDescriptorSets(m_command_buffers[m_current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout, 0, static_cast<uint32_t>(l_descriptor_set.size()), l_descriptor_set.data(), 0, nullptr);
  
  // Test run of push constants.
  static glm::vec4 const s_colour_mod{.5,1,.5,1};
  m_device_functions->vkCmdPushConstants(m_command_buffers[m_current_frame], m_pipeline_layout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(glm::vec4), static_cast<void const*>(&s_colour_mod));
  
  //m_device_functions->vkCmdPushConstants(m_command_buffers[m_current_frame], m_pipeline_layout, VK_SHADER_STAGE_VERTEX_BIT, sizeof(glm::vec4), sizeof(Example_Uniform_Buffer_Object), static_cast<void const*>(&m_ubo));


  // Now we draw using the indices
  m_device_functions->vkCmdDrawIndexed(m_command_buffers[m_current_frame], static_cast<uint32_t>(c_indices.size()), 1, 0, 0, 0);
    
  // End the renderpass 
  m_device_functions->vkCmdEndRenderPass(m_command_buffers[m_current_frame]);




  // Lets try drawing it again in the corner...
  uint32_t const l_half_x{ m_swapchain.extent.width / 2 };
  uint32_t const l_half_y{ m_swapchain.extent.height / 2 };
  
  // if you want to not clear this then the pipeline needs to be changed...
  // BEWARE: VkClearValue is a union, set ONLY ONE MEMBER
  std::array<VkClearValue, 2> l_clear_values2{};

  
  // colour image
  // THIS IS ALSO A UNION: can be float, int32_t, uint32_t
  // Non-float usage depends on the image format...
  l_clear_values2[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
  //l_clear_values[0].depthStencil = { 0.0f, 0 }; // ignored

  // depth image
  //l_clear_values[1].color = { 0.0f, 0.0f, 0.0f, 0.0f }; // ignored
  l_clear_values2[1].depthStencil = { 1.0f, 0 };

  // Begin the render pass
  VkRenderPassBeginInfo l_render_pass_info2 = make_default<VkRenderPassBeginInfo>();
  //l_render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  l_render_pass_info2.renderPass = m_render_pass;
  l_render_pass_info2.framebuffer = m_swapchain_framebuffers[a_swapchain_image_index];
  l_render_pass_info2.renderArea.offset.x = 0;
  l_render_pass_info2.renderArea.offset.y = 0;
  l_render_pass_info2.renderArea.extent.width = l_half_x;
  l_render_pass_info2.renderArea.extent.height = l_half_y;
  l_render_pass_info2.clearValueCount = static_cast<uint32_t>(l_clear_values2.size());
  l_render_pass_info2.pClearValues = l_clear_values2.data();

  m_device_functions->vkCmdBeginRenderPass(m_command_buffers[m_current_frame], &l_render_pass_info2, VK_SUBPASS_CONTENTS_INLINE);

  // Bind a graphics pipeline - have to do this inside the render pass
  m_device_functions->vkCmdBindPipeline(m_command_buffers[m_current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline);
  // Got to do this every time things get drawn with a dynamic pipeline.
  // These only do anything if a pipeline is bound in the same command buffer.
  
  VkViewport l_viewport = make_default<VkViewport>();
  l_viewport.x = 0.0f;
  l_viewport.y = 0.0f;
  l_viewport.width = static_cast<float>(l_half_x);
  l_viewport.height = static_cast<float>(l_half_y);
  l_viewport.minDepth = 0.0f;
  l_viewport.maxDepth = 1.0f;

  m_device_functions->vkCmdSetViewport(m_command_buffers[m_current_frame], 0, 1, &l_viewport);

  VkRect2D l_scissor = make_default<VkRect2D>();

  // Top left quadrant
  l_scissor.offset.x = 0;
  l_scissor.offset.y = 0;
  l_scissor.extent.width = l_half_x;
  l_scissor.extent.height = l_half_y;

  m_device_functions->vkCmdSetScissor(m_command_buffers[m_current_frame], 0, 1, &l_scissor);

  // Bind vertex buffers
  //std::array<VkBuffer, 1> l_vertex_buffers{ m_vertex.buffer };
  //std::array<VkDeviceSize, 1> l_offsets{ 0 };
  m_device_functions->vkCmdBindVertexBuffers(m_command_buffers[m_current_frame], 0, static_cast<uint32_t>(l_vertex_buffers.size()), l_vertex_buffers.data(), l_offsets.data());

  // Bind the index buffer - there can be only one
  m_device_functions->vkCmdBindIndexBuffer(m_command_buffers[m_current_frame], m_index.buffer, 0, VK_INDEX_TYPE_UINT32);

  // Bind descriptor sets
  //std::array<VkDescriptorSet, 1> l_descriptor_set{ m_descriptor_sets[m_current_frame] };
  m_device_functions->vkCmdBindDescriptorSets(m_command_buffers[m_current_frame], VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeline_layout, 0, static_cast<uint32_t>(l_descriptor_set.size()), l_descriptor_set.data(), 0, nullptr);

  // Test run of push constants.
  static glm::vec4 const s_colour_mod2{ 1.0,0.5,0.5,1.0 };
  m_device_functions->vkCmdPushConstants(m_command_buffers[m_current_frame], m_pipeline_layout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(glm::vec4), static_cast<void const*>(&s_colour_mod2));

  // Now we draw using the indices
  m_device_functions->vkCmdDrawIndexed(m_command_buffers[m_current_frame], static_cast<uint32_t>(c_indices.size()), 1, 0, 0, 0);

  // End the renderpass 
  m_device_functions->vkCmdEndRenderPass(m_command_buffers[m_current_frame]);







  // End the command buffer
  if (m_device_functions->vkEndCommandBuffer(m_command_buffers[m_current_frame]) != VK_SUCCESS)
  {
    throw std::runtime_error("Vulkan: Failed to record command buffer.");
  }
}

void sdlxvulkan::Application::Implementation::draw_frame()
{
  // Get the next swapchain image
  //-------------

  //std::cout << "Draw Frame Start" << std::endl;
  std::array<VkFence, 1> l_fences{ m_fences[m_current_frame] };
  m_device_functions->vkWaitForFences(m_device, 1, l_fences.data(), VK_TRUE, std::numeric_limits<uint64_t>::max());
  //std::cout << "waiting for fence "<< m_fences[m_current_frame] << std::endl;
  //vkResetFences(m_device, 1, &m_fences[m_current_frame]);
  if (m_device_functions->vkResetFences(m_device, static_cast<uint32_t>(l_fences.size()), l_fences.data()) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to reset fence." };
  }
  
  // Get the next swapcahin image. Swapchain could have changed.
  uint32_t l_swapchain_image_index{0};
  // since the max for this an insane amount of time, we timeout at less.
  
  //static uint64_t const c_timeout_nanoseconds{ std::numeric_limits<uint64_t>::max() };
  // one second...
  static uint64_t const c_timeout_nanoseconds{ 1000000000 };

  VkResult l_result = m_device_functions->vkAcquireNextImageKHR(m_device, m_swapchain.handle, c_timeout_nanoseconds, m_image_available_semaphores[m_current_frame], VK_NULL_HANDLE, &l_swapchain_image_index);
  if (l_result != VK_SUCCESS)
  {
    std::cout << vkresult_string(l_result) << std::endl;
    if (l_result != VK_SUBOPTIMAL_KHR)
    {
      throw std::runtime_error("Vulkan:: Failed to acquire swap chain image.");
    }
  }

  // Write the render commands
  //-------------

  // If we want to detach rendering from knowing about what it is rendering
  // to, then this needs to change.
  write_frame_commands(l_swapchain_image_index);


  // Execute the render commands
  //-------------

  //std::cout << "current frame = " << m_current_frame << " aquired = " << l_image_index << std::endl;
  // Submit the command quue

  // going to use semaphores to synchronise
  
  std::array<VkSemaphore, 1> l_wait_semaphores { m_image_available_semaphores[m_current_frame] };
  std::array<VkPipelineStageFlags, 1> l_wait_stages { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
  std::array<VkSemaphore, 1> l_signal_semaphores { m_render_finished_semaphores[m_current_frame] };

  assert(!m_command_buffers.empty());
  std::array<VkCommandBuffer,1> l_command_buffers{};
  //l_command_buffers[0] = m_fixed_command_buffer;
  l_command_buffers[0] = m_command_buffers[m_current_frame];

  VkSubmitInfo l_submit_info = make_default<VkSubmitInfo>();
  //l_submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  //l_submit_info.pNext = nullptr;
  l_submit_info.waitSemaphoreCount = static_cast<uint32_t>(l_wait_semaphores.size());
  l_submit_info.pWaitSemaphores = l_wait_semaphores.data();
  l_submit_info.pWaitDstStageMask = l_wait_stages.data();
  l_submit_info.commandBufferCount = static_cast<uint32_t>(l_command_buffers.size());
  l_submit_info.pCommandBuffers = l_command_buffers.data();
  l_submit_info.signalSemaphoreCount = static_cast<uint32_t>(l_signal_semaphores.size());
  l_submit_info.pSignalSemaphores = l_signal_semaphores.data();


  // Finally we send the commands off to be done
  if (m_device_functions->vkQueueSubmit(m_graphics_queue, 1, &l_submit_info, m_fences[m_current_frame]) != VK_SUCCESS)
  {
    throw std::runtime_error{ "Vulkan: Failed to submit command queue." };
  }
  //std::cout << "queue submitted" << std::endl;


  // Present the finished swapchain image
  //-------------
  
  std::array<VkSwapchainKHR, 1> l_swapchains { m_swapchain.handle };

  VkPresentInfoKHR l_present_info = make_default<VkPresentInfoKHR>();
  //l_present_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  //l_present_info.pNext = nullptr;
  l_present_info.waitSemaphoreCount = 1;
  l_present_info.pWaitSemaphores = l_signal_semaphores.data(); // This is the part that means we wait til render is done
  l_present_info.swapchainCount = 1;
  l_present_info.pSwapchains = l_swapchains.data();
  l_present_info.pImageIndices = &l_swapchain_image_index;
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

  Example_Uniform_Buffer_Object l_ubo{};
  l_ubo.model = glm::rotate(glm::mat4(1.0f), l_time * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

  l_ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

  l_ubo.proj = glm::perspective(glm::radians(45.0f), m_swapchain.extent.width / static_cast<float>(m_swapchain.extent.height), 0.1f, 10.0f);

  l_ubo.proj[1][1] *= -1;
  /*
  // can use this to fiddle with the shader...
  float l_change = l_time - static_cast<int>(l_time);
  l_ubo.color.r += l_time;
  l_ubo.color.g += l_time;
  l_ubo.color.b += l_time;
  l_ubo.color.a += l_time;
  */
  m_ubo = l_ubo;

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
  catch (std::runtime_error& a_exception)
  {
    std::cout << a_exception.what() << std::endl;
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