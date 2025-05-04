# 定义SRC_LIST变量，包含该目录下的所有文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

# 指定生成可执行文件
add_executable(Chatserver ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

# 正确链接库（使用 target_link_libraries）
target_link_libraries(Chatserver  muduo_net muduo_base mysqlclient hiredis pthread)