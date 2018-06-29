#ifndef SDLXVULKAN_PHYSICAL_DEVICE_HPP
#define SDLXVULKAN_PHYSICAL_DEVICE_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#include <vector>
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Instance_OLD;
  class Surface_OLD;

  //---------------------------------------------------------------------------
  // Physical_Device
  //---------------------------------------------------------------------------
  // Holds all of the information relating to a Vulkan Physical Device.
  
  class Physical_Device_OLD
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkPhysicalDevice>;
    Data_Type m_data;
        
  public:
    // Special 6
    //============================================================
    Physical_Device_OLD(VkPhysicalDevice a_physical_device, Instance_OLD const& a_instance);
    ~Physical_Device_OLD();

    Physical_Device_OLD(Physical_Device_OLD const& a_other);
    Physical_Device_OLD& operator=(Physical_Device_OLD const& a_other);

    Physical_Device_OLD(Physical_Device_OLD && a_other);
    Physical_Device_OLD& operator=(Physical_Device_OLD && a_other);

    // Interface
    //============================================================
    VkPhysicalDevice get() const noexcept       { return m_data.get(); }
    operator VkPhysicalDevice() const noexcept  { return m_data.get(); }

    Instance_OLD const& get_instance() const noexcept;

    VkPhysicalDeviceProperties get_properties() const;
    VkPhysicalDeviceMemoryProperties get_memory_properties() const;
    std::vector<VkQueueFamilyProperties> get_queue_familiy_properties() const;
    std::vector<VkExtensionProperties> get_extension_properties() const;
    // other things go here

    // Using the supplied properties, determine the right kind of memory to allocate.
    // Success returns the index to the value required to allocate the right type of memory. 
    // Failure throws if no matching memory found.
    uint32_t get_memory_type_from_properties(uint32_t a_typebits, VkMemoryPropertyFlags a_requirements) const;
    
    bool can_graphics() const;
    uint32_t first_graphics_qfi() const;    

    // requires knowledge of the surface. Should this be seperate? 
    // What happens with multiple windows... Is needed by the swapchain
    bool can_present(Surface_OLD const& a_surface) const;
    uint32_t first_present_qfi(Surface_OLD const& a_surface) const;
    
    // Since these can change everytime the surface changes these shouldn't be stashed
    VkSurfaceCapabilitiesKHR get_surface_cababilites(Surface_OLD const& a_surface) const;
    std::vector<VkSurfaceFormatKHR> get_surface_formats(Surface_OLD const& a_surface) const;
    std::vector<VkPresentModeKHR>  get_present_modes(Surface_OLD const& a_surface) const;
  };

  // Using the supplied properties, determine the right kind of memory to allocate.
  // Success returns the index to the value required to allocate the right type of memory. 
  // Failure throws if no matching memory found.
  //uint32_t get_memory_type_from_properties(VkPhysicalDeviceMemoryProperties const& a_properties, uint32_t a_typebits, VkMemoryPropertyFlags a_requirements);

} // namespace sdlxvulkan


//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Physical_Device
//---------------------------------------------------------------------------

// Special 6
//============================================================
inline sdlxvulkan::Physical_Device_OLD::Physical_Device_OLD(Physical_Device_OLD const& a_other) = default;
inline sdlxvulkan::Physical_Device_OLD& sdlxvulkan::Physical_Device_OLD::operator=(Physical_Device_OLD const& a_other) = default;

inline sdlxvulkan::Physical_Device_OLD::Physical_Device_OLD(Physical_Device_OLD && a_other) = default;
inline sdlxvulkan::Physical_Device_OLD& sdlxvulkan::Physical_Device_OLD::operator=(Physical_Device_OLD && a_other) = default;

// Interface
//============================================================


#endif // SDLXVULKAN_PHYSICAL_DEVICE_HPP
