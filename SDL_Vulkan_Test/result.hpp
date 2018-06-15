#ifndef SDLXVULKAN_RESULT_HPP
#define SDLXVULKAN_RESULT_HPP

enum VkResult;

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // Result
  //---------------------------------------------------------------------------
  // Holds a VkResult and any type of data. Built to allow functions which 
  // simplify the call for count, call for data that happens a lot in Vulkan.

  template <typename T>
  struct Result
  {
    Result(VkResult a_result, T const& a_data) :
      result{ a_result },
      data{ a_data }
    {
    }
    Result(VkResult a_result, T && a_data) :
      result{ a_result },
      data{ std::move(a_data) }
    {
    }

    VkResult result;
    T data;
  };

}

#endif // SDLXVULKAN_RESULT_HPP