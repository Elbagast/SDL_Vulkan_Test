#include "app_files.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cassert>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace
{
  decltype(auto) imp_get_dirpath(std::string const& a_arg0)
  {
    using namespace std::experimental::filesystem;
    return path{ u8path(a_arg0).remove_filename() };
  }
}

std::string sdlxvulkan::get_dirpath(std::string const& a_arg0)
{
  return imp_get_dirpath(a_arg0).u8string();
}

std::string sdlxvulkan::get_filepath(std::string const& a_arg0, std::string const& a_filename)
{
  using namespace std::experimental::filesystem;
  path l_directory = imp_get_dirpath(a_arg0);
  path l_filepath{ l_directory / u8path(a_filename) };

  std::string l_result{ l_filepath.u8string() };
  if (!exists(l_filepath))
  {
    throw std::runtime_error{ std::string{ "Filesystem: File does not exist: " } + l_result };
  }

  return l_result;
}
/*
std::string sdlxvulkan::get_shader_filepath(std::string const& a_arg0, std::string const& a_filename)
{
  using namespace std::experimental::filesystem;
  path const l_directory{ u8path(a_arg0).remove_filename() };
  path l_filepath{ l_directory / u8path(a_filename) };

  std::string l_result{ l_filepath.u8string() };

  if (!exists(l_filepath))
  {
    throw std::runtime_error{ std::string{ "Filesystem: Shader file does not exist: " } + l_result };
  }
  // Open the file and get the data...
  //std::cout << "Getting shader file: " << l_result << std::endl;

  return l_result;
};
*/
std::vector<char> sdlxvulkan::get_file_bytes(std::string const& a_filepath)
{
  // Open the file and seek to the end
  std::ifstream l_filestream{ a_filepath, std::ios::ate | std::ios::binary };
  if (!l_filestream.is_open())
  {
    throw std::runtime_error{ std::string{ "Filesystem: Could not open file " } +a_filepath };
  }

  // Get the file size in bytes
  std::size_t l_file_size = l_filestream.tellg();
  std::vector<char> l_file_buffer{};
  l_file_buffer.resize(l_file_size);

  // Go to the start
  l_filestream.seekg(0);

  // get all the file at once
  l_filestream.read(l_file_buffer.data(), l_file_size);

  l_filestream.close();

  return l_file_buffer;
}

namespace
{
  class STB_Pixel_Deleter
  {
  public:
    void operator()(stbi_uc* a_ptr) const noexcept
    {
      stbi_image_free(a_ptr);
    }
  };

  using STB_Pixels = std::unique_ptr<stbi_uc, STB_Pixel_Deleter>;
}

sdlxvulkan::STB_Image::STB_Image(std::string const& a_filepath) :
  m_width{0},
  m_height{0},
  m_channels{0},
  m_size{0},
  m_data{nullptr}
{
  m_data = stbi_load(a_filepath.c_str(), &m_width, &m_height, &m_channels, STBI_rgb_alpha);
  if (m_data == nullptr)
  {
    throw std::runtime_error{ std::string{"STB: failed to load an image file: "} + a_filepath };
  }
  assert(m_width != 0);
  assert(m_height != 0);
  //assert(m_channels == STBI_rgb_alpha);
// catch the pointer with its deleter function
  //std::unique_ptr<stbi_uc, std::add_pointer_t<decltype(stbi_image_free)>> l_caught{ l_pixels, stbi_image_free };
  //STB_Pixels l_caught{ l_pixels };

  m_size = m_width * m_height * 4;

  std::cout << "image made: " << a_filepath << " w=" << m_width << " h=" << m_height << " c=" << m_channels << " s=" << m_size << std::endl;


  /*
  // this copy op is damn slow
  m_data.reserve(l_size);
  for (std::size_t l_index = 0; l_index != l_size; ++l_index, ++l_pixels)
  {
    m_data.push_back(static_cast<char>(*l_pixels));
  }
  assert(m_data.size() == l_size);*/
  //stbi_image_free(l_pixels);
}

sdlxvulkan::STB_Image::~STB_Image()
{
  stbi_image_free(m_data);
}
