#ifndef SDLXVULKAN_DEBUG_CALLBACK_HPP
#define SDLXVULKAN_DEBUG_CALLBACK_HPP

#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#include "vulkan_ptr.hpp"
#endif
#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif 

namespace sdlxvulkan
{
  class Instance_OLD;
  
  //---------------------------------------------------------------------------
  // Abstract_Debug_Callback
  //---------------------------------------------------------------------------
  // Manages a Vulkan debug callback with reference counting. You must supply
  // it with a free function that will be used, along with the situations it
  // is to be used in.

  class Abstract_Debug_Callback
  {
  private:
    // Member Data
    //============================================================   
    using Data_Type = Vulkan_Sptr<VkDebugReportCallbackEXT>;
    Data_Type m_data;

  public:
    // Special 6
    //============================================================
    Abstract_Debug_Callback
    (
      Instance_OLD const& a_instance,
      VkDebugReportFlagsEXT a_flags,
      VkAllocationCallbacks const* a_allocation_callbacks = nullptr
    );
    virtual ~Abstract_Debug_Callback();

    // Interface
    //============================================================
    VkDebugReportCallbackEXT get() const noexcept       { return m_data.get(); }
    operator VkDebugReportCallbackEXT() const noexcept  { return m_data.get(); }

    Instance_OLD const& get_instance() const noexcept;

    // Implement this to use the data and do whatever.
    virtual void do_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg ) = 0;
  };

  //------------------------------------------------------------------------------------------------------------------------------------------------------
  
  //---------------------------------------------------------------------------
  // Debug_Callback_Message_Cerr
  //---------------------------------------------------------------------------
  // Basic Abstract_Debug_Callback implementation that outputs the message to
  // std::cerr when there is an error or a warning.

  class Debug_Callback_Message_Cerr :
    public Abstract_Debug_Callback
  {
  public:
    // Special 6
    //============================================================
    Debug_Callback_Message_Cerr
    (
      Instance_OLD const& a_instance,
      VkAllocationCallbacks const* a_allocation_callbacks = nullptr
    );
    ~Debug_Callback_Message_Cerr() override final;

    // Interface
    //============================================================
    // Implement this to use the data and do whatever.
    void do_callback(VkDebugReportFlagsEXT a_flags, VkDebugReportObjectTypeEXT a_obj_type, uint64_t a_obj, size_t a_location, int32_t a_code, const char* a_layer_prefix, const char* a_msg) override final;
  };  
} // namespace sdlxvulkan

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SDLXVULKAN_DEBUG_CALLBACK_HPP