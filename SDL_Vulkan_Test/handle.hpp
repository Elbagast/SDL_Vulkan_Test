#ifndef SDLXVULKAN_HANDLE_HPP
#define SDLXVULKAN_HANDLE_HPP

#include <type_traits>
#include <memory>
#include "vulkan_ptr.hpp"

namespace sdlxvulkan
{
  // Generising handle some more.
  // How do we make the Destroyer generic?
  /*
  // instance core destroy
  void vkDestroyInstance(VkInstance instance, 
    VkAllocationCallbacks const* pAllocator) const noexcept;

  // instance ext destroy
  void vkDestroyDebugReportCallbackEXT(VkInstance instance, 
    VkDebugReportCallbackEXT callback, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyDebugUtilsMessengerEXT(VkInstance instance, 
    VkDebugUtilsMessengerEXT messenger, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroySurfaceKHR(VkInstance instance, 
    VkSurfaceKHR surface, VkAllocationCallbacks const* pAllocator) const noexcept;

  // device core destroy
  void vkDestroyBuffer(VkDevice device, 
    VkBuffer buffer, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyBufferView(VkDevice device, 
    VkBufferView bufferView, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyCommandPool(VkDevice device, 
    VkCommandPool commandPool, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyDescriptorPool(VkDevice device, 
    VkDescriptorPool descriptorPool, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyDescriptorSetLayout(VkDevice device, 
    VkDescriptorSetLayout descriptorSetLayout, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyDescriptorUpdateTemplate(VkDevice device, 
    VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyDevice(VkDevice device, 
    VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyEvent(VkDevice device, 
    VkEvent event, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyFence(VkDevice device, 
    VkFence fence, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyFramebuffer(VkDevice device, 
    VkFramebuffer framebuffer, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyImage(VkDevice device, 
    VkImage image, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyImageView(VkDevice device, 
    VkImageView imageView, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyPipeline(VkDevice device, 
    VkPipeline pipeline, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyPipelineCache(VkDevice device, 
    VkPipelineCache pipelineCache, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyPipelineLayout(VkDevice device, 
    VkPipelineLayout pipelineLayout, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyQueryPool(VkDevice device, 
    VkQueryPool queryPool, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyRenderPass(VkDevice device, 
    VkRenderPass renderPass, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroySampler(VkDevice device, 
    VkSampler sampler, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroySamplerYcbcrConversion(VkDevice device, 
    VkSamplerYcbcrConversion ycbcrConversion, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroySemaphore(VkDevice device, 
    VkSemaphore semaphore, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyShaderModule(VkDevice device, 
    VkShaderModule shaderModule, VkAllocationCallbacks const* pAllocator) const noexcept;
  
  // device ext destroy
  void vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, 
    VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyIndirectCommandsLayoutNVX(VkDevice device, 
    VkIndirectCommandsLayoutNVX indirectCommandsLayout, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyObjectTableNVX(VkDevice device, 
    VkObjectTableNVX objectTable, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroySamplerYcbcrConversionKHR(VkDevice device, 
    VkSamplerYcbcrConversion ycbcrConversion, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroySwapchainKHR(VkDevice device, 
    VkSwapchainKHR swapchain, VkAllocationCallbacks const* pAllocator) const noexcept;
  void vkDestroyValidationCacheEXT(VkDevice device, 
    VkValidationCacheEXT validationCache, VkAllocationCallbacks const* pAllocator) const noexcept;

  // device core free
  void vkFreeCommandBuffers(VkDevice device, 
    VkCommandPool commandPool, uint32_t commandBufferCount, VkCommandBuffer const* pCommandBuffers) const noexcept;
  VkResult vkFreeDescriptorSets(VkDevice device, 
    VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, VkDescriptorSet const* pDescriptorSets) const noexcept;
  void vkFreeMemory(VkDevice device, 
    VkDeviceMemory memory, VkAllocationCallbacks const* pAllocator) const noexcept;
  */

  // formats:
  // as free functions:
  // void()(VkInstance, VkAllocationCallbacks const*) x1
  // void()(VkInstance, T, VkAllocationCallbacks const*) x3
  // 
  // void()(VkDevice, VkAllocationCallbacks const*) x1
  // void()(VkDevice, T, VkAllocationCallbacks const*) x27
  //
  // void()(VkDevice, T, uint32_t, R*) x3
  
  //class Instance;
  //class Instance_Functions;
    

 

  //---------------------------------------------------------------------------
  // Handle<T>
  //---------------------------------------------------------------------------
  // Explicitly and implicitly convertible reference counted handle.

  template <typename T>
  class Handle
  {
  public:
    using Pointer = std::add_pointer_t<T>;
    using Type = T;
  private:
    //static_assert(std::is_pointer_v<T>, "Supplied T is not a pointer type, cannot use.");
    std::shared_ptr<Type> m_data;
  public:
    // Special 6
    //============================================================
    // Create using the supplied data.
    template <typename Destroyer>
    Handle(Pointer a_ptr, Destroyer a_destroyer);
    explicit Handle(std::shared_ptr<Type> const& a_ptr);
    explicit Handle(std::shared_ptr<Type>&& a_ptr);
    ~Handle();

    Handle(Handle const& a_other);
    Handle& operator=(Handle const& a_other);

    Handle(Handle && a_other);
    Handle& operator=(Handle && a_other);

    // Interface
    //============================================================
    // Explcitly convert.
    Pointer get() const noexcept;

    // Implicitly convert.
    operator Pointer() const noexcept { return get(); }// not having this here breaks things

    template <typename Destroyer>
    Destroyer* get_destroyer() const noexcept
    {
      return std::get_deleter<Destroyer>(m_data);
    }
  };



  template <typename T>
  using Vulkan_Handle = Handle<internal::Vulkan_Handle_Typechecker_T<T>>;


}

//------------------------------------------------------------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------
// Handle<T>
//---------------------------------------------------------------------------

// Special 6
//============================================================
template <typename T>
template <typename Destroyer>
inline sdlxvulkan::Handle<T>::Handle(Pointer a_ptr, Destroyer a_destroyer) :
  m_data{ a_ptr, a_destroyer }
{
}
template <typename T>
inline sdlxvulkan::Handle<T>::Handle(std::shared_ptr<Type> const& a_ptr) :
  m_data{ a_ptr }
{
}
template <typename T>
inline sdlxvulkan::Handle<T>::Handle(std::shared_ptr<Type> && a_ptr) :
  m_data{ std::move(a_ptr) }
{
}
template <typename T>
inline sdlxvulkan::Handle<T>::~Handle() = default;

template <typename T>
inline sdlxvulkan::Handle<T>::Handle(Handle const& a_other) = default;
template <typename T>
inline sdlxvulkan::Handle<T>& sdlxvulkan::Handle<T>::operator=(Handle const& a_other) = default;

template <typename T>
inline sdlxvulkan::Handle<T>::Handle(Handle && a_other) = default;
template <typename T>
inline sdlxvulkan::Handle<T>& sdlxvulkan::Handle<T>::operator=(Handle && a_other) = default;

// Interface
//============================================================
// Explcitly convert.
template <typename T>
inline typename sdlxvulkan::Handle<T>::Pointer sdlxvulkan::Handle<T>::get() const noexcept
{
  return m_data.get();
} 
/*
// Implicitly convert.
template <typename T>
inline typename sdlxvulkan::Handle<T>::operator Pointer() const noexcept
{
  return m_data.get();
}
*/

#endif // SDLXVULKAN_HANDLE_HPP