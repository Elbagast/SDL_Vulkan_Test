#ifndef SDLXVULKAN_CUBE_DATA_HPP
#define SDLXVULKAN_CUBE_DATA_HPP

namespace sdlxvulkan
{
  //--------------------------------------------------------------------------------------
  // Mesh and VertexFormat Data
  //--------------------------------------------------------------------------------------
  struct Vertex 
  {
    float posX, posY, posZ, posW;  // Position data
    float r, g, b, a;              // Color
  };

  struct VertexUV 
  {
    float posX, posY, posZ, posW;  // Position data
    float u, v;                    // texture u,v
  };

#define XYZ1(_x_, _y_, _z_) (_x_), (_y_), (_z_), 1.f
#define UV(_u_, _v_) (_u_), (_v_)

  static Vertex const g_vertex_buffer_data[] =
  {
    { XYZ1(-1, -1, -1), XYZ1(0.f, 0.f, 0.f) },{ XYZ1(1, -1, -1), XYZ1(1.f, 0.f, 0.f) },{ XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },{ XYZ1(1, -1, -1), XYZ1(1.f, 0.f, 0.f) },{ XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },

    { XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },{ XYZ1(-1, 1, 1), XYZ1(0.f, 1.f, 1.f) },{ XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 1.f) },{ XYZ1(-1, 1, 1), XYZ1(0.f, 1.f, 1.f) },{ XYZ1(1, 1, 1), XYZ1(1.f, 1.f, 1.f) },

    { XYZ1(1, 1, 1), XYZ1(1.f, 1.f, 1.f) },{ XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },{ XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 1.f) },{ XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },{ XYZ1(1, -1, -1), XYZ1(1.f, 0.f, 0.f) },

    { XYZ1(-1, 1, 1), XYZ1(0.f, 1.f, 1.f) },{ XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },{ XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },{ XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },{ XYZ1(-1, -1, -1), XYZ1(0.f, 0.f, 0.f) },

    { XYZ1(1, 1, 1), XYZ1(1.f, 1.f, 1.f) },{ XYZ1(-1, 1, 1), XYZ1(0.f, 1.f, 1.f) },{ XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },
    { XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },{ XYZ1(-1, 1, 1), XYZ1(0.f, 1.f, 1.f) },{ XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },

    { XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 1.f) },{ XYZ1(1, -1, -1), XYZ1(1.f, 0.f, 0.f) },{ XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },
    { XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },{ XYZ1(1, -1, -1), XYZ1(1.f, 0.f, 0.f) },{ XYZ1(-1, -1, -1), XYZ1(0.f, 0.f, 0.f) },
  };

  static Vertex const g_vertex_buffer_solid_face_colors_data[] =
  {
    // red face
    { XYZ1(-1, -1, 1), XYZ1(1.f, 0.f, 0.f) },
    { XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 0.f) },
    { XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 0.f) },
    { XYZ1(1, -1, 1), XYZ1(1.f, 0.f, 0.f) },
    { XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 0.f) },
    { XYZ1(1, 1, 1), XYZ1(1.f, 0.f, 0.f) },
    // green face
    { XYZ1(-1, -1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(-1, 1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 0.f) },
    { XYZ1(1, 1, -1), XYZ1(0.f, 1.f, 0.f) },
    // blue face
    { XYZ1(-1, 1, 1), XYZ1(0.f, 0.f, 1.f) },
    { XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },
    { XYZ1(-1, 1, -1), XYZ1(0.f, 0.f, 1.f) },
    { XYZ1(-1, 1, -1), XYZ1(0.f, 0.f, 1.f) },
    { XYZ1(-1, -1, 1), XYZ1(0.f, 0.f, 1.f) },
    { XYZ1(-1, -1, -1), XYZ1(0.f, 0.f, 1.f) },
    // yellow face
    { XYZ1(1, 1, 1), XYZ1(1.f, 1.f, 0.f) },
    { XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },
    { XYZ1(1, -1, 1), XYZ1(1.f, 1.f, 0.f) },
    { XYZ1(1, -1, 1), XYZ1(1.f, 1.f, 0.f) },
    { XYZ1(1, 1, -1), XYZ1(1.f, 1.f, 0.f) },
    { XYZ1(1, -1, -1), XYZ1(1.f, 1.f, 0.f) },
    // magenta face
    { XYZ1(1, 1, 1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(1, 1, -1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(1, 1, -1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(-1, 1, 1), XYZ1(1.f, 0.f, 1.f) },
    { XYZ1(-1, 1, -1), XYZ1(1.f, 0.f, 1.f) },
    // cyan face
    { XYZ1(1, -1, 1), XYZ1(0.f, 1.f, 1.f) },
    { XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 1.f) },
    { XYZ1(-1, -1, 1), XYZ1(0.f, 1.f, 1.f) },
    { XYZ1(-1, -1, 1), XYZ1(0.f, 1.f, 1.f) },
    { XYZ1(1, -1, -1), XYZ1(0.f, 1.f, 1.f) },
    { XYZ1(-1, -1, -1), XYZ1(0.f, 1.f, 1.f) },
  };

  static VertexUV const g_vertex_buffer_texture_data[] = 
  {
    // left face
    { XYZ1(-1, -1, -1), UV(1.f, 0.f) },  // lft-top-front
    { XYZ1(-1, 1, 1), UV(0.f, 1.f) },    // lft-btm-back
    { XYZ1(-1, -1, 1), UV(0.f, 0.f) },   // lft-top-back
    { XYZ1(-1, 1, 1), UV(0.f, 1.f) },    // lft-btm-back
    { XYZ1(-1, -1, -1), UV(1.f, 0.f) },  // lft-top-front
    { XYZ1(-1, 1, -1), UV(1.f, 1.f) },   // lft-btm-front
                                         // front face
    { XYZ1(-1, -1, -1), UV(0.f, 0.f) },  // lft-top-front
    { XYZ1(1, -1, -1), UV(1.f, 0.f) },   // rgt-top-front
    { XYZ1(1, 1, -1), UV(1.f, 1.f) },    // rgt-btm-front
    { XYZ1(-1, -1, -1), UV(0.f, 0.f) },  // lft-top-front
    { XYZ1(1, 1, -1), UV(1.f, 1.f) },    // rgt-btm-front
    { XYZ1(-1, 1, -1), UV(0.f, 1.f) },   // lft-btm-front
                                         // top face
    { XYZ1(-1, -1, -1), UV(0.f, 1.f) },  // lft-top-front
    { XYZ1(1, -1, 1), UV(1.f, 0.f) },    // rgt-top-back
    { XYZ1(1, -1, -1), UV(1.f, 1.f) },   // rgt-top-front
    { XYZ1(-1, -1, -1), UV(0.f, 1.f) },  // lft-top-front
    { XYZ1(-1, -1, 1), UV(0.f, 0.f) },   // lft-top-back
    { XYZ1(1, -1, 1), UV(1.f, 0.f) },    // rgt-top-back
                                         // bottom face
    { XYZ1(-1, 1, -1), UV(0.f, 0.f) },  // lft-btm-front
    { XYZ1(1, 1, 1), UV(1.f, 1.f) },    // rgt-btm-back
    { XYZ1(-1, 1, 1), UV(0.f, 1.f) },   // lft-btm-back
    { XYZ1(-1, 1, -1), UV(0.f, 0.f) },  // lft-btm-front
    { XYZ1(1, 1, -1), UV(1.f, 0.f) },   // rgt-btm-front
    { XYZ1(1, 1, 1), UV(1.f, 1.f) },    // rgt-btm-back
                                        // right face
    { XYZ1(1, 1, -1), UV(0.f, 1.f) },   // rgt-btm-front
    { XYZ1(1, -1, 1), UV(1.f, 0.f) },   // rgt-top-back
    { XYZ1(1, 1, 1), UV(1.f, 1.f) },    // rgt-btm-back
    { XYZ1(1, -1, 1), UV(1.f, 0.f) },   // rgt-top-back
    { XYZ1(1, 1, -1), UV(0.f, 1.f) },   // rgt-btm-front
    { XYZ1(1, -1, -1), UV(0.f, 0.f) },  // rgt-top-front
                                        // back face
    { XYZ1(-1, 1, 1), UV(1.f, 1.f) },   // lft-btm-back
    { XYZ1(1, 1, 1), UV(0.f, 1.f) },    // rgt-btm-back
    { XYZ1(-1, -1, 1), UV(1.f, 0.f) },  // lft-top-back
    { XYZ1(-1, -1, 1), UV(1.f, 0.f) },  // lft-top-back
    { XYZ1(1, 1, 1), UV(0.f, 1.f) },    // rgt-btm-back
    { XYZ1(1, -1, 1), UV(0.f, 0.f) },   // rgt-top-back
  };
}

#endif // !SDLXVULKAN_CUBE_DATA_HPP
