#include "pch.h"

#include <geodata/Map.h>

namespace geodata {

auto swap_y_with_z(const glm::vec3 &vector) -> glm::vec3 {
  return {vector.x, vector.z, vector.y};
}

auto swap_y_with_z(const geometry::Box &box) -> geometry::Box {
  return geometry::Box{swap_y_with_z(box.min()), swap_y_with_z(box.max())};
}

Map::Map(const std::string &name, const geometry::Box &bounding_box)
    : m_name{name}, m_bounding_box{swap_y_with_z(bounding_box)} {}

Map::Map(Map &&other) noexcept
    : m_name{std::move(other.m_name)}, m_bounding_box{std::move(
                                           other.m_bounding_box)},
      m_vertices{std::move(other.m_vertices)}, m_indices{std::move(
                                                   other.m_indices)} {}

void Map::add(const Entity &entity) {
  ASSERT(entity.mesh != nullptr, "Geodata", "Entity must have mesh");

  // Swap Y-up with Z-up
  static constexpr auto identity = glm::mat4{
      {1.0f, 0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 1.0f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f},
  };

  std::vector<glm::vec3> normals;

  for (const auto &instance_matrix : entity.mesh->instance_matrices) {
    const auto vertex_count = m_vertices.size();

    const auto model_matrix = identity * entity.model_matrix * instance_matrix;
    const auto normal_matrix = glm::inverseTranspose(glm::mat3{model_matrix});

    for (const auto &vertex : entity.mesh->vertices) {
      const auto transformed_vertex =
          model_matrix * glm::vec4{vertex.position, 1.0f};

      m_vertices.emplace_back(transformed_vertex);
      normals.emplace_back(glm::normalize(normal_matrix * vertex.normal));
    }

    for (std::size_t index = 0; index < entity.mesh->indices.size();
         index += 3) {

      const auto *indices = &entity.mesh->indices[index];
      const auto *vertices = &m_vertices[vertex_count];

      // Try to fix winding
      const auto average_normal = glm::normalize(
          (normals[indices[0]] + normals[indices[1]] + normals[indices[2]]) /
          3.0f);

      const auto face_normal = glm::triangleNormal(
          vertices[indices[2]], vertices[indices[1]], vertices[indices[0]]);

      if (glm::dot(average_normal, face_normal) >= 0.0f) {
        m_indices.push_back(vertex_count + indices[2]);
        m_indices.push_back(vertex_count + indices[1]);
        m_indices.push_back(vertex_count + indices[0]);
      } else {
        m_indices.push_back(vertex_count + indices[0]);
        m_indices.push_back(vertex_count + indices[1]);
        m_indices.push_back(vertex_count + indices[2]);
      }
    }
  }
}

auto Map::name() const -> const std::string & { return m_name; }

auto Map::bounding_box() const -> geometry::Box {
  return swap_y_with_z(m_bounding_box);
}

auto Map::internal_bounding_box() const -> const geometry::Box & {
  return m_bounding_box;
}

auto Map::vertices() const -> const std::vector<glm::vec3> & {
  return m_vertices;
}

auto Map::indices() const -> const std::vector<unsigned int> & {
  return m_indices;
}

} // namespace geodata
