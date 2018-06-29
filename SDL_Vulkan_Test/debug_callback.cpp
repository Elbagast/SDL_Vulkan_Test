#include "debug_callback.hpp"

#include "instance.hpp"
#include "instance_functions.hpp"

#include <cassert>
#include <iostream>

namespace sdlxvulkan
{
  namespace
  {
    //---------------------------------------------------------------------------
    // Debug_Callback_Destroyer
    //---------------------------------------------------------------------------

    class Debug_Callback_Destroyer
    {
    public:
      // Member Data
      //============================================================
      Instance_OLD m_instance;
      VkAllocationCallbacks const* m_allocation_callbacks;

      // Special 6
      //============================================================
      Debug_Callback_Destroyer(Instance_OLD const& a_instance, VkAllocationCallbacks const* a_allocation_callbacks) noexcept :
        m_instance{ a_instance },
        m_allocation_callbacks{ a_allocation_callbacks }
      {
        std::cout << "sdlxvulkan::Debug_Callback_Destroyer::Debug_Callback_Destroyer()" << std::endl;
      }

      // Interface
      //============================================================
      void operator()(VkDebugReportCallbackEXT a_debug_callback) const noexcept
      {
        //assert(m_instance.vk_functions().vkDestroyDebugReportCallbackEXT != nullptr);
        m_instance.vk_functions().vkDestroyDebugReportCallbackEXT(m_instance, a_debug_callback, m_allocation_callbacks);
        std::cout << "sdlxvulkan::Debug_Callback_Destroyer::operator()" << std::endl;
      }
    };
    

    // Callback function that is given to Vulkan. It will interpret
    // the user data void* as an Abstract_Debug_Callback* and call
    // Abstract_Debug_Callback::do_callback on it with the arguments.
    // Always returns VK_FALSE.
    VKAPI_ATTR VkBool32 VKAPI_CALL imp_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg, void* a_user_data)
    {
      static_cast<Abstract_Debug_Callback*>(a_user_data)->do_callback(a_flags, a_obj_type, a_obj, a_location, a_code, a_layer_prefix, a_msg);
      return VK_FALSE;
    }

    
    decltype(auto) make_except_debug_callback
    (
      Instance_OLD const& a_instance,
      PFN_vkDebugReportCallbackEXT a_callback,
      VkDebugReportFlagsEXT a_flags,
      void* a_user_data,
      VkAllocationCallbacks const* a_allocation_callbacks
    )
    {
      // If we break here then the instance initialisation failed to get the extension function pointers.
      // This probably means VK_EXT_DEBUG_REPORT_EXTENSION_NAME was not in the extension names used to
      // create the Instance.

      VkDebugReportCallbackEXT l_debug_callback{};

      VkDebugReportCallbackCreateInfoEXT l_callback_info{};
      l_callback_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
      l_callback_info.pNext = nullptr;
      l_callback_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
      l_callback_info.pfnCallback = a_callback;
      l_callback_info.pUserData = a_user_data;

      // Maybe an extension readiness check here via the instance functions?
      if (a_instance.vk_functions().vkCreateDebugReportCallbackEXT(a_instance, &l_callback_info, a_allocation_callbacks, &l_debug_callback) != VK_SUCCESS)
      {
        throw std::runtime_error("Vulkan: Failed to set up debug callback!");
      }
      return make_except_vulkan_sptr<VkDebugReportCallbackEXT, Debug_Callback_Destroyer>(l_debug_callback, a_instance, a_allocation_callbacks);
    }
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Abstract_Debug_Callback
//---------------------------------------------------------------------------


// Special 6
//============================================================

sdlxvulkan::Abstract_Debug_Callback::Abstract_Debug_Callback
(
  Instance_OLD const& a_instance,
  VkDebugReportFlagsEXT a_flags,
  VkAllocationCallbacks const* a_allocation_callbacks
) :
  m_data{ make_except_debug_callback(a_instance, sdlxvulkan::imp_callback, a_flags, static_cast<void*>(this), a_allocation_callbacks) }
{
  //std::cout << "sdlxvulkan::Debug_Callback::Debug_Callback()" << std::endl;
}

sdlxvulkan::Abstract_Debug_Callback::~Abstract_Debug_Callback()
{
  //std::cout << "sdlxvulkan::Debug_Callback::~Debug_Callback()" << std::endl;
}

sdlxvulkan::Instance_OLD const& sdlxvulkan::Abstract_Debug_Callback::get_instance() const noexcept
{
  return std::get_deleter<Debug_Callback_Destroyer>(m_data)->m_instance;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Debug_Callback_Message_Cerr
//---------------------------------------------------------------------------


// Special 6
//============================================================
sdlxvulkan::Debug_Callback_Message_Cerr::Debug_Callback_Message_Cerr
(
  Instance_OLD const& a_instance,
  VkAllocationCallbacks const* a_allocation_callbacks
) :
  Abstract_Debug_Callback{ a_instance, VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT, a_allocation_callbacks }
{
}
sdlxvulkan::Debug_Callback_Message_Cerr::~Debug_Callback_Message_Cerr() = default;

// Interface
//============================================================
// Implement this to use the data and do whatever.
void sdlxvulkan::Debug_Callback_Message_Cerr::do_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg)
{
  std::cerr << "DEBUG: " << a_msg << std::endl << std::endl;
}