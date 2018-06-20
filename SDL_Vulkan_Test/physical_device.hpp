#ifndef SDLXVULKAN_PHYSICAL_DEVICE_HPP
#define SDLXVULKAN_PHYSICAL_DEVICE_HPP

#include "handle.hpp"
#include "instance.hpp"
#include "surface.hpp"
#include <vector>
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Surface;
  //---------------------------------------------------------------------------
  // Physical_Device
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Physical Device.


  class Physical_Device :
    private Vulkan_Handle<VkPhysicalDevice>
  {
  private:
    using Inherited_Type = Vulkan_Handle<VkPhysicalDevice>;

    VkPhysicalDeviceProperties m_properties;
    VkPhysicalDeviceMemoryProperties m_memory_properties;
    std::vector<VkQueueFamilyProperties> m_queue_familiy_properties;
    std::vector<VkExtensionProperties> m_extension_properties;

    uint32_t m_graphics_qfi;
    uint32_t m_present_qfi;


  public:
    using Inherited_Type::get;
    using Inherited_Type::operator Pointer;

    // Special 6
    //============================================================
    Physical_Device(VkPhysicalDevice a_physical_device, Instance const& a_instance, Surface const& a_surface);
    ~Physical_Device();

    Physical_Device(Physical_Device const& a_other);
    Physical_Device& operator=(Physical_Device const& a_other);

    Physical_Device(Physical_Device && a_other);
    Physical_Device& operator=(Physical_Device && a_other);

    // Interface
    //============================================================

    VkPhysicalDeviceProperties const& get_properties() const noexcept;
    VkPhysicalDeviceMemoryProperties const& get_memory_properties() const noexcept;
    std::vector<VkQueueFamilyProperties> const& get_queue_familiy_properties() const noexcept;
    std::vector<VkExtensionProperties> const& get_extension_properties() const noexcept;

    bool can_graphics() const noexcept;
    
    // If we stash this outside then we don't have to worry about fast access to it in this class.
    uint32_t graphics_qfi() const noexcept;    

    // requires knowledge of the surface. Should this be seperate? 
    // What happens with multiple windows... Is needed by the swapchain
    bool can_present() const noexcept;
    uint32_t present_qfi() const noexcept; 

    // Using the supplied properties, determine the right kind of memory to allocate.
    // Success returns the index to the value required to allocate the right type of memory. 
    // Failure throws if no matching memory found.
    uint32_t get_memory_type_from_properties(uint32_t a_typebits, VkMemoryPropertyFlags  a_requirements) const;

    // Since these can change everytime the surface changes these shouldn't be stashed
    VkSurfaceCapabilitiesKHR get_surface_cababilites(Surface const& a_surface) const;
    std::vector<VkSurfaceFormatKHR> get_surface_formats(Surface const& a_surface) const;
    std::vector<VkPresentModeKHR>  get_present_modes(Surface const& a_surface) const;
  };  
}


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Physical_Device
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Physical_Device::Physical_Device(Physical_Device const& a_other) = default;
inline sdlxvulkan::Physical_Device& sdlxvulkan::Physical_Device::operator=(Physical_Device const& a_other) = default;

inline sdlxvulkan::Physical_Device::Physical_Device(Physical_Device && a_other) = default;
inline sdlxvulkan::Physical_Device& sdlxvulkan::Physical_Device::operator=(Physical_Device && a_other) = default;

// Interface
//============================================================

inline uint32_t sdlxvulkan::Physical_Device::graphics_qfi() const noexcept
{
  return m_graphics_qfi;
}


inline uint32_t sdlxvulkan::Physical_Device::present_qfi() const noexcept
{
  return m_present_qfi;
}


#endif // SDLXVULKAN_WINDOW_HPP
