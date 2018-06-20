#ifndef SDLXVULKAN_GLOBAL_FUNCTIONS_HPP
#define SDLXVULKAN_GLOBAL_FUNCTIONS_HPP

#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

#ifndef INCLUDE_STD_CASSERT
#define INCLUDE_STD_CASSERT
#include <cassert>
#endif

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // Global_Functions
  //---------------------------------------------------------------------------
  // Holds pointers to the Vulkan functions that don't require a specific 
  // VkInstance to use - the ones required to make a VkInstance. Also guards
  // access to them so that any usage problems are caught.

  class Global_Functions
  {
  private:
    // Member Data
    //============================================================   
    // The function that will get the others.
    PFN_vkGetInstanceProcAddr m_vkGetInstanceProcAddr;

    // Functions that don't need an instance to use
    PFN_vkCreateInstance m_vkCreateInstance;
    PFN_vkEnumerateInstanceExtensionProperties m_vkEnumerateInstanceExtensionProperties;
    PFN_vkEnumerateInstanceLayerProperties m_vkEnumerateInstanceLayerProperties;
    PFN_vkEnumerateInstanceVersion m_vkEnumerateInstanceVersion;

  public:
    // Special 6
    //============================================================
    // Construct with all the stored function pointers as nullptr. All calls
    // will fail in this state.
    Global_Functions() noexcept;

    // Construct using the supplied vkGetInstanceProcAddr function pointer, 
    // storing it and using it to get the other function pointers. All calls
    // *should* succeed in this state.
    explicit Global_Functions(PFN_vkGetInstanceProcAddr a_vkGetInstanceProcAddr) noexcept;
    
    ~Global_Functions();

    Global_Functions(Global_Functions const& a_other);
    Global_Functions& operator=(Global_Functions const& a_other);

    Global_Functions(Global_Functions && a_other);
    Global_Functions& operator=(Global_Functions && a_other);

    // Interface
    //============================================================
    PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, char const* pName) const noexcept;

    VkResult vkCreateInstance(VkInstanceCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkInstance* pInstance) const noexcept;
    VkResult vkEnumerateInstanceExtensionProperties(char const* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) const noexcept;
    VkResult vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties) const noexcept;
    VkResult vkEnumerateInstanceVersion(uint32_t* pApiVersion) const noexcept;
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Global_Functions
//---------------------------------------------------------------------------
// Holds pointers to the Vulkan functions that don't require a specific 
// VkInstance to use - the ones required to make a VkInstance. Also guards
// access to them so that any usage problems are caught.

// Special 6
//============================================================
inline sdlxvulkan::Global_Functions::~Global_Functions() = default;

inline sdlxvulkan::Global_Functions::Global_Functions(Global_Functions const& a_other) = default;
inline sdlxvulkan::Global_Functions& sdlxvulkan::Global_Functions::operator=(Global_Functions const& a_other) = default;

inline sdlxvulkan::Global_Functions::Global_Functions(Global_Functions && a_other) = default;
inline sdlxvulkan::Global_Functions& sdlxvulkan::Global_Functions::operator=(Global_Functions && a_other) = default;

// Interface
//============================================================
inline PFN_vkVoidFunction sdlxvulkan::Global_Functions::vkGetInstanceProcAddr(VkInstance instance, char const* pName) const noexcept
{
  assert(m_vkGetInstanceProcAddr != nullptr);
  return m_vkGetInstanceProcAddr(instance, pName);
}

inline VkResult sdlxvulkan::Global_Functions::vkCreateInstance(VkInstanceCreateInfo const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkInstance* pInstance) const noexcept
{
  assert(m_vkCreateInstance != nullptr);
  return m_vkCreateInstance(pCreateInfo, pAllocator, pInstance);
}
inline VkResult sdlxvulkan::Global_Functions::vkEnumerateInstanceExtensionProperties(char const* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) const noexcept
{
  assert(m_vkEnumerateInstanceExtensionProperties != nullptr);
  return m_vkEnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties);
}
inline VkResult sdlxvulkan::Global_Functions::vkEnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties) const noexcept
{
  assert(m_vkEnumerateInstanceLayerProperties != nullptr);
  return m_vkEnumerateInstanceLayerProperties(pPropertyCount, pProperties);
}
inline VkResult sdlxvulkan::Global_Functions::vkEnumerateInstanceVersion(uint32_t* pApiVersion) const noexcept
{
  assert(m_vkEnumerateInstanceVersion != nullptr);
  return m_vkEnumerateInstanceVersion(pApiVersion);
}

#endif // SDLXVULKAN_GLOBAL_FUNCTIONS_HPP