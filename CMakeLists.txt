if(CONFIG_HAS_LAIRDCONNECTIVITY)
  zephyr_include_directories(.)

if(CONFIG_LAIRDCONNECTIVITY_UWG)
  zephyr_include_directories(Uwg)
  zephyr_include_directories(Uwg/include)
endif()

if(CONFIG_LAIRDCONNECTIVITY_MSC)
  zephyr_include_directories(Msc)
  zephyr_include_directories(Msc/include)
endif()

if(CONFIG_LAIRDCONNECTIVITY_BLR)
  zephyr_include_directories(Blr)
  zephyr_include_directories(Blr/include)
endif()

  zephyr_sources_ifdef(CONFIG_LAIRDCONNECTIVITY_MSC    Msc/src/MscCRC32.c)
  zephyr_sources_ifdef(CONFIG_LAIRDCONNECTIVITY_BLR    Blr/src/BlrPublic.c)
endif()
