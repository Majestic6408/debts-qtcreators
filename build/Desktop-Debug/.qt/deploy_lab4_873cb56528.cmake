include("C:/qtprojects/lab4/build/Desktop-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/lab4-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE "C:/qtprojects/lab4/build/Desktop-Debug/lab4.exe"
    GENERATE_QT_CONF
)
