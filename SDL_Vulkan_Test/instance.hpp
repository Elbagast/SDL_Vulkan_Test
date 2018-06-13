#ifndef SDLXVULKAN_INSTANCE_HPP
#define SDLXVULKAN_INSTANCE_HPP

#include <vector>
#include <string>
#include <vulkan/vulkan.h>

namespace sdlxvulkan
{
  class Instance;
  class Physical_Device;
  class Device;
  class Shader;
  class Swapchain;
  class Image_View;


  class Instance
  {
  public:
    std::vector<Physical_Device> get_physical_devices() const;
    Device get_device(Physical_Device const& a_physical_device) const;
  };

  class Device
  {
  public:
    Shader make_shader(std::string const& a_filepath) const;
    Swapchain make_swapchain();// has arguments

  };

  class Swapchain
  {
  public:

  };


  //---------------------------------------------------------------------------
  // Instance
  //---------------------------------------------------------------------------
  // Manages the SDL system and Vulkan instance.

  class Instance
  {
  private:
    // Member Data
    //============================================================
    class Implementation;

    std::unique_ptr<Implementation> m_implementation;

    Implementation* imp() noexcept { return m_implementation.get(); }
    Implementation const* cimp() const noexcept { return m_implementation.get(); }

  public:
    // Special 6
    //============================================================
    Instance();
    ~Instance();

    Application(Application const& a_other) = delete;
    Application& operator=(Application const& a_other) = delete;

    Application(Application && a_other) = delete;
    Application& operator=(Application && a_other) = delete;

    // Interface
    //============================================================
    int execute();
  };
}

#endif // SDLXVULKAN_APPLICATION_HPP