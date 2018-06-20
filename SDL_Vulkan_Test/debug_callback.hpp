#ifndef SDLXVULKAN_DEBUG_CALLBACK_HPP
#define SDLXVULKAN_DEBUG_CALLBACK_HPP

#include "handle.hpp"
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Instance;


  static VKAPI_ATTR VkBool32 VKAPI_CALL example_debug_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg, void* a_user_data)
  {
    return VK_FALSE;
  }
  
  //---------------------------------------------------------------------------
  // Debug_Callback
  //---------------------------------------------------------------------------
  // Manages a Vulkan debug callback with reference counting.

  class Debug_Callback :
    private Vulkan_Handle<VkDebugReportCallbackEXT>
  {
  private:
    using Inherited_Type = Vulkan_Handle<VkDebugReportCallbackEXT>;
  public:
    using Inherited_Type::get;
    using Inherited_Type::operator Pointer;

  public:
    // Special 6
    //============================================================
    Debug_Callback(Instance const& a_instance, PFN_vkDebugReportCallbackEXT a_callback, VkDebugReportFlagsEXT a_flags);
    ~Debug_Callback();

    Debug_Callback(Debug_Callback const& a_other);
    Debug_Callback& operator=(Debug_Callback const& a_other);

    Debug_Callback(Debug_Callback && a_other);
    Debug_Callback& operator=(Debug_Callback && a_other);

    // Interface
    //============================================================
  };
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Debug_Callback
//---------------------------------------------------------------------------

// Special 6
//============================================================

inline sdlxvulkan::Debug_Callback::Debug_Callback(Debug_Callback const& a_other) = default;
inline sdlxvulkan::Debug_Callback& sdlxvulkan::Debug_Callback::operator=(Debug_Callback const& a_other) = default;

inline sdlxvulkan::Debug_Callback::Debug_Callback(Debug_Callback && a_other) = default;
inline sdlxvulkan::Debug_Callback& sdlxvulkan::Debug_Callback::operator=(Debug_Callback && a_other) = default;


#endif // SDLXVULKAN_DEBUG_CALLBACK_HPP