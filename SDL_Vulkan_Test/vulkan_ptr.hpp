#ifndef SDLXVULKAN_VULKAN_PTR_HPP
#define SDLXVULKAN_VULKAN_PTR_HPP

#include <type_traits>
#include <memory>

namespace sdlxvulkan
{
  namespace internal
  {
    //---------------------------------------------------------------------------
    // Vulkan_Handle_Typechecker<T>
    //---------------------------------------------------------------------------
    // When supplied with a Vulkan handle type, chop off the pointer, and make 
    // sure the conversion all works.

    template <typename T>
    class Vulkan_Handle_Typechecker
    {
    public:
      static_assert(std::is_pointer_v<T>, "Supplied Vulkan Type is not a pointer type, cannot use.");
      using Type = std::remove_pointer_t<T>;
      static_assert(std::is_same_v<T, std::add_pointer_t<Type>>, "Bad conversion reversal.");
    };

    template <typename T>
    using Vulkan_Handle_Typechecker_T = typename Vulkan_Handle_Typechecker<T>::Type;
  }
  
  // Helper for implemenation of smart Vulkan handles. Ties a type to a Destroyer
  // object that will hold the parent smart handle(s) and clean up the Vulkan
  // handle properly.
  template <typename T, typename Destroyer>
  using Vulkan_Uptr = std::unique_ptr<internal::Vulkan_Handle_Typechecker_T<T>, Destroyer>;

  // The pimpl data type for a given Vulkan handle. The Destroyer is present but
  // not publically available, allowing the smart handle to reveal what it wants.
  template <typename T>
  using Vulkan_Sptr = std::shared_ptr<internal::Vulkan_Handle_Typechecker_T<T>>;

  // Once we have a Vulkan handle, we need to bind it to a destroyer so that it
  // cleans up properly regardless of whether or not the shared_ptr creation
  // fails. To do this we put it in a unique_ptr first with a noexcept 
  // constructor. Then we try and make the shared_ptr.
  template <typename T, typename Destroyer, typename...Args>
  Vulkan_Sptr<T> make_except_vulkan_sptr(T a_vkhandle, Args&&... a_args)
  {
    Vulkan_Uptr<T,Destroyer> l_capture{ a_vkhandle, Destroyer{std::forward<Args>(a_args)...} };
    return Vulkan_Sptr<T>{std::move(l_capture)};
  }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // SDLXVULKAN_VULKAN_PTR_HPP