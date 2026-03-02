# ModelViews 子目录构建配置
add_library(ModelViews STATIC
    UserProfileWrapper.cpp
    GuWrapper.cpp
    UserPrizeWrapper.cpp
    EloRecordWrapper.cpp
    DailyCountWrapper.cpp
    UserWrapper.cpp
)

target_link_libraries(ModelViews PRIVATE Qt6::Core Qt6::Qml)
