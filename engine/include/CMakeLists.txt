set(PROTON_ENGINE_ASSETS_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/assets/image.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/assets/model.h
        PARENT_SCOPE)

set(PROTON_ENGINE_COMPONENTS_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/components/camera.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/components/mesh_renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/components/proton_script.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/components/tag.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/components/transform.h
        PARENT_SCOPE)

set(PROTON_ENGINE_CORE_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/application.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/asset_manager.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/entity.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/entrypoint.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/key_codes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/key_state.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/core/scene.h
        PARENT_SCOPE)

set(PROTON_ENGINE_RENDERER_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/renderer/mesh.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/renderer/renderer.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/renderer/shader_program.h
        ${CMAKE_CURRENT_SOURCE_DIR}/protonengine/renderer/texture.h
        PARENT_SCOPE)