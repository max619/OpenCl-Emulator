#pragma once

namespace CL {

class Utils final
{
public:
  Utils() = delete;

  static cl_int storeString(const std::string& str,
                            size_t param_value_size,
                            void* param_value,
      size_t* param_value_size_ret);
};

}
