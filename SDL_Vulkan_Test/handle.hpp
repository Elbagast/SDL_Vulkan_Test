#ifndef SDLXVULKAN_HANDLE_HPP
#define SDLXVULKAN_HANDLE_HPP

#include <type_traits>
#include <memory>

namespace sdlxvulkan
{
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



  namespace internal
  {
    // When supplied with a Vulkan type, chop off the pointer
    template <typename T>
    class Vulkan_Handle_Helper
    {
    public:
      static_assert(std::is_pointer_v<T>, "Supplied Vulkan Type is not a pointer type, cannot use.");
      using Type = std::remove_pointer_t<T>;
      static_assert(std::is_same_v<T, std::add_pointer_t<Type>>, "Bad conversion reversal.");
    };
  }

  template <typename T>
  using Vulkan_Handle = Handle<typename internal::Vulkan_Handle_Helper<T>::Type>;

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