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

bool operator==(VkViewport const& a_lhs, VkViewport const& a_rhs) noexcept;
bool operator!=(VkViewport const& a_lhs, VkViewport const& a_rhs) noexcept;

bool operator==(VkRect2D const& a_lhs, VkRect2D const& a_rhs) noexcept;
bool operator!=(VkRect2D const& a_lhs, VkRect2D const& a_rhs) noexcept;

bool operator==(VkOffset2D const& a_lhs, VkOffset2D const& a_rhs) noexcept;
bool operator!=(VkOffset2D const& a_lhs, VkOffset2D const& a_rhs) noexcept;

bool operator==(VkOffset3D const& a_lhs, VkOffset3D const& a_rhs) noexcept;
bool operator!=(VkOffset3D const& a_lhs, VkOffset3D const& a_rhs) noexcept;

bool operator==(VkExtent2D const& a_lhs, VkExtent2D const& a_rhs) noexcept;
bool operator!=(VkExtent2D const& a_lhs, VkExtent2D const& a_rhs) noexcept;

#endif // SDLXVULKAN_VULKAN_IO_HPP