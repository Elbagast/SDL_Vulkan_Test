#ifndef SDLXVULKAN_INSTANCE_HPP
#define SDLXVULKAN_INSTANCE_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#include <vector>
#include <string>
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class System;
  class Window;

  class Instance_Functions;
  class Physical_Device;

  //---------------------------------------------------------------------------
  // Instance
  //---------------------------------------------------------------------------
  // Holds a VkInstance with reference counting and cleans up properly. 

  class Instance
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkInstance>;
    Data_Type m_data;

  public:    
    // Special 6
    //============================================================
    // Create using the supplied data.
    Instance
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
      VkAllocationCallbacks const* a_allocation_callbacks = nullptr
    );

    ~Instance();

    Instance(Instance const& a_other);
    Instance& operator=(Instance const& a_other);

    Instance(Instance && a_other);
    Instance& operator=(Instance && a_other);

    // Interface
    //============================================================
    VkInstance get() const noexcept       { return m_data.get(); }
    operator VkInstance() const noexcept  { return m_data.get(); }

    Instance_Functions const& vk_functions() const;

    System const& get_system() const noexcept;
    Window const& get_window() const noexcept;
    VkAllocationCallbacks const* get_allocation_callbacks() const noexcept;

    uint32_t get_physical_device_count() const noexcept;
    std::vector<Physical_Device> get_physical_devices() const;
  };
  
  
  template
  <
    typename T_Raw_Handle,
    void (Instance_Functions::*T_Instance_Function)(VkInstance, T_Raw_Handle, VkAllocationCallbacks const*) const noexcept,
    void(*T_Post_Function)(void)
  >
    class Instance_Child_Destroyer
  {
  private:
    Instance m_instance;
    VkAllocationCallbacks const* m_allocation_callbacks;
  public:
    Instance_Child_Destroyer(Instance const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks) :
      m_instance{ a_instance },
      m_allocation_callbacks{ a_allocation_callbacks }
    {}

    // Must provide conversion from the handle type to Instance...
    void operator()(T_Raw_Handle a_raw_handle) const noexcept
    {
      (m_instance.vk_functions().*T_Instance_Function)(m_instance, a_raw_handle, m_allocation_callbacks);
      T_Post_Function();
    }

    Instance const& get_instance() const noexcept
    {
      return m_parent;
    }
  };

}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Instance
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Instance::Instance(Instance const& a_other) = default;
inline sdlxvulkan::Instance& sdlxvulkan::Instance::operator=(Instance const& a_other) = default;

inline sdlxvulkan::Instance::Instance(Instance && a_other) = default;
inline sdlxvulkan::Instance& sdlxvulkan::Instance::operator=(Instance && a_other) = default;

#endif // SDLXVULKAN_INSTANCE_HPP