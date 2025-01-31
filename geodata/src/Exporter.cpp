#include "pch.h"

#include <geodata/Exporter.h>

#include "L2JSerializer.h"

namespace geodata {

Exporter::Exporter(const std::filesystem::path &root_path)
    : m_root_path{root_path} {

  ASSERT(std::filesystem::exists(m_root_path), "Geodata",
         "Geodata output directory not exists: " << m_root_path);
}

void Exporter::export_l2j_geodata(const ExportBuffer &buffer,
                                  const std::string &name) const {

  const auto l2j_path = m_root_path / (name + ".l2j");
  std::ofstream output{l2j_path, std::ios::binary};

  L2JSerializer serializer;
  serializer.serialize(buffer, output);

  utils::Log(utils::LOG_INFO, "Geodata")
      << "Geodata exported: " << l2j_path << std::endl;
}

} // namespace geodata
