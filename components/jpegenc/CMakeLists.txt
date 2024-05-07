set(srcs 
    "src/JPEGENC.cpp"
    "src/jpeg.inl"
)
idf_component_register(SRCS ${srcs}      
                    REQUIRES "jpegenc"
                    INCLUDE_DIRS "src"
)
