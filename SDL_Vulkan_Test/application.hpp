#ifndef SDLXVULKAN_APPLICATION_HPP
#define SDLXVULKAN_APPLICATION_HPP

#include <memory>

namespace sdlxvulkan
{
  //---------------------------------------------------------------------------
  // Application
  //---------------------------------------------------------------------------
  // Manages the application.

  class Application
  {
  private:
    // Pimpl Data
    //============================================================
    class Implementation;

    std::unique_ptr<Implementation> m_implementation;

    Implementation* imp() noexcept              { return m_implementation.get(); }
    Implementation const* cimp() const noexcept { return m_implementation.get(); }
    
  public:
    // Special 6
    //============================================================
    Application(int argc, char** argv);
    ~Application();

    Application(Application const& a_other) = delete;
    Application& operator=(Application const& a_other) = delete;

    Application(Application && a_other) = delete;
    Application& operator=(Application && a_other) = delete;

    // Interface
    //============================================================
    int execute();
  };
}

#endif // SDLXVULKAN_APPLICATION_HPP