file(REMOVE_RECURSE
  "generated-sources/include/xpp/proto/composite.hpp"
  "generated-sources/include/xpp/proto/randr.hpp"
  "generated-sources/include/xpp/proto/x.hpp"
  "generated-sources/include/xpp/proto/xkb.hpp"
  "libxpp.a"
  "libxpp.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/xpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
