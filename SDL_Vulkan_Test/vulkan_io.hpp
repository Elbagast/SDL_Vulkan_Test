#ifndef SDLXVULKAN_VULKAN_IO_HPP
#define SDLXVULKAN_VULKAN_IO_HPP

#include <iosfwd>
#include <string>
#include <vulkan/vulkan.h>


std::ostream& flags_out(std::ostream& a_ostream, VkQueueFlags a_queue_flags);

std::ostream& operator<<(std::ostream& a_ostream, VkExtent3D const& a_extent);

std::ostream& operator<<(std::ostream& a_ostream, VkExtent2D const& a_ext);

std::ostream& operator<<(std::ostream& a_ostream, VkSurfaceCapabilitiesKHR const& a_sc);


char const* vkresult_c_string(VkResult a_value);

std::string vkresult_string(VkResult a_value);


#endif // SDLXVULKAN_VULKAN_IO_HPP