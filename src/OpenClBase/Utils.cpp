#include "OpenClBase.hpp"

namespace CL {

cl_int
Utils::storeString(const std::string& str,
                   size_t param_value_size,
                   void* param_value,
                   size_t* param_value_size_ret)
{
  if (param_value && !param_value_size ||
      !param_value && !param_value_size_ret) {
    return CL_INVALID_VALUE;
  }

  if (param_value_size_ret) {
    *param_value_size_ret = str.size();
  }

  if (param_value && param_value_size >= str.size()) {
    if (memcpy_s(param_value, param_value_size, str.data(), str.size())) {
      return CL_INVALID_VALUE;
    }
    return CL_SUCCESS;
  }
  return CL_INVALID_VALUE;
}

}
