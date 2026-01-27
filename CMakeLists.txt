idf_component_register(SRCS "chien.c"
                    INCLUDE_DIRS "."
                    REQUIRES rc522
                    REQUIRES freertos log
   )
