#ifndef SDLXVULKAN_APP_FILES_HPP
#define SDLXVULKAN_APP_FILES_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace sdlxvulkan
{
  std::string get_dirpath(std::string const& a_arg0);

  std::string get_filepath(std::string const& a_arg0, std::string const& a_filename);

  //std::string get_shader_filepath(std::string const& a_arg0, std::string const& a_filename);

  std::vector<char> get_file_bytes(std::string const& a_filepath);

  class STB_Image
  {
  private:
    int m_width;
    int m_height;
    int m_channels;
    std::size_t m_size;
    unsigned char* m_data;
  public:
    explicit STB_Image(std::string const& a_filepath);
    ~STB_Image();

    int width() const noexcept          { return m_width; }
    int height() const noexcept         { return m_height; }
    int channels() const noexcept       { return m_channels; }
    std::size_t size() const noexcept   { return m_size; }
    unsigned char const* data() const noexcept   { return m_data; }
  };

  struct Vertex
  {
    glm::vec3 pos;
    glm::vec2 texCoord;
  };
  
  class Model
  {
  private:

  public:
    explicit Model(std::string const& a_filepath);
    ~Model();


  };

} // namespace sdlxvulkan

#endif // SDLXVULKAN_APP_FILES_HPP