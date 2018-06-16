#include "debug_callback.hpp"

#include "instance.hpp"

#include <cassert>
#include <iostream>


namespace sdlxvulkan
{
  namespace
  {
    VkDebugReportCallbackEXT make_debug_callback(Instance const& a_instance, PFN_vkDebugReportCallbackEXT a_callback, VkDebugReportFlagsEXT a_flags)
    {
      VkDebugReportCallbackEXT l_debug_callback{};

      VkDebugReportCallbackCreateInfoEXT l_callback_info{};
      l_callback_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
      l_callback_info.pNext = nullptr;
      l_callback_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
      l_callback_info.pfnCallback = a_callback;
      l_callback_info.pUserData = nullptr;

      if (a_instance.vkCreateDebugReportCallbackEXT(&l_callback_info, nullptr, &l_debug_callback) != VK_SUCCESS)
      {
        throw std::runtime_error("Vulkan: Failed to set up debug callback!");
      }
      return l_debug_callback;
    }


    //---------------------------------------------------------------------------
    // Debug_Callback_Destroyer
    //---------------------------------------------------------------------------

    class Debug_Callback_Destroyer
    {
    private:
      // Member Data
      //============================================================
      mutable Instance m_instance;

    public:
      // Special 6
      //============================================================
      Debug_Callback_Destroyer(Instance const& a_instance) :
        m_instance{ a_instance }
      {
      }
      ~Debug_Callback_Destroyer() = default;

      Debug_Callback_Destroyer(Debug_Callback_Destroyer const& a_other) = default;
      Debug_Callback_Destroyer& operator=(Debug_Callback_Destroyer const& a_other) = default;

      Debug_Callback_Destroyer(Debug_Callback_Destroyer && a_other) = default;
      Debug_Callback_Destroyer& operator=(Debug_Callback_Destroyer && a_other) = default;

      // Interface
      //============================================================
      void operator()(VkDebugReportCallbackEXT a_debug_callback) const noexcept
      {
        m_instance.vkDestroyDebugReportCallbackEXT(a_debug_callback, nullptr);
        std::cout << "sdlxvulkan::Debug_Callback_Destroyer::operator()" << std::endl;
      }
    };
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Surface
//---------------------------------------------------------------------------

// Special 6
//============================================================

sdlxvulkan::Debug_Callback::Debug_Callback(Instance const& a_instance, PFN_vkDebugReportCallbackEXT a_callback, VkDebugReportFlagsEXT a_flags) :
  Inherited_Type{ make_debug_callback(a_instance, a_callback, a_flags), Debug_Callback_Destroyer{ a_instance } }
{
  std::cout << "sdlxvulkan::Debug_Callback::Debug_Callback()" << std::endl;
}

sdlxvulkan::Debug_Callback::~Debug_Callback()
{
  std::cout << "sdlxvulkan::Debug_Callback::~Debug_Callback()" << std::endl;
}
