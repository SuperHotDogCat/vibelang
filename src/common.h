#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <map>
#include <memory>

namespace novus {

class Type;
using SubstitutionMap = std::map<std::string, std::shared_ptr<Type>>;

} // namespace novus

#endif
